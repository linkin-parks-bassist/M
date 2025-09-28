#include <Arduino.h>
#include "M.h"

static const int pot_pins[4] = {14, 17, 22, 16};
static const int switch_pins[3] = {4, 5, 9};

static const float pot_affine_coef[3] = {7.0/1023.0, -1.0/1023.0, -1.0/1023.0};
static const float pot_affine_offs[3] = {-0.18,  1.0, 1.0};

int thread_id;

float   pots[N_POTS];
int switches[N_SWITCHES];
int switch_changed[N_SWITCHES];

float pot_value(m_hw_ctrl_context *cxt, int pot)
{
	#ifdef ENABLE_POTS
	if (pot < 0 || pot > N_POTS || !cxt)
		return 0;
	
	return (pot_affine_coef[pot] * (float)analogRead(cxt->pot_pins[pot])) + pot_affine_offs[pot];
	#else
	return 0.0;
	#endif
}

int init_hardware_controls(m_hw_ctrl_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	#ifdef ENABLE_POTS
	for (int i = 0; i < N_POTS; i++)
	{
		cxt->pot_pins[i] = pot_pins[i];
		pinMode(cxt->pot_pins[i], INPUT);
		cxt->pots[i] = pot_value(cxt, i);
		delayMicroseconds(10);
	}
	#endif
	
	for (int i = 0; i < N_SWITCHES; i++)
	{
		cxt->switch_pins[i] = switch_pins[i];
		pinMode(cxt->switch_pins[i], INPUT_PULLUP);
		cxt->switch_states[i] = digitalRead(cxt->switch_pins[i]);
		cxt->switch_changed[i] = 0;
	}
	
	#ifdef ENABLE_POTS
	for (int i = 0; i < N_POTS; i++)
	{
		cxt->pot_links[i].active = 0;
		cxt->pot_links[i].pot = i;
		cxt->pot_links[i].param = 0;
		cxt->pot_links[i].min = 0.0;
		cxt->pot_links[i].max = 10.0;
	}
	#endif
	
	for (int i = 0; i < N_SWITCHES; i++)
	{
		cxt->switch_links[i].active = 0;
		cxt->switch_links[i].pipeline = NULL;
		cxt->switch_links[i].transformer = NULL;
	}
	
	return NO_ERROR;
}

int poll_hardware_controls(m_hw_ctrl_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	#ifdef ENABLE_POTS
	analogRead(cxt->pot_pins[0]);
	delayMicroseconds(10);
	
	for (int i = 0; i < N_POTS; i++)
	{
		analogRead(cxt->pot_pins[i]);
		delayMicroseconds(10);
		cxt->pots[i] = pot_value(cxt, i);
	}
	#endif
	
	int new_val;
	for (int i = 0; i < N_SWITCHES; i++)
	{
		new_val 				 = digitalRead(cxt->switch_pins[i]);
		cxt->switch_changed[i]  |= new_val != cxt->switch_states[i];
		cxt->switch_states[i] 	 = new_val;
	}
	
	#ifdef PRINT_HW_CTRL_DATA
	
	#ifdef ENABLE_POTS
	m_printf("Pots: (");
	for (int i = 0; i < N_POTS; i++)
	{
		m_printf("%6f", cxt->pots[i]);
		if (i < N_POTS - 1)
			m_printf(", ");
	}
	m_printf("), ");
	#endif
	
	m_printf("Switches: (");
	for (int i = 0; i < N_SWITCHES; i++)
	{
		m_printf("%d", cxt->switch_states[i]);
		if (i < N_SWITCHES - 1)
			m_printf(", ");
	}
	m_printf(")\n");
	
	#endif
	
	return NO_ERROR;
}

#define POT_NOISE_THRESHOLD 0.05

int execute_hw_ctrl_links(m_hw_ctrl_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	int ret_val = NO_ERROR;
	
	#ifdef ENABLE_POTS
	float new_val;
	
	for (int i = 0; i < N_POTS; i++)
	{
		if (cxt->pot_links[i].active)
		{
			// If the pot link is active but has NULL parameter pointer
			// Report a malformed pot link, and place its index in the
			// final byte of the returned value word
			// This error code may be overwritten in the case of multiple
			// malformed links but whatevs
			if (!cxt->pot_links[i].param)
			{
				ret_val = ERR_POT_LINK_MALFORMED | i << 24;
				continue;
			}
			new_val = (cxt->pot_links[i].min + (cxt->pot_links[i].max - cxt->pot_links[i].min) * cxt->pots[i]);
			
			if (fabs(cxt->pot_links[i].max - cxt->pot_links[i].min) > 1e-30)
			{
				// Only bother changing the value in the case that it has changed by a significant amount
				// (say, 5 percent), to avoid triggering lots of recalculations caused by noise
				if (fabs(new_val - cxt->pot_links[i].param->value) / fabs(cxt->pot_links[i].max) > POT_NOISE_THRESHOLD)
				{
					cxt->pot_links[i].param->value = new_val;
					cxt->pot_links[i].param->updated = 1;
				}
				else
				{
					cxt->pot_links[i].param->updated = 0;
				}
			}
			else
			{
				if (fabs(cxt->pot_links[i].param->value - cxt->pot_links[i].min) > 1e-30)
				{
					cxt->pot_links[i].param->value = cxt->pot_links[i].min;
					cxt->pot_links[i].param->updated = 1;
				}
			}
		}
	}
	#endif
	
	for (int i = 0; i < N_SWITCHES; i++)
	{
		if (cxt->switch_changed[i] && cxt->switch_links[i].active)
		{
			switch (cxt->switch_links[i].type)
			{
				case SWITCH_PIPELINE:
					if (cxt->switch_links[i].pipeline)
					{
						switch_active_pipeline(cxt->switch_links[i].pipeline);
					}
					else
					{
						ret_val = ERR_SWITCH_LINK_MALFORMED | i << 24;
					}
					break;
				
				case SWITCH_BYPASS_TRANSFORMER:
					if (cxt->switch_links[i].transformer)
					{
						cxt->switch_links[i].transformer->bypass = !cxt->switch_links[i].transformer->bypass;
					}
					else
					{
						ret_val = ERR_SWITCH_LINK_MALFORMED | i << 24;
					}
					break;
				
				default:
					ret_val = ERR_SWITCH_LINK_MALFORMED | i << 24;
					break;
			}
		}
		
		cxt->switch_changed[i] = 0;
	}
	
	return ret_val;
}

int link_pot_to_parameter(m_hw_ctrl_context *cxt, int pot_n, m_parameter *param, float min_value, float max_value)
{
	#ifdef ENABLE_POTS
	if (!cxt)
		return ERR_NULL_PTR;
	
	if (!(0 <= pot_n && pot_n < N_POTS))
		return ERR_BAD_ARGS;
	
	cxt->pot_links[pot_n].active = 1;
	cxt->pot_links[pot_n].param	 = param;
	cxt->pot_links[pot_n].min 	 = min_value;
	cxt->pot_links[pot_n].max 	 = max_value;
	
	return NO_ERROR;
	#else
	return NO_ERROR;
	#endif
}

int link_switch_to_pipeline(m_hw_ctrl_context *cxt, int switch_n, m_pipeline *pipeline)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	if (!(0 <= switch_n && switch_n < N_SWITCHES))
		return ERR_BAD_ARGS;
	
	cxt->switch_links[switch_n].active 	 	= 1;
	cxt->switch_links[switch_n].type 	 	= SWITCH_PIPELINE;
	cxt->switch_links[switch_n].pipeline 	= pipeline;
	cxt->switch_links[switch_n].transformer = NULL;
	
	return NO_ERROR;
}

int link_switch_to_bypass_transformer(m_hw_ctrl_context *cxt, int switch_n, m_audio_transformer *transformer)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	if (!(0 <= switch_n && switch_n < N_SWITCHES))
		return ERR_BAD_ARGS;
	
	cxt->switch_links[switch_n].active 	 	= 1;
	cxt->switch_links[switch_n].type 	 	= SWITCH_BYPASS_TRANSFORMER;
	cxt->switch_links[switch_n].pipeline 	= NULL;
	cxt->switch_links[switch_n].transformer = transformer;
	
	return NO_ERROR;
}

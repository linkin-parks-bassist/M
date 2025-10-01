#include "M.h"

m_pipeline *new_pipeline = NULL;

#define NOISE_DELTA 0.999

float avg_noise[AUDIO_BLOCK_SAMPLES];
int noise_counter = 0;

int pipeline_switch_scheduled = 0;

void set_active_pipeline(m_pipeline *pipeline)
{
	global_cxt.active_pipeline = pipeline;
	//m_printf("Obtained new active pipeline, 0x%x.\n", global_cxt.active_pipeline);
}

int switch_active_pipeline(m_pipeline *pipeline)
{
	if (!pipeline)
		return ERR_NULL_PTR;
	
	if (pipeline == new_pipeline)
		return NO_ERROR;
	
	m_printf("pipeline switch scheduled\n");
	
	new_pipeline = pipeline;
	pipeline_switch_scheduled = 1;
	
	return NO_ERROR;
}

void update_all()
{
	NVIC_SET_PENDING(IRQ_SOFTWARE);
}

bool update_setup()
{
	if (update_scheduled)
		return false;
	
	attachInterruptVector(IRQ_SOFTWARE, m_software_isr);
	NVIC_SET_PRIORITY(IRQ_SOFTWARE, 208); // 255 = lowest priority
	NVIC_ENABLE_IRQ(IRQ_SOFTWARE);
	
	update_scheduled = true;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		avg_noise[i] = 0.0;
	return true;
}

void update_stop()
{
	NVIC_DISABLE_IRQ(IRQ_SOFTWARE);
	update_scheduled = false;
}

int update_avg_noise(int16_t *block)
{
	int   silence = 0;
	float energy  = 0.0;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		energy += block[i] * block[i];
	
	energy = sqrt(energy);
	
	if (energy < 2000)
	{
		if (noise_counter > 64)
		{
			for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
				avg_noise[i] = NOISE_DELTA * avg_noise[i] + (1.0 - NOISE_DELTA) * block[i];
			
			silence = 1;
		}
		else
		{
			noise_counter++;
		}
	}
	else
	{
		noise_counter = 0;
	}
	
	return silence;
}

float smoothed_transition_function(float ratio, float power)
{
	if (ratio > 1.0)
		return 1.0;
	else if (ratio < 0.0)
		return 0.0;
	else if (ratio < 0.5)
		return pow(2.0, power - 1.0) * pow(ratio, power);
	else
		return 1.0 - pow(2.0, power - 1.0) * pow(1.0 - ratio, power);
}

#define PIPELINE_SWITCH_SAMPLES 256
int switch_progress;
int switch_in_progress = 0;

#define AVG_DURATION_UPDATE_COEF 0.99f
//#define PRINT_TIMES

void m_software_isr()
{
	static uint32_t last_runtime = micros();
	
	static float avg_roundtrip_duration_micros 	= 0.0;
	static float avg_compute_duration_micros 	= 0.0;
	
	uint32_t start_time = micros();
	
	int ret_val;
	static int runs = 0;
	i2s_input_update();
	
	int16_t block[AUDIO_BLOCK_SAMPLES];
	
	update_avg_noise(i2s_input_blocks[1].data);
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		block[i] = i2s_input_blocks[1].data[i] - (int16_t)avg_noise[i];
	
	//pretty_print_block(block, "Input: \n");
	
	if (!global_cxt.active_pipeline)
	{
		i2s_output_transmit_mono_int(block);
	}
	else
	{
		if (pipeline_switch_scheduled)
		{
			if (new_pipeline)
			{
				if (global_cxt.active_pipeline)
				{
					switch_in_progress 	= 1;
					switch_progress 	= 0;
				}
				else
				{
					set_active_pipeline(new_pipeline);
				}
			}
			
			pipeline_switch_scheduled = 0;
		}
		
		if (switch_in_progress)
		{
			//m_printf("Switch in progress...\n");
			float out_buffer[AUDIO_BLOCK_SAMPLES];
			float *out1, *out2;
			float ratio, coef;
			
			//m_printf("Compute pipelines...\n");
			compute_pipeline(global_cxt.active_pipeline, block);
			compute_pipeline(new_pipeline,	block);
			
			out1 = global_cxt.active_pipeline->output_node.block->data;
			out2 = new_pipeline->output_node.block->data;
			
			//m_printf("outputs: 0x%x, 0x%x\n", out1, out2);
			//m_printf("interpolate outputs...\n");
			for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
			{
				ratio = (float)switch_progress / (float)PIPELINE_SWITCH_SAMPLES;
				
				coef = smoothed_transition_function(ratio, 3);
				//m_printf("ratio = %6f, coef = %6f\n", ratio, coef);
				
				out_buffer[i] = (1.0 - coef) * out1[i] + coef * out2[i];
				
				switch_progress++;
			}
			
			//m_printf("transmit output...\n");
			i2s_output_transmit_mono_float(out_buffer);
			
			if (switch_progress >= PIPELINE_SWITCH_SAMPLES)
			{
				//m_printf("transition complete\n");
				global_cxt.active_pipeline = new_pipeline;
				new_pipeline 	= NULL;
				
				switch_in_progress = 0;
			}
		}
		else
		{
			ret_val = compute_pipeline(global_cxt.active_pipeline, block);
			
			if (ret_val == ERR_PIPELINE_BUSTED)
			{
				if (global_cxt.active_pipeline->err_flags & PIPELINE_ERR_FLAG_UNCONFIGURED)
					global_cxt.unconfigured_pipeline = global_cxt.active_pipeline;
			}
			#ifdef PRINT_BLOCKS
			serial_print_blocks(2, global_cxt.active_pipeline->input_node.block->data,  global_cxt.active_pipeline->output_node.block->data);
			#endif
			i2s_output_transmit_mono_float(global_cxt.active_pipeline->output_node.block->data);
		}
	}
	
	avg_roundtrip_duration_micros = avg_roundtrip_duration_micros * AVG_DURATION_UPDATE_COEF + (start_time - last_runtime) * (1.0 - AVG_DURATION_UPDATE_COEF);
	last_runtime = start_time;
	
	avg_compute_duration_micros = avg_compute_duration_micros * AVG_DURATION_UPDATE_COEF + ((float)(micros() - start_time)) * (1.0 - AVG_DURATION_UPDATE_COEF);
	
	i2s_output_update();
	
	runs++;
	
	#ifdef PRINT_TIMES
	if (runs % 256 == 0)
		m_printf("average compute duration: %6fms. average round-trip duration: %6fms. Compute takes %03f%% of round-trip\n",
			avg_compute_duration_micros * 0.001, avg_roundtrip_duration_micros * 0.001,
			(avg_roundtrip_duration_micros == 0.0) ? 0 : 100.0 * (avg_compute_duration_micros/avg_roundtrip_duration_micros));
	#endif

	asm("DSB");
}

#include "M.h"

int init_transformer(m_audio_transformer *trans, int type,
					 unsigned int n_inputs,  unsigned int n_outputs,
					 vec2i 		   *inputs,  vec2i 		  *outputs,
					 int n_parameters,
					 void *transformer_data,
					 int (*compute_transformer)(float **dest, float **src, void *transformer_data))
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->type = type;
	
	trans->bypass = 0;
	
	trans->n_inputs  = n_inputs;
	trans->n_outputs = n_outputs;
	
	if (inputs)
	{
		for (unsigned int i = 0; i < n_inputs && i < MAX_TRANSFORMER_INPUTS; i++)
			trans->inputs[i] = inputs[i];
		
		for (unsigned int i = 0; i < n_outputs && i < MAX_TRANSFORMER_OUTPUTS; i++)
			trans->outputs[i] = outputs[i];
	}
	
	trans->transformer_data 	= transformer_data;
	trans->compute_transformer 	= compute_transformer;
	
	trans->n_parameters = 0;
	trans->parameters 	= (n_parameters) ? (m_parameter**)malloc(sizeof(m_parameter*) * n_parameters) : NULL;
	
	return NO_ERROR;
}

void run_bypass(float **dest, float **src, int n_inputs, int n_valid_inputs, int n_outputs)
{
	float tmp;
		
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		tmp = 0.0;
		for (int j = 0; j < n_inputs; j++)
			if (src[j]) tmp += src[j][i] / n_valid_inputs;
		
		for (int j = 0; j < n_outputs; j++)
			if (dest[j]) dest[j][i] = tmp;
	}
}

int propagate_transformer(m_pipeline *pipeline, m_audio_transformer *trans)
{
	if (!pipeline || !trans)
		return ERR_NULL_PTR;
		
	m_pipeline_node *inputs [MAX_TRANSFORMER_INPUTS ];
	m_pipeline_node *outputs[MAX_TRANSFORMER_OUTPUTS];
	
	float  *src[MAX_TRANSFORMER_INPUTS];
	float *dest[MAX_TRANSFORMER_INPUTS];
	
	unsigned int i;
	int n_valid_inputs = 0;
	
	for (i = 0; i < trans->n_inputs; i++)
	{
		inputs[i] = pipeline_get_node(pipeline, trans->inputs[i]);
		
		if (inputs[i] && inputs[i]->active && inputs[i]->block)
		{
			src[i] = inputs[i]->block->data;
			n_valid_inputs++;
		}
		else
		{
			src[i] = NULL;
		}
	}
	
	while (i < MAX_TRANSFORMER_INPUTS)
	{
		src[i] 			= NULL;
		inputs[i] 		= NULL;
		i++;
	}
	
	#ifdef PRINT_TRANSFORMER_INFO
	for (i = 0; i < MAX_TRANSFORMER_INPUTS; i++)
		m_printf("Input %d: coordinates (%d, %d). Buffer pointer: 0x%08x\n", i, trans->inputs[i].x, trans->inputs[i].y, src[i]);
	#endif
	
	int n_valid_outputs = 0;
	int calc = 1;
	
	for (i = 0; i < trans->n_outputs; i++)
	{
		outputs[i] = pipeline_get_node(pipeline, trans->outputs[i]);
		
		if (outputs[i] && outputs[i]->block)
		{
			dest[i] = outputs[i]->block->data;
			n_valid_outputs++;
		}
		else
		{
			dest[i] = NULL;
		}
	}
	
	while (i < MAX_TRANSFORMER_OUTPUTS)
	{
		dest[i] 		= NULL;
		outputs[i] 		= NULL;
		i++;
	}
	
	#ifdef PRINT_TRANSFORMER_INFO
	for (i = 0; i < MAX_TRANSFORMER_INPUTS; i++)
		m_printf("Output %d: coordinates (%d, %d). Buffer pointer: 0x%08x\n", i, trans->outputs[i].x, trans->outputs[i].y, dest[i]);
	#endif
	
	int ret_val = NO_ERROR;
	
	if (!trans->compute_transformer)
	{
		ret_val = ERR_TRANSFORMER_MALFORMED;
		calc = 0;
	}
	
	if (trans->bypass)
		calc = 0;
	
	if (calc)
		ret_val = trans->compute_transformer(dest, src, trans->transformer_data);
	
	if (!calc || ret_val != NO_ERROR)
		run_bypass(dest, src, trans->n_inputs, n_valid_inputs, trans->n_outputs);
	
	#ifdef PRINT_TRANSFORMER_INFO
	m_printf("Transformer type: ");
	switch (trans->type)
	{
		case TRANSFORMER_BUFFER:
			m_printf("buffer.\n");
			break;
			
		case TRANSFORMER_AMPLIFIER:
			m_printf("amplifier.\n");
			break;
		
		case TRANSFORMER_MIXER:
			m_printf("mixer.\n");
			break;
		
		case TRANSFORMER_BIQUAD:
			m_printf("biquad.\n");
			break;
		
		case TRANSFORMER_DISTORTION:
			m_printf("arctan distortion.\n");
			break;
		
		case TRANSFORMER_WAVESHAPER:
			m_printf("compression.\n");
			break;
		
		case TRANSFORMER_COMPRESSOR:
			m_printf("compression.\n");
			break;
		
		default:
			m_printf("unknown !\n");
			return ERR_TRANSFORMER_MALFORMED;
	}
	
	for (int i = 0; i < trans->n_parameters; i++)
	{
		if (trans->parameters[i])
		{
			m_printf("%s = %6f,\n", trans->parameters[i]->name, trans->parameters[i]->value);
		}
	}
	
	if (ret_val == NO_ERROR)
		m_printf("Computed sucessfully\n");
	else
		m_printf("Error %d\n", ret_val);
	
	float amp_abs_max = 0.0;
	
	m_printf("Bypass: %d. Function pointer: 0x%x.\n", trans->bypass, trans->compute_transformer);
	
	for (int i = 0; i < MAX_TRANSFORMER_OUTPUTS; i++)
	{
		if (!dest[i])
			continue;
		
		for (int j = 0; j < AUDIO_BLOCK_SAMPLES; j++)
		{
			if (fabs(dest[i][j]) > amp_abs_max)
				amp_abs_max = fabs(dest[i][j]);
		}
		
		m_printf("Output %d peak amplitude: %4f\n", i, amp_abs_max);
	}
	#endif
	
	return ret_val;
}

int transformer_add_parameter(m_audio_transformer *trans, m_parameter *param)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	if (!param)
		return ERR_BAD_ARGS;
	
	trans->parameters[trans->n_parameters] = param;
	trans->n_parameters++;
	
	return NO_ERROR;
}

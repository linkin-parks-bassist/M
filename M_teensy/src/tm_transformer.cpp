#include "tm.h"

int init_transformer_default(tm_audio_transformer *trans, uint16_t type)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->bypass = 0;
	trans->runs = 0;
	
	for (int i = 0; i < TRANSFORMER_MAX_INPUTS; i++)
		trans->inputs[i] = DISCONNECTED;
	
	for (int i = 0; i < TRANSFORMER_MAX_OUTPUTS; i++)
		trans->outputs[i] = DISCONNECTED;
	
	int ret_val;
	
	switch (type)
	{
		case TRANSFORMER_BUFFER: 		ret_val = init_buffer_default	 (trans); 	break;
		case TRANSFORMER_MIXER: 		ret_val = init_mixer_default	 (trans); 	break;
		case TRANSFORMER_AMPLIFIER: 	ret_val = init_amp_default		 (trans); 	break;
		case TRANSFORMER_BIQUAD: 		ret_val = init_biquad_default	 (trans); 	break;
		case TRANSFORMER_WAVESHAPER: 	ret_val = init_waveshaper_default(trans); 	break;
		case TRANSFORMER_DISTORTION: 	ret_val = init_distortion_default(trans); 	break;
		case TRANSFORMER_COMPRESSOR: 	ret_val = init_compressor_default(trans); 	break;
		
		default: ret_val = ERR_BAD_ARGS; break;
	}
	
	if (ret_val != NO_ERROR)
	{
		if (trans->transformer_data);
			free(trans->transformer_data);
	}
	
	return ret_val;
}

int init_transformer(tm_audio_transformer *trans, int type,
					 unsigned int n_inputs,  unsigned int n_outputs,
					 vec2i 		   *inputs,  vec2i 		  *outputs,
					 int n_parameters,
					 void *transformer_data,
					 int (*compute_transformer)(float **dest, float **src, void *transformer_data))
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->type 	= type;
	trans->bypass 	= 0;
	trans->runs 	= 0;
	
	trans->n_inputs  = (n_inputs  < TRANSFORMER_MAX_INPUTS)  ? n_inputs  : TRANSFORMER_MAX_INPUTS;
	trans->n_outputs = (n_outputs < TRANSFORMER_MAX_OUTPUTS) ? n_outputs : TRANSFORMER_MAX_OUTPUTS;
	
	unsigned int i;
	if (inputs)
	{
		for (i = 0; i < n_inputs; i++)
			trans->inputs[i] = inputs ? inputs[i] : DISCONNECTED;
		
		for (; i < TRANSFORMER_MAX_INPUTS; i++)
			trans->inputs[i] = DISCONNECTED;
	}
	
	if (outputs)
	{
		for (i = 0; i < n_outputs; i++)
			trans->outputs[i] = outputs ? outputs[i] : DISCONNECTED;
		
		for (; i < TRANSFORMER_MAX_OUTPUTS; i++)
			trans->outputs[i] = DISCONNECTED;
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

int propagate_transformer(tm_pipeline *pipeline, tm_audio_transformer *trans)
{
	if (!pipeline || !trans)
		return ERR_NULL_PTR;
	
	trans->runs++;
	
	tm_pipeline_node *inputs [TRANSFORMER_MAX_INPUTS ];
	tm_pipeline_node *outputs[TRANSFORMER_MAX_OUTPUTS];
	
	float  *src[TRANSFORMER_MAX_INPUTS];
	float *dest[TRANSFORMER_MAX_INPUTS];
	
	unsigned int i;
	int n_valid_inputs = 0;
	
	for (i = 0; i < trans->n_inputs; i++)
	{
		inputs[i] = pipeline_get_node(pipeline, trans->inputs[i]);
		
		if (inputs[i] && inputs[i]->block)
		{
			src[i] = inputs[i]->block->data;
			n_valid_inputs++;
		}
		else
		{
			src[i] = NULL;
		}
	}
	
	while (i < TRANSFORMER_MAX_INPUTS)
	{
		src[i] 			= NULL;
		inputs[i] 		= NULL;
		i++;
	}
	
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
	
	while (i < TRANSFORMER_MAX_OUTPUTS)
	{
		dest[i] 		= NULL;
		outputs[i] 		= NULL;
		i++;
	}
	
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
	if (trans->runs % 256 == 0)
	{
		
		
		if (ret_val == NO_ERROR)
			tm_printf("Computed sucessfully\n");
		else
			tm_printf("Error %d\n", ret_val);
		
		float amp_abs_max = 0.0;
		
		tm_printf("Bypass: %d. Function pointer: 0x%x.\n", trans->bypass, trans->compute_transformer);
		
		for (int i = 0; i < TRANSFORMER_MAX_OUTPUTS; i++)
		{
			if (!dest[i])
				continue;
			
			for (int j = 0; j < AUDIO_BLOCK_SAMPLES; j++)
			{
				if (fabs(dest[i][j]) > amp_abs_max)
					amp_abs_max = fabs(dest[i][j]);
			}
			
			tm_printf("Output %d peak amplitude: %4f\n", i, amp_abs_max);
		}
	}
	#endif
	
	return ret_val;
}

int transformer_add_parameter(tm_audio_transformer *trans, m_parameter *param)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	if (!param)
		return ERR_BAD_ARGS;
	
	trans->parameters[trans->n_parameters] = param;
	trans->n_parameters++;
	
	return NO_ERROR;
}

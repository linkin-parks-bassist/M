#include "tm.h"

int init_transformer(tm_transformer *trans, int type,
					 unsigned int n_inputs,  unsigned int n_outputs,
					 vec2i 		   *inputs,  vec2i 		  *outputs,
					 int n_options, int n_parameters,
					 void *data_struct,
					 int (*compute_transformer)(float **dest, float **src, void *data_struct))
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
	
	trans->data_struct 	= data_struct;
	trans->compute_transformer 	= compute_transformer;
	
	trans->n_options = 0;
	trans->option_array_size = n_options;
	trans->options 	 = (n_options) ? (tm_option**)malloc(sizeof(tm_option*) * n_options) : NULL;
	
	for (int i = 0; i < n_options; i++)
		trans->options[i] = NULL;
	
	
	
	return NO_ERROR;
}

int transformer_init_parameter_array(tm_transformer *trans, int n)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	if (n == 0)
	{
		trans->n_parameters = 0;
		trans->parameter_array_size = 0;
		trans->parameters = NULL;
		return NO_ERROR;
	}
	
	trans->n_parameters = 0;
	trans->parameter_array_size = n;
	trans->parameters 	= (n) ? (tm_parameter**)malloc(sizeof(tm_parameter*) * n) : NULL;
	
	if (!trans->parameters)
		return ERR_ALLOC_FAIL;
	
	for (int i = 0; i < n; i++)
		trans->parameters[i] = NULL;
	
	return NO_ERROR;
}

int transformer_init_n_options(tm_transformer *trans, int n)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->n_options = 0;
	trans->option_array_size = n;
	trans->options 	= (n) ? (tm_option**)malloc(sizeof(tm_option*) * n) : NULL;
	
	if (!trans->options)
		return ERR_ALLOC_FAIL;
	
	for (int i = 0; i < n; i++)
		trans->options[i] = NULL;
	
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

int propagate_transformer(tm_pipeline *pipeline, tm_transformer *trans)
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
		ret_val = trans->compute_transformer(dest, src, trans->data_struct);
	
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

int transformer_add_option(tm_transformer *trans, tm_option *option)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	if (!option)
		return ERR_BAD_ARGS;
	
	if (trans->n_options == trans->option_array_size)
		return ERR_BAD_ARGS;
	
	trans->options[trans->n_options] = option;
	trans->n_options++;
	
	return NO_ERROR;
}

int transformer_add_parameter(tm_transformer *trans, tm_parameter *param)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	if (!param)
		return ERR_BAD_ARGS;
	
	if (trans->n_parameters == trans->parameter_array_size)
		return ERR_BAD_ARGS;
	
	trans->parameters[trans->n_parameters] = param;
	trans->n_parameters++;
	
	return NO_ERROR;
}

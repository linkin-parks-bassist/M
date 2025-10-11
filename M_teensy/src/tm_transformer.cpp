#include "tm.h"

int init_transformer(tm_transformer *trans, int type,
					 unsigned int n_inputs,  unsigned int n_outputs,
					 vec2i 		   *inputs,  vec2i 		  *outputs,
					 int n_options, int n_parameters,
					 void *data_struct,
					 int (*compute_transformer)(void *data_struct, float **dest, float **src, int n_samples))
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

#define MAX_BLOCK_DIVIDER 8

static int rectify_block_divider(int divider)
{
	int i = 1;
	
	do {
		if (divider < i)
			return i;
		
		i = 2 * i;
	} while (i <= MAX_BLOCK_DIVIDER);
	
	return MAX_BLOCK_DIVIDER;
}


int run_transformer(tm_transformer *trans, float **dest, float **src)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int divider = 1;
	int local_divider;
	int any_updates = 0;
	int n_samples;
	
	int long_update[trans->n_parameters];
	float deltas[trans->n_parameters];
	
	float *inputs[TRANSFORMER_MAX_INPUTS];
	float *outputs[TRANSFORMER_MAX_OUTPUTS];
	
	for (int i = 0; i < TRANSFORMER_MAX_INPUTS; i++)
		inputs [i] = src  ? src [i] : NULL;
	
	for (int i = 0; i < TRANSFORMER_MAX_OUTPUTS; i++)
		outputs[i] = dest ? dest[i] : NULL;
	
	for (int i = 0; i < trans->n_parameters; i++)
		long_update[i] = 0;
	
	// Calculate delts for all updated parameters
	// and determine how much to divide the block
	for (int i = 0; i < trans->n_parameters && i < trans->parameter_array_size; i++)
	{
		deltas[i] = 0.0;
		if (!trans->parameters[i])
		{
			tm_printf("Transformer %p has NULL parameter at index %d\n", trans, i);
			continue;
		}
		
		if (!trans->parameters[i]->updated)
			continue;
		
		any_updates = 1;
		
		// If a negative max_jump has snuck in, rectify this
		if (trans->parameters[i]->max_jump < 0)
			trans->parameters[i]->max_jump = -trans->parameters[i]->max_jump;
		
		// I'll be dividing by max_jump. It cannot be too small.
		// I'll use max_jump = 0.0 as "just update instantaneously"
		if (trans->parameters[i]->max_jump < 1e-12)
		{
			trans->parameters[i]->value = trans->parameters[i]->new_value;
			trans->parameters[i]->updated = 0;
			continue;
		}
		
		// Take the difference
		deltas[i] = trans->parameters[i]->new_value - trans->parameters[i]->value;
		
		// If it's smaller than the max jump, just go ahead and change
		// the value. If max_jump is set well, there will be no artifact
		if (fabsf(deltas[i]) < trans->parameters[i]->max_jump)
		{
			trans->parameters[i]->value = trans->parameters[i]->new_value;
			trans->parameters[i]->updated = 0;
			deltas[i] = 0.0;
			continue;
		}
		
		// Otherwise, calculate the min steps needed to move to the
		// new value in jumps of at most max_jump
		local_divider = (int)(fabsf(deltas[i] / trans->parameters[i]->max_jump));
		
		// If it's too big, we won't carry out the full update this block
		long_update[i] = (local_divider > MAX_BLOCK_DIVIDER);
		
		// replace local_divider by the smallest power of 2 greater than it
		// which is also no larger than MAX_BLOCK_DIVIDER, and
		// accumulate the max over all parameters into the global divider
		divider = binary_max(divider, rectify_block_divider(local_divider));
	}
	
	
	// If no parameters have been updated, just run the transformer like normal
	if (!any_updates)
	{
		trans->compute_transformer(trans->data_struct, outputs, inputs, AUDIO_BLOCK_SAMPLES);
		return NO_ERROR;
	}
	
	// Otherwise, divide the block into [divider] many sub-blocks
	n_samples = AUDIO_BLOCK_SAMPLES / divider;
	
	// Divide the deltas by the divider; if any have too-big updates,
	// set their deltas as their max instantenous jump (in the right direction)
	if (divider > 1)
	{
		for (int i = 0; i < trans->n_parameters; i++)
		{
			if (long_update[i])
				deltas[i] = trans->parameters[i]->max_jump * ((deltas[i] < 0) ? -1.0 : 1.0);
			else
				deltas[i] /= divider;
		}
	}
	
	// The actual computation!
	for (int i = 0; i < divider; i++)
	{
		// Apply deltas...
		for (int j = 0; j < trans->n_parameters; j++)
		{
			if (trans->parameters[j] && trans->parameters[j]->updated)
				trans->parameters[j]->value += deltas[j];
		}
		
		if (trans->reconfigure)
			trans->reconfigure((void*)trans->data_struct);
		
		// Hand the partial block over to the transformer for computation
		trans->compute_transformer(trans->data_struct, outputs, inputs, n_samples);
		
		
		for (int j = 0; j < TRANSFORMER_MAX_INPUTS; j++)
			inputs [j] = inputs [j] ? &inputs [j][n_samples] : NULL;
		
		for (int j = 0; j < TRANSFORMER_MAX_OUTPUTS; j++)
			outputs[j] = outputs[j] ? &outputs[j][n_samples] : NULL;
	}
	
	// After having applied the transformer, if any parameters
	// had a full update this block, their value will be near .new_value
	// but not necessarily exactly equal to it, due to floating point
	// imprecision. So, set it equal, and 0 out the parameter's updated flag
	for (int i = 0; i < trans->n_parameters; i++)
	{
		if (trans->parameters[i] && trans->parameters[i]->updated && !long_update[i])
		{
			trans->parameters[i]->value = trans->parameters[i]->new_value;
			trans->parameters[i]->updated = 0;
		}
	}
	
	// One last reconfigure, for the road
	if (trans->reconfigure)
		trans->reconfigure((void*)trans->data_struct);
	
	return NO_ERROR;
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
	
	// run_transformer
	if (calc)
		ret_val = trans->compute_transformer(trans->data_struct, dest, src, AUDIO_BLOCK_SAMPLES);
	
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


tm_parameter *transformer_get_parameter(tm_transformer *trans, uint16_t ppid)
{
	if (!trans)
		return NULL;
	
	if (!trans->parameters)
		return NULL;
	
	if (ppid >= trans->n_parameters)
		return NULL;
	
	if (ppid >= trans->parameter_array_size)
		return NULL;
	
	return trans->parameters[ppid];
}

tm_option *transformer_get_option(tm_transformer *trans, uint16_t oid)
{
	if (!trans)
		return NULL;
	
	if (!trans->options)
		return NULL;
	
	if (oid >= trans->n_options)
		return NULL;
	
	if (oid >= trans->option_array_size)
		return NULL;
	
	return trans->options[oid];
}

void free_transformer(tm_transformer *trans)
{
	if (!trans)
		return;
	
	if (trans->parameters)
		free(trans->parameters);
	if (trans->options)
		free(trans->options);
	
	if (trans->data_struct)
	{
		if (trans->free_struct)
			trans->free_struct(trans->data_struct);
		else
			free(trans->data_struct);
	}
	
	free(trans);
}


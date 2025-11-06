#include "m_eng.h"

static const char *FNAME = "m_eng_transformer.c";
int transformer_init_parameter_array(m_eng_transformer *trans, int n)
{
	FUNCTION_START();

	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (n == 0)
	{
		trans->n_parameters = 0;
		trans->parameter_array_size = 0;
		trans->parameters = NULL;
		RETURN_ERR_CODE(NO_ERROR);
	}
	
	trans->n_parameters = 0;
	trans->parameter_array_size = n;
	trans->parameters 	= (m_eng_parameter**)malloc(sizeof(m_eng_parameter*) * n);
	
	if (!trans->parameters)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}
	
	for (int i = 0; i < n; i++)
		trans->parameters[i] = NULL;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int transformer_init_setting_array(m_eng_transformer *trans, int n)
{
	FUNCTION_START();

	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (n == 0)
	{
		trans->n_settings = 0;
		trans->setting_array_size = 0;
		trans->settings = NULL;
		RETURN_ERR_CODE(NO_ERROR);
	}
	
	trans->n_settings = 0;
	trans->setting_array_size = n;
	trans->settings 	= (m_eng_setting**)malloc(sizeof(m_eng_setting*) * n);
	
	if (!trans->settings)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}
	
	for (int i = 0; i < n; i++)
		trans->settings[i] = NULL;
	
	RETURN_ERR_CODE(NO_ERROR);
}

void run_bypass(float **dest, float **src, int n_inputs, int n_valid_inputs, int n_outputs)
{
	FUNCTION_START();

	float tmp;
		
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		tmp = 0.0;
		for (int j = 0; j < n_inputs; j++)
			if (src[j]) tmp += src[j][i] / n_valid_inputs;
		
		for (int j = 0; j < n_outputs; j++)
			if (dest[j]) dest[j][i] = tmp;
	}
	
	RETURN_VOID();
}

#define MAX_BLOCK_DIVIDER 8

static int rectify_block_divider(int divider)
{
	FUNCTION_START();
	
	int i = 1;
	
	do {
		if (divider < i)
		{
			return i;
		}
		
		i = 2 * i;
	} while (i <= MAX_BLOCK_DIVIDER);
	
	RETURN_INT(MAX_BLOCK_DIVIDER);
}


int run_transformer(m_eng_transformer *trans, float *dest, float *src)
{
	FUNCTION_START();
	
	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (!trans->compute_transformer)
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	int divider = 1;
	int local_divider;
	int any_updates = 0;
	int n_samples;
	
	int long_update[trans->n_parameters];
	float deltas[trans->n_parameters];
	
	float max_jump;
	float factor;
	
	for (int i = 0; i < trans->n_parameters; i++)
		long_update[i] = 0;
	
	// Calculate deltas for all updated parameters
	// and determine how much to divide the block
	for (int i = 0; i < trans->n_parameters && i < trans->parameter_array_size; i++)
	{
		deltas[i] = 0.0;
		if (!trans->parameters[i])
		{
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
		
		// If the parameter has the logarithmic scale, scale the max_jump by its value
		// So it moves faster when it's higher, like how e.g., a cutoff frequency
		// should work
		max_jump = (trans->parameters[i]->scale == PARAMETER_SCALE_LOGARITHMIC)
			? (trans->parameters[i]->max_jump * trans->parameters[i]->value)
			:  trans->parameters[i]->max_jump;
		// If it's smaller than the max jump, just go ahead and change
		// the value. If max_jump is set well, there will be no artifact
		if (fabsf(deltas[i]) < max_jump)
		{
			trans->parameters[i]->value = trans->parameters[i]->new_value;
			trans->parameters[i]->updated = 0;
			deltas[i] = 0.0;
			// but, make sure to reconfigure the transformer !
			if (trans->reconfigure)
				trans->reconfigure((void*)trans->data_struct);
			continue;
		}
		// Otherwise, calculate the min steps needed to move to the
		// new value in jumps of at most max_jump
		local_divider = (int)(fabsf(deltas[i] / max_jump));
		
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
		trans->compute_transformer(trans->data_struct, dest, src, AUDIO_BLOCK_SAMPLES);
		RETURN_ERR_CODE(NO_ERROR);
	}
	
	
	if (trans->reconfigure)
		trans->reconfigure((void*)trans->data_struct);
	
	// Otherwise, divide the block into [divider] many sub-blocks
	n_samples = AUDIO_BLOCK_SAMPLES / divider;
	
	// Divide the deltas by the divider; if any have too-big updates,
	// set their deltas as their max instantenous jump (in the right direction)
	if (divider > 1)
	{
		for (int i = 0; i < trans->n_parameters; i++)
		{
			if (long_update[i])
			{
				factor = ((deltas[i] < 0) ? -1.0 : 1.0) * ((trans->parameters[i]->scale == PARAMETER_SCALE_LOGARITHMIC) ? trans->parameters[i]->value : 1.0);
				deltas[i] = factor * trans->parameters[i]->max_jump;
			}
			else
			{
				deltas[i] /= divider;
			}
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
		trans->compute_transformer(trans->data_struct, dest, src, n_samples);
		
		src  = &src [n_samples];
		dest = &dest[n_samples];
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
	
	RETURN_ERR_CODE(NO_ERROR);
}

int propagate_transformer(m_eng_pipeline *pipeline, m_eng_transformer *trans)
{
	FUNCTION_START();

	if (!pipeline || !trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	trans->runs++;
	
	m_eng_pipeline_node *inputs [TRANSFORMER_MAX_INPUTS ];
	m_eng_pipeline_node *outputs[TRANSFORMER_MAX_OUTPUTS];
	
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
	
	if (!trans->compute_transformer_nl && !trans->compute_transformer)
	{
		ret_val = ERR_TRANSFORMER_MALFORMED;
		calc = 0;
	}
	
	if (trans->bypass)
		calc = 0;
	
	// run_transformer
	if (calc)
	{
		if (trans->compute_transformer_nl)
			ret_val = trans->compute_transformer_nl(trans->data_struct, dest, src, AUDIO_BLOCK_SAMPLES);
		else
			ret_val = trans->compute_transformer(trans->data_struct, dest[0], src[0], AUDIO_BLOCK_SAMPLES);
	}
	
	if (!calc || ret_val != NO_ERROR)
		run_bypass(dest, src, trans->n_inputs, n_valid_inputs, trans->n_outputs);
	
	#ifdef PRINT_TRANSFORMER_INFO
	if (trans->runs % 256 == 0)
	{
		
		
		if (ret_val == NO_ERROR)
			m_eng_printf("Computed sucessfully\n");
		else
			m_eng_printf("Error %d\n", ret_val);
		
		float amp_abs_max = 0.0;
		
		m_eng_printf("Bypass: %d. Function pointer: 0x%x.\n", trans->bypass, trans->compute_transformer);
		
		for (int i = 0; i < TRANSFORMER_MAX_OUTPUTS; i++)
		{
			if (!dest[i])
				continue;
			
			for (int j = 0; j < AUDIO_BLOCK_SAMPLES; j++)
			{
				if (fabs(dest[i][j]) > amp_abs_max)
					amp_abs_max = fabs(dest[i][j]);
			}
			
			m_eng_printf("Output %d peak amplitude: %4f\n", i, amp_abs_max);
		}
	}
	#endif
	
	RETURN_ERR_CODE(ret_val);
}

int transformer_add_setting(m_eng_transformer *trans, m_eng_setting *setting)
{
	FUNCTION_START();

	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (!setting)
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	if (trans->n_settings == trans->setting_array_size)
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	trans->settings[trans->n_settings] = setting;
	trans->n_settings++;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int transformer_add_parameter(m_eng_transformer *trans, m_eng_parameter *param)
{
	FUNCTION_START();

	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (!param)
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	if (trans->n_parameters == trans->parameter_array_size)
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	trans->parameters[trans->n_parameters] = param;
	trans->n_parameters++;
	
	RETURN_ERR_CODE(NO_ERROR);
}

m_eng_parameter *transformer_get_parameter(m_eng_transformer *trans, uint16_t ppid)
{
	if (!trans)
	{
		RETURN_PTR(NULL);
	}
	
	if (!trans->parameters)
	{
		RETURN_PTR(NULL);
	}
	
	if (ppid >= trans->n_parameters)
	{
		RETURN_PTR(NULL);
	}
	
	if (ppid >= trans->parameter_array_size)
	{
		RETURN_PTR(NULL);
	}
	
	return trans->parameters[ppid];
}

m_eng_setting *transformer_get_setting(m_eng_transformer *trans, uint16_t oid)
{
	FUNCTION_START();
	
	if (!trans)
	{
		RETURN_PTR(NULL);
	}
	
	if (!trans->settings)
	{
		RETURN_PTR(NULL);
	}
	
	if (oid >= trans->n_settings)
	{
		RETURN_PTR(NULL);
	}
	
	if (oid >= trans->setting_array_size)
	{
		RETURN_PTR(NULL);
	}
	
	RETURN_PTR(trans->settings[oid]);
}

void free_transformer(m_eng_transformer *trans)
{
	FUNCTION_START();

	m_eng_printf("free_transformer\n");
	if (!trans)
	{
		RETURN_VOID();
	}
	
	m_eng_printf("trans->parameters = %p, trans->settings = %p, trans->data_struct = %p\n",
		trans->parameters, trans->settings, trans->data_struct);
	
	if (trans->parameters)
	{
		m_eng_printf("Freeing parameter array...\n");
		free(trans->parameters);
	}
	if (trans->settings)
	{
		m_eng_printf("Freeing setting array...\n");
		free(trans->settings);
	}
	
	if (trans->data_struct)
	{
		m_eng_printf("Freeing data struct...trans->free_struct = %p\n", trans->free_struct);
		if (trans->free_struct)
			trans->free_struct(trans->data_struct);
		else
			free(trans->data_struct);
	}
	
	free(trans);
}

int clone_transformer(m_eng_transformer **dest_ptr, m_eng_transformer *src)
{
	FUNCTION_START();

	if (!dest_ptr || !src)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (!*dest_ptr)
	{
		*dest_ptr = (m_eng_transformer*)malloc(sizeof(m_eng_transformer));
		if (!*dest_ptr)
		{
			RETURN_ERR_CODE(ERR_ALLOC_FAIL);
		}
	}
	
	m_eng_transformer *dest = *dest_ptr;
	
	int ret_val = init_transformer(dest, src->type);
	
	if (ret_val != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}
	
	dest->id = src->id;
	
	dest->n_inputs  = src->n_inputs;
	dest->n_outputs = src->n_outputs;
	
	dest->bypass = src->bypass;
	
	for (int i = 0; i < TRANSFORMER_MAX_INPUTS; i++)
		dest->inputs[i] = src->inputs[i];
	
	for (int i = 0; i < TRANSFORMER_MAX_OUTPUTS; i++)
		dest->outputs[i] = src->outputs[i];
	
	if (src->settings)
	{
		for (int i = 0; i < dest->n_settings; i++)
		{
			if (dest->settings[i] && src->settings[i])
				memcpy(dest->settings[i], src->settings[i], sizeof(m_eng_setting));
		}
	}
	
	if (src->parameters)
	{
		for (int i = 0; i < dest->n_parameters; i++)
		{
			if (dest->parameters[i] && src->parameters[i])
				memcpy(dest->parameters[i], src->parameters[i], sizeof(m_eng_parameter));
		}
	}
	
	dest->compute_transformer 		= src->compute_transformer;
	dest->compute_transformer_nl 	= src->compute_transformer_nl;
	dest->reconfigure 				= src->reconfigure;
	dest->free_struct 				= src->free_struct;
	dest->clone_struct 				= src->clone_struct;
	
	dest->runs = src->runs;
	dest->struct_size = src->struct_size;
	dest->transition_policy = src->transition_policy;
	
	if (dest->clone_struct)
	{
		ret_val = dest->clone_struct(dest->data_struct, src->data_struct);
		if (ret_val != NO_ERROR)
		{
			RETURN_ERR_CODE(ret_val);
		}
	}
	else
	{
		memcpy(dest->data_struct, src->data_struct, dest->struct_size);
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

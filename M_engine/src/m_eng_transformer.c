#include "m_eng.h"

static const char *FNAME = "m_transformer.c";
int transformer_init_parameter_array(m_transformer *trans, int n)
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
	trans->parameters 	= (m_parameter**)malloc(sizeof(m_parameter*) * n);
	
	if (!trans->parameters)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}
	
	for (int i = 0; i < n; i++)
		trans->parameters[i] = NULL;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int transformer_init_setting_array(m_transformer *trans, int n)
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
	trans->settings 	= (m_setting**)malloc(sizeof(m_setting*) * n);
	
	if (!trans->settings)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}
	
	for (int i = 0; i < n; i++)
		trans->settings[i] = NULL;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int transformer_init_controls(m_transformer *trans)
{
	FUNCTION_START();
	
	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	trans->band_mode.value = TRANSFORMER_MODE_FULL_SPECTRUM;
	
	init_setting(&trans->band_mode, TRANSFORMER_MODE_FULL_SPECTRUM);
	
	init_parameter(&trans->wet_mix, 1.0, 0.0, 1.0, 0.001, PARAMETER_SCALE_LINEAR);
	
	init_parameter(&trans->input_lpf.cutoff_frequency, 4000.0, 1.0, 4000, 0.0225, PARAMETER_SCALE_LOGARITHMIC);
	init_parameter(&trans->input_hpf.cutoff_frequency, 1.0, 1.0, 4000, 0.0225, PARAMETER_SCALE_LOGARITHMIC);
	
	init_lr_low_pass_filter_str(&trans->input_lpf);
	init_lr_high_pass_filter_str(&trans->input_hpf);
	
	reconfigure_lr_low_pass_filter(&trans->input_lpf);
	reconfigure_lr_high_pass_filter(&trans->input_hpf);
	
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


int run_transformer(m_transformer *trans, float *dest, float *src)
{
	FUNCTION_START();
	
	//m_printf("run_transformer\n");
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
	
	int n_parameters = binary_min(trans->n_parameters, trans->parameter_array_size) + N_NATIVE_PARAMETERS;
	int n_settings 	 = binary_min(trans->n_settings,   trans->setting_array_size  ) + N_NATIVE_SETTINGS;
	
	int long_update[n_parameters];
	float deltas[n_parameters];
	
	m_parameter *parameters[n_parameters];
	m_setting *settings[n_settings];
	
	for (int i = 0; i < n_settings; i++)
		settings[i] = NULL;
	
	for (int i = 0; i < n_parameters; i++)
		parameters[i] = NULL;
	
	settings[0] = &trans->band_mode;
	
	for (int i = 0; i < binary_min(trans->n_settings, trans->setting_array_size); i++)
		settings[i + N_NATIVE_SETTINGS] = trans->settings[i];
	
	parameters[0] = &trans->wet_mix;
	parameters[1] = &trans->input_lpf.cutoff_frequency;
	parameters[2] = &trans->input_hpf.cutoff_frequency;
	
	for (int i = 0; i < binary_min(trans->n_parameters, trans->parameter_array_size); i++)
		parameters[i + N_NATIVE_PARAMETERS] = trans->parameters[i];
	
	int setting_reconf = 0;
	
	float max_jump;
	float factor;
	
	float *tmp = NULL;
	float *local_src = NULL;
	float *wet_buffer = NULL;
	
	float *local_dest;	
	float *src_saved;
	
	if (!(tmp 		 = allocate_buffer())) goto run_transformer_alloc_fail;
	if (!(local_src  = allocate_buffer())) goto run_transformer_alloc_fail;
	if (!(wet_buffer = allocate_buffer())) goto run_transformer_alloc_fail;

	local_dest = wet_buffer;	
	src_saved = src;
	
	// First, check for any settings updated. But only bother if the transformer is reconfigurable
	if (trans->reconfigure)
	{
		for (int i = 0; i < n_settings; i++)
		{
			if (settings[i] && settings[i]->updated)
				setting_reconf = 1;
		}
		
		// Setting updates trigger a reconfigure
		if (setting_reconf && trans->reconfigure)
				trans->reconfigure((void*)trans->data_struct);
		
		// Clear updatedness flags
		for (int i = 0; i < n_settings; i++)
		{
			if (settings[i])
				settings[i]->updated = 0;
		}
	}
	
	for (int i = 0; i < n_parameters; i++)
		long_update[i] = 0;
	
	// Calculate deltas for all updated parameters
	// and determine how much to divide the block
	for (int i = 0; i < n_parameters; i++)
	{
		deltas[i] = 0.0;
		if (!parameters[i])
		{
			continue;
		}
		
		if (!parameters[i]->updated)
			continue;
		
		
		any_updates = 1;
		
		// If a negative max_jump has snuck in, rectify this
		if (parameters[i]->max_jump < 0)
			parameters[i]->max_jump = -parameters[i]->max_jump;
		
		// I'll be dividing by max_jump. It cannot be too small.
		// I'll use max_jump = 0.0 as "just update instantaneously"
		if (parameters[i]->max_jump < 1e-12)
		{
			parameters[i]->value = parameters[i]->new_value;
			parameters[i]->updated = 0;
			continue;
		}
		// Take the difference
		deltas[i] = parameters[i]->new_value - parameters[i]->value;
		
		// If the parameter has the logarithmic scale, scale the max_jump by its value
		// So it moves faster when it's higher, like how e.g., a cutoff frequency
		// should work
		max_jump = (parameters[i]->scale == PARAMETER_SCALE_LOGARITHMIC)
			? (parameters[i]->max_jump * parameters[i]->value)
			:  parameters[i]->max_jump;
		// If it's smaller than the max jump, just go ahead and change
		// the value. If max_jump is set well, there will be no artifact
		if (fabsf(deltas[i]) < max_jump)
		{
			parameters[i]->value = parameters[i]->new_value;
			parameters[i]->updated = 0;
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
	
	if (!any_updates)
	{
		divider = 1;
	}
	else
	{
		if (trans->reconfigure)
			trans->reconfigure((void*)trans->data_struct);
		
		// Divide the deltas by the divider; if any have too-big updates,
		// set their deltas as their max instantenous jump (in the right direction)
		if (divider > 1)
		{
			for (int i = 0; i < n_parameters; i++)
			{
				if (long_update[i])
				{
					factor = ((deltas[i] < 0) ? -1.0 : 1.0) * ((parameters[i]->scale == PARAMETER_SCALE_LOGARITHMIC) ? parameters[i]->value : 1.0);
					deltas[i] = factor * parameters[i]->max_jump;
				}
				else
				{
					deltas[i] /= divider;
				}
			}
		}
	}
	
	n_samples = AUDIO_BLOCK_SAMPLES / divider;
	
	//m_printf("trans->band_mode.value = %d\n", trans->band_mode.value);
	// The actual computation!
	for (int i = 0; i < divider; i++)
	{
		// Apply deltas...
		for (int j = 0; j < n_parameters; j++)
		{
			if (parameters[j] && parameters[j]->updated)
				parameters[j]->value += deltas[j];
		}
		
		if (trans->reconfigure)
			trans->reconfigure((void*)trans->data_struct);
		
		
		//m_printf("made it to %s:%s\n", FNAME, XSTR(__LINE__));
		if (trans->band_mode.value == TRANSFORMER_MODE_FULL_SPECTRUM)
		{
			for (int i = 0; i < n_samples; i++)
				local_src[i] = src[i];
		}
		else
		{
			/*m_printf("Input block:\n");
			for (int i = 0; i < n_samples; i++)
			{
				m_printf("%s%.03f%s", (src[i] > 0) ? " " : "-", fabsf(src[i]), ((i + 1) % 16 == 0) ? "\n" : " ");
			}
			m_printf("\n");*/
			
			if (trans->input_lpf.cutoff_frequency.updated)
				reconfigure_lr_low_pass_filter(&trans->input_lpf);
			
			if (trans->input_hpf.cutoff_frequency.updated)
				reconfigure_lr_high_pass_filter(&trans->input_hpf);
			
			switch (trans->band_mode.value)
			{
				case TRANSFORMER_MODE_LOWER_SPECTRUM:
					//m_printf("Lower spectrum mode. Cutoff frequencey: %f\n", trans->input_lpf.cutoff_frequency.value);
					calc_lr_low_pass_filter(&trans->input_lpf, local_src, src, n_samples);
					break;
				case TRANSFORMER_MODE_UPPER_SPECTRUM:
					//m_printf("Upper spectrum mode. Cutoff frequencey: %f\n", trans->input_hpf.cutoff_frequency.value);
					calc_lr_high_pass_filter(&trans->input_hpf, local_src, src, n_samples);
					break;
				case TRANSFORMER_MODE_BAND:
					//m_printf("Band mode. Cutoff frequenceies: %f, %f\n", trans->input_lpf.cutoff_frequency.value, trans->input_hpf.cutoff_frequency.value);
					calc_lr_low_pass_filter(&trans->input_lpf, tmp, src, n_samples);
					calc_lr_high_pass_filter(&trans->input_hpf, local_src, tmp, n_samples);
					break;
			}

			for (int i = 0; i < n_samples; i++)
			{
				tmp[i] = src[i] - local_src[i];
			}
		}
		
		// Hand the partial block over to the transformer for computation
		trans->compute_transformer(trans->data_struct, local_dest, local_src, n_samples);
		
		if (trans->band_mode.value != TRANSFORMER_MODE_FULL_SPECTRUM)
		{
			for (int i = 0; i < n_samples; i++)
				local_dest[i] += tmp[i];
		}
		
		src  = &src [n_samples];
		local_dest = &local_dest[n_samples];
		
		//m_printf("made it to %s:%s\n", FNAME, XSTR(__LINE__));
	}
	
	
	//m_printf("made it to %s:%s\n", FNAME, XSTR(__LINE__));
	// After having applied the transformer, if any parameters
	// had a full update this block, their value will be near .new_value
	// but not necessarily exactly equal to it, due to floating point
	// imprecision. So, set it equal, and 0 out the parameter's updated flag
	for (int i = 0; i < n_parameters; i++)
	{
		if (parameters[i] && parameters[i]->updated && !long_update[i])
		{
			parameters[i]->value = parameters[i]->new_value;
			parameters[i]->updated = 0;
		}
	}
	
	//m_printf("made it to %s:%s\n", FNAME, XSTR(__LINE__));
	// Mix the wets with the dries in the dest buffer; done!
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		dest[i] = trans->wet_mix.value * wet_buffer[i] + (1.0 - trans->wet_mix.value) * src_saved[i];
	
	release_buffer(tmp);
	release_buffer(local_src);
	release_buffer(wet_buffer);
	
	//m_printf("made it to %s:%s\n", FNAME, XSTR(__LINE__));
	
	//m_printf("run_transformer done\n");
	RETURN_ERR_CODE(NO_ERROR);
	
run_transformer_alloc_fail:
	
	if (tmp) release_buffer(tmp);
	if (local_src) release_buffer(local_src);
	if (wet_buffer) release_buffer(wet_buffer);
	
	RETURN_ERR_CODE(ERR_ALLOC_FAIL);
}

#ifdef GRAPH_PIPELINE
int propagate_transformer(m_eng_graph *pipeline, m_transformer *trans)
{
	FUNCTION_START();

	if (!pipeline || !trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	trans->runs++;
	
	m_eng_graph_node *inputs [TRANSFORMER_MAX_INPUTS ];
	m_eng_graph_node *outputs[TRANSFORMER_MAX_OUTPUTS];
	
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
			m_printf("Computed sucessfully\n");
		else
			m_printf("Error %d\n", ret_val);
		
		float amp_abs_max = 0.0;
		
		m_printf("Bypass: %d. Function pointer: 0x%x.\n", trans->bypass, trans->compute_transformer);
		
		for (int i = 0; i < TRANSFORMER_MAX_OUTPUTS; i++)
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
	}
	#endif
	
	RETURN_ERR_CODE(ret_val);
}
#endif

int transformer_add_setting(m_transformer *trans, m_setting *setting)
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

int transformer_add_parameter(m_transformer *trans, m_parameter *param)
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

m_parameter *transformer_get_parameter(m_transformer *trans, uint16_t ppid)
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
		switch (ppid)
		{
			case TRANSFORMER_WET_MIX_PID:
				RETURN_PTR(&trans->wet_mix);
				
			case TRANSFORMER_BAND_LP_CUTOFF_PID:
				RETURN_PTR(&trans->input_lpf.cutoff_frequency);
				
			case TRANSFORMER_BAND_HP_CUTOFF_PID:
				RETURN_PTR(&trans->input_hpf.cutoff_frequency);
			
			default:
				RETURN_PTR(NULL);
		}
	}
	
	return trans->parameters[ppid];
}

m_setting *transformer_get_setting(m_transformer *trans, uint16_t sid)
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
	
	if (sid >= trans->n_settings)
	{
		switch (sid)
		{
			case TRANSFORMER_BAND_MODE_SID:
				RETURN_PTR(&trans->band_mode);
			
			default:
				RETURN_PTR(NULL);
		}
	}
	
	RETURN_PTR(trans->settings[sid]);
}

void free_transformer(m_transformer *trans)
{
	FUNCTION_START();

	m_printf("free_transformer\n");
	if (!trans)
	{
		RETURN_VOID();
	}
	
	m_printf("trans->parameters = %p, trans->settings = %p, trans->data_struct = %p\n",
		trans->parameters, trans->settings, trans->data_struct);
	
	if (trans->parameters)
	{
		m_printf("Freeing parameter array...\n");
		free(trans->parameters);
	}
	if (trans->settings)
	{
		m_printf("Freeing setting array...\n");
		free(trans->settings);
	}
	
	if (trans->data_struct)
	{
		m_printf("Freeing data struct...trans->free_struct = %p\n", trans->free_struct);
		if (trans->free_struct)
			trans->free_struct(trans->data_struct);
		else
			free(trans->data_struct);
	}
	
	free(trans);
}

int clone_transformer(m_transformer **dest_ptr, m_transformer *src)
{
	FUNCTION_START();

	if (!dest_ptr || !src)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (!*dest_ptr)
	{
		*dest_ptr = (m_transformer*)malloc(sizeof(m_transformer));
		if (!*dest_ptr)
		{
			RETURN_ERR_CODE(ERR_ALLOC_FAIL);
		}
	}
	
	m_transformer *dest = *dest_ptr;
	
	int ret_val = init_transformer(dest, src->type);
	
	if (ret_val != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}
	
	dest->id = src->id;
	
	if (src->settings)
	{
		for (int i = 0; i < dest->n_settings; i++)
		{
			if (dest->settings[i] && src->settings[i])
				memcpy(dest->settings[i], src->settings[i], sizeof(m_setting));
		}
	}
	
	if (src->parameters)
	{
		for (int i = 0; i < dest->n_parameters; i++)
		{
			if (dest->parameters[i] && src->parameters[i])
				memcpy(dest->parameters[i], src->parameters[i], sizeof(m_parameter));
		}
	}
	
	dest->compute_transformer 		= src->compute_transformer;
	dest->compute_transformer_nl 	= src->compute_transformer_nl;
	dest->reconfigure 				= src->reconfigure;
	dest->free_struct 				= src->free_struct;
	dest->clone_struct 				= src->clone_struct;
	
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

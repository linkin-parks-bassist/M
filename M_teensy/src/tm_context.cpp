#include "tm.h"

int init_tm_context(tm_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	cxt->profile_array_size = PROFILE_ARRAY_INITIAL_SIZE;
	
	do {
		cxt->profiles = (tm_profile*)malloc(sizeof(tm_profile) * cxt->profile_array_size);
		if (!cxt->profiles)
			cxt->profile_array_size /= 2;
	} while (!cxt->profiles && cxt->profile_array_size);
	
	if (!cxt->profiles)
		return ERR_ALLOC_FAIL;
	
	for (int i = 1; i < cxt->profile_array_size; i++)
		nullify_profile(&cxt->profiles[i]);
	
	init_bypass_profile(&cxt->profiles[0]);
	cxt->n_profiles = 1;
	cxt->active_profile = 0;
	
	cxt->unconfigured_pipeline = NULL;
	
	cxt->status_flags = M_STATUS_FRESH_BOOT;
	
	cxt->profile_switch_triggered = 0;
	cxt->profiles_switching = 0;
	cxt->profile_switch_progress = 0;
	
	cxt->new_profile = 0;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		cxt->avg_noise[i] = 0.0;
	
	cxt->noise_counter = 0;
	
	return NO_ERROR;
}

/* Returns error codes in negative; otherwise, returns the index (ID) of the new profile */
int tm_context_new_profile(tm_context *cxt)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	// Do I need a " - 1" here? I don't think so. But, if I get random crashes later, revisit this
	if (cxt->n_profiles >= cxt->profile_array_size)
	{
		int try_size = PROFILES_MALLOC_CHUNK_SIZE;
		tm_profile *new_ptr = NULL;
		
		do
		{
			new_ptr = (tm_profile*)malloc(sizeof(tm_profile) * (cxt->profile_array_size + try_size));
			if (!new_ptr)
				try_size /= 2;
		} while (!new_ptr && try_size);
		
		if (!new_ptr)
			return -ERR_ALLOC_FAIL;
		
		memcpy(new_ptr, cxt->profiles, sizeof(tm_profile) * (cxt->profile_array_size));
		free(cxt->profiles);
		cxt->profiles = new_ptr;
		cxt->profile_array_size += try_size;
		
		for (int i = cxt->n_profiles; i < cxt->profile_array_size; i++)
			nullify_profile(&cxt->profiles[i]);
	}
	
	init_profile(&cxt->profiles[cxt->n_profiles++]);
	
	
	
	return cxt->n_profiles - 1;
}

m_parameter *cxt_get_parameter_by_id(tm_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id)
{
	if (!cxt)
		return NULL;
	
	if (profile_id >= cxt->n_profiles)
		return NULL;
	
	tm_audio_transformer *trans = pipe_line_get_transformer_by_id(&cxt->profiles[profile_id].pipe_line, transformer_id);
	
	if (parameter_id >= trans->n_parameters)
		return NULL;
	
	return trans->parameters[parameter_id];
}

m_parameter *cxt_get_parameter_by_id_str(tm_context *cxt, m_parameter_id id)
{
	if (!cxt)
		return NULL;
	
	if (id.profile_id >= cxt->n_profiles)
		return NULL;
	
	tm_audio_transformer *trans = pipe_line_get_transformer_by_id(&cxt->profiles[id.profile_id].pipe_line, id.transformer_id);
	
	if (id.parameter_id >= trans->n_parameters)
		return NULL;
	
	return trans->parameters[id.parameter_id];
}

int update_paramter_value_by_id(tm_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id, m_param_value new_value)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	m_parameter *param = cxt_get_parameter_by_id(cxt, profile_id, transformer_id, parameter_id);
	
	if (!param)
		return ERR_BAD_ARGS;
	
	param->val = new_value;
	
	return NO_ERROR;
}

int update_paramter_value_by_id_str(tm_context *cxt, m_parameter_id id, m_param_value new_value)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	m_parameter *param = cxt_get_parameter_by_id_str(cxt, id);
	
	if (!param)
		return ERR_BAD_ARGS;
	
	param->val = new_value;
	
	return NO_ERROR;
}

void tm_safe_reboot(tm_context *cxt)
{
	tm_printf("Rebooting...\n");
	_reboot_Teensyduino_(); //rofl
}

int reset_context(tm_context *cxt)
{
	return ERR_UNIMPLEMENTED;
	
	if (!cxt)
		return ERR_NULL_PTR;
	
	return NO_ERROR;
}

int cxt_append_transformer_to_profile(tm_context *cxt, uint16_t profile_id, uint16_t type)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	if (profile_id > cxt->n_profiles)
		return -ERR_BAD_ARGS;
	
	int ret_val = pipe_line_append_transformer_type(&cxt->profiles[profile_id].pipe_line, type);
	
	return ret_val;
}

int cxt_insert_transformer_to_profile (tm_context *cxt, uint16_t profile_id, uint16_t type, uint16_t pos)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	if (profile_id > cxt->n_profiles)
		return -ERR_BAD_ARGS;
	
	int ret_val = pipe_line_insert_transformer_type(&cxt->profiles[profile_id].pipe_line, type, pos);
	
	return ret_val;
}

int cxt_prepend_transformer_to_profile(tm_context *cxt, uint16_t profile_id, uint16_t type)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	if (profile_id > cxt->n_profiles)
		return -ERR_BAD_ARGS;
	
	int ret_val = pipe_line_prepend_transformer_type(&cxt->profiles[profile_id].pipe_line, type);
	
	return ret_val;
}

int cxt_get_n_profile_transformers(tm_context *cxt, uint16_t profile_id)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	if (cxt->n_profiles <= profile_id)
		return -ERR_BAD_ARGS;
	
	return cxt->profiles[profile_id].pipe_line.n_transformers;
}

int cxt_get_n_transformer_params(tm_context *cxt, uint16_t profile_id, uint16_t transformer_id)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	tm_audio_transformer *trans = cxt_get_transformer_by_id(cxt, profile_id, transformer_id);
	
	if (!trans)
		return -ERR_BAD_ARGS;
	
	return trans->n_parameters;
}

int cxt_get_transformer_type(tm_context *cxt, uint16_t profile_id, uint16_t transformer_id)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	tm_audio_transformer *trans = cxt_get_transformer_by_id(cxt, profile_id, transformer_id);
	
	if (!trans)
		return -ERR_BAD_ARGS;
	
	return trans->type;
}


int cxt_get_transformer_id_by_pos (tm_context *cxt, uint16_t profile_id, uint16_t pos)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	if (profile_id >= cxt->n_profiles)
		return -ERR_BAD_ARGS;
	
	if (pos >= cxt->profiles[profile_id].pipe_line.n_transformers)
		return -ERR_BAD_ARGS;
	
	if (!cxt->profiles[profile_id].pipe_line.transformers[pos])
		return -ERR_BAD_ARGS;
	
	return cxt->profiles[profile_id].pipe_line.transformers[pos]->id;
}

tm_audio_transformer *cxt_get_transformer_by_id(tm_context *cxt, uint16_t profile_id, uint16_t transformer_id)
{
	if (!cxt)
		return NULL;
	
	if (profile_id >= cxt->n_profiles)
		return NULL;
	
	return pipe_line_get_transformer_by_id(&cxt->profiles[profile_id].pipe_line, transformer_id);
}

m_param_type cxt_get_parameter_type(tm_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id)
{
	m_parameter *param = cxt_get_parameter_by_id(cxt, profile_id, transformer_id, parameter_id);
	
	if (!param)
		return M_PARAM_ERR;
	
	return param->type;
}

m_param_value cxt_get_parameter_value(tm_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id)
{
	m_parameter *param = cxt_get_parameter_by_id(cxt, profile_id, transformer_id, parameter_id);
	
	if (!param)
		return {.level=0.0};
	
	return param->val;
}

int	cxt_set_parameter_value(tm_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id, m_param_value new_value)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	m_parameter *param = cxt_get_parameter_by_id_str(cxt, {.profile_id=profile_id, .transformer_id=transformer_id, parameter_id=parameter_id});
	
	if (!param)
		return ERR_BAD_ARGS;
	
	param->val = new_value;
	
	return NO_ERROR;
}


char *cxt_get_parameter_name(tm_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id)
{
	if (!cxt)
		return NULL;
	
	m_parameter *param = cxt_get_parameter_by_id_str(cxt, {.profile_id=profile_id, .transformer_id=transformer_id, parameter_id=parameter_id});
	
	if (!param)
		return NULL;
	
	return param->name;
}

int cxt_set_parameter_name(tm_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id, const char *new_name)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	m_parameter *param = cxt_get_parameter_by_id_str(cxt, {.profile_id=profile_id, .transformer_id=transformer_id, parameter_id=parameter_id});
	
	if (!param)
		return ERR_BAD_ARGS;
	
	if (param->name)
		free(param->name);
	
	param->name = new_name ? strndup(new_name, PARAM_NAME_MAX_LEN) : NULL;
	
	return NO_ERROR;
}

int cxt_set_active_profile(tm_context *cxt, uint16_t profile_id)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	cxt->active_profile = profile_id;
	
	return NO_ERROR;
}

int cxt_switch_to_profile(tm_context *cxt, uint16_t profile_id)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	if (profile_id == cxt->active_profile)
		return NO_ERROR;
	
	if (profile_id >= cxt->n_profiles)
		return ERR_BAD_ARGS;
	
	tm_printf("Switching to profile %d\n");
	cxt->profile_switch_triggered = 1;
	cxt->new_profile = profile_id;
	
	return NO_ERROR;
}

#define SILENCE_ENERGY_THRESHOLD 	2000
#define SILENCE_BLOCKS_THRESHOLD 	64

#define NOISE_DELTA 				0.999

int cxt_update_avg_noise(tm_context *cxt, int16_t *block)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	float energy  = 0.0;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		energy += block[i] * block[i];
	
	energy = sqrt(energy);
	
	if (energy < SILENCE_ENERGY_THRESHOLD)
	{
		if (cxt->noise_counter > SILENCE_BLOCKS_THRESHOLD)
		{
			for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
				cxt->avg_noise[i] = NOISE_DELTA * cxt->avg_noise[i] + (1.0 - NOISE_DELTA) * block[i];
		}
		else
		{
			cxt->noise_counter++;
		}
	}
	else
	{
		cxt->noise_counter = 0;
	}
	
	return NO_ERROR;
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

#define AVG_DURATION_UPDATE_COEF 0.99f
//#define PRINT_TIMES

int runs = 0;

int cxt_process(tm_context *cxt)
{
	static uint32_t last_runtime = micros();
	
	static float avg_roundtrip_duration_micros 	= 0.0;
	static float avg_compute_duration_micros 	= 0.0;
	
	tm_pipeline *new_pipeline 	= NULL;
	tm_pipeline *active_pipeline = NULL;
	
	tm_pipe_line *new_pipe_line 		= NULL;
	tm_pipe_line *active_pipe_line 	= NULL;
	
	int16_t block[AUDIO_BLOCK_SAMPLES];
	
	float *input_buffer;
	float *output_buffer;
	
	uint32_t start_time = micros();
	
	int ret_val;
	
	i2s_input_update();
	cxt_update_avg_noise(cxt, i2s_input_blocks[1].data);
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		block[i] = i2s_input_blocks[1].data[i] - (int16_t)cxt->avg_noise[i];
	
	// This function should only be called with argument global_cxt, 
	// which is definitely not NULL. But if it is, for some reason,
	// called with a NULL pointer, just put the input in the output
	if (!cxt)
		goto oughtnt_happen;
	
	active_pipeline  = &cxt->profiles[cxt->active_profile].pipeline;
	active_pipe_line = &cxt->profiles[cxt->active_profile].pipe_line;
	// Now, this is just impossible, but, better not to trust that
	if (!active_pipeline)
		goto cant_possibly_happen;
	
	input_buffer  = allocate_buffer();
	output_buffer = allocate_buffer();
	
	convert_block_int_to_float(input_buffer, block);
	
	#ifdef PRETTY_PRINT_BLOCKS
	pretty_print_block(block, "Input: \n");
	#endif
	
	if (cxt->profile_switch_triggered)
	{
		cxt->profiles_switching 	  = 1;
		cxt->profile_switch_progress  = 0;
		cxt->profile_switch_triggered = 0;
	}
	
	if (cxt->profiles_switching)
	{
		float *output_buffer_2 = allocate_buffer();
		tm_printf("Allocated output_buffer_2 = %p\n", output_buffer_2);
		
		new_pipeline  = &cxt->profiles[cxt->new_profile].pipeline;
		new_pipe_line = &cxt->profiles[cxt->new_profile].pipe_line;
		
		tm_printf("new_pipe_line = %p\n", new_pipe_line);
		
		tm_printf("Switch in progress...\n");
		float ratio, coef;
		
		//tm_printf("Compute pipelines...\n");
		//compute_pipeline(active_pipeline, block);
		//compute_pipeline(   new_pipeline, block);
		
		
		tm_printf("output_buffer_2 = %p\n", output_buffer_2);
		compute_pipe_line(active_pipe_line, output_buffer,   input_buffer);
		compute_pipe_line(   new_pipe_line, output_buffer_2, input_buffer);
		
		tm_printf("computed pipelines...\n");
		
		//out1 = active_pipeline->output_node.block->data;
		//out2 =    new_pipeline->output_node.block->data;
		
		//tm_printf("outputs: 0x%x, 0x%x\n", out1, out2);
		//tm_printf("interpolate outputs...\n");
		for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		{
			ratio = (float)(cxt->profile_switch_progress) / (float)M_PROFILE_SWITCH_SAMPLES;
			
			coef = smoothed_transition_function(ratio, 3);
			//tm_printf("ratio = %6f, coef = %6f\n", ratio, coef);
			
			//tmp_block[i] = (1.0 - coef) * out1[i] + coef * out2[i];
			output_buffer[i] = (1.0 - coef) * output_buffer[i] + coef * output_buffer_2[i];
			
			cxt->profile_switch_progress++;
		}
		
		tm_printf("combined outputs...\n");
		
		//tm_printf("transmit output...\n");
		i2s_output_transmit_mono_float(output_buffer);
		
		if (cxt->profile_switch_progress >= M_PROFILE_SWITCH_SAMPLES)
		{
			//tm_printf("transition complete\n");
			cxt->active_profile 	= cxt->new_profile;
			cxt->profiles_switching = 0;
		}
		
		release_buffer(output_buffer_2);
	}
	else
	{
		ret_val = compute_pipeline(active_pipeline, block);
		compute_pipe_line(active_pipe_line, output_buffer,   input_buffer);
		
		/*if (ret_val == ERR_PIPELINE_BUSTED)
		{
			if (active_pipeline->err_flags & PIPELINE_ERR_FLAG_UNCONFIGURED)
				cxt->unconfigured_pipeline = active_pipeline;
		}*/
		#ifdef PRINT_BLOCKS
		serial_print_blocks(2, active_pipeline->input_node.block->data,  active_pipeline->output_node.block->data);
		#endif
		i2s_output_transmit_mono_float(output_buffer);
	}
	
	#ifdef PRETTY_PRINT_BLOCKS
	pretty_print_block_float(output_buffer, "Output: \n");
	#endif
	
	release_buffer(input_buffer);
	release_buffer(output_buffer);
	
	avg_roundtrip_duration_micros = avg_roundtrip_duration_micros * AVG_DURATION_UPDATE_COEF + (start_time - last_runtime) * (1.0 - AVG_DURATION_UPDATE_COEF);
	last_runtime = start_time;
	
	avg_compute_duration_micros = avg_compute_duration_micros * AVG_DURATION_UPDATE_COEF + ((float)(micros() - start_time)) * (1.0 - AVG_DURATION_UPDATE_COEF);
	
	i2s_output_update();
	
	runs++;
	
	if (runs % 256 == 0)
	{
	#ifdef PRINT_TIMES
		tm_printf("average compute duration: %6fms. average round-trip duration: %6fms. Compute takes %03f%% of round-trip\n",
			avg_compute_duration_micros * 0.001, avg_roundtrip_duration_micros * 0.001,
			(avg_roundtrip_duration_micros == 0.0) ? 0 : 100.0 * (avg_compute_duration_micros/avg_roundtrip_duration_micros));
	#endif
	}

	asm("DSB");
	
	return NO_ERROR;

oughtnt_happen:
cant_possibly_happen:
	i2s_output_transmit_mono_int(block);
	asm("DSB");
	return ERR_NULL_PTR;
}

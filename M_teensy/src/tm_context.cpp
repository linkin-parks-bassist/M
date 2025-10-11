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
	
	init_profile(&cxt->profiles[0]);
	cxt->n_profiles = 1;
	cxt->active_profile = 0;
	
	cxt->unconfigured_pipeline = NULL;
	
	cxt->status_flags = M_STATUS_FRESH_BOOT;
	
	cxt->profile_switch_triggered 	= 0;
	cxt->profiles_switching 		= 0;
	cxt->profile_switch_progress 	= 0;
	cxt->profile_switch_type  		= TRANSITION_MONOBLOCK_COS2;
	
	cxt->new_profile = 0;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		cxt->avg_noise[i] = 0.0;
	
	cxt->noise_counter = 0;
	
	for (int i = 0; i < DECLICK_BUFSIZE; i++)
		cxt->declick_buffer[i] = 0.0;
	
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

int cxt_profile_id_valid(tm_context *cxt, uint16_t pid)
{
	if (!cxt)
		return 0;
	
	return (pid <= (unsigned int)cxt->n_profiles);
}

int cxt_transformer_id_valid(tm_context *cxt, uint16_t pid, uint16_t tid)
{
	if (!cxt_profile_id_valid(cxt, pid))
		return 0;
	
	if (tid >= (unsigned int)cxt->profiles[pid].back_pipeline->n_transformers)
		return 0;
	
	return (pipe_line_get_transformer_by_id(cxt->profiles[pid].back_pipeline, tid) != NULL);
}

int pcxt_profile_id_valid(tm_context *cxt, uint16_t pid, uint16_t tid, uint16_t ppid)
{
	if (!cxt_transformer_id_valid(cxt, pid, tid))
		return 0;
	
	tm_transformer *trans = pipe_line_get_transformer_by_id(cxt->profiles[pid].back_pipeline, tid);
	
	if (!trans)
		return 0;
	
	return (trans->n_parameters >= ppid && trans->parameters[ppid]);
}


tm_parameter *cxt_get_parameter_by_id(tm_context *cxt, uint16_t pid, uint16_t tid, uint16_t ppid)
{
	if (!cxt)
		return NULL;
	
	if (pid >= cxt->n_profiles)
		return NULL;
	
	tm_transformer *trans = pipe_line_get_transformer_by_id(cxt->profiles[pid].front_pipeline, tid);
	
	if (ppid >= trans->n_parameters)
		return NULL;
	
	return trans->parameters[ppid];
}

tm_parameter *cxt_get_front_parameter_by_id(tm_context *cxt, uint16_t pid, uint16_t tid, uint16_t ppid)
{
	if (!cxt)
		return NULL;
	
	if (pid >= cxt->n_profiles)
		return NULL;
	
	tm_transformer *trans = pipe_line_get_transformer_by_id(cxt->profiles[pid].front_pipeline, tid);
	
	if (ppid >= trans->n_parameters)
		return NULL;
	
	return trans->parameters[ppid];
}

tm_parameter *cxt_get_back_parameter_by_id(tm_context *cxt, uint16_t pid, uint16_t tid, uint16_t ppid)
{
	if (!cxt)
		return NULL;
	
	if (pid >= cxt->n_profiles)
		return NULL;
	
	tm_transformer *trans = pipe_line_get_transformer_by_id(cxt->profiles[pid].back_pipeline, tid);
	
	if (ppid >= trans->n_parameters)
		return NULL;
	
	return trans->parameters[ppid];
}

int cxt_update_parameter_value_by_id(tm_context *cxt, uint16_t pid, uint16_t tid, uint16_t ppid, float new_value)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	if (pid >= cxt->n_profiles)
		return ERR_INVALID_PROFILE_ID;
	
	tm_transformer *front_trans = pipe_line_get_transformer_by_id(cxt->profiles[pid].front_pipeline, tid);
	
	if (!front_trans)
		return ERR_INVALID_TRANSFORMER_ID;
	
	tm_transformer *back_trans = pipe_line_get_transformer_by_id(cxt->profiles[pid].back_pipeline, tid);
	
	if (!back_trans)
		return ERR_INCONSISTENT_BACK_PIPELINE;
	
	tm_parameter *front_param = transformer_get_parameter(front_trans, ppid);
	
	if (!front_param)
		return ERR_INVALID_PARAMETER_ID;
	
	tm_parameter *back_param = transformer_get_parameter(back_trans, ppid);
	
	if (!back_param)
		return ERR_INCONSISTENT_BACK_PIPELINE;
	
	front_param->new_value = new_value;
	front_param->updated = 1;
	
	if (cxt->profiles[pid].pipelines_swapping)
	{
		back_param->new_value = new_value;
		back_param->updated = 1;
	}
	else
	{
		back_param->value = new_value;
		back_param->updated = 0;
	}
	
	return NO_ERROR;
}

tm_option *cxt_get_option_by_id(tm_context *cxt, uint16_t pid, uint16_t tid, uint16_t oid)
{
	if (!cxt)
		return NULL;
	
	if (pid >= cxt->n_profiles)
		return NULL;
	
	tm_transformer *trans = pipe_line_get_transformer_by_id(cxt->profiles[pid].back_pipeline, tid);
	
	if (oid >= trans->n_options)
		return NULL;
	
	return trans->options[oid];
}

int cxt_update_option_value_by_id(tm_context *cxt, uint16_t pid, uint16_t tid, uint16_t oid, float new_value)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	tm_option *option = cxt_get_option_by_id(cxt, pid, tid, oid);
	
	if (!option)
		return ERR_BAD_ARGS;
	
	return update_option(option, new_value);
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

int cxt_append_transformer_to_profile(tm_context *cxt, uint16_t pid, uint16_t type)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	if (pid > cxt->n_profiles)
		return -ERR_BAD_ARGS;
	
	int ret_val = profile_apply_pipeline_mod(&cxt->profiles[cxt->active_profile], create_pipe_line_mod_append_transformer(type));
	
	return ret_val;
}

int cxt_remove_transformer_from_profile(tm_context *cxt, uint16_t pid, uint16_t tid)
{
	tm_printf("cxt_remove_transformer_from_profile...\n");
	if (!cxt)
		return -ERR_NULL_PTR;
	
	if (pid > cxt->n_profiles)
		return -ERR_BAD_ARGS;
	
	int ret_val = profile_apply_pipeline_mod(&cxt->profiles[cxt->active_profile], create_pipe_line_mod_remove_transformer(tid));
	
	tm_printf("cxt_remove_transformer_from_profile done. ret_val = %s\n", m_error_code_to_string(ret_val));
	return ret_val;
}

int cxt_move_transformer(tm_context *cxt, uint16_t tid, uint16_t new_pos)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	int ret_val = profile_apply_pipeline_mod(&cxt->profiles[cxt->active_profile], create_pipe_line_mod_move_transformer(tid, new_pos));
	
	return ret_val;
}

int cxt_insert_transformer_to_profile(tm_context *cxt, uint16_t pid, uint16_t type, uint16_t pos)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	if (pid > cxt->n_profiles)
		return -ERR_BAD_ARGS;
	
	int ret_val = pipe_line_insert_transformer_type(cxt->profiles[pid].back_pipeline, type, pos);
	
	return ret_val;
}

int cxt_prepend_transformer_to_profile(tm_context *cxt, uint16_t pid, uint16_t type)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	if (pid > cxt->n_profiles)
		return -ERR_BAD_ARGS;
	
	int ret_val = pipe_line_prepend_transformer_type(cxt->profiles[pid].back_pipeline, type);
	
	return ret_val;
}

int cxt_get_n_profile_transformers(tm_context *cxt, uint16_t pid)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	if (cxt->n_profiles <= pid)
		return -ERR_BAD_ARGS;
	
	return cxt->profiles[pid].back_pipeline->n_transformers;
}

int cxt_get_n_transformer_params(tm_context *cxt, uint16_t pid, uint16_t tid)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	tm_transformer *trans = cxt_get_transformer_by_id(cxt, pid, tid);
	
	if (!trans)
		return -ERR_BAD_ARGS;
	
	return trans->n_parameters;
}

int cxt_get_n_transformer_options(tm_context *cxt, uint16_t pid, uint16_t tid)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	tm_transformer *trans = cxt_get_transformer_by_id(cxt, pid, tid);
	
	if (!trans)
		return -ERR_BAD_ARGS;
	
	return trans->n_options;
}

int cxt_get_transformer_type(tm_context *cxt, uint16_t pid, uint16_t tid)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	tm_transformer *trans = cxt_get_transformer_by_id(cxt, pid, tid);
	
	if (!trans)
		return -ERR_BAD_ARGS;
	
	return trans->type;
}


int cxt_get_tid_by_pos(tm_context *cxt, uint16_t pid, uint16_t pos)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	if (pid >= cxt->n_profiles)
		return -ERR_BAD_ARGS;
	
	if (pos >= cxt->profiles[pid].back_pipeline->n_transformers)
		return -ERR_BAD_ARGS;
	
	if (!cxt->profiles[pid].back_pipeline->transformers[pos])
		return -ERR_BAD_ARGS;
	
	return cxt->profiles[pid].back_pipeline->transformers[pos]->id;
}

tm_transformer *cxt_get_transformer_by_id(tm_context *cxt, uint16_t pid, uint16_t tid)
{
	if (!cxt)
		return NULL;
	
	if (pid >= cxt->n_profiles)
		return NULL;
	
	return pipe_line_get_transformer_by_id(cxt->profiles[pid].back_pipeline, tid);
}

int cxt_set_active_profile(tm_context *cxt, uint16_t pid)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	cxt->active_profile = pid;
	
	return NO_ERROR;
}

int cxt_switch_to_profile(tm_context *cxt, uint16_t pid)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	if (pid == cxt->active_profile)
		return NO_ERROR;
	
	if (pid >= cxt->n_profiles)
		return ERR_BAD_ARGS;
	
	tm_printf("Switching to profile %d\n");
	cxt->profile_switch_triggered = 1;
	cxt->new_profile = pid;
	cxt->profile_switch_progress = 0;
	cxt->profile_switch_type = cxt->profiles[cxt->n_profiles].transition_policy;
	
	switch (cxt->profile_switch_type)
	{
		case TRANSITION_QUADBLOCK_COS2:
			cxt->profile_switch_samples = 4 * AUDIO_BLOCK_SAMPLES;
			break;
		
		case TRANSITION_OCTOBLOCK_COS2:
			cxt->profile_switch_samples = 8 * AUDIO_BLOCK_SAMPLES;
			break;
		
		default:
			cxt->profile_switch_samples = 2 * AUDIO_BLOCK_SAMPLES;
	}
	
	return NO_ERROR;
}

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

#define AVG_DURATION_UPDATE_COEF 0.99f

int runs = 0;

int cxt_process(tm_context *cxt)
{
	static uint32_t last_runtime = micros();
	uint32_t end_time;
	
	int16_t block[AUDIO_BLOCK_SAMPLES];
	uint8_t click_buffer[AUDIO_BLOCK_SAMPLES + DECLICK_BUFSIZE - 1];
	
	static float avg_roundtrip_duration_micros 	= 0.0;
	static float avg_compute_duration_micros 	= 0.0;
	
	float s1, s2;
	float *tmp;
	
	i2s_input_update();
	cxt_update_avg_noise(cxt, i2s_input_blocks[1].data);
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		block[i] = i2s_input_blocks[1].data[i] - (int16_t)cxt->avg_noise[i];
	
	if (cxt->profile_switch_triggered)
	{
		cxt->profiles_switching 	  = 1;
		cxt->profile_switch_progress  = 0;
		cxt->profile_switch_triggered = 0;
	}
	
	tm_profile *active_profile = &cxt->profiles[cxt->active_profile];
	
	float *src = allocate_buffer();
	float *dest = NULL;
	
	float *input_buffers [2] = {NULL, NULL};
	float *output_buffers[2] = {NULL, NULL};
	
	float ratio;
	uint32_t start_time = micros();
	
	if (!src)
		goto panic_bypass;
	
	convert_block_int_to_float(src, block);
	
	dest = allocate_buffer();
	
	if (!dest)
		goto panic_bypass;
	
	if (cxt->profiles_switching)
	{
		tm_profile *new_profile = &cxt->profiles[cxt->new_profile];
		
		int switch_complete = 0;
		
		input_buffers [0] = src;
		input_buffers [1] = src;
		
		output_buffers[0] = allocate_buffer();
		output_buffers[1] = allocate_buffer();
		
		if (!output_buffers[0] || !output_buffers[1])
		{
			input_buffers [0] = NULL;
			input_buffers [1] = NULL;
			
			goto panic_bypass;
		}
		
		if (cxt->profile_switch_type == TRANSITION_TAIL)
		{
			input_buffers[0] = allocate_buffer();
			
			if (!input_buffers[0])
				goto panic_bypass;
			
			if (cxt->profile_switch_progress > TAIL_INPUT_FADE_SAMPLES)
			{
				for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
					input_buffers[0][i] = 0.0;
			}
			else
			{
				for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
				{
					ratio = (float)(cxt->profile_switch_progress++) / (float)TAIL_INPUT_FADE_SAMPLES;
					input_buffers[0][i] = trig_transition_function(ratio) * src[i];
				}
			}
			
			profile_process(active_profile, output_buffers[0], input_buffers[0]);
			profile_process(   new_profile, output_buffers[1], input_buffers[1]);
			
			float energy = 0.0;
			
			for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
				energy += sqr(output_buffers[0][i]);
			
			if (energy < SILENCE_ENERGY_THRESHOLD)
			{
				switch_complete = 1;
				memcpy(dest, output_buffers[1], AUDIO_BLOCK_SAMPLES * sizeof(float));
			}
			else
			{
				if (cxt->profile_switch_progress < TAIL_NEW_FADE_IN_SAMPLES)
				{
					for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
						dest[i] = trig_transition_function((float)(cxt->profile_switch_progress++) / TAIL_NEW_FADE_IN_SAMPLES) * output_buffers[0][i] + output_buffers[1][i];
				}
				else
				{
					for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
						dest[i] = output_buffers[0][i] + output_buffers[1][i];
				}
			}
			
			release_buffer(input_buffers[0]);
		}
		else
		{
			profile_process(active_profile, output_buffers[0], input_buffers[0]);
			profile_process(   new_profile, output_buffers[1], input_buffers[1]);
			
			float coef;
			for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
			{
				ratio = (float)(cxt->profile_switch_progress) / (float)cxt->profile_switch_samples;
				
				coef = trig_transition_function(ratio);
				dest[i] = coef * output_buffers[0][i] + (1.0 - coef) * output_buffers[1][i];
				
				cxt->profile_switch_progress++;
			}
			
			if (cxt->profile_switch_progress >= cxt->profile_switch_samples)
				switch_complete = 1;
		}
		
		if (switch_complete)
		{
			cxt->active_profile = cxt->new_profile;
			cxt->profiles_switching = 0;
		}
		
		release_buffer(output_buffers[0]);
		release_buffer(output_buffers[1]);
	}
	else
	{
		profile_process(active_profile, dest, src);
	}
	
	i2s_output_transmit_mono_float(dest);
	i2s_output_update();
	
	avg_roundtrip_duration_micros = avg_roundtrip_duration_micros * AVG_DURATION_UPDATE_COEF + (start_time - last_runtime) * (1.0 - AVG_DURATION_UPDATE_COEF);
	last_runtime = start_time;
	
	end_time = micros();
	avg_compute_duration_micros = avg_compute_duration_micros * AVG_DURATION_UPDATE_COEF + ((float)(end_time - start_time)) * (1.0 - AVG_DURATION_UPDATE_COEF);
	
	runs++;
	
	if (runs % 256 == 0)
	{
	#ifdef PRINT_TIMES
		tm_printf("compute duration: %6fms. average compute duration: %6fms. average round-trip duration: %6fms. Compute takes %03f%% of round-trip\n",
			(float)(end_time - start_time) * 0.001, avg_compute_duration_micros * 0.001, avg_roundtrip_duration_micros * 0.001,
			(avg_roundtrip_duration_micros == 0.0) ? 0 : 100.0 * (avg_compute_duration_micros/avg_roundtrip_duration_micros));
	#endif
	}

	
	release_buffer(src);
	release_buffer(dest);

	asm("DSB");
	
	return NO_ERROR;

panic_bypass:
	if (src)
		release_buffer(src);
	if (dest)
		release_buffer(dest);
	
	if (output_buffers[0])
		release_buffer(output_buffers[0]);
	
	if (output_buffers[1])
		release_buffer(output_buffers[1]);
	
	tm_printf("alloc fail!!\n");
	i2s_output_transmit_mono_int(block);
	asm("DSB");
	return ERR_NULL_PTR;
}

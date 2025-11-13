#include "m_eng.h"

static const char *FNAME = "m_eng_context.c";

int init_m_eng_context(m_eng_context *cxt)
{
	FUNCTION_START();

	if (!cxt)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	
	int ret_val = NO_ERROR;
	cxt->profile_array_size = PROFILE_ARRAY_INITIAL_SIZE;
	
	do {
		cxt->profiles = (m_eng_profile*)malloc(sizeof(m_eng_profile) * cxt->profile_array_size);
		if (!cxt->profiles)
			cxt->profile_array_size /= 2;
	} while (!cxt->profiles && cxt->profile_array_size);
	
	if (!cxt->profiles)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}
	
	for (int i = 0; i < cxt->profile_array_size; i++)
		nullify_profile(&cxt->profiles[i]);
	
	init_profile(&cxt->profiles[0]);
	cxt->n_profiles = 1;
	cxt->active_profile = 0;
	cxt->profiles[0].active = 1;
	
	cxt->status_flags = M_STATUS_FRESH_BOOT;
	
	cxt->profile_switch_triggered 	= 0;
	cxt->profiles_switching 		= 0;
	cxt->profile_switch_progress 	= 0;
	cxt->profile_switch_type  		= TRANSITION_MONOBLOCK_COS2;
	
	cxt->new_profile = 0;
	
	for (int i = 0; i < DECLICK_BUFSIZE; i++)
		cxt->declick_buffer[i] = 0.0;
	
	cxt->profile_maintainance_index = 0;
	
	init_low_pass_filter_str(&cxt->input_lpf);
	cxt->input_lpf.cutoff_frequency.value = 20000.0;
	reconfigure_low_pass_filter(&cxt->input_lpf);
	
	init_high_pass_filter_str(&cxt->output_hpf);
	cxt->output_hpf.cutoff_frequency.value = 5.0;
	reconfigure_high_pass_filter(&cxt->output_hpf);
	
	ret_val = init_transformer(&cxt->output_amp, TRANSFORMER_AMPLIFIER);
	
	((m_eng_amplifier_str*)cxt->output_amp.data_struct)->mode.value 	= M_ENG_AMPLIFIER_DB;
	((m_eng_amplifier_str*)cxt->output_amp.data_struct)->gain.value 	= -90.0;
	((m_eng_amplifier_str*)cxt->output_amp.data_struct)->gain.old_value = -90.0;
	((m_eng_amplifier_str*)cxt->output_amp.data_struct)->gain.new_value = -90.0;
	((m_eng_amplifier_str*)cxt->output_amp.data_struct)->gain.updated 	= 1;
	
	cxt->runs = 0;
	
	RETURN_ERR_CODE(ret_val);
}

/* Returns error codes in negative; otherwise, returns the index (ID) of the new profile */
int m_eng_context_new_profile(m_eng_context *cxt)
{
	FUNCTION_START();

	if (!cxt)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	// Do I need a " - 1" here? I don't think so. But, if I get random crashes later, revisit this
	if (cxt->n_profiles >= cxt->profile_array_size)
	{
		int try_size = PROFILES_MALLOC_CHUNK_SIZE;
		m_eng_profile *new_ptr = NULL;
		
		do
		{
			new_ptr = (m_eng_profile*)malloc(sizeof(m_eng_profile) * (cxt->profile_array_size + try_size));
			if (!new_ptr)
				try_size /= 2;
		} while (!new_ptr && try_size);
		
		if (!new_ptr)
		{
			RETURN_NEG_ERR_CODE(ERR_ALLOC_FAIL);
		}
		
		memcpy(new_ptr, cxt->profiles, sizeof(m_eng_profile) * (cxt->profile_array_size));
		free(cxt->profiles);
		cxt->profiles = new_ptr;
		cxt->profile_array_size += try_size;
		
		for (int i = cxt->n_profiles; i < cxt->profile_array_size; i++)
			nullify_profile(&cxt->profiles[i]);
	}
	
	init_profile(&cxt->profiles[cxt->n_profiles++]);
	
	RETURN_INT(cxt->n_profiles - 1);
}

int cxt_profile_id_valid(m_eng_context *cxt, uint16_t pid)
{
	FUNCTION_START();

	if (!cxt)
	{
		RETURN_INT(0);
	}
	
	RETURN_INT(pid <= (unsigned int)cxt->n_profiles);
}

int cxt_transformer_id_valid(m_eng_context *cxt, uint16_t pid, uint16_t tid)
{
	FUNCTION_START();

	if (!cxt_profile_id_valid(cxt, pid))
	{
		RETURN_INT(0);
	}
	
	if (tid >= (unsigned int)cxt->profiles[pid].back_pipeline->n_transformers)
	{
		RETURN_INT(0);
	}
	
	RETURN_INT(pipeline_get_transformer_by_id(cxt->profiles[pid].back_pipeline, tid) != NULL);
}

int pcxt_profile_id_valid(m_eng_context *cxt, uint16_t pid, uint16_t tid, uint16_t ppid)
{
	FUNCTION_START();

	if (!cxt_transformer_id_valid(cxt, pid, tid))
	{
		RETURN_INT(0);
	}
	
	m_transformer *trans = pipeline_get_transformer_by_id(cxt->profiles[pid].back_pipeline, tid);
	
	if (!trans)
	{
		RETURN_INT(0);
	}
	
	RETURN_INT(trans->n_parameters >= ppid && trans->parameters[ppid]);
}


m_parameter *cxt_get_parameter_by_id(m_eng_context *cxt, uint16_t pid, uint16_t tid, uint16_t ppid)
{
	FUNCTION_START();
	
	if (!cxt)
	{
		RETURN_PTR(NULL);
	}
	
	if (pid == 0xFFFF)
	{
		switch (ppid)
		{
			case 0:
				if (cxt->output_amp.data_struct)
				{
					RETURN_PTR(&((m_eng_amplifier_str*)cxt->output_amp.data_struct)->gain);
				}
				
			default:
				RETURN_PTR(NULL);
		}
	}
	
	if (pid >= cxt->n_profiles)
	{
		RETURN_PTR(NULL);
	}
	
	if (tid == 0xFFFF)
	{
		switch (ppid)
		{
			case 0:
				if (cxt->profiles[pid].output_amp.data_struct)
				{
					RETURN_PTR(&((m_eng_amplifier_str*)cxt->profiles[pid].output_amp.data_struct)->gain);
				}
				
				RETURN_PTR(NULL);
			
			default:
				RETURN_PTR(NULL);
		}
	}
	
	m_transformer *trans = pipeline_get_transformer_by_id(cxt->profiles[pid].front_pipeline, tid);
	
	if (!trans)
	{
		RETURN_PTR(NULL);
	}
	
	if (ppid >= trans->n_parameters)
	{
		RETURN_PTR(NULL);
	}
	
	RETURN_PTR(trans->parameters[ppid]);
}

m_parameter *cxt_get_front_parameter_by_id(m_eng_context *cxt, uint16_t pid, uint16_t tid, uint16_t ppid)
{
	FUNCTION_START();
	
	if (!cxt)
	{
		RETURN_PTR(NULL);
	}
	
	if (pid >= cxt->n_profiles)
	{
		RETURN_PTR(NULL);
	}
	
	m_transformer *trans = pipeline_get_transformer_by_id(cxt->profiles[pid].front_pipeline, tid);
	
	if (!trans)
	{
		RETURN_PTR(NULL);
	}
	
	if (ppid >= trans->n_parameters)
	{
		RETURN_PTR(NULL);
	}
	
	RETURN_PTR(trans->parameters[ppid]);
}

m_parameter *cxt_get_back_parameter_by_id(m_eng_context *cxt, uint16_t pid, uint16_t tid, uint16_t ppid)
{
	FUNCTION_START();
	
	if (!cxt)
	{
		RETURN_PTR(NULL);
	}
	
	if (pid >= cxt->n_profiles)
	{
		RETURN_PTR(NULL);
	}
	
	m_transformer *trans = pipeline_get_transformer_by_id(cxt->profiles[pid].back_pipeline, tid);
	
	if (!trans)
	{
		RETURN_PTR(NULL);
	}
	
	if (ppid >= trans->n_parameters)
	{
		RETURN_PTR(NULL);
	}
	
	RETURN_PTR(trans->parameters[ppid]);
}

int cxt_update_parameter_value_by_id(m_eng_context *cxt, uint16_t pid, uint16_t tid, uint16_t ppid, float new_value)
{
	FUNCTION_START();

	if (!cxt)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (pid == 0xFFFF || tid == 0xFFFF)
	{
		m_parameter *param = cxt_get_parameter_by_id(cxt, pid, tid, ppid);
		
		if (!param)
		{
			RETURN_ERR_CODE(ERR_INVALID_PARAMETER_ID);
		}
		
		param->new_value = new_value;
		param->updated = 1;
		
		RETURN_ERR_CODE(NO_ERROR);
	}
	
	if (pid >= cxt->n_profiles)
	{
		RETURN_ERR_CODE(ERR_INVALID_PROFILE_ID);
	}
	
	m_transformer *front_trans = pipeline_get_transformer_by_id(cxt->profiles[pid].front_pipeline, tid);
	
	if (!front_trans)
	{
		RETURN_ERR_CODE(ERR_INVALID_TRANSFORMER_ID);
	}
	
	m_transformer *back_trans = pipeline_get_transformer_by_id(cxt->profiles[pid].back_pipeline, tid);
	
	m_parameter *front_param = transformer_get_parameter(front_trans, ppid);
	
	if (!front_param)
	{
		RETURN_ERR_CODE(ERR_INVALID_PARAMETER_ID);
	}
	
	m_parameter *back_param = transformer_get_parameter(back_trans, ppid);
	
	if (cxt->profiles[pid].active)
	{
		front_param->new_value = new_value;
		front_param->updated = 1;
		
		if (cxt->profiles[pid].pipelines_swapping && back_param)
		{
			back_param->new_value = new_value;
			back_param->updated = 1;
		}
		else if (back_param)
		{
			back_param->value = new_value;
			back_param->updated = 0;
		}
		else
		{
			RETURN_ERR_CODE(ERR_INCONSISTENT_BACK_PIPELINE);
		}
	}
	else
	{
		front_param->new_value = new_value;
		front_param->old_value = new_value;
		front_param->value = new_value;
		front_param->updated = 1;
		if (back_param)
		{
			back_param->new_value = new_value;
			back_param->old_value = new_value;
			back_param->value = new_value;
			back_param->updated = 1;
		}
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

m_setting *cxt_get_setting_by_id(m_eng_context *cxt, uint16_t pid, uint16_t tid, uint16_t sid)
{
	FUNCTION_START();
	
	if (!cxt)
	{
		RETURN_PTR(NULL);
	}
	
	if (pid >= cxt->n_profiles)
	{
		RETURN_PTR(NULL);
	}
	
	m_transformer *trans = pipeline_get_transformer_by_id(cxt->profiles[pid].back_pipeline, tid);
	
	RETURN_PTR(transformer_get_setting(trans, sid));
}

int cxt_update_setting_value_by_id(m_eng_context *cxt, uint16_t pid, uint16_t tid, uint16_t sid, uint16_t new_value)
{
	FUNCTION_START();

	if (!cxt)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (pid >= cxt->n_profiles)
	{
		RETURN_ERR_CODE(ERR_INVALID_PROFILE_ID);
	}
	
	m_pipeline_mod mod = create_pipeline_mod_change_transformer_setting(tid, sid, new_value);
	
	RETURN_ERR_CODE(profile_apply_pipeline_mod(&cxt->profiles[pid], mod));
}

void m_eng_safe_reboot(m_eng_context *cxt)
{
	FUNCTION_START();

	m_printf("Rebooting...\n");
	#ifndef M_SIMULATED
	_reboot_Teensyduino_(); //rofl
	#else
	
	#endif
	
	RETURN_VOID();
}

int reset_context(m_eng_context *cxt)
{
	FUNCTION_START();

	RETURN_ERR_CODE(ERR_UNIMPLEMENTED);
	
	if (!cxt)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

int cxt_append_transformer_to_profile(m_eng_context *cxt, uint16_t pid, uint16_t type)
{
	FUNCTION_START();

	if (!cxt)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (pid > cxt->n_profiles)
	{
		RETURN_NEG_ERR_CODE(ERR_BAD_ARGS);
	}
	
	int ret_val = profile_apply_pipeline_mod(&cxt->profiles[pid], create_pipeline_mod_append_transformer(type));
	
	if (ret_val < 0)
	{
		RETURN_ERR_CODE(-ret_val);
	}
	
	
	RETURN_INT(ret_val);
}

int cxt_remove_transformer_from_profile(m_eng_context *cxt, uint16_t pid, uint16_t tid)
{
	FUNCTION_START();

	m_printf("cxt_remove_transformer_from_profile...\n");
	if (!cxt)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (pid > cxt->n_profiles)
	{
		RETURN_NEG_ERR_CODE(ERR_BAD_ARGS);
	}
	
	int ret_val = profile_apply_pipeline_mod(&cxt->profiles[cxt->active_profile], create_pipeline_mod_remove_transformer(tid));
	
	m_printf("cxt_remove_transformer_from_profile done. ret_val = %s\n", m_error_code_to_string(ret_val));
	RETURN_ERR_CODE(ret_val);
}

int cxt_move_transformer(m_eng_context *cxt, uint16_t tid, uint16_t new_pos)
{
	FUNCTION_START();

	if (!cxt)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	int ret_val = profile_apply_pipeline_mod(&cxt->profiles[cxt->active_profile], create_pipeline_mod_move_transformer(tid, new_pos));
	
	RETURN_ERR_CODE(ret_val);
}

int cxt_insert_transformer_to_profile(m_eng_context *cxt, uint16_t pid, uint16_t type, uint16_t pos)
{
	FUNCTION_START();

	if (!cxt)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (pid > cxt->n_profiles)
	{
		RETURN_NEG_ERR_CODE(ERR_BAD_ARGS);
	}
	
	int ret_val = pipeline_insert_transformer_type(cxt->profiles[pid].back_pipeline, type, pos);
	
	RETURN_ERR_CODE(ret_val);
}

int cxt_prepend_transformer_to_profile(m_eng_context *cxt, uint16_t pid, uint16_t type)
{
	FUNCTION_START();

	if (!cxt)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (pid > cxt->n_profiles)
	{
		RETURN_NEG_ERR_CODE(ERR_BAD_ARGS);
	}
	
	int ret_val = pipeline_prepend_transformer_type(cxt->profiles[pid].back_pipeline, type);
	
	RETURN_ERR_CODE(ret_val);
}

int cxt_get_n_profile_transformers(m_eng_context *cxt, uint16_t pid)
{
	FUNCTION_START();

	if (!cxt)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (cxt->n_profiles <= pid)
	{
		RETURN_NEG_ERR_CODE(ERR_BAD_ARGS);
	}
	
	RETURN_INT(cxt->profiles[pid].back_pipeline->n_transformers);
}

int cxt_get_n_transformer_params(m_eng_context *cxt, uint16_t pid, uint16_t tid)
{
	FUNCTION_START();

	if (!cxt)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_transformer *trans = cxt_get_transformer_by_id(cxt, pid, tid);
	
	if (!trans)
	{
		RETURN_NEG_ERR_CODE(ERR_BAD_ARGS);
	}
	
	RETURN_INT(trans->n_parameters);
}

int cxt_get_n_transformer_settings(m_eng_context *cxt, uint16_t pid, uint16_t tid)
{
	FUNCTION_START();

	if (!cxt)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_transformer *trans = cxt_get_transformer_by_id(cxt, pid, tid);
	
	if (!trans)
	{
		RETURN_NEG_ERR_CODE(ERR_BAD_ARGS);
	}
	
	RETURN_INT(trans->n_settings);
}

int cxt_get_transformer_type(m_eng_context *cxt, uint16_t pid, uint16_t tid)
{
	FUNCTION_START();

	if (!cxt)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_transformer *trans = cxt_get_transformer_by_id(cxt, pid, tid);
	
	if (!trans)
	{
		RETURN_NEG_ERR_CODE(ERR_BAD_ARGS);
	}
	
	RETURN_INT(trans->type);
}


int cxt_get_tid_by_pos(m_eng_context *cxt, uint16_t pid, uint16_t pos)
{
	FUNCTION_START();

	if (!cxt)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (pid >= cxt->n_profiles)
	{
		RETURN_NEG_ERR_CODE(ERR_BAD_ARGS);
	}
	
	if (pos >= cxt->profiles[pid].back_pipeline->n_transformers)
	{
		RETURN_NEG_ERR_CODE(ERR_BAD_ARGS);
	}
	
	if (!cxt->profiles[pid].back_pipeline->transformers[pos])
	{
		RETURN_NEG_ERR_CODE(ERR_BAD_ARGS);
	}
	
	RETURN_INT(cxt->profiles[pid].back_pipeline->transformers[pos]->id);
}

m_transformer *cxt_get_transformer_by_id(m_eng_context *cxt, uint16_t pid, uint16_t tid)
{
	FUNCTION_START();
	
	if (!cxt)
	{
		RETURN_PTR(NULL);
	}
	
	if (pid >= cxt->n_profiles)
	{
		RETURN_PTR(NULL);
	}
	
	RETURN_PTR(pipeline_get_transformer_by_id(cxt->profiles[pid].back_pipeline, tid));
}

int cxt_set_active_profile(m_eng_context *cxt, uint16_t pid)
{
	FUNCTION_START();

	if (!cxt)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	cxt->active_profile = pid;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int cxt_switch_to_profile(m_eng_context *cxt, uint16_t pid)
{
	FUNCTION_START();

	if (!cxt)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (pid == cxt->active_profile)
	{
		RETURN_ERR_CODE(NO_ERROR);
	}
	
	if (pid >= cxt->n_profiles)
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	m_printf("Switching to profile %d\n");
	cxt->profile_switch_triggered = 1;
	cxt->new_profile = pid;
	cxt->profile_switch_progress = 0;
	cxt->profile_switch_type = binary_max(cxt->profiles[pid].transition_policy, cxt->profiles[cxt->active_profile].transition_policy);
	
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
	
	RETURN_ERR_CODE(NO_ERROR);
}

#define AVG_DURATION_UPDATE_COEF 0.99f

int cxt_process(m_eng_context *cxt)
{
	FUNCTION_START();
	
	#ifndef M_SIMULATED
	static uint32_t last_runtime = 0;
	uint32_t end_time;
	
	if (!last_runtime)
		last_runtime = micros();
	#else
	
	#endif
	
	
	int16_t block[AUDIO_BLOCK_SAMPLES];
	uint8_t click_buffer[AUDIO_BLOCK_SAMPLES + DECLICK_BUFSIZE - 1];
	
	static float avg_roundtrip_duration_micros 	= 0.0;
	static float avg_compute_duration_micros 	= 0.0;
	
	float s1, s2;
	
	#ifndef M_SIMULATED
	i2s_input_update();
	#else
	
	#endif
	
	if (cxt->profile_switch_triggered)
	{
		cxt->profiles_switching 	  = 1;
		cxt->profile_switch_progress  = 0;
		cxt->profile_switch_triggered = 0;
	}
	
	m_eng_profile *active_profile = &cxt->profiles[cxt->active_profile];
	
	float *src  = NULL;
	float *tmp  = NULL;
	float *dest = NULL;
	
	float *input_buffers [2] = {NULL, NULL};
	float *output_buffers[2] = {NULL, NULL};
	
	float ratio;
	
	#ifndef M_SIMULATED
	uint32_t start_time = micros();
	#else
	
	#endif
	
	if (!(src  = allocate_buffer())) goto panic_bypass;
	if (!(tmp  = allocate_buffer())) goto panic_bypass;
	if (!(dest = allocate_buffer())) goto panic_bypass;
	
	#ifndef M_SIMULATED
	convert_block_int_to_float(tmp, i2s_input_blocks[1]);
	#else
	m_sim_get_input_block(tmp);
	
	/*m_printf("Obtained simulated input block:\n");
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		m_printf("%s%.04f%s", (tmp[i] >= 0.0) ? " " : "", tmp[i], ((i+1) % 32 == 0) ? "\n" : " ");
	}*/
	#endif
	
	calc_low_pass_filter(&cxt->input_lpf, src, tmp, AUDIO_BLOCK_SAMPLES);
	
	
	if (cxt->profiles_switching)
	{
		m_eng_profile *new_profile = &cxt->profiles[cxt->new_profile];
		
		new_profile->active = 1;
		
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
			cxt->profiles[cxt->active_profile].active = 0;
			cxt->active_profile = cxt->new_profile;
			cxt->profiles[cxt->active_profile].active = 1;
			cxt->profiles_switching = 0;
		}
		
		release_buffer(output_buffers[0]);
		release_buffer(output_buffers[1]);
	}
	else
	{
		profile_process(active_profile, dest, src);
	}
	
	calc_high_pass_filter(&cxt->output_hpf, tmp, dest, AUDIO_BLOCK_SAMPLES);
	
	run_transformer(&cxt->output_amp, dest, tmp);
	
	// Finally, clamp the results to [-1, 1]
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		dest[i] = (dest[i] < -1.0) ? -1.0 : ((dest[i] > 1.0) ? 1.0 : dest[i]);
	
	#ifndef M_SIMULATED
	i2s_output_transmit_mono_float(dest);
	i2s_output_update();
	
	avg_roundtrip_duration_micros = avg_roundtrip_duration_micros * AVG_DURATION_UPDATE_COEF + (start_time - last_runtime) * (1.0 - AVG_DURATION_UPDATE_COEF);
	last_runtime = start_time;
	
	end_time = micros();
	avg_compute_duration_micros = avg_compute_duration_micros * AVG_DURATION_UPDATE_COEF + ((float)(end_time - start_time)) * (1.0 - AVG_DURATION_UPDATE_COEF);
	
	if (cxt->runs % 256 == 0)
	{
	#ifdef PRINT_TIMES
		m_printf("compute duration: %6fms. average compute duration: %6fms. average round-trip duration: %6fms. Compute takes %03f%% of round-trip\n",
			(float)(end_time - start_time) * 0.001, avg_compute_duration_micros * 0.001, avg_roundtrip_duration_micros * 0.001,
			(avg_roundtrip_duration_micros == 0.0) ? 0 : 100.0 * (avg_compute_duration_micros/avg_roundtrip_duration_micros));
	#endif
	}

	#else
	m_sim_get_output_block(dest);
	#endif
	
	memcpy(cxt->prev_block, src, AUDIO_BLOCK_SAMPLES * sizeof(float));
	
	release_buffer(src);
	release_buffer(tmp);
	release_buffer(dest);

	#ifndef M_SIMULATED
	asm("DSB");
	#endif
	
	RETURN_ERR_CODE(NO_ERROR);

panic_bypass:
	if (src)  release_buffer(src);
	if (tmp)  release_buffer(tmp);
	if (dest) release_buffer(dest);
	
	if (output_buffers[0]) release_buffer(output_buffers[0]);
	if (output_buffers[1]) release_buffer(output_buffers[1]);
	
	m_printf("cxt_process: alloc fail!!\n");
	
	#ifndef M_SIMULATED
	i2s_output_transmit_mono_int(block);
	asm("DSB");
	#else
	
	#endif
	RETURN_ERR_CODE(ERR_ALLOC_FAIL);
}

// A function periodically, relatively infrequently called
// which goes through and checks the states of profiles
// and fixes any errors that have crept in. This 
// may be heavy, so it only does one at a time,
// then ticks a counter so that it goes through all
// of them, eventually, every so often
int cxt_run_scheduled_maintainance(m_eng_context *cxt)
{
	FUNCTION_START();

	if (!cxt)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	// Ensure the profile exists
	cxt->profile_maintainance_index = cxt->profile_maintainance_index % cxt->n_profiles;
	
	// Perform the maintainance
	int ret_val = profile_scheduled_maintainance(&cxt->profiles[cxt->profile_maintainance_index]);
	
	// Increment the index counter
	cxt->profile_maintainance_index = (cxt->profile_maintainance_index + 1) % cxt->n_profiles;
	
	RETURN_ERR_CODE(ret_val);
}

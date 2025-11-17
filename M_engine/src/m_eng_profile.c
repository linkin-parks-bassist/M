#include "m_eng.h"

static const char *FNAME = "m_eng_profile.c";

int nullify_profile(m_eng_profile *profile)
{
	FUNCTION_START();

	if (!profile)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	profile->front_pipeline = NULL;
	profile->back_pipeline 	= NULL;
	
	profile->pipelines_swapping 	 = 0;
	profile->pipeline_swap_progress  = 0;
	profile->pipeline_swap_samples 	 = 0;
	profile->pipeline_swap_type 	 = 0;
	
	profile->transition_policy = TRANSITION_MONOBLOCK_COS2;
	
	profile->jobs  = NULL;
	profile->blocked_jobs = NULL;
	
	profile->active = 0;
	
	profile->runs = 0;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int init_profile(m_eng_profile *profile)
{
	FUNCTION_START();

	if (!profile)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	profile->back_pipeline = NULL;
	
	profile->front_pipeline = (m_pipeline*)m_alloc(sizeof(m_pipeline));
	
	if (!profile->front_pipeline)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}
	
	profile->back_pipeline = (m_pipeline*)m_alloc(sizeof(m_pipeline));
	
	if (!profile->back_pipeline)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}
	
	init_pipeline(profile->front_pipeline);
	init_pipeline(profile->back_pipeline);
	
	profile->pipelines_swapping 	 = 0;
	profile->pipeline_swap_progress  = 0;
	profile->pipeline_swap_samples 	 = 0;
	profile->pipeline_swap_type 	 = 0;
	
	profile->transition_policy = TRANSITION_MONOBLOCK_COS2;
	
	profile->jobs  = NULL;
	profile->blocked_jobs = NULL;
	
	profile->prev_block = allocate_buffer();
	
	if (!profile->prev_block)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}
	
	profile->active = 0;
	
	memset(profile->prev_block, 0, AUDIO_BLOCK_SAMPLES);
	
	int ret_val = init_transformer(&profile->output_amp, TRANSFORMER_AMPLIFIER);
	
	m_printf("init profile complete. amp->gain.updated = %d\n", ((m_eng_amplifier_str*)profile->output_amp.data_struct)->gain.updated);
	
	RETURN_ERR_CODE(ret_val);
}


int profile_print_job_list(m_eng_profile *profile)
{
	FUNCTION_START();

	m_printf("Printing job list.\n");
	
	int i = 0;
	m_pipeline_mod_ll *current = profile->jobs;
	
	while (current)
	{
		m_printf("Job %i: ", i);
		switch (current->data.type)
		{
			case PIPELINE_MOD_APPEND_TRANSFORMER:
				m_printf("append transformer of type %d\n", current->data.data);
				break;
			
			
			case PIPELINE_MOD_MOVE_TRANSFORMER:
				m_printf("move transformer %d to position %d\n", current->data.tid, current->data.data);
				break;
			
			case PIPELINE_MOD_REMOVE_TRANSFORMER:
				m_printf("remove transformer %d\n", current->data.tid);
				break;
			
			case PIPELINE_MOD_CHANGE_TRANSFORMER_SETTING:
				m_printf("change setting %d.%d to %d\n", current->data.tid, current->data.data, current->data.sdata);
				break;
				
			default:
				m_printf("ERROR! Unrecognised job %d\n", current->data.type);
				break;
		}
		current = current->next;
		i++;
	}
	
	m_printf("Done\n");
	RETURN_ERR_CODE(NO_ERROR);
}

int profile_print_ujob_list(m_eng_profile *profile)
{
	FUNCTION_START();

	m_printf("Printing ujob list.\n");
	
	int i = 0;
	m_pipeline_mod_ll *current = profile->blocked_jobs;
	
	while (current)
	{
		m_printf("Job %i: ", i);
		switch (current->data.type)
		{
			case PIPELINE_MOD_APPEND_TRANSFORMER:
				m_printf("append transformer of type %d\n", current->data.data);
				break;
			
			
			case PIPELINE_MOD_MOVE_TRANSFORMER:
				m_printf("move transformer %d to position %d\n", current->data.tid, current->data.data);
				break;
			
			case PIPELINE_MOD_CHANGE_TRANSFORMER_SETTING:
				m_printf("change setting %d.%d to %d\n", current->data.tid, current->data.data, current->data.sdata);
				break;
				
			default:
				m_printf("ERROR! Unrecognised job %d\n", current->data.type);
				break;
		}
		current = current->next;
		i++;
	}
	
	m_printf("Done\n");
	
	RETURN_ERR_CODE(NO_ERROR);
}

/**
 * @brief Applies the given modification to the given profile
 * 
 * If the current profile is active, to prevent audio artifacts, pipeline modifications
 * ("mods", encoded by #m_pipeline_mod) are applied in the background - to an inactive
 * copy of the profile's pipeline (the "back pipeline"), and the outputs from the front
 * and back pipeline are smoothly cross-faded between, after which it can be safely
 * applied to the (now back, previously front) pipeline, keeping the two in sync.
 * 
 * To achieve this, #profile_apply_pipeline_mod calls #apply_pipeline_mod to apply
 * the mod to the back pipeline,  calls #profile_trigger_pipeline_swap to trigger 
 * the pipeline swap, and saves the mod in a linked list (\ref m_eng_profile::jobs).
 * After the swap is complete, #profile_update will retrieve the job from the list
 * and apply it to the back (previously front) pipeline.
 * 
 * If, however, when #profile_apply_pipeline_mod is called, a pipeline swap is already
 * in progress, the mod is *not* applied, but rather stored in a second linked list,
 * (\ref m_eng_profile::blocked_jobs), whereupon #profile_update will apply it (after
 * the swap is finished and any jobs waiting in (\ref m_eng_profile::jobs) have been
 * applied) by calling #profile_apply_pipeline_mod.
 * 
 * @param profile The profile to be modified
 * @param mod A struct describing the modification to apply
 */

int profile_apply_pipeline_mod(m_eng_profile *profile, m_pipeline_mod mod)
{
	FUNCTION_START();

	m_printf("profile_apply_pipeline_mod %s on run %d\n", pipeline_mod_type_string(mod.type), profile->runs);
	if (!profile)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_pipeline_mod_ll *nl;
	int err_code = NO_ERROR;
	int ret_val = NO_ERROR;
	
	if (!profile->active)
	{
		m_printf("Profile is not active; apply willy-nilly\n");
		ret_val = apply_pipeline_mod(profile->front_pipeline, mod, &err_code);
		
		if (err_code != NO_ERROR)
		{
			RETURN_ERR_CODE(err_code);
		}
		
		apply_pipeline_mod(profile->back_pipeline, mod, &err_code);
		
		if (err_code != NO_ERROR)
		{
			RETURN_ERR_CODE(err_code);
		}
		
		RETURN_INT(ret_val);
	}
	
	if (!profile->pipelines_swapping)
	{
		m_printf("Profile is active; pipelines are not swapping. Apply with care\n");
		ret_val = apply_pipeline_mod(profile->back_pipeline, mod, &err_code);
		
		if (err_code != NO_ERROR)
		{
			RETURN_ERR_CODE(err_code);
		}
		
		profile->transition_policy = binary_max(profile->front_pipeline->transition_policy, profile->back_pipeline->transition_policy);
		profile_trigger_pipeline_swap(profile);
		
		nl = m_pipeline_mod_ll_append(profile->jobs, mod);
		if (nl)
		{
			profile->jobs = nl;
		}
		else
		{
			RETURN_ERR_CODE(ERR_ALLOC_FAIL);
		}
	}
	else
	{
		m_printf("Profile is active and pipelines are swapping. Log to apply later\n");
		nl = m_pipeline_mod_ll_append(profile->blocked_jobs, mod);
		if (nl)
		{
			profile->blocked_jobs = nl;
		}
		else
		{
			printf("Failed: cannot appent pipeline mod; alloc failure\n");
			RETURN_ERR_CODE(ERR_ALLOC_FAIL);
		}
		
		profile_print_ujob_list(profile);
	}
	
	RETURN_INT(ret_val);
}

int profile_update(m_eng_profile *profile)
{
	FUNCTION_START();

	if (!profile)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_pipeline_mod_ll *next;
	
	int err_code;
	
	if (!profile->pipelines_swapping)
	{
		if (profile->jobs)
		{
			profile_print_job_list(profile);
		}
		
		while (profile->jobs)
		{
			apply_pipeline_mod(profile->back_pipeline, profile->jobs->data, &err_code);
			next = profile->jobs->next;
			m_free(profile->jobs);
			profile->jobs = next;
		}
		
		if (profile->blocked_jobs)
		{
			profile_print_ujob_list(profile);
			profile_apply_pipeline_mod(profile, profile->blocked_jobs->data);
			next = profile->blocked_jobs->next;
			m_free(profile->blocked_jobs);
			profile->blocked_jobs = next;
		}
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

int profile_process(m_eng_profile *profile, float *dest, float *src)
{
	FUNCTION_START();
	
	if (!profile || !dest || !src)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (!profile->front_pipeline)
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	int ret_val, ret_val_2;
	
	int run_amp = 1;
	
	float *local_dest = allocate_buffer();
	
	if (!local_dest)
	{
		run_amp = 0;
		local_dest = dest;
	}
	
	if (profile->pipelines_swapping)
	{	
		//printf("pipelines swapping! swap type = %d, n_samples = %d, progress = %d\n", profile->pipeline_swap_type, profile->pipeline_swap_samples, profile->pipeline_swap_progress);
		if (!profile->back_pipeline)
		{
			//m_printf("ERROR: Back pipeline doesn't exist!!\n");
			RETURN_ERR_CODE(ERR_BAD_ARGS);
		}
		
		/*if (!profile->back_pipeline_warmed_up)
		{
			float *tmp = allocate_buffer();
			if (tmp)
			{
				compute_pipeline(profile->back_pipeline, tmp, profile->prev_block);
				profile->back_pipeline_warmed_up = 1;
				
				release_buffer(tmp);
			}
			else
			{
				m_printf("Could allocate temporary buffer to warm up back pipeline!\n");
			}
		}*/
		
		int swap_complete = 0;
		
		float *input_buffers [2] = {src, src};
		float *output_buffers[2] = {allocate_buffer(), allocate_buffer()};
		
		if (!output_buffers[0])
		{
			if (output_buffers[1])
				release_buffer(output_buffers[1]);
			RETURN_ERR_CODE(ERR_ALLOC_FAIL);
		}
		if (!output_buffers[1])
		{
			release_buffer(output_buffers[0]);
			RETURN_ERR_CODE(ERR_ALLOC_FAIL);
		}
		
		float ratio;
		
		if (profile->pipeline_swap_type == TRANSITION_TAIL)
		{
			m_voice_printf(M_VOICE_PR, "YO! TAIL TRANSITION!\n");
			input_buffers[0] = allocate_buffer();
			
			if (!input_buffers[0])
			{
				release_buffer(output_buffers[0]);
				release_buffer(output_buffers[1]);
				RETURN_ERR_CODE(ERR_ALLOC_FAIL);
			}
			
			if (profile->pipeline_swap_progress > TAIL_INPUT_FADE_SAMPLES)
			{
				for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
					input_buffers[0][i] = 0.0;
			}
			else
			{
				for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
				{
					ratio = (float)(profile->pipeline_swap_progress + i) / (float)TAIL_INPUT_FADE_SAMPLES;
					input_buffers[0][i] = trig_transition_function(ratio) * src[i];
				}
			}
			
			ret_val   = compute_pipeline(profile->front_pipeline, output_buffers[0], input_buffers[0]);
			ret_val_2 = compute_pipeline(profile->back_pipeline,  output_buffers[1], input_buffers[1]);
			
			if (!(ret_val == NO_ERROR) && (ret_val_2 == NO_ERROR))
			{
				m_printf("ERROR: compute_pipeline ERROR CODES (%d, %d)\n", ret_val, ret_val_2);
			}
			
			float energy = 0.0;
			
			for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
				energy += sqr(output_buffers[0][i]);
			
			if (energy < SILENCE_ENERGY_THRESHOLD)
			{
				swap_complete = 1;
				memcpy(local_dest, output_buffers[1], AUDIO_BLOCK_SAMPLES * sizeof(float));
			}
			else
			{
				if (profile->pipeline_swap_progress < TAIL_NEW_FADE_IN_SAMPLES)
				{
					for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
						local_dest[i] = output_buffers[0][i] + (trig_transition_function((float)(profile->pipeline_swap_progress++) / TAIL_NEW_FADE_IN_SAMPLES) * output_buffers[1][i]);
				}
				else
				{
					for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
						local_dest[i] = output_buffers[0][i] + output_buffers[1][i];
					
					profile->pipeline_swap_progress += AUDIO_BLOCK_SAMPLES;
				}
			}
			
			release_buffer(input_buffers[0]);
		}
		else
		{
			ret_val   = compute_pipeline(profile->front_pipeline, output_buffers[0], input_buffers[0]);
			ret_val_2 = compute_pipeline(profile->back_pipeline,  output_buffers[1], input_buffers[1]);
			
			if (!(ret_val == NO_ERROR) && (ret_val_2 == NO_ERROR))
			{
				m_printf("ERROR: compute_pipeline ERROR CODES (%d, %d)\n", ret_val, ret_val_2);
			}
			
			float coef;
			for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
			{
				ratio = (float)(profile->pipeline_swap_progress) / (float)profile->pipeline_swap_samples;
				
				coef = trig_transition_function(ratio);
				
				local_dest[i] = coef * output_buffers[0][i] + (1.0 - coef) * output_buffers[1][i];
				profile->pipeline_swap_progress++;
			}
			
			if (profile->pipeline_swap_progress >= profile->pipeline_swap_samples)
				swap_complete = 1;
		}
		
		if (swap_complete)
		{
			m_pipeline *tmp = profile->front_pipeline;
			profile->front_pipeline = profile->back_pipeline;
			profile->back_pipeline = tmp;
			
			profile->pipelines_swapping = 0;
		}
		
		release_buffer(output_buffers[0]);
		release_buffer(output_buffers[1]);
	}
	else
	{
		if (local_dest)
			ret_val = compute_pipeline(profile->front_pipeline, local_dest, src);
		else
			ret_val = compute_pipeline(profile->front_pipeline, local_dest, src);
		
		if (ret_val != NO_ERROR)
		{
			m_printf("PIPELINE COMPUTATION ERROR %d\n", ret_val);
		}
	}
	
	memcpy(profile->prev_block, src, AUDIO_BLOCK_SAMPLES);
	
	if (run_amp)
	{
		
		run_transformer(&profile->output_amp, dest, local_dest);
		release_buffer(local_dest);
		
	}
	else
	{
		float g = powf(10, ((m_eng_amplifier_str*)profile->output_amp.data_struct)->gain.value / 20.0);
		for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
			dest[i] *= g;
		
		M_LOG_ERROR(ERR_ALLOC_FAIL);
	}
	
	profile->runs++;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int profile_trigger_pipeline_swap(m_eng_profile *profile)
{
	FUNCTION_START();

	m_printf("Initiating a pipeline swap\n");
	if (!profile)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	int transition_policy = profile->front_pipeline->transition_policy;
	if (profile->back_pipeline->transition_policy > transition_policy)
		transition_policy = profile->back_pipeline->transition_policy;
	
	printf("Transition policy: %d\n", transition_policy);
	
	switch (transition_policy)
	{
		case TRANSITION_QUADBLOCK_COS2:
			profile->pipeline_swap_samples = 4 * AUDIO_BLOCK_SAMPLES;
			break;
		
		case TRANSITION_OCTOBLOCK_COS2:
			profile->pipeline_swap_samples = 8 * AUDIO_BLOCK_SAMPLES;
			break;
		
		default:
			profile->pipeline_swap_samples = 2 * AUDIO_BLOCK_SAMPLES;
	}
	
	profile->pipeline_swap_progress = 0;
	profile->pipeline_swap_type = transition_policy;
	
	profile->pipelines_swapping = 1;
	profile->back_pipeline_warmed_up = 0;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int profile_regenerate_back_pipeline(m_eng_profile *profile)
{
	FUNCTION_START();

	if (!profile)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	clone_pipeline(&profile->back_pipeline, profile->front_pipeline);
	
	RETURN_ERR_CODE(NO_ERROR);
}

int profile_scheduled_maintainance(m_eng_profile *profile)
{
	FUNCTION_START();

	if (!profile)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	// If the profile is up to something, don't touch it
	if (profile->jobs || profile->blocked_jobs || profile->pipelines_swapping)
	{
		RETURN_ERR_CODE(NO_ERROR);
	}
	
	// If we are dealing with an active profile, prevent interruptions
	if (profile->active)
		m_eng_enable_software_interrupts();
	
	// If the back pipeline doesn't match the front pipeline, destroy it
	// and copy the front pipeline in its place
	if (pipeline_compare(profile->back_pipeline, profile->front_pipeline) != 0)
	{
		m_printf("Warning: inconsistent back pipeline detected in profile %p. Regenerating...\n", profile);
		profile_regenerate_back_pipeline(profile);
		m_printf("Done.\n");
	}
	
	// Run a recent block through the pipeline which may be activated
	// this keeps stateful transformers ready to give valid output should
	// they be called upon to, which smooths transitions
	if (profile->active)
		compute_pipeline(profile->back_pipeline, NULL, global_cxt.prev_block);
	else
		compute_pipeline(profile->front_pipeline, NULL, global_cxt.prev_block);
	
	m_eng_enable_software_interrupts();
	
	RETURN_ERR_CODE(NO_ERROR);
}

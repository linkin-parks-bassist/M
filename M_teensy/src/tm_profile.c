#include "tm.h"

static const char *FNAME = "tm_profile.c";

float trig_transition_function(float x)
{
	if (x > 1.0)
	{
		0.0;
	}
	if (x > 0.0)
	{
		float y = cos(1.57079632679 * x);
		return y * y;
	}
	
	1.0;
}

int nullify_profile(tm_profile *profile)
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
	profile->ujobs = NULL;
	
	profile->active = 0;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int init_profile(tm_profile *profile)
{
	FUNCTION_START();

	if (!profile)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	profile->back_pipeline = NULL;
	
	profile->front_pipeline = (tm_pipe_line*)malloc(sizeof(tm_pipe_line));
	
	if (!profile->front_pipeline)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}
	
	profile->back_pipeline = (tm_pipe_line*)malloc(sizeof(tm_pipe_line));
	
	if (!profile->back_pipeline)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}
	
	init_pipe_line(profile->front_pipeline);
	init_pipe_line(profile->back_pipeline);
	
	profile->pipelines_swapping 	 = 0;
	profile->pipeline_swap_progress  = 0;
	profile->pipeline_swap_samples 	 = 0;
	profile->pipeline_swap_type 	 = 0;
	
	profile->transition_policy = TRANSITION_MONOBLOCK_COS2;
	
	profile->jobs  = NULL;
	profile->ujobs = NULL;
	
	profile->prev_block = allocate_buffer();
	
	if (!profile->prev_block)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}
	
	profile->active = 0;
	
	memset(profile->prev_block, 0, AUDIO_BLOCK_SAMPLES);
	
	RETURN_ERR_CODE(NO_ERROR);
}


int profile_print_job_list(tm_profile *profile)
{
	FUNCTION_START();

	tm_printf("Printing job list.\n");
	
	int i = 0;
	tm_pipe_line_mod_linked_list *current = profile->jobs;
	
	while (current)
	{
		tm_printf("Job %i: ", i);
		switch (current->data.type)
		{
			case PIPE_LINE_MOD_APPEND_TRANSFORMER:
				tm_printf("append transformer of type %d\n", current->data.data);
				break;
			
			
			case PIPE_LINE_MOD_MOVE_TRANSFORMER:
				tm_printf("move transformer %d to position %d\n", current->data.tid, current->data.data);
				break;
			
			case PIPE_LINE_MOD_REMOVE_TRANSFORMER:
				tm_printf("remove transformer %d\n", current->data.tid);
				break;
			
			default:
				tm_printf("ERROR! Unrecognised job!\n");
				break;
		}
		current = current->next;
		i++;
	}
	
	tm_printf("Done\n");
	RETURN_ERR_CODE(NO_ERROR);
}

int profile_print_ujob_list(tm_profile *profile)
{
	FUNCTION_START();

	tm_printf("Printing ujob list.\n");
	
	int i = 0;
	tm_pipe_line_mod_linked_list *current = profile->ujobs;
	
	while (current)
	{
		tm_printf("Job %i: ", i);
		switch (current->data.type)
		{
			case PIPE_LINE_MOD_APPEND_TRANSFORMER:
				tm_printf("append transformer of type %d\n", current->data.data);
				break;
			
			
			case PIPE_LINE_MOD_MOVE_TRANSFORMER:
				tm_printf("move transformer %d to position %d\n", current->data.tid, current->data.data);
				break;
			
			default:
				tm_printf("ERROR! Unrecognised job!\n");
				break;
		}
		current = current->next;
		i++;
	}
	
	tm_printf("Done\n");
	
	RETURN_ERR_CODE(NO_ERROR);
}

int profile_apply_pipeline_mod(tm_profile *profile, tm_pipe_line_mod mod)
{
	FUNCTION_START();

	tm_printf("Applying a type %d pipeline mod\n", mod.type);
	if (!profile)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	tm_pipe_line_mod_linked_list *nl;
	int ret_val = NO_ERROR;
	
	if (!profile->active)
	{
		ret_val = apply_pipe_line_mod(profile->front_pipeline, mod);
		
		if (ret_val != NO_ERROR)
		{
			RETURN_ERR_CODE(ret_val);
		}
		
		ret_val = apply_pipe_line_mod(profile->back_pipeline, mod);
		
		RETURN_ERR_CODE(ret_val);
	}
	
	if (!profile->pipelines_swapping)
	{
		tm_printf("There is no pipeline swap occuring; safe to apply to back pipeline\n");
		ret_val = apply_pipe_line_mod(profile->back_pipeline, mod);
		
		tm_printf("Applied\n");
		profile_trigger_pipeline_swap(profile);
		
		profile->transition_policy = binary_max(profile->front_pipeline->transition_policy, profile->back_pipeline->transition_policy);
		
		nl = tm_pipe_line_mod_linked_list_append(profile->jobs, mod);
		if (nl)
		{
			profile->jobs = nl;
		}
		else
		{
			RETURN_ERR_CODE(ERR_ALLOC_FAIL);
		}
		
		profile_print_job_list(profile);
	}
	else
	{
		tm_printf("There is a pipeline swap occuring. I will log the job for later.\n");
		
		nl = tm_pipe_line_mod_linked_list_append(profile->ujobs, mod);
		if (nl)
		{
			profile->ujobs = nl;
		}
		else
		{
			RETURN_ERR_CODE(ERR_ALLOC_FAIL);
		}
		
		profile_print_ujob_list(profile);
	}
	
	tm_printf("Function returned\n");
	RETURN_ERR_CODE(ret_val);
}

int profile_update(tm_profile *profile)
{
	FUNCTION_START();

	if (!profile)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	int tps = (profile->ujobs != NULL);
	tm_pipe_line_mod_linked_list *next;
	
	if (!profile->pipelines_swapping)
	{
		while (profile->jobs)
		{
			apply_pipe_line_mod(profile->back_pipeline, profile->jobs->data);
			next = profile->jobs->next;
			free(profile->jobs);
			profile->jobs = next;
		}
		
		while (profile->ujobs)
		{
			apply_pipe_line_mod(profile->back_pipeline, profile->ujobs->data);
			next = profile->ujobs->next;
			free(profile->ujobs);
			profile->ujobs = next;
		}
		
		if (tps)
			profile_trigger_pipeline_swap(profile);
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

int profile_process(tm_profile *profile, float *dest, float *src)
{
	FUNCTION_START();

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
	
	if (profile->pipelines_swapping)
	{	
		//printf("pipelines swapping! swap type = %d, n_samples = %d, progress = %d\n", profile->pipeline_swap_type, profile->pipeline_swap_samples, profile->pipeline_swap_progress);
		if (!profile->back_pipeline)
		{
			tm_printf("ERROR: Back pipeline doesn't exist!!\n");
			RETURN_ERR_CODE(ERR_BAD_ARGS);
		}
		
		/*if (!profile->back_pipeline_warmed_up)
		{
			float *tmp = allocate_buffer();
			if (tmp)
			{
				compute_pipe_line(profile->back_pipeline, tmp, profile->prev_block);
				profile->back_pipeline_warmed_up = 1;
				
				release_buffer(tmp);
			}
			else
			{
				tm_printf("Could allocate temporary buffer to warm up back pipeline!\n");
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
			
			ret_val   = compute_pipe_line(profile->front_pipeline, output_buffers[0], input_buffers[0]);
			ret_val_2 = compute_pipe_line(profile->back_pipeline,  output_buffers[1], input_buffers[1]);
			
			if (!(ret_val == NO_ERROR) && (ret_val_2 == NO_ERROR))
			{
				tm_printf("ERROR: compute_pipe_line ERROR CODES (%d, %d)\n", ret_val, ret_val_2);
			}
			
			float energy = 0.0;
			
			for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
				energy += sqr(output_buffers[0][i]);
			
			if (energy < SILENCE_ENERGY_THRESHOLD)
			{
				swap_complete = 1;
				memcpy(dest, output_buffers[1], AUDIO_BLOCK_SAMPLES * sizeof(float));
			}
			else
			{
				if (profile->pipeline_swap_progress < TAIL_NEW_FADE_IN_SAMPLES)
				{
					for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
						dest[i] = output_buffers[0][i] + (trig_transition_function((float)(profile->pipeline_swap_progress++) / TAIL_NEW_FADE_IN_SAMPLES) * output_buffers[1][i]);
				}
				else
				{
					for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
						dest[i] = output_buffers[0][i] + output_buffers[1][i];
					
					profile->pipeline_swap_progress += AUDIO_BLOCK_SAMPLES;
				}
			}
			
			release_buffer(input_buffers[0]);
		}
		else
		{
			ret_val   = compute_pipe_line(profile->front_pipeline, output_buffers[0], input_buffers[0]);
			ret_val_2 = compute_pipe_line(profile->back_pipeline,  output_buffers[1], input_buffers[1]);
			
			if (!(ret_val == NO_ERROR) && (ret_val_2 == NO_ERROR))
			{
				tm_printf("ERROR: compute_pipe_line ERROR CODES (%d, %d)\n", ret_val, ret_val_2);
			}
			
			float coef;
			for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
			{
				ratio = (float)(profile->pipeline_swap_progress) / (float)profile->pipeline_swap_samples;
				
				coef = trig_transition_function(ratio);
				
				dest[i] = coef * output_buffers[0][i] + (1.0 - coef) * output_buffers[1][i];
				profile->pipeline_swap_progress++;
			}
			
			if (profile->pipeline_swap_progress >= profile->pipeline_swap_samples)
				swap_complete = 1;
		}
		
		if (swap_complete)
		{
			tm_pipe_line *tmp = profile->front_pipeline;
			profile->front_pipeline = profile->back_pipeline;
			profile->back_pipeline = tmp;
			
			profile->pipelines_swapping = 0;
		}
		
		release_buffer(output_buffers[0]);
		release_buffer(output_buffers[1]);
	}
	else
	{
		ret_val = compute_pipe_line(profile->front_pipeline, dest, src);
		
		if (ret_val != NO_ERROR)
		{
			tm_printf("PIPELINE COMPUTATION ERROR %d\n", ret_val);
		}
	}
	
	memcpy(profile->prev_block, src, AUDIO_BLOCK_SAMPLES);
	
	RETURN_ERR_CODE(NO_ERROR);
}

int profile_trigger_pipeline_swap(tm_profile *profile)
{
	FUNCTION_START();

	tm_printf("Initiating a pipeline swap\n");
	if (!profile)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	int transition_policy = profile->front_pipeline->transition_policy;
	if (profile->back_pipeline->transition_policy > transition_policy)
		transition_policy = profile->back_pipeline->transition_policy;
	
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

int profile_regenerate_back_pipeline(tm_profile *profile)
{
	FUNCTION_START();

	if (!profile)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	clone_pipe_line(&profile->back_pipeline, profile->front_pipeline);
	
	RETURN_ERR_CODE(NO_ERROR);
}

int profile_scheduled_maintainance(tm_profile *profile)
{
	FUNCTION_START();

	if (!profile)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	// If the profile is up to something, don't touch it
	if (profile->jobs || profile->ujobs || profile->pipelines_swapping)
	{
		RETURN_ERR_CODE(NO_ERROR);
	}
	
	// If we are dealing with an active profile, prevent interruptions
	if (profile->active)
		tm_enable_software_interrupts();
	
	// If the back pipeline doesn't match the front pipeline, destroy it
	// and copy the front pipeline in its place
	if (pipe_line_compare(profile->back_pipeline, profile->front_pipeline) != 0)
	{
		tm_printf("Warning: inconsistent back pipeline detected in profile %p. Regenerating...\n", profile);
		profile_regenerate_back_pipeline(profile);
		tm_printf("Done.\n");
	}
	
	// Run a recent block through the pipeline which may be activated
	// this keeps stateful transformers ready to give valid output should
	// they be called upon to, which smooths transitions
	if (profile->active)
		compute_pipe_line(profile->back_pipeline, NULL, global_cxt.prev_block);
	else
		compute_pipe_line(profile->front_pipeline, NULL, global_cxt.prev_block);
	
	tm_enable_software_interrupts();
	
	RETURN_ERR_CODE(NO_ERROR);
}

#ifndef M_PROFILE_H_
#define M_PROFILE_H_

typedef struct
{
	//tm_pipeline pipeline;
	tm_pipe_line *front_pipeline;
	tm_pipe_line *back_pipeline;
	
	int pipelines_swapping;
	int pipeline_swap_progress;
	int pipeline_swap_samples;
	int pipeline_swap_type;
	int back_pipeline_warmed_up;
	
	tm_pipe_line_mod_linked_list *jobs;
	tm_pipe_line_mod_linked_list *ujobs;
	
	int active;
	int transition_policy;
	
	float *prev_block;
} tm_profile;

int nullify_profile(tm_profile *profile);
int init_profile(tm_profile *profile);
int init_bypass_profile(tm_profile *profile);

int profile_process(tm_profile *profile, float *dest, float *src);
int profile_update(tm_profile *profile);

int profile_apply_pipeline_mod(tm_profile *profile, tm_pipe_line_mod mod);

int profile_trigger_pipeline_swap(tm_profile *profile);

#endif

#ifndef M_PROFILE_H_
#define M_PROFILE_H_

#include "m_eng_pipe_line.h"

typedef struct
{
	//m_eng_pipeline pipeline;
	m_eng_pipe_line *front_pipeline;
	m_eng_pipe_line *back_pipeline;
	
	int pipelines_swapping;
	int pipeline_swap_progress;
	int pipeline_swap_samples;
	int pipeline_swap_type;
	int back_pipeline_warmed_up;
	
	m_eng_pipe_line_mod_linked_list *jobs;
	m_eng_pipe_line_mod_linked_list *ujobs;
	
	int active;
	int transition_policy;
	
	float *prev_block;
	
	m_eng_transformer output_amp;
} m_eng_profile;

int nullify_profile(m_eng_profile *profile);
int init_profile(m_eng_profile *profile);
int init_bypass_profile(m_eng_profile *profile);

int profile_process(m_eng_profile *profile, float *dest, float *src);
int profile_update(m_eng_profile *profile);

int profile_apply_pipeline_mod(m_eng_profile *profile, m_eng_pipe_line_mod mod);

int profile_trigger_pipeline_swap(m_eng_profile *profile);

int profile_scheduled_maintainance(m_eng_profile *profile);

#endif

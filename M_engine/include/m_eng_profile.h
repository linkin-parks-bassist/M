#ifndef M_ENG_PROFILE_H_
#define M_ENG_PROFILE_H_

#include "m_eng_pipeline.h"

typedef struct
{
	//m_eng_graph pipeline;
	m_pipeline *front_pipeline;
	m_pipeline *back_pipeline;
	
	int pipelines_swapping;
	int pipeline_swap_progress;
	int pipeline_swap_samples;
	int pipeline_swap_type;
	int back_pipeline_warmed_up;
	
	m_pipeline_mod_ll *jobs;
	m_pipeline_mod_ll *ujobs;
	
	int active;
	int transition_policy;
	
	float *prev_block;
	
	m_transformer output_amp;
} m_eng_profile;

int nullify_profile(m_eng_profile *profile);
int init_profile(m_eng_profile *profile);
int init_bypass_profile(m_eng_profile *profile);

int profile_process(m_eng_profile *profile, float *dest, float *src);
int profile_update(m_eng_profile *profile);

int profile_apply_pipeline_mod(m_eng_profile *profile, m_pipeline_mod mod);

int profile_trigger_pipeline_swap(m_eng_profile *profile);

int profile_scheduled_maintainance(m_eng_profile *profile);

#endif

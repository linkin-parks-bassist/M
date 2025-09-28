#ifndef M_CONTEXT_H_
#define M_CONTEXT_H_

#define MAX_N_PROFILES 128

typedef struct
{
	m_hw_ctrl_context hw_ctrl;
	m_pipeline *active_pipeline;
	
	int n_profiles;
	int active_profile;
	m_profile profiles[MAX_N_PROFILES];
} m_context;

int init_m_context(m_context *cxt);

int m_context_new_profile(m_context *cxt);


extern m_context global_cxt;

#endif

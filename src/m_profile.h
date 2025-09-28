#ifndef M_PROFILE_H_
#define M_PROFILE_H_

typedef struct
{
	m_pipeline pipeline;
} m_profile;

int nullify_profile(m_profile *profile);
int init_profile(m_profile *profile);
int init_bypass_profile(m_profile *profile);

#endif

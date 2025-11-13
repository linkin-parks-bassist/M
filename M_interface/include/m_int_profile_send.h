#ifndef M_INT_PROFILE_SEND_H_
#define M_INT_PROFILE_SEND_H_

struct m_profile_send_job;

typedef struct m_int_trans_send_job
{
	m_transformer *trans;
	struct m_profile_send_job *profile_job;
	
	m_parameter_pll *current_param;
	int parameter_index;
} m_int_trans_send_job;

DECLARE_LINKED_PTR_LIST(m_int_trans_send_job);

typedef struct m_profile_send_job
{
	m_profile *profile;
	
	m_int_trans_send_job_pll *tsjs;
} m_profile_send_job;

void send_all_profiles_to_teensy(m_int_context *cxt);

void send_profile_to_teensy(m_profile *profile);
void send_new_profile_to_teensy(m_profile *profile);

#endif

#ifndef M_INT_PROFILE_SEND_H_
#define M_INT_PROFILE_SEND_H_

struct m_int_profile_send_job;

typedef struct m_int_trans_send_job
{
	m_int_transformer *trans;
	struct m_int_profile_send_job *profile_job;
	
	parameter_ll *current_param;
	int parameter_index;
} m_int_trans_send_job;

DECLARE_LINKED_PTR_LIST(m_int_trans_send_job);

typedef struct m_int_profile_send_job
{
	m_int_profile *profile;
	
	m_int_trans_send_job_ptr_linked_list *tsjs;
} m_int_profile_send_job;

void send_all_profiles_to_teensy(m_int_context *cxt);

void send_profile_to_teensy(m_int_profile *profile);
void send_new_profile_to_teensy(m_int_profile *profile);

#endif

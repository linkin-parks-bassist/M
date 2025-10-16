#ifndef EM_PROFILE_SEND_H_
#define EM_PROFILE_SEND_H_

struct em_profile_send_job;

typedef struct em_trans_send_job
{
	em_transformer *trans;
	struct em_profile_send_job *profile_job;
	
	int parameter_index;
} em_trans_send_job;

DECLARE_LINKED_PTR_LIST(em_trans_send_job);

typedef struct em_profile_send_job
{
	em_profile *profile;
	
	em_trans_send_job_ptr_linked_list *tsjs;
} em_profile_send_job;

void send_new_profile_to_teensy(em_profile *profile);

#endif

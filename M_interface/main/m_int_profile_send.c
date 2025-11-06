#include "m_int.h"

IMPLEMENT_LINKED_PTR_LIST(m_int_trans_send_job);

static const char *TAG = "m_int_profile_send.c";

void transformer_job_recieve_parameter_value_response(et_msg msg, te_msg response);
void send_profile_job_discard_tsj(m_int_profile_send_job *job);
void send_profile_job_dispatch_tsj(m_int_profile_send_job *job);

void send_all_profiles_to_teensy(m_int_context *cxt)
{
	if (!cxt)
		return;
	
	profile_ll *current = cxt->profiles;
	
	while (current)
	{
		if (current->data)
		{
			if (current->data->default_profile)
			{
				send_profile_to_teensy(current->data);
			}
			else
			{
				send_new_profile_to_teensy(current->data);
			}
		}
		
		current = current->next;
	}
}

void transformer_job_send_parameter_value(m_int_trans_send_job *job)
{
	if (!job || !job->current_param)
		return;
	
	m_int_parameter *param = job->current_param->data;
		
	if (!param)
	{
		printf("oh....\n");
		return;
	}
	
	et_msg msg = create_et_msg(ET_MESSAGE_SET_PARAM_VALUE, "sssf",
		job->trans->profile_id, job->trans->transformer_id, job->parameter_index, param->val);
	
	msg.callback = transformer_job_recieve_parameter_value_response;
	msg.cb_arg = job;
	
	queue_msg_to_teensy(msg);
}

void transformer_job_recieve_parameter_value_response(et_msg msg, te_msg response)
{
	m_int_trans_send_job *job = (m_int_trans_send_job*)msg.cb_arg;
	
	if (!job)
		return;
	
	if (job->current_param)
	{
		job->current_param = job->current_param->next;
		transformer_job_send_parameter_value(job);
	}
	
	if (!job->current_param && job->profile_job)
	{
		printf("That is all the parameters we have! Time for next transformer send...job = %p\n", job->profile_job);
		send_profile_job_discard_tsj(job->profile_job);
		printf("Once more, that is, job = %p\n", job->profile_job);
		send_profile_job_dispatch_tsj(job->profile_job);
		
		m_int_free(job);
	}	
}

void transformer_send_job_recieve_transformer_id(et_msg msg, te_msg response)
{
	m_int_trans_send_job *job = (m_int_trans_send_job*)msg.cb_arg;
	
	if (!job)
	{
		#ifndef M_SIMULATED
		ESP_LOGE(TAG, "Did not recieve job with ID recieve callback");
		#endif
		return;
	}
	
	if (!job->trans)
	{
		#ifndef M_SIMULATED
		ESP_LOGE(TAG, "Transformer send job has no transformer");
		#endif
		return;
	}
	
	if (response.type != TE_MESSAGE_TRANSFORMER_ID)
	{
		#ifndef M_SIMULATED
		ESP_LOGE(TAG, "Teensy did not return transformer ID\n");
		#endif
		return;
	}
	
	uint16_t pid;
	uint16_t tid;
	
	memcpy(&pid, &response.data[0], sizeof(uint16_t));
	memcpy(&tid, &response.data[2], sizeof(uint16_t));
	
	transformer_set_id(job->trans, pid, tid);
	
	printf("Recieved transformer ID from Teensy ! it is %d.%d\n", pid, tid);
	
	job->current_param = job->trans->parameters;
	transformer_job_send_parameter_value(job);
}

void send_profile_job_discard_tsj(m_int_profile_send_job *job)
{
	if (!job)
		return;
	
	if (!job->tsjs)
		return;
	
	printf("send_profile_job_discard_tsj. job = %p. job->tsjs = %p. job->tsjs->next = %p\n", job, job->tsjs, (job->tsjs ? job->tsjs->next : NULL));
	
	m_int_trans_send_job_ptr_linked_list *next = job->tsjs->next;
	
	m_int_free(job->tsjs);
	job->tsjs = next;
}

void send_profile_job_dispatch_tsj(m_int_profile_send_job *job)
{
	if (!job)
		return;
	
	printf("send_profile_job_dispatch_tsj. job = %p\n", job);
	if (job->tsjs)
	{
		if (!job->tsjs->data || !job->tsjs->data->trans)
		{
			printf("Why is this NULL ???\n");
		}
		else
		{
			printf("Tell Teensy to append a transformer of type %s to profile %d\n", transformer_type_to_string(job->tsjs->data->trans->type), job->profile->id);
			et_msg msg = create_et_msg(ET_MESSAGE_APPEND_TRANSFORMER, "ss", job->profile->id, job->tsjs->data->trans->type);
			msg.callback = transformer_send_job_recieve_transformer_id;
			msg.cb_arg = job->tsjs->data;
			
			queue_msg_to_teensy(msg);
		}
	}
	else
	{
		printf("All out of transformers! Job done\n");
		m_int_free(job);
	}
}

void profile_send_job_recieve_profile_id(et_msg msg, te_msg response)
{
	m_int_profile_send_job *job = (m_int_profile_send_job*)msg.cb_arg;
	
	if (!job)
	{
		#ifndef M_SIMULATED
		ESP_LOGE(TAG, "Did not recieve job with ID recieve callback");
		#endif
		return;
	}
	
	if (!job->profile)
	{
		#ifndef M_SIMULATED
		ESP_LOGE(TAG, "Profile send job has no profile");
		#endif
		return;
	}
	
	uint16_t id;
	memcpy(&id, response.data, sizeof(uint16_t));
	
	profile_set_id(job->profile, id);
	
	printf("Teensy created a new profile, ID: %d\n", job->profile->id);
	if (job->tsjs)
	{
		if (!job->tsjs->data->trans)
		{
			#ifndef M_SIMULATED
			ESP_LOGE(TAG, "Transformer send job has no transformer");
			#endif
			free_m_int_trans_send_job_ptr_linked_list(job->tsjs);
			return;
		}
		
		printf("Sending the first transformer to Teensy...\n");
		send_profile_job_dispatch_tsj(job);
	}
	else
	{
		m_int_free(job);
	}
}

void send_profile_to_teensy(m_int_profile *profile)
{
	if (!profile)
		return;
	
	printf("Sending profile to Teensy!\n");
	m_int_profile_send_job *job = m_int_malloc(sizeof(m_int_profile_send_job));
	
	if (!job)
		return;
	
	job->tsjs = NULL;
	job->profile = profile;
	
	m_int_transformer_ll *current = profile->pipeline.transformers;
	
	m_int_trans_send_job *tsj;
	
	int i = 0;
	while (current)
	{
		tsj = m_int_malloc(sizeof(m_int_trans_send_job));
		
		if (!tsj)
		{
			free_m_int_trans_send_job_ptr_linked_list(job->tsjs);
			#ifndef M_SIMULATED
			ESP_LOGE(TAG, "Alloc fail in \'send_new_profile_to_teensy\'");
			#endif
			return;
		}
		printf("Transformer %d. Pointer: %p\n", i, current->data);
		tsj->trans = current->data;
		tsj->profile_job = job;
		tsj->parameter_index = 0;
		job->tsjs = m_int_trans_send_job_ptr_linked_list_append(job->tsjs, tsj);
		current = current->next;
	}
	
	send_profile_job_dispatch_tsj(job);
}

void send_new_profile_to_teensy(m_int_profile *profile)
{
	if (!profile)
		return;
	
	printf("Sending profile to Teensy!\n");
	m_int_profile_send_job *job = m_int_malloc(sizeof(m_int_profile_send_job));
	
	if (!job)
		return;
	
	job->tsjs = NULL;
	job->profile = profile;
	
	m_int_transformer_ll *current = profile->pipeline.transformers;
	
	m_int_trans_send_job *tsj;
	
	printf("Transformers in profile:\n");
	
	int i = 0;
	while (current)
	{
		tsj = m_int_malloc(sizeof(m_int_trans_send_job));
		
		if (!tsj)
		{
			free_m_int_trans_send_job_ptr_linked_list(job->tsjs);
			#ifndef M_SIMULATED
			ESP_LOGE(TAG, "Alloc fail in \'send_new_profile_to_teensy\'");
			#endif
			return;
		}
		printf("Transformer %d. Pointer: %p\n", i, current->data);
		tsj->trans = current->data;
		tsj->profile_job = job;
		tsj->parameter_index = 0;
		job->tsjs = m_int_trans_send_job_ptr_linked_list_append(job->tsjs, tsj);
		current = current->next;
	}
	
	printf("%d items in the trans send job list\n", i);
	
	printf("Ask Teensy to create a new profile... job = %p, job->tsjs = %p\n", job, job->tsjs);
	et_msg msg = create_et_msg_nodata(ET_MESSAGE_CREATE_PROFILE);
	msg.callback = profile_send_job_recieve_profile_id;
	msg.cb_arg = job;
	
	queue_msg_to_teensy(msg);
}

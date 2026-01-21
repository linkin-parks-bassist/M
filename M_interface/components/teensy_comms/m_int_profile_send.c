#include "m_int.h"

IMPLEMENT_LINKED_PTR_LIST(m_int_trans_send_job);

static const char *TAG = "m_profile_send.c";

void transformer_job_recieve_parameter_value_response(m_message msg, m_response response);
void send_profile_job_discard_tsj(m_profile_send_job *job);
void send_profile_job_dispatch_tsj(m_profile_send_job *job);

void send_all_profiles_to_teensy(m_context *cxt)
{
	if (!cxt)
		return;
	
	profile_ll *current = cxt->profiles;
	
	while (current)
	{
		if (current->data)
		{
			send_new_profile_to_teensy(current->data);
		}
		
		current = current->next;
	}
}

void transformer_job_send_parameter_value(m_int_trans_send_job *job)
{
	if (!job || !job->current_param)
		return;
	
	m_parameter *param = job->current_param->data;
		
	if (!param)
	{
		printf("oh....\n");
		return;
	}
	
	m_message msg = create_m_message(M_MESSAGE_SET_PARAM_VALUE, "sssf",
		job->trans->profile->id, job->trans->id, job->parameter_index, param->value);
	
	msg.callback = transformer_job_recieve_parameter_value_response;
	msg.cb_arg = job;
	
	queue_msg_to_teensy(msg);
}

void transformer_job_recieve_parameter_value_response(m_message msg, m_response response)
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
		send_profile_job_discard_tsj(job->profile_job);
		send_profile_job_dispatch_tsj(job->profile_job);
		
		m_free(job);
	}	
}

void transformer_send_job_recieve_transformer_id(m_message msg, m_response response)
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
	
	if (response.type != M_RESPONSE_TRANSFORMER_ID)
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
	
	job->current_param = job->trans->parameters;
	transformer_job_send_parameter_value(job);
}

void send_profile_job_discard_tsj(m_profile_send_job *job)
{
	if (!job)
		return;
	
	if (!job->tsjs)
		return;
	
	m_int_trans_send_job_pll *next = job->tsjs->next;
	
	m_free(job->tsjs);
	job->tsjs = next;
}

void send_profile_job_dispatch_tsj(m_profile_send_job *job)
{
	if (!job)
		return;
	
	if (job->tsjs)
	{
		if (!job->tsjs->data || !job->tsjs->data->trans)
		{
			printf("Why is this NULL ???\n");
		}
		else
		{
			m_message msg = create_m_message(M_MESSAGE_APPEND_TRANSFORMER, "ss", job->profile->id, job->tsjs->data->trans->type);
			msg.callback = transformer_send_job_recieve_transformer_id;
			msg.cb_arg = job->tsjs->data;
			
			queue_msg_to_teensy(msg);
		}
	}
	else
	{
		m_free(job);
	}
}

void profile_send_job_recieve_profile_id(m_message msg, m_response response)
{
	m_profile_send_job *job = (m_profile_send_job*)msg.cb_arg;
	
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
	
	if (job->tsjs)
	{
		if (!job->tsjs->data->trans)
		{
			#ifndef M_SIMULATED
			ESP_LOGE(TAG, "Transformer send job has no transformer");
			#endif
			free_m_int_trans_send_job_pll(job->tsjs);
			return;
		}
		
		send_profile_job_dispatch_tsj(job);
	}
	else
	{
		m_free(job);
	}
}

void send_profile_to_teensy(m_profile *profile)
{
	if (!profile)
		return;
	
	m_profile_send_job *job = m_alloc(sizeof(m_profile_send_job));
	
	if (!job)
		return;
	
	job->tsjs = NULL;
	job->profile = profile;
	
	m_transformer_pll *current = profile->pipeline.transformers;
	
	m_int_trans_send_job *tsj;
	
	int i = 0;
	while (current)
	{
		tsj = m_alloc(sizeof(m_int_trans_send_job));
		
		if (!tsj)
		{
			free_m_int_trans_send_job_pll(job->tsjs);
			#ifndef M_SIMULATED
			ESP_LOGE(TAG, "Alloc fail in \'send_new_profile_to_teensy\'");
			#endif
			return;
		}
		tsj->trans = current->data;
		tsj->profile_job = job;
		tsj->parameter_index = 0;
		job->tsjs = m_int_trans_send_job_pll_append(job->tsjs, tsj);
		current = current->next;
	}
	
	send_profile_job_dispatch_tsj(job);
}

void send_new_profile_to_teensy(m_profile *profile)
{
	if (!profile)
		return;
	
	m_profile_send_job *job = m_alloc(sizeof(m_profile_send_job));
	
	if (!job)
		return;
	
	job->tsjs = NULL;
	job->profile = profile;
	
	m_transformer_pll *current = profile->pipeline.transformers;
	
	m_int_trans_send_job *tsj;
	
	int i = 0;
	while (current)
	{
		tsj = m_alloc(sizeof(m_int_trans_send_job));
		
		if (!tsj)
		{
			free_m_int_trans_send_job_pll(job->tsjs);
			#ifndef M_SIMULATED
			ESP_LOGE(TAG, "Alloc fail in \'send_new_profile_to_teensy\'");
			#endif
			return;
		}
		tsj->trans = current->data;
		tsj->profile_job = job;
		tsj->parameter_index = 0;
		job->tsjs = m_int_trans_send_job_pll_append(job->tsjs, tsj);
		current = current->next;
	}
	
	m_message msg = create_m_message_nodata(M_MESSAGE_CREATE_PROFILE);
	msg.callback = profile_send_job_recieve_profile_id;
	msg.cb_arg = job;
	
	queue_msg_to_teensy(msg);
}

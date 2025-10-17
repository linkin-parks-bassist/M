#include "em.h"

IMPLEMENT_LINKED_PTR_LIST(em_trans_send_job);

static const char *TAG = "em_profile_send.c";

void transformer_job_recieve_parameter_value_response(et_msg msg, te_msg response);
void send_profile_job_discard_tsj(em_profile_send_job *job);
void send_profile_job_dispatch_tsj(em_profile_send_job *job);

void transformer_job_send_parameter_value(em_trans_send_job *job)
{
	//printf("sending parameter %d value to teensy...\b", job->parameter_index);
	et_msg msg = create_et_msg(ET_MESSAGE_SET_PARAM_VALUE, "sssf",
		job->trans->profile_id, job->trans->transformer_id, job->parameter_index, job->trans->parameters[job->parameter_index].val);
	msg.callback = transformer_job_recieve_parameter_value_response;
	msg.cb_arg = job;
	
	queue_msg_to_teensy(msg);
}

void transformer_job_recieve_parameter_value_response(et_msg msg, te_msg response)
{
	em_trans_send_job *job = (em_trans_send_job*)msg.cb_arg;
	
	if (!job)
		return;
	
	job->parameter_index++;
	
	if (job->parameter_index < job->trans->n_parameters)
	{
		transformer_job_send_parameter_value(job);
	}
	else if (job->profile_job)
	{
		//printf("That is all the parameters we have! Time for next transformer send...job = %p\n", job->profile_job);
		send_profile_job_discard_tsj(job->profile_job);
		//printf("Once more, that is, job = %p\n", job->profile_job);
		send_profile_job_dispatch_tsj(job->profile_job);
		
		free(job);
	}
}

void transformer_send_job_recieve_transformer_id(et_msg msg, te_msg response)
{
	em_trans_send_job *job = (em_trans_send_job*)msg.cb_arg;
	
	if (!job)
	{
		ESP_LOGE(TAG, "Did not recieve job with ID recieve callback");
		return;
	}
	
	if (!job->trans)
	{
		ESP_LOGE(TAG, "Transformer send job has no transformer");
		return;
	}
	
	if (response.type != TE_MESSAGE_TRANSFORMER_ID)
	{
		ESP_LOGE(TAG, "Teensy did not return transformer ID\n");
		return;
	}
	
	uint16_t pid;
	uint16_t tid;
	
	memcpy(&pid, &response.data[0], sizeof(uint16_t));
	memcpy(&tid, &response.data[2], sizeof(uint16_t));
	
	transformer_set_id(job->trans, pid, tid);
	
	//printf("Recieved transformer ID from Teensy ! it is %d.%d\n", pid, tid);
	
	transformer_job_send_parameter_value(job);
}

void send_profile_job_discard_tsj(em_profile_send_job *job)
{
	if (!job)
		return;
	
	if (!job->tsjs)
		return;
	
	//printf("send_profile_job_discard_tsj. job = %p. job->tsjs = %p. job->tsjs->next = %p\n", job, job->tsjs, (job->tsjs ? job->tsjs->next : NULL));
	
	em_trans_send_job_ptr_linked_list *next = job->tsjs->next;
	
	free(job->tsjs);
	job->tsjs = next;
}

void send_profile_job_dispatch_tsj(em_profile_send_job *job)
{
	if (!job)
		return;
	
	//printf("send_profile_job_dispatch_tsj. job = %p\n", job);
	if (job->tsjs)
	{
		if (!job->tsjs->data || !job->tsjs->data->trans)
		{
			//printf("Why is this NULL ???\n");
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
		//printf("All out of transformers! Job done\n");
		free(job);
	}
}

void profile_send_job_recieve_profile_id(et_msg msg, te_msg response)
{
	em_profile_send_job *job = (em_profile_send_job*)msg.cb_arg;
	
	if (!job)
	{
		ESP_LOGE(TAG, "Did not recieve job with ID recieve callback");
		return;
	}
	
	if (!job->profile)
	{
		ESP_LOGE(TAG, "Profile send job has no profile");
		return;
	}
	
	printf("profile_send_job_recieve_profile_id. job = %p, job->profile = %p, job->tsjs = %p, job->tsjs->data->trans = %p\n",
		job, job->profile, job->tsjs, job->tsjs ? job->tsjs->data->trans : NULL);
	
	memcpy(&job->profile->id, response.data, sizeof(uint16_t));
	
	printf("Teensy created a new profile, ID: %d\n", job->profile->id);
	if (job->tsjs)
	{
		if (!job->tsjs->data->trans)
		{
			ESP_LOGE(TAG, "Transformer send job has no transformer");
			free_em_trans_send_job_ptr_linked_list(job->tsjs);
			return;
		}
		
		//printf("Sending the first transformer to Teensy...\n");
		send_profile_job_dispatch_tsj(job);
	}
	else
	{
		free(job);
	}
}

void send_new_profile_to_teensy(em_profile *profile)
{
	if (!profile)
		return;
	
	//printf("Sending profile to Teensy!\n");
	em_profile_send_job *job = malloc(sizeof(em_profile_send_job));
	
	if (!job)
		return;
	
	job->tsjs = NULL;
	job->profile = profile;
	
	em_transformer_ll *current = profile->pipeline.transformers;
	
	em_trans_send_job *tsj;
	
	//printf("Transformers in profile:\n");
	
	int i = 0;
	while (current)
	{
		tsj = malloc(sizeof(em_trans_send_job));
		
		if (!tsj)
		{
			free_em_trans_send_job_ptr_linked_list(job->tsjs);
			ESP_LOGE(TAG, "Alloc fail in \'send_new_profile_to_teensy\'");
			return;
		}
		//printf("Transformer %d. Pointer: %p\n", i, current->data);
		tsj->trans = current->data;
		tsj->profile_job = job;
		tsj->parameter_index = 0;
		job->tsjs = em_trans_send_job_ptr_linked_list_append(job->tsjs, tsj);
		current = current->next;
	}
	
	//printf("%d items in the trans send job list\n", i);
	
	//printf("Ask Teensy to create a new profile... job = %p, job->tsjs = %p\n", job, job->tsjs);
	et_msg msg = create_et_msg_nodata(ET_MESSAGE_CREATE_PROFILE);
	msg.callback = profile_send_job_recieve_profile_id;
	msg.cb_arg = job;
	
	queue_msg_to_teensy(msg);
}

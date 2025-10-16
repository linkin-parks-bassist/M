#include "em.h"

#define INITIAL_PROFILE_ARRAY_LENGTH 8
#define PROFILE_ARRAY_CHUNK_SIZE	 8

int init_em_context(em_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	cxt->n_profiles = 1;
	
	cxt->active_profile = malloc(sizeof(em_profile));
	cxt->working_profile = cxt->active_profile;
	
	cxt->profiles = NULL;
	
	if (!cxt->active_profile)
		return ERR_ALLOC_FAIL;
	
	init_em_profile(cxt->active_profile);
	em_profile_set_default_name_from_id(cxt->active_profile);
	
	cxt->active_profile->active = 1;
	
	printf("Created profile, %p. Name: %s\n", cxt->active_profile, cxt->active_profile->name);
	
	profile_ll *nl = em_profile_ptr_linked_list_append(cxt->profiles, cxt->active_profile);
	
	if (!nl)
	{
		free_profile(cxt->active_profile);
		return ERR_ALLOC_FAIL;
	}
	
	cxt->profiles = nl;
	
	cxt->saved_profiles_loaded = 0;
	
	return NO_ERROR;
}

int em_context_add_profile(em_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	em_profile *profile = malloc(sizeof(em_profile));
	
	if (!profile)
		return ERR_ALLOC_FAIL;
	
	init_em_profile(profile);
	
	profile_ll *nl = em_profile_ptr_linked_list_append(cxt->profiles, profile);
	
	if (!nl)
	{
		free_profile(profile);
		return ERR_ALLOC_FAIL;
	}
	
	cxt->profiles = nl;
	
	cxt->n_profiles++;
	
	return NO_ERROR;
}

em_profile *cxt_get_profile_by_id(em_context *cxt, uint16_t profile_id)
{
	if (!cxt)
		return NULL;
	
	profile_ll *current = cxt->profiles;
	
	while (current)
	{
		if (current->data && current->data->id == profile_id)
			return current->data;
		
		current = current->next;
	}
	
	return NULL;
}

em_transformer *cxt_get_transformer_by_id(em_context *cxt, uint16_t profile_id, uint16_t transformer_id)
{
	if (!cxt)
		return NULL;
	
	em_profile *profile = cxt_get_profile_by_id(cxt, profile_id);
	
	if (!profile)
		return NULL;
	
	em_transformer_ptr_linked_list *current = profile->pipeline.transformers;
	
	while (current)
	{
		if (current->data && current->data->transformer_id == transformer_id)
			return current->data;
		
		current = current->next;
	}
	
	return NULL;
}

em_parameter *cxt_get_parameter_by_id(em_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id)
{
	if (!cxt)
		return NULL;
	
	em_transformer *trans = cxt_get_transformer_by_id(cxt, profile_id, transformer_id);
	
	if (!trans)
		return NULL;
	
	if (parameter_id >= trans->n_parameters)
		return NULL;
	
	return &trans->parameters[parameter_id];
}

em_option *cxt_get_option_by_id(em_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t option_id)
{
	if (!cxt)
		return NULL;
	
	em_transformer *trans = cxt_get_transformer_by_id(cxt, profile_id, transformer_id);
	
	if (!trans)
		return NULL;
	
	if (option_id >= trans->n_options)
		return NULL;
	
	return &trans->options[option_id];
}

int cxt_transformer_id_to_position(em_context *cxt, uint16_t profile_id, uint16_t transformer_id)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	em_profile *profile = cxt_get_profile_by_id(cxt, profile_id);
	
	if (!profile)
		return -ERR_INVALID_PROFILE_ID;
	
	transformer_ll *current = profile->pipeline.transformers;
	
	int i = 0;
	while (current)
	{
		if (current->data && current->data->transformer_id == transformer_id)
			return i;
		
		current = current->next;
		i++;
	}
	
	return -ERR_INVALID_TRANSFORMER_ID;
}

int cxt_transformer_position_to_id(em_context *cxt, uint16_t profile_id, uint16_t transformer_pos)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	em_profile *profile = cxt_get_profile_by_id(cxt, profile_id);
	
	if (!profile)
		return -ERR_INVALID_PROFILE_ID;
	
	transformer_ll *current = profile->pipeline.transformers;
	
	int i = 0;
	while (current)
	{
		if (i == transformer_pos)
		{
			if (!current->data)
				return ERR_NULL_PTR;
			
			return current->data->transformer_id;
		}
		
		current = current->next;
		i++;
	}
	
	return -ERR_INVALID_TRANSFORMER_ID;
}

int cxt_remove_profile(em_context *cxt, em_profile *profile)
{
	if (!cxt || !profile)
		return ERR_NULL_PTR;
	
	profile_ll *current = cxt->profiles;
	profile_ll *prev = NULL;
	
	if (profile && profile->fname)
		remove(profile->fname);
	
	while (current)
	{
		if (current->data == profile)
		{
			queue_msg_to_teensy(create_et_msg(ET_MESSAGE_DELETE_PROFILE, "s", profile->id));
			
			if (!prev)
			{
				cxt->profiles = current->next;
			}
			else
			{
				prev->next = current->next;
			}
			
			free_profile(profile);
			free(current);
			
			return NO_ERROR;
		}
		
		prev = current;
		current = current->next;
	}
	
	return ERR_INVALID_PROFILE_ID;
}

int cxt_remove_transformer(em_context *cxt, uint16_t pid, uint16_t tid)
{
	printf("cxt_remove_transformer\n");
	if (!cxt)
		return ERR_NULL_PTR;
	
	int ret_val = em_profile_remove_transformer(cxt_get_profile_by_id(cxt, pid), tid);
	
	if (ret_val == NO_ERROR)
	{
		queue_msg_to_teensy(create_et_msg(ET_MESSAGE_REMOVE_TRANSFORMER, "ss", pid, tid));
	}
	
	printf("cxt_remove_transformer done\n");
	return ret_val;
}

int set_active_profile(em_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	if (profile == global_cxt.active_profile)
		return NO_ERROR;
	
	em_profile_set_inactive(global_cxt.active_profile);
	em_profile_set_active(profile);
	
	global_cxt.active_profile = profile;
	
	return queue_msg_to_teensy(create_et_msg(ET_MESSAGE_SWITCH_PROFILE, "s", profile->id));
}

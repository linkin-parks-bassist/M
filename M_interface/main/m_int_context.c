#include "m_int.h"

#define INITIAL_PROFILE_ARRAY_LENGTH 8
#define PROFILE_ARRAY_CHUNK_SIZE	 8

int init_m_int_context(m_int_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	cxt->n_profiles = 0;
	
	cxt->active_profile  = NULL;
	cxt->working_profile = NULL;
	cxt->default_profile = NULL;
	
	cxt->profiles  = NULL;
	cxt->sequences = NULL;
	cxt->sequence  = NULL;
	
	cxt->default_profile_exists = 0;
	cxt->saved_profiles_loaded = 0;
	
	init_settings(&cxt->settings);
	
	init_parameter(&cxt->settings.global_volume, "Volume", -90.0, -12.0, 12.0);
	cxt->settings.global_volume.units = " dB";
	cxt->settings.global_volume.id = (m_int_parameter_id){.profile_id = 0xFFFF, .transformer_id = 0, .parameter_id = 0};
	
	return NO_ERROR;
}

int context_no_default_profile(m_int_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	cxt->active_profile = m_int_malloc(sizeof(m_int_profile));
	cxt->working_profile = cxt->active_profile;
	cxt->default_profile = cxt->active_profile;
	
	if (!cxt->active_profile)
		return ERR_ALLOC_FAIL;
	
	init_m_int_profile(cxt->active_profile);
	create_profile_view_for(cxt->active_profile);
	m_int_profile_set_default_name_from_id(cxt->active_profile);
	
	cxt->active_profile->active = 1;
	
	printf("Created profile, %p. Name: %s\n", cxt->active_profile, cxt->active_profile->name);
	profile_ll *nl = m_int_profile_ptr_linked_list_append(NULL, cxt->active_profile);
	
	if (!nl)
	{
		free_profile(cxt->active_profile);
		return ERR_ALLOC_FAIL;
	}
	
	nl->next = cxt->profiles;
	cxt->profiles = nl;
	
	cxt->active_profile->default_profile = 1;
	
	return NO_ERROR;
}

int m_int_context_add_profile(m_int_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	m_int_profile *profile = m_int_malloc(sizeof(m_int_profile));
	
	if (!profile)
		return ERR_ALLOC_FAIL;
	
	init_m_int_profile(profile);
	
	profile_ll *nl = m_int_profile_ptr_linked_list_append(cxt->profiles, profile);
	
	if (!nl)
	{
		free_profile(profile);
		return ERR_ALLOC_FAIL;
	}
	
	cxt->profiles = nl;
	
	cxt->n_profiles++;
	
	return NO_ERROR;
}

m_int_profile *m_int_context_add_profile_rp(m_int_context *cxt)
{
	if (!cxt)
		return NULL;
	
	m_int_profile *profile = m_int_malloc(sizeof(m_int_profile));
	
	if (!profile)
		return NULL;
	
	init_m_int_profile(profile);
	
	profile_ll *nl = m_int_profile_ptr_linked_list_append(cxt->profiles, profile);
	
	if (!nl)
	{
		free_profile(profile);
		return NULL;
	}
	
	cxt->profiles = nl;
	
	cxt->n_profiles++;
	
	return profile;
}

m_int_sequence *m_int_context_add_sequence_rp(m_int_context *cxt)
{
	if (!cxt)
		return NULL;
	
	m_int_sequence *sequence = m_int_malloc(sizeof(m_int_sequence));
	
	if (!sequence)
		return NULL;
	
	init_m_int_sequence(sequence);
	
	sequence_ll *nl = m_int_sequence_ptr_linked_list_append(cxt->sequences, sequence);
	
	if (!nl)
	{
		free_sequence(sequence);
		return NULL;
	}
	
	cxt->sequences = nl;
	
	return sequence;
}

m_int_profile *cxt_get_profile_by_id(m_int_context *cxt, uint16_t profile_id)
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

m_int_transformer *cxt_get_transformer_by_id(m_int_context *cxt, uint16_t profile_id, uint16_t transformer_id)
{
	if (!cxt)
		return NULL;
	
	m_int_profile *profile = cxt_get_profile_by_id(cxt, profile_id);
	
	if (!profile)
		return NULL;
	
	m_int_transformer_ptr_linked_list *current = profile->pipeline.transformers;
	
	while (current)
	{
		if (current->data && current->data->transformer_id == transformer_id)
			return current->data;
		
		current = current->next;
	}
	
	return NULL;
}

m_int_parameter *cxt_get_parameter_by_id(m_int_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id)
{
	if (!cxt)
		return NULL;
	
	m_int_transformer *trans = cxt_get_transformer_by_id(cxt, profile_id, transformer_id);
	
	if (!trans)
		return NULL;
	
	return transformer_get_parameter(trans, parameter_id);
}

m_int_setting *cxt_get_setting_by_id(m_int_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id)
{
	if (!cxt)
		return NULL;
	
	m_int_transformer *trans = cxt_get_transformer_by_id(cxt, profile_id, transformer_id);
	
	if (!trans)
		return NULL;
	
	return transformer_get_setting(trans, parameter_id);
}

int cxt_transformer_id_to_position(m_int_context *cxt, uint16_t profile_id, uint16_t transformer_id)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	m_int_profile *profile = cxt_get_profile_by_id(cxt, profile_id);
	
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

int cxt_transformer_position_to_id(m_int_context *cxt, uint16_t profile_id, uint16_t transformer_pos)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	m_int_profile *profile = cxt_get_profile_by_id(cxt, profile_id);
	
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

int cxt_remove_profile(m_int_context *cxt, m_int_profile *profile)
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
			m_int_free(current);
			
			return NO_ERROR;
		}
		
		prev = current;
		current = current->next;
	}
	
	return ERR_INVALID_PROFILE_ID;
}

int cxt_remove_sequence(m_int_context *cxt, m_int_sequence *sequence)
{
	if (!cxt || !sequence)
		return ERR_NULL_PTR;
	
	sequence_ll *current = cxt->sequences;
	sequence_ll *prev = NULL;
	
	if (sequence && sequence->fname)
		remove(sequence->fname);
	
	while (current)
	{
		if (current->data == sequence)
		{
			if (!prev)
			{
				cxt->sequences = current->next;
			}
			else
			{
				prev->next = current->next;
			}
			
			free_sequence(sequence);
			m_int_free(current);
			
			return NO_ERROR;
		}
		
		prev = current;
		current = current->next;
	}
	
	return ERR_INVALID_PROFILE_ID;
}

int cxt_remove_transformer(m_int_context *cxt, uint16_t pid, uint16_t tid)
{
	printf("cxt_remove_transformer\n");
	if (!cxt)
		return ERR_NULL_PTR;
	
	int ret_val = m_int_profile_remove_transformer(cxt_get_profile_by_id(cxt, pid), tid);
	
	if (ret_val == NO_ERROR)
	{
		queue_msg_to_teensy(create_et_msg(ET_MESSAGE_REMOVE_TRANSFORMER, "ss", pid, tid));
	}
	
	printf("cxt_remove_transformer done\n");
	return ret_val;
}

int set_active_profile(m_int_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	if (profile == global_cxt.active_profile)
		return NO_ERROR;
	
	m_int_profile_set_inactive(global_cxt.active_profile);
	m_int_profile_set_active(profile);
	
	global_cxt.active_profile = profile;
	
	return queue_msg_to_teensy(create_et_msg(ET_MESSAGE_SWITCH_PROFILE, "s", profile->id));
}

int set_working_profile(m_int_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	if (profile == global_cxt.working_profile)
		return NO_ERROR;
	
	global_cxt.working_profile = profile;
	
	return NO_ERROR;
}

int resolve_default_profile(m_int_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	profile_ll *current = cxt->profiles;
	profile_ll *prev = NULL;
	
	printf("resolve default profile. cxt->settings.default_profile = %s\n", cxt->settings.default_profile ? cxt->settings.default_profile : "(NULL)!");
	if (!cxt->settings.default_profile)
	{
		return NO_ERROR;
	}
	
	while (current)
	{
		if (current->data && current->data->fname && strcmp(current->data->fname, cxt->settings.default_profile) == 0)
		{
			profile_set_id(current->data, 0);
			current->data->default_profile = 1;
			
			// Put the default first in the list
			if (prev)
			{
				prev->next = current->next;
				current->next = cxt->profiles;
				cxt->profiles = current;
			}
			
			cxt->active_profile  = current->data;
			cxt->working_profile = current->data;
			cxt->default_profile = current->data;
			m_int_profile_set_active(current->data);
			
			cxt->default_profile_exists = 1;
			
			printf("Found it!\n");
			return NO_ERROR;
		}
		
		prev = current;
		current = current->next;
	}
	
	return NO_ERROR;
}

int set_profile_as_default(m_int_context *cxt, m_int_profile *profile)
{
	if (!cxt || !profile)
		return ERR_NULL_PTR;
	
	if (!profile->fname)
	{
		save_profile(profile);
		
		if (cxt->default_profile)
		{
			cxt->default_profile->default_profile = 0;
		}
	}
	
	cxt->default_profile = profile;
	profile->default_profile = 1;
	
	xSemaphoreTake(settings_mutex, portMAX_DELAY);
	cxt->settings.default_profile = profile->fname;
	cxt->settings.changed = 1;
	xSemaphoreGive(settings_mutex);
	
	return NO_ERROR;
}

void context_print_profiles(m_int_context *cxt)
{
	if (!cxt)
		return;
		
	printf("Printing profiles...\n");
	
	profile_ll *current = global_cxt.profiles;
	
	
	int i = 0;
	while (current)
	{
		printf("Profile %d, stored at %p, ", i, current->data);
		
		if (current->data)
		{
			int j = 0;
			transformer_ll *ct = current->data->pipeline.transformers;
			
			while (ct)
			{
				ct = ct->next;
				j++;
			}
			printf("has name %s, and has %d transformers%s", current->data->name ? current->data->name : "(NULL)", j, (j > 0) ? ", which are\n" : "\n\n");
			
			ct = current->data->pipeline.transformers;
			
			while (ct)
			{
				printf("\t%s,\n", (ct->data && transformer_type_name(ct->data->type)) ? transformer_type_name(ct->data->type) : "UNKNOWN");
				ct = ct->next;
			}
		}
		printf("it is%s the default profile.\n", current->data->default_profile ? "" : " NOT");
		current = current->next;
		i++;
	}
	
	if (i == 0)
	{
		printf("There are none!\n");
	}
}

int cxt_set_all_profiles_left_button_to_main_menu(m_int_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	profile_ll *current = cxt->profiles;
	
	while (current)
	{
		if (current->data && current->data->view_page)
		{
			profile_view_set_left_button_mode(current->data->view_page, LEFT_BUTTON_MENU);
		}
		
		current = current->next;
	}
	
	return NO_ERROR;
}

int cxt_handle_hw_switch(m_int_context *cxt, int sw)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	printf("cxt_handle_hw_switch, sw = %d\n", sw);
	
	if (cxt->sequence)
	{
		if (sw == 0)
			m_sequence_regress(cxt->sequence);
		else if (sw == 1)
			m_sequence_advance(cxt->sequence);
	}
	
	return NO_ERROR;
}

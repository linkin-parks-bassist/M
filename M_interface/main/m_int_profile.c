#include "m_int.h"

static const char *TAG = "m_int_profile.c";

IMPLEMENT_LINKED_PTR_LIST(m_int_profile);

int init_m_int_profile(m_int_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	profile->id = 0;
	
	int ret_val = init_m_int_pipeline(&profile->pipeline);
	
	profile->view_page = NULL;
	profile->name = NULL;
	profile->id = 0;
	
	profile->fname = NULL;
	
	profile->active = 0;
	profile->unsaved_changes = 1;
	profile->gbs = NULL;
	
	profile->listings = NULL;
	profile->default_profile = 0;
	
	if (ret_val != NO_ERROR)
		return ret_val;
	
	init_parameter(&profile->volume, "Volume", 0.0, -12.0, 12.0);
	profile->volume.units = " dB";
	profile->volume.id = (m_int_parameter_id){.profile_id = 0, .transformer_id = 0xFFFF, .parameter_id = 0};
	
	return NO_ERROR;
}

int profile_set_id(m_int_profile *profile, uint16_t id)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	profile->id = id;
	profile->volume.id.profile_id = id;
	
	if (profile->pipeline.transformers)
	{
		transformer_ll *current = profile->pipeline.transformers;
		
		while (current)
		{
			if (current->data)
			{
				current->data->profile_id = id;
			}
			current = current->next;
		}
	}
	
	return NO_ERROR;
}

int m_int_profile_set_active(m_int_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	profile->active = 1;
	
	menu_item_ll *current = profile->listings;
	
	while (current)
	{
		profile_listing_menu_item_refresh_active(current->data);
		current = current->next;
	}
	
	return NO_ERROR;
}

int m_int_profile_set_inactive(m_int_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	profile->active = 0;
	
	menu_item_ll *current = profile->listings;
	
	while (current)
	{
		profile_listing_menu_item_refresh_active(current->data);
		current = current->next;
	}
	
	return NO_ERROR;
}

int m_int_profile_add_menu_listing(m_int_profile *profile, m_int_menu_item *listing)
{
	if (!profile || !listing)
		return ERR_NULL_PTR;
	
	menu_item_ll *nl = m_int_menu_item_ptr_linked_list_append(profile->listings, listing);
	
	if (nl)
		profile->listings = nl;
	else
		return ERR_ALLOC_FAIL;
	
	return NO_ERROR;
}

int profile_add_gb_reference(m_int_profile *profile, m_int_glide_button *gb)
{
	if (!profile || !gb)
		return ERR_NULL_PTR;
	
	glide_button_ll *nl = m_int_glide_button_ptr_linked_list_append(profile->gbs, gb);
	
	if (nl)
		profile->gbs = nl;
	else
		return ERR_ALLOC_FAIL;
	
	return NO_ERROR;
}


int m_int_profile_set_default_name_from_id(m_int_profile *profile)
{
	printf("m_int_profile_set_default_name_from_id\n");
	if (!profile)
		return ERR_NULL_PTR;
	
	printf("ID = %d\n", profile->id);
	
	// Compute the digits in the ID. 
	int id_digits;
	int id_div = profile->id + 1;
	
	for (id_digits = 0; id_div || !id_digits; id_div = id_div / 10)
		id_digits++;
	
	if (profile->name)
		m_int_free(profile->name);
	
	profile->name = m_int_malloc(9 + id_digits);
	
	if (!profile->name)
		return ERR_ALLOC_FAIL;
	
	sprintf(profile->name, "Profile %d", profile->id + 1);
	
	printf("Resulting name: %s\n", profile->name);
	
	return NO_ERROR;
}

m_int_transformer *m_int_profile_append_transformer_type(m_int_profile *profile, uint16_t type)
{
	if (!profile)
		return NULL;
	
	m_int_transformer *trans = m_int_pipeline_append_transformer_type(&profile->pipeline, type);
	
	if (!trans)
		return NULL;
	
	trans->profile_id = profile->id;
	trans->profile = profile;
	
	return trans;
}


int m_int_profile_remove_transformer(m_int_profile *profile, uint16_t id)
{
	printf("cxt_remove_transformer\n");
	if (!profile)
		return ERR_NULL_PTR;
	
	int ret_val = m_int_pipeline_remove_transformer(&profile->pipeline, id);
	
	printf("cxt_remove_transformer done. ret_val = %s\n", m_error_code_to_string(ret_val));
	return ret_val;
}

int clone_profile(m_int_profile *dest, m_int_profile *src)
{
	if (!src || !dest)
		return ERR_NULL_PTR;
	
	printf("Cloning profile\n");
	
	printf("Clone name...\n");
	dest->name = m_int_strndup(src->name, PROFILE_NAM_ENG_MAX_LEN);
	clone_parameter(&dest->volume, &src->volume);
	dest->id = src->id;
	
	printf("Clone pipeline...\n");
	clone_pipeline(&dest->pipeline, &src->pipeline);
	
	printf("Done!\n");
	dest->view_page = NULL;
	
	return NO_ERROR;
}

void gut_profile(m_int_profile *profile)
{
	if (!profile)
		return;
	
	printf("Gut view page %p...\n", profile->view_page);
	if (profile->view_page)
		profile->view_page->free_all(profile->view_page);
	
	profile->view_page = NULL;
	
	printf("Gut name %p...\n", profile->name);
	if (profile->name)
		m_int_free(profile->name);
	
	profile->name = NULL;
	
	printf("Gut profile...\n");
	gut_pipeline(&profile->pipeline);
	printf("Done!\n");
}

void free_profile(m_int_profile *profile)
{
	if (!profile)
		return;
		
	gut_profile(profile);
	
	m_int_free(profile);
}

int profile_propagate_name_change(m_int_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	if (profile->view_page)
	{
		profile_view_change_name(profile->view_page, profile->name);
	}
	
	menu_item_ll *current_mi = profile->listings;
	
	while (current_mi)
	{
		profile_listing_menu_item_change_name(current_mi->data, profile->name);
		current_mi = current_mi->next;
	}
	
	glide_button_ll *current_gb = profile->gbs;
	
	while (current_gb)
	{
		glide_button_change_label(current_gb->data, profile->name);
		current_gb = current_gb->next;
	}
	
	return NO_ERROR;
}

void new_profile_receive_id(et_msg msg, te_msg response)
{
	m_int_profile *profile = msg.cb_arg;
	
	if (!profile)
	{
		printf("ERROR: Profile ID recieved, but no profile associated !\n");
		return;
	}
	
	uint16_t id;
	memcpy(&id, response.data, sizeof(uint16_t));
	
	printf("New profile recieved its ID: %d\n", id);
	
	profile_set_id(profile, id);
	m_int_profile_set_default_name_from_id(profile);
	
	if (lvgl_port_lock(-1))
	{
		profile_propagate_name_change(profile);
		lvgl_port_unlock();
	}
}

m_int_profile *create_new_profile_with_teensy()
{
	m_int_profile *new_profile = m_int_context_add_profile_rp(&global_cxt);
	
	if (!new_profile)
	{
		printf("ERROR: Couldn't create new profile\n");
		return NULL;
	}
	
	et_msg msg = create_et_msg_nodata(ET_MESSAGE_CREATE_PROFILE);
	
	msg.callback = new_profile_receive_id;
	msg.cb_arg = new_profile;
	
	queue_msg_to_teensy(msg);
	
	create_profile_view_for(new_profile);
	
	printf("create_new_profile_with_teensy: global_cxt.ui_cxt.profile_list = %p\n", global_cxt.ui_cxt.profile_list);
	if (global_cxt.ui_cxt.profile_list)
	{
		profile_list_add_profile(global_cxt.ui_cxt.profile_list, new_profile);
	}
	
	return new_profile;
}

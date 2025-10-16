#include "em.h"

static const char *TAG = "em_profile.c";

IMPLEMENT_LINKED_PTR_LIST(em_profile);

int init_em_profile(em_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	profile->id = 0;
	
	int ret_val = init_em_pipeline(&profile->pipeline);
	
	profile->view_page = NULL;
	profile->name = NULL;
	profile->id = 0;
	
	profile->fname = NULL;
	
	profile->active = 0;
	profile->unsaved_changes = 1;
	
	profile->listings = NULL;
	
	if (ret_val != NO_ERROR)
		return ret_val;
	
	return NO_ERROR;
}

int em_profile_set_active(em_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	profile->active = 1;
	
	menu_item_ll *current = profile->listings;
	
	while (current)
	{
		profile_listing_menu_item_refresh_active(current->data, profile->active);
		current = current->next;
	}
	
	return NO_ERROR;
}

int em_profile_set_inactive(em_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	profile->active = 0;
	
	menu_item_ll *current = profile->listings;
	
	while (current)
	{
		profile_listing_menu_item_refresh_active(current->data, profile->active);
		current = current->next;
	}
	
	return NO_ERROR;
}

int em_profile_add_menu_listing(em_profile *profile, em_menu_item *listing)
{
	if (!profile || !listing)
		return ERR_NULL_PTR;
	
	menu_item_ll *nl = em_menu_item_ptr_linked_list_append(profile->listings, listing);
	
	if (nl)
		profile->listings = nl;
	else
		return ERR_ALLOC_FAIL;
	
	return NO_ERROR;
}

int em_profile_set_default_name_from_id(em_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	// Compute the digits in the ID. 
	int id_digits;
	int id_div = profile->id;
	
	for (id_digits = 0; id_div || !id_digits; id_div = id_div / 10)
		id_digits++;
	
	profile->name = malloc(9 + id_digits);
	
	if (!profile->name)
		return ERR_ALLOC_FAIL;
	
	sprintf(profile->name, "Profile %d", id_digits);
	
	return NO_ERROR;
}

em_transformer *em_profile_append_transformer_type(em_profile *profile, uint16_t type)
{
	if (!profile)
		return NULL;
	
	em_transformer *trans = em_pipeline_append_transformer_type(&profile->pipeline, type);
	
	if (!trans)
		return NULL;
	
	trans->profile_id = profile->id;
	
	return trans;
}


int em_profile_remove_transformer(em_profile *profile, uint16_t id)
{
	printf("cxt_remove_transformer\n");
	if (!profile)
		return ERR_NULL_PTR;
	
	int ret_val = em_pipeline_remove_transformer(&profile->pipeline, id);
	
	printf("cxt_remove_transformer done. ret_val = %s\n", m_error_code_to_string(ret_val));
	return ret_val;
}

int clone_profile(em_profile *dest, em_profile *src)
{
	if (!src || !dest)
		return ERR_NULL_PTR;
	
	printf("Cloning profile\n");
	
	printf("Clone name...\n");
	dest->name = strndup(src->name, PROFILE_NAME_MAX_LEN);
	dest->id = src->id;
	
	printf("Clone pipeline...\n");
	clone_pipeline(&dest->pipeline, &src->pipeline);
	
	printf("Done!\n");
	dest->view_page = NULL;
	
	return NO_ERROR;
}

void gut_profile(em_profile *profile)
{
	if (!profile)
		return;
	
	printf("Gut view page %p...\n", profile->view_page);
	if (profile->view_page)
		profile->view_page->free_all(profile->view_page);
	
	profile->view_page = NULL;
	
	printf("Gut name %p...\n", profile->name);
	if (profile->name)
		free(profile->name);
	
	profile->name = NULL;
	
	printf("Gut profile...\n");
	gut_pipeline(&profile->pipeline);
	printf("Done!\n");
}

void free_profile(em_profile *profile)
{
	if (!profile)
		return;
		
	gut_profile(profile);
	
	free(profile);
}

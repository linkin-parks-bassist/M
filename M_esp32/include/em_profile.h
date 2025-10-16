#ifndef EM_PROFILE_H_
#define EM_PROFILE_H_

#define PROFILE_NAME_MAX_LEN 128

struct em_menu_item_ptr_linked_list;

typedef struct em_profile
{
	char *name;
	uint16_t id;
	em_pipeline pipeline;
	
	em_ui_page *view_page;
	struct em_menu_item_ptr_linked_list *listings;
	
	char *fname;
	
	int active;
	int unsaved_changes;
} em_profile;

DECLARE_LINKED_PTR_LIST(em_profile);

int init_em_profile(em_profile *profile);
int init_em_pipeline(em_pipeline *pipeline);

int em_profile_set_default_name_from_id(em_profile *profile);

em_transformer *em_profile_append_transformer_type(em_profile *profile, uint16_t type);
int em_profile_remove_transformer(em_profile *profile, uint16_t id);

int clone_profile(em_profile *dest, em_profile *src);
void gut_profile(em_profile *profile);
void free_profile(em_profile *profile);

int em_profile_set_active(em_profile *profile);
int em_profile_set_inactive(em_profile *profile);

struct em_menu_item;

int em_profile_add_menu_listing(em_profile *profile, struct em_menu_item *listing);

#endif

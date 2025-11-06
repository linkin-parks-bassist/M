#ifndef M_INT_PROFILE_H_
#define M_INT_PROFILE_H_

#define PROFILE_NAM_ENG_MAX_LEN 128

struct m_int_menu_item_ptr_linked_list;

typedef struct m_int_profile
{
	char *name;
	uint16_t id;
	m_int_pipeline pipeline;
	
	m_int_ui_page *view_page;
	struct m_int_menu_item_ptr_linked_list *listings;
	
	m_int_parameter volume;
	
	char *fname;
	
	int active;
	int default_profile;
	int unsaved_changes;
} m_int_profile;

DECLARE_LINKED_PTR_LIST(m_int_profile);

int init_m_int_profile(m_int_profile *profile);
int init_m_int_pipeline(m_int_pipeline *pipeline);

int profile_set_id(m_int_profile *profile, uint16_t id);

int m_int_profile_set_default_name_from_id(m_int_profile *profile);
int profile_propagate_name_change(m_int_profile *profile);

m_int_transformer *m_int_profile_append_transformer_type(m_int_profile *profile, uint16_t type);
int m_int_profile_remove_transformer(m_int_profile *profile, uint16_t id);

int clone_profile(m_int_profile *dest, m_int_profile *src);
void gut_profile(m_int_profile *profile);
void free_profile(m_int_profile *profile);

int m_int_profile_set_active(m_int_profile *profile);
int m_int_profile_set_inactive(m_int_profile *profile);

void new_profile_receive_id(et_msg msg, te_msg response);

struct m_int_menu_item;

int m_int_profile_add_menu_listing(m_int_profile *profile, struct m_int_menu_item *listing);

#endif

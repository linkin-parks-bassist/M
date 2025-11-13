#ifndef M_INT_PROFILE_H_
#define M_INT_PROFILE_H_

#define PROFILE_NAM_ENG_MAX_LEN 128

#include "m_profile.h"

DECLARE_LINKED_PTR_LIST(m_profile);

int init_m_profile(m_profile *profile);
int init_m_pipeline(m_pipeline *pipeline);

int profile_set_id(m_profile *profile, uint16_t id);

int m_profile_set_default_name_from_id(m_profile *profile);
int profile_propagate_name_change(m_profile *profile);

m_transformer *m_profile_append_transformer_type(m_profile *profile, uint16_t type);
int m_profile_remove_transformer(m_profile *profile, uint16_t id);

int clone_profile(m_profile *dest, m_profile *src);
void gut_profile(m_profile *profile);
void free_profile(m_profile *profile);

int m_profile_set_active(m_profile *profile);
int m_profile_set_inactive(m_profile *profile);

void new_profile_receive_id(et_msg msg, te_msg response);

struct m_int_menu_item;

int m_profile_add_menu_listing(m_profile *profile, struct m_int_menu_item *listing);

m_profile *create_new_profile_with_teensy();

int profile_add_gb_reference(m_profile *profile, m_int_glide_button *gb);

#endif

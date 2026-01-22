#ifndef M_INT_PROFILE_H_
#define M_INT_PROFILE_H_

#define PROFILE_NAME_MAX_LEN 128

#define M_PROFILE_MUTEX_TIMEOUT_MS 10

#include "m_linked_list.h"
#include "m_int_parameter.h"
#include "m_profile.h"
#include "m_int_pipeline.h"
#include "m_int_transformer.h"
#include "m_comms.h"

DECLARE_LINKED_PTR_LIST(m_profile);

int init_m_profile(m_profile *profile);
int init_m_pipeline(m_pipeline *pipeline);

int profile_set_id(m_profile *profile, uint16_t id);

int m_profile_set_default_name_from_id(m_profile *profile);

m_transformer *m_profile_append_transformer_type(m_profile *profile, uint16_t type);
m_transformer *m_profile_append_transformer_eff(m_profile *profile, m_effect_desc *eff);
int m_profile_remove_transformer(m_profile *profile, uint16_t id);

int clone_profile(m_profile *dest, m_profile *src);
void gut_profile(m_profile *profile);
void free_profile(m_profile *profile);

int m_profile_set_active(m_profile *profile);
int m_profile_set_inactive(m_profile *profile);

void new_profile_receive_id(m_message msg, m_response response);

struct m_int_menu_item;

int m_profile_add_representation(m_profile *profile, m_representation *rep);
int m_profile_remove_representation(m_profile *profile, m_representation *rep);

int m_profile_add_name_representation(m_profile *profile, m_representation *rep);
int m_profile_remove_name_representation(m_profile *profile, m_representation *rep);

int m_profile_add_id_representation(m_profile *profile, m_representation *rep);
int m_profile_remove_id_representation(m_profile *profile, m_representation *rep);

m_profile *create_new_profile_with_teensy();

int m_profile_save(m_profile *profile);

int m_profile_update_representations		(m_profile *profile);
int m_profile_update_name_representations	(m_profile *profile);
int m_profile_update_id_representations		(m_profile *profile);

int m_profile_if_active_update_fpga(m_profile *profile);
int m_profile_program_fpga(m_profile *profile);

#endif

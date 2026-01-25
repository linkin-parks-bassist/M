#ifndef M_ESP32_CONTEXT_H_
#define M_ESP32_CONTEXT_H_

#define MAX_N_PROFILES 256

#include "m_int_sequence.h"
#include "m_linked_list.h"
#include "m_int_profile.h"
#include "m_int_settings.h"

#include "m_int_parameter.h"
#include "m_effect.h"

typedef m_profile_pll profile_ll;

typedef struct m_context
{
	int n_profiles;
	int active_profile_id;
	
	m_profile *working_profile;
	m_profile *active_profile;
	m_profile *default_profile;
	
	m_global_pages pages;
	
	profile_ll *profiles;
	sequence_ll *sequences;
	
	m_int_sequence main_sequence;
	m_int_sequence *sequence;
	
	int saved_profiles_loaded;
	int saved_sequences_loaded;
	
	m_settings settings;
	
	m_effect_desc_pll *effects;
} m_context;

extern m_context global_cxt;

int m_init_context(m_context *cxt);
int m_context_init_effect_list(m_context *cxt);
int m_context_init_main_sequence(m_context *cxt);
int m_context_init_ui(m_context *cxt);

int m_context_enlarge_profile_array(m_context *cxt);
int m_context_set_n_profiles(m_context *cxt, int n);
int m_context_add_profile(m_context *cxt);
m_profile *m_context_add_profile_rp(m_context *cxt);

m_int_sequence *m_context_add_sequence_rp(m_context *cxt);

m_transformer *cxt_get_transformer_by_id(m_context *cxt, uint16_t profile_id, uint16_t transformer_id);
m_parameter *cxt_get_parameter_by_id(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id);
int cxt_get_parameter_and_transformer_by_id(m_context *cxt, m_parameter_id id, m_parameter **pp, m_transformer **tp);
m_setting *cxt_get_setting_by_id(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id);

int cxt_transformer_id_to_position(m_context *cxt, uint16_t profile_id, uint16_t transformer_id);
int cxt_transformer_position_to_id(m_context *cxt, uint16_t profile_id, uint16_t transformer_pos);

int cxt_remove_transformer(m_context *cxt, uint16_t pid, uint16_t tid);
int cxt_remove_profile(m_context *cxt, m_profile *profile);
int cxt_remove_sequence(m_context *cxt, m_int_sequence *sequence);

int set_active_profile(m_profile *profile);
int set_active_profile_from_sequence(m_profile *profile);
int set_working_profile(m_profile *profile);

int context_no_default_profile(m_context *cxt);
int resolve_default_profile(m_context *cxt);

int set_profile_as_default(m_context *cxt, m_profile *profile);

void context_print_profiles(m_context *cxt);

int cxt_set_all_profiles_left_button_to_main_menu(m_context *cxt);

int cxt_handle_hw_switch(m_context *cxt, int sw);

m_profile *cxt_find_profile(m_context *cxt, const char *fname);

#endif

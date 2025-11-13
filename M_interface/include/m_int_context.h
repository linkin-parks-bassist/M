#ifndef M_ESP32_CONTEXT_H_
#define M_ESP32_CONTEXT_H_

#define MAX_N_PROFILES 256

typedef m_profile_pll profile_ll;

typedef struct
{
	int n_profiles;
	int active_profile_id;
	
	m_profile *working_profile;
	m_profile *active_profile;
	m_profile *default_profile;
	
	m_int_ui_context ui_cxt;
	
	profile_ll *profiles;
	sequence_ll *sequences;
	
	m_int_sequence *sequence;
	
	int saved_profiles_loaded;
	int default_profile_exists;
	
	m_settings settings;
} m_int_context;

extern m_int_context global_cxt;

int init_m_int_context(m_int_context *cxt);

int m_int_context_enlarge_profile_array(m_int_context *cxt);
int m_int_context_set_n_profiles(m_int_context *cxt, int n);
int m_int_context_add_profile(m_int_context *cxt);
m_profile *m_int_context_add_profile_rp(m_int_context *cxt);

m_int_sequence *m_int_context_add_sequence_rp(m_int_context *cxt);

m_transformer *cxt_get_transformer_by_id(m_int_context *cxt, uint16_t profile_id, uint16_t transformer_id);
m_parameter *cxt_get_parameter_by_id(m_int_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id);
m_setting *cxt_get_setting_by_id(m_int_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id);

int cxt_transformer_id_to_position(m_int_context *cxt, uint16_t profile_id, uint16_t transformer_id);
int cxt_transformer_position_to_id(m_int_context *cxt, uint16_t profile_id, uint16_t transformer_pos);

int cxt_remove_transformer(m_int_context *cxt, uint16_t pid, uint16_t tid);
int cxt_remove_profile(m_int_context *cxt, m_profile *profile);
int cxt_remove_sequence(m_int_context *cxt, m_int_sequence *sequence);

int set_active_profile(m_profile *profile);
int set_working_profile(m_profile *profile);

int context_no_default_profile(m_int_context *cxt);
int resolve_default_profile(m_int_context *cxt);

int set_profile_as_default(m_int_context *cxt, m_profile *profile);

void context_print_profiles(m_int_context *cxt);

int cxt_set_all_profiles_left_button_to_main_menu(m_int_context *cxt);

int cxt_handle_hw_switch(m_int_context *cxt, int sw);

#endif

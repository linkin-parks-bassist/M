#ifndef M_ESP32_CONTEXT_H_
#define M_ESP32_CONTEXT_H_

#define MAX_N_PROFILES 256

typedef em_profile_ptr_linked_list profile_ll;

typedef struct
{
	int n_profiles;
	int active_profile_id;
	
	em_profile *working_profile;
	em_profile *active_profile;
	
	em_ui_context ui_cxt;
	
	em_profile_ptr_linked_list *profiles;
	
	int saved_profiles_loaded;
} em_context;

extern em_context global_cxt;

int init_em_context(em_context *cxt);

int em_context_enlarge_profile_array(em_context *cxt);
int em_context_set_n_profiles(em_context *cxt, int n);
int em_context_add_profile(em_context *cxt);

em_transformer *cxt_get_transformer_by_id(em_context *cxt, uint16_t profile_id, uint16_t transformer_id);
em_parameter *cxt_get_parameter_by_id(em_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id);
em_option *cxt_get_option_by_id(em_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t option_id);

int cxt_transformer_id_to_position(em_context *cxt, uint16_t profile_id, uint16_t transformer_id);
int cxt_transformer_position_to_id(em_context *cxt, uint16_t profile_id, uint16_t transformer_pos);

int cxt_remove_profile(em_context *cxt, em_profile *profile);
int cxt_remove_transformer(em_context *cxt, uint16_t pid, uint16_t tid);

int set_active_profile(em_profile *profile);

#endif

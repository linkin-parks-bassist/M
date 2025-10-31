#ifndef M_CONTEXT_H_
#define M_CONTEXT_H_

#include "tm_profile.h"
#include "m_vec2i.h"

#define M_PROFILE_SWITCH_SAMPLES 	256
#define PROFILES_MALLOC_CHUNK_SIZE 	16
#define PROFILE_ARRAY_INITIAL_SIZE	64

#define SILENCE_ENERGY_THRESHOLD 	2000
#define SILENCE_BLOCKS_THRESHOLD 	64

#define DECLICK_BUFSIZE 6

#define CLICK_SLOPE_THRESHOLD 0.5

//#define PRINT_TIMES
//#define PRINT_BLOCKS
//#define PRETTY_PRINT_BLOCKS
//#define PRINT_PROFILE

typedef struct
{
	uint16_t status_flags;
	
	int n_profiles;
	int profile_array_size;
	tm_profile *profiles;
	
	int active_profile;
	int profile_switch_triggered;
	int new_profile;
	
	tm_pipeline *unconpfigured_pipeline;
	
	int profiles_switching;
	int profile_switch_progress;
	int profile_switch_samples;
	int profile_switch_type;
	
	float declick_buffer[DECLICK_BUFSIZE];
	
	int profile_maintainance_index;
	float prev_block[AUDIO_BLOCK_SAMPLES];
	
	int runs;
	
	tm_high_pass_filter_str output_hpf;
	tm_low_pass_filter_str input_lpf;
	tm_transformer output_amp;
} tm_context;

int init_tm_context(tm_context *cxt);

int tm_context_new_profile(tm_context *cxt);

extern tm_context global_cxt;

int cxt_set_active_profile(tm_context *cxt, uint16_t pid);
int cxt_switch_to_profile (tm_context *cxt, uint16_t pid);

int cxt_profile_id_valid	(tm_context *cxt, uint16_t pid);
int cxt_transformer_id_valid(tm_context *cxt, uint16_t pid, uint16_t tid);
int cxt_parameter_id_valid	(tm_context *cxt, uint16_t pid, uint16_t tid, uint16_t ppid);

tm_parameter *cxt_get_parameter_by_id(tm_context *cxt, uint16_t pid, uint16_t tid, uint16_t ppid);
int      	  cxt_update_parameter_value_by_id(tm_context *cxt, uint16_t pid, uint16_t tid, uint16_t ppid, float new_value);

tm_setting *cxt_get_setting_by_id(tm_context *cxt, uint16_t pid, uint16_t tid, uint16_t oid);
int        cxt_update_setting_value_by_id(tm_context *cxt, uint16_t pid, uint16_t tid, uint16_t oid, uint16_t new_value);

int cxt_append_transformer_to_profile (tm_context *cxt, uint16_t pid, uint16_t type);
int cxt_remove_transformer_from_profile(tm_context *cxt, uint16_t pid, uint16_t tid);
int cxt_insert_transformer_to_profile (tm_context *cxt, uint16_t pid, uint16_t type, uint16_t pos);
int cxt_prepend_transformer_to_profile(tm_context *cxt, uint16_t pid, uint16_t type);

int cxt_get_n_profile_transformers(tm_context *cxt, uint16_t pid);
int cxt_get_n_transformer_params  (tm_context *cxt, uint16_t pid, uint16_t tid);
int cxt_get_n_transformer_settings (tm_context *cxt, uint16_t pid, uint16_t tid);
int cxt_get_transformer_type	  (tm_context *cxt, uint16_t pid, uint16_t tid);
int cxt_get_tid_by_pos 			  (tm_context *cxt, uint16_t pid, uint16_t pos);

tm_transformer *cxt_get_transformer_by_id(tm_context *cxt, uint16_t pid, uint16_t tid);

int cxt_move_transformer(tm_context *cxt, uint16_t tid, uint16_t new_pos);

int cxt_process(tm_context *cxt);

void tm_safe_reboot(tm_context *cxt);
int reset_context(tm_context *cxt);

int cxt_run_scheduled_maintainance(tm_context *cxt);

#endif

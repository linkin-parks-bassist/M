#ifndef M_CONTEXT_H_
#define M_CONTEXT_H_

#include "m_eng_profile.h"
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
	m_eng_profile *profiles;
	
	int active_profile;
	int profile_switch_triggered;
	int new_profile;
	
	#ifdef GRAPH_PIPELIME
	m_eng_pipeline *unconpfigured_pipeline;
	#endif
	
	int profiles_switching;
	int profile_switch_progress;
	int profile_switch_samples;
	int profile_switch_type;
	
	float declick_buffer[DECLICK_BUFSIZE];
	
	int profile_maintainance_index;
	float prev_block[AUDIO_BLOCK_SAMPLES];
	
	int runs;
	
	m_eng_high_pass_filter_str output_hpf;
	m_eng_low_pass_filter_str input_lpf;
	m_eng_transformer output_amp;
} m_eng_context;

int init_m_eng_context(m_eng_context *cxt);

int m_eng_context_new_profile(m_eng_context *cxt);

extern m_eng_context global_cxt;

int cxt_set_active_profile(m_eng_context *cxt, uint16_t pid);
int cxt_switch_to_profile (m_eng_context *cxt, uint16_t pid);

int cxt_profile_id_valid	(m_eng_context *cxt, uint16_t pid);
int cxt_transformer_id_valid(m_eng_context *cxt, uint16_t pid, uint16_t tid);
int cxt_parameter_id_valid	(m_eng_context *cxt, uint16_t pid, uint16_t tid, uint16_t ppid);

m_eng_parameter *cxt_get_parameter_by_id(m_eng_context *cxt, uint16_t pid, uint16_t tid, uint16_t ppid);
int      	  cxt_update_parameter_value_by_id(m_eng_context *cxt, uint16_t pid, uint16_t tid, uint16_t ppid, float new_value);

m_eng_setting *cxt_get_setting_by_id(m_eng_context *cxt, uint16_t pid, uint16_t tid, uint16_t sid);
int        cxt_update_setting_value_by_id(m_eng_context *cxt, uint16_t pid, uint16_t tid, uint16_t sid, uint16_t new_value);

int cxt_append_transformer_to_profile (m_eng_context *cxt, uint16_t pid, uint16_t type);
int cxt_remove_transformer_from_profile(m_eng_context *cxt, uint16_t pid, uint16_t tid);
int cxt_insert_transformer_to_profile (m_eng_context *cxt, uint16_t pid, uint16_t type, uint16_t pos);
int cxt_prepend_transformer_to_profile(m_eng_context *cxt, uint16_t pid, uint16_t type);

int cxt_get_n_profile_transformers(m_eng_context *cxt, uint16_t pid);
int cxt_get_n_transformer_params  (m_eng_context *cxt, uint16_t pid, uint16_t tid);
int cxt_get_n_transformer_settings (m_eng_context *cxt, uint16_t pid, uint16_t tid);
int cxt_get_transformer_type	  (m_eng_context *cxt, uint16_t pid, uint16_t tid);
int cxt_get_tid_by_pos 			  (m_eng_context *cxt, uint16_t pid, uint16_t pos);

m_eng_transformer *cxt_get_transformer_by_id(m_eng_context *cxt, uint16_t pid, uint16_t tid);

int cxt_move_transformer(m_eng_context *cxt, uint16_t tid, uint16_t new_pos);

int cxt_process(m_eng_context *cxt);

void m_eng_safe_reboot(m_eng_context *cxt);
int reset_context(m_eng_context *cxt);

int cxt_run_scheduled_maintainance(m_eng_context *cxt);

#endif

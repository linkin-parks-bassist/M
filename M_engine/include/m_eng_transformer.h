#ifndef M_TRANSFORMER_H_
#define M_TRANSFORMER_H_

#include "m_transformer_enum.h"
#include "m_vec2i.h"

#include "m_eng_parameter.h"

#define TRANSFORMER_MAX_INPUTS		4
#define TRANSFORMER_MAX_OUTPUTS		4

#define FADER_FADE_IN  0
#define FADER_FADE_OUT 1

#define PRINT_TRANSFORMER_INFO

#define TRANSFORMER_SWITCH_ACTION_BYPASS 0

#define TRANSFORMER_TRANSITION_INSTANT			0
#define TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR 1
#define TRANSFORMER_TRANSITION_BIBLOCK_LINEAR 	2
#define TRANSFORMER_TRANSITION_QUADBLOCK_LINEAR 3
#define TRANSFORMER_TRANSITION_TAIL				4

#define N_NATIVE_PARAMETERS 3
#define N_NATIVE_SETTINGS 1

#include "m_eng_linkowitz_riley.h"

typedef struct
{
	uint16_t type;
	uint16_t id;
	
	unsigned int n_inputs, n_outputs;
	
	int bypass;
	
	vec2i inputs [TRANSFORMER_MAX_INPUTS ];
	vec2i outputs[TRANSFORMER_MAX_OUTPUTS];

	int n_settings;
	int setting_array_size;
	m_eng_setting **settings;
	
	m_eng_setting band_mode;

	int n_parameters;
	int parameter_array_size;
	m_eng_parameter **parameters;
	
	m_eng_parameter wet_mix;
	m_eng_parameter band_lp_cutoff;
	m_eng_parameter band_hp_cutoff;
	m_eng_parameter band_center;
	m_eng_parameter band_width;
	
	m_eng_lr_low_pass_filter_str  input_lpf;
	m_eng_lr_high_pass_filter_str input_hpf;
	
	void *data_struct;
	int (*compute_transformer)(void *data_struct, float *dest, float *src, int n_samples);
	int (*compute_transformer_nl)(void *data_struct, float **dest, float **src, int n_samples);
	
	int (*reconfigure)(void *data_struct);
	int (*clone_struct)(void *dest, void *src);
	int (*free_struct)(void *data_struct);
	
	int runs;
	size_t struct_size;
	int transition_policy;
} m_eng_transformer;

int transformer_add_setting(m_eng_transformer *trans, m_eng_setting *setting);
int transformer_add_parameter(m_eng_transformer *trans, m_eng_parameter *param);

m_eng_parameter *transformer_get_parameter(m_eng_transformer *trans, uint16_t ppid);
m_eng_setting   *transformer_get_setting  (m_eng_transformer *trans, uint16_t sid );

int transformer_init_parameter_array(m_eng_transformer *trans, int n);
int transformer_init_setting_array(m_eng_transformer *trans, int n);

int run_transformer(m_eng_transformer *trans, float *dest, float *src);

void free_transformer(m_eng_transformer *trans);

int clone_transformer(m_eng_transformer **dest_ptr, m_eng_transformer *src);

const char *transformer_type_to_string(uint16_t type);

int transformer_init_controls(m_eng_transformer *trans);

#endif

#ifndef M_ENG_TRANSFORMER_H_
#define M_ENG_TRANSFORMER_H_

#include "m_transformer_enum.h"

#include "m_parameter.h"

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

#include "m_transformer.h"

int transformer_add_setting(m_transformer *trans, m_setting *setting);
int transformer_add_parameter(m_transformer *trans, m_parameter *param);

m_parameter *transformer_get_parameter(m_transformer *trans, uint16_t ppid);
m_setting   *transformer_get_setting  (m_transformer *trans, uint16_t sid );

int transformer_init_parameter_array(m_transformer *trans, int n);
int transformer_init_setting_array(m_transformer *trans, int n);

int run_transformer(m_transformer *trans, float *dest, float *src);

void free_transformer(m_transformer *trans);

int clone_transformer(m_transformer **dest_ptr, m_transformer *src);

const char *transformer_type_to_string(uint16_t type);

int transformer_init_controls(m_transformer *trans);

#endif

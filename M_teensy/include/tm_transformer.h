#ifndef M_TRANSFORMER_H_
#define M_TRANSFORMER_H_

#include "m_vec2i.h"

#define TRANSFORMER_MAX_INPUTS		4
#define TRANSFORMER_MAX_OUTPUTS		4

#include "m_transformer_enum.h"

#define FADER_FADE_IN  0
#define FADER_FADE_OUT 1

#define PRINT_TRANSFORMER_INFO

#define TRANSFORMER_SWITCH_ACTION_BYPASS 0

#define TRANSFORMER_TRANSITION_INSTANT			0
#define TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR 1
#define TRANSFORMER_TRANSITION_BIBLOCK_LINEAR 	2
#define TRANSFORMER_TRANSITION_QUADBLOCK_LINEAR 3
#define TRANSFORMER_TRANSITION_TAIL				4

typedef struct
{
	uint16_t type;
	uint16_t id;
	
	unsigned int n_inputs, n_outputs;
	
	int bypass;
	
	vec2i inputs [TRANSFORMER_MAX_INPUTS ];
	vec2i outputs[TRANSFORMER_MAX_OUTPUTS];

	int n_options;
	int option_array_size;
	tm_option **options;

	int n_parameters;
	int parameter_array_size;
	tm_parameter **parameters;
	
	void *data_struct;
	int (*compute_transformer)(void *data_struct, float *dest, float *src, int n_samples);
	int (*compute_transformer_nl)(void *data_struct, float **dest, float **src, int n_samples);
	
	int (*reconfigure)(void *data_struct);
	int (*free_struct)(void *data_struct);
	
	int runs;
	int transition_policy;
} tm_transformer;

int transformer_add_option(tm_transformer *trans, tm_option *option);
int transformer_add_parameter(tm_transformer *trans, tm_parameter *param);

tm_parameter *transformer_get_parameter(tm_transformer *trans, uint16_t ppid);
tm_option *transformer_get_option(tm_transformer *trans, uint16_t oid);

int transformer_init_parameter_array(tm_transformer *trans, int n);
int transformer_init_option_array(tm_transformer *trans, int n);

int run_transformer(tm_transformer *trans, float *dest, float *src);

void free_transformer(tm_transformer *trans);

const char *transformer_type_to_string(uint16_t type);

#endif

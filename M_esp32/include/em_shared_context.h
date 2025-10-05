#ifndef ESP32_CONTEXT_H_
#define ESP32_CONTEXT_H_

#define MAX_N_PROFILES 256

typedef struct
{
	char *name;
	m_param_option_t val;
} parameter_option;

typedef struct
{
	m_param_type type;
	
	m_param_value val;
	m_param_value min;
	m_param_value max;
	
	m_parameter_id id;
	
	char *name;
	
	int n_options;
	parameter_option *options;
} teensy_parameter;

/* Stripped-down structs to keep track of what is going on in Teensyland */
typedef struct
{
	uint16_t profile_id;
	uint16_t transformer_id;
	
	int type;
	int position;
	
	int n_parameters;
	int parameter_array_length;
	teensy_parameter *parameters;
} teensy_transformer;

typedef struct
{
	int width, height;
	
	int n_transformers;
	int transformer_array_length;
	teensy_transformer *transformers;
} teensy_pipeline;

typedef struct
{
	char *name;
	uint16_t id;
	teensy_pipeline pipeline;
} teensy_profile;

typedef struct
{
	int n_profiles;
	int active_profile;
	
	int profile_array_length;
	
	teensy_profile *profiles;
} teensy_context;

int init_teensy_context(teensy_context *cxt);
int teensy_context_enlarge_profile_array(teensy_context *cxt);

int teensy_context_set_n_profiles(teensy_context *cxt, int n);

int teensy_context_add_profile(teensy_context *cxt);

int init_teensy_profile(teensy_profile *profile);
int init_teensy_pipeline(teensy_pipeline *pipeline);

int teensy_profile_set_default_name_from_id(teensy_profile *profile);

int teensy_pipeline_enlarge_transformer_array(teensy_pipeline *pipeline);

int teensy_pipeline_set_n_transformers(teensy_pipeline *pipeline, int n);

int teensy_pipeline_append_transformer_type (teensy_pipeline *pipeline, uint16_t type);
int teensy_pipeline_insert_transformer_type (teensy_pipeline *pipeline, uint16_t type, int position);
int teensy_pipeline_prepend_transformer_type(teensy_pipeline *pipeline, uint16_t type);

int init_teensy_transformer(teensy_transformer *trans);
int teensy_transformer_enlarge_parameter_array(teensy_transformer *trans);

int teensy_transformer_set_n_parameters(teensy_transformer *trans, int n);

int teensy_transformer_add_parameter(teensy_transformer *trans, teensy_parameter *param);

int init_teensy_parameter(teensy_parameter *param);

teensy_transformer *cxt_get_transformer_by_id(teensy_context *cxt, uint16_t profile_id, uint16_t transformer_id);
teensy_parameter *cxt_get_parameter_by_id(teensy_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id);

int cxt_transformer_id_to_position(teensy_context *cxt, uint16_t profile_id, uint16_t transformer_id);
int cxt_transformer_position_to_id(teensy_context *cxt, uint16_t profile_id, uint16_t transformer_pos);

int init_default_transformer_by_type(teensy_transformer *trans, uint16_t type, uint16_t profile_id, uint16_t transformer_id);

#endif

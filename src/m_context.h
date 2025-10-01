#ifndef M_CONTEXT_H_
#define M_CONTEXT_H_

#define MAX_N_PROFILES 128

typedef struct
{
	uint16_t status_flags;
	
	m_pipeline *active_pipeline;
	
	int n_profiles;
	int active_profile;
	m_profile profiles[MAX_N_PROFILES];
	
	m_pipeline *unconfigured_pipeline;
} m_context;

int init_m_context(m_context *cxt);

int m_context_new_profile(m_context *cxt);

extern m_context global_cxt;

int update_paramter_value_by_id (m_context *cxt, m_parameter_id id, m_param_value new_value);
m_parameter *get_parameter_by_id(m_context *cxt, m_parameter_id id);

int cxt_add_transformer_to_profile(m_context *cxt, uint16_t profile_id, uint16_t type);

int cxt_get_n_profile_transformers(m_context *cxt, uint16_t profile_id);
int cxt_get_n_transformer_params  (m_context *cxt, uint16_t profile_id, uint16_t transformer_id);
int cxt_get_transformer_type	  (m_context *cxt, uint16_t profile_id, uint16_t transformer_id);

m_param_type  cxt_get_parameter_type (m_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id);
m_param_value cxt_get_parameter_value(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id);
int			  cxt_set_parameter_value(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id, m_param_value new_value);

char *cxt_get_parameter_name	(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id);
int   cxt_set_parameter_name	(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id, const char *new_name);

vec2i cxt_get_transformer_input (m_context *cxt, uint16_t profile_id, uint16_t transformer_id, int input);
int   cxt_set_transformer_input (m_context *cxt, uint16_t profile_id, uint16_t transformer_id, int input, int nx, int ny);
vec2i cxt_get_transformer_output(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, int output);
int   cxt_set_transformer_output(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, int output, int nx, int ny);

void m_safe_reboot(m_context *cxt);
int reset_context(m_context *cxt);

#endif

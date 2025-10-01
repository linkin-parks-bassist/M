#include "M.h"

int init_m_context(m_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	cxt->n_profiles = 1;
	cxt->active_profile = 0;
	
	init_bypass_profile(&cxt->profiles[0]);
	cxt->active_pipeline = &cxt->profiles[0].pipeline;
	
	for (int i = 1; i < MAX_N_PROFILES; i++)
		nullify_profile(&cxt->profiles[i]);
	
	cxt->unconfigured_pipeline = NULL;
	
	cxt->status_flags = M_STATUS_FRESH_BOOT;
	
	return NO_ERROR;
}

/* Returns error codes in negative; otherwise, returns the index (ID) of the new profile */
int m_context_new_profile(m_context *cxt)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	if (cxt->n_profiles >= MAX_N_PROFILES)
		return -ERR_FIXED_ARRAY_FULL;
	
	init_profile(&cxt->profiles[cxt->n_profiles++]);
	
	return cxt->n_profiles - 1;
}

int update_paramter_value_by_id(m_context *cxt, m_parameter_id id, m_param_value new_value)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	if (!parameter_id_str_valid(cxt, id))
		return ERR_BAD_ARGS;
	
	m_parameter *param = cxt->profiles[id.profile_id].pipeline.transformers[id.transformer_id]->parameters[id.parameter_id];
	
	if (!param)
		return ERR_BAD_ARGS;
	
	m_printf("Changing parameter %d.%d.%d to value ", id.profile_id, id.transformer_id, id.parameter_id);
	switch (param->type)
	{
		case M_PARAM_OPTION:
			m_printf("%d\n", new_value.option);
			break;
		case M_PARAM_SWITCH:
			m_printf("%d\n", new_value.active);
			break;
		default:
			m_printf("%.2f\n", new_value.level);
			break;
	}
	
	param->val = new_value;
	param->updated = 1;
	
	return NO_ERROR;
}

m_parameter *get_parameter_by_id(m_context *cxt, m_parameter_id id)
{
	if (!parameter_id_str_valid(cxt, id))
		return NULL;
	
	return cxt->profiles[id.profile_id].pipeline.transformers[id.transformer_id]->parameters[id.parameter_id];
}

void m_safe_reboot(m_context *cxt)
{
	m_printf("Rebooting...\n");
	_reboot_Teensyduino_(); //rofl
}

int reset_context(m_context *cxt)
{
	return ERR_UNIMPLEMENTED;
	
	if (!cxt)
		return ERR_NULL_PTR;
	
	return NO_ERROR;
}

int cxt_add_transformer_to_profile(m_context *cxt, uint16_t profile_id, uint16_t type)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	if (profile_id > cxt->n_profiles)
		return ERR_BAD_ARGS;
	
	int ret_val = pipeline_add_transformer_by_type(&cxt->profiles[profile_id].pipeline, type);
	
	return ret_val;
}

int context_get_n_profile_transformers(m_context *cxt, uint16_t profile_id)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	if (cxt->n_profiles <= profile_id)
		return -ERR_BAD_ARGS;
	
	return cxt->profiles[profile_id].pipeline.n_transformers;
}

int context_get_n_transformer_params(m_context *cxt, uint16_t profile_id, uint16_t transformer_id)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	if (!transformer_id_valid(cxt, profile_id, transformer_id))
		return -ERR_BAD_ARGS;
	
	return cxt->profiles[profile_id].pipeline.transformers[transformer_id]->n_parameters;
}

int context_get_transformer_type(m_context *cxt, uint16_t profile_id, uint16_t transformer_id)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	if (!transformer_id_valid(cxt, profile_id, transformer_id))
		return -ERR_BAD_ARGS;
	
	return cxt->profiles[profile_id].pipeline.transformers[transformer_id]->type;
}

m_param_type context_get_parameter_type(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id)
{
	if (!cxt)
		return M_PARAM_ERR;
	
	if (!parameter_id_valid(cxt, profile_id, transformer_id, parameter_id))
		return M_PARAM_ERR;
	
	return cxt->profiles[profile_id].pipeline.transformers[transformer_id]->parameters[parameter_id]->type;
}

m_param_value context_get_parameter_value(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id)
{
	if (!cxt)
		return {.level=0.0};
	
	if (!parameter_id_valid(cxt, profile_id, transformer_id, parameter_id))
		return {.level=0.0};
	
	return cxt->profiles[profile_id].pipeline.transformers[transformer_id]->parameters[parameter_id]->val;
}

int	context_set_parameter_value(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id, m_param_value new_value)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	if (!parameter_id_valid(cxt, profile_id, transformer_id, parameter_id))
		return ERR_BAD_ARGS;
	
	m_parameter *param = get_parameter_by_id(cxt, {.profile_id=profile_id, .transformer_id=transformer_id, parameter_id=parameter_id});
	
	if (!param)
		return ERR_BAD_ARGS;
	
	param->val = new_value;
	
	return NO_ERROR;
}


char *context_get_parameter_name(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id)
{
	if (!cxt)
		return NULL;
	
	if (!parameter_id_valid(cxt, profile_id, transformer_id, parameter_id))
		return NULL;
	
	m_parameter *param = get_parameter_by_id(cxt, {.profile_id=profile_id, .transformer_id=transformer_id, parameter_id=parameter_id});
	
	if (!param)
		return NULL;
	
	return param->name;
}

int context_set_parameter_name(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id, const char *new_name)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	if (!parameter_id_valid(cxt, profile_id, transformer_id, parameter_id))
		return ERR_BAD_ARGS;
	
	m_parameter *param = get_parameter_by_id(cxt, {.profile_id=profile_id, .transformer_id=transformer_id, parameter_id=parameter_id});
	
	if (!param)
		return ERR_BAD_ARGS;
	
	if (param->name)
		free(param->name);
	
	param->name = new_name ? strndup(new_name, PARAM_NAME_MAX_LEN) : NULL;
	
	return NO_ERROR;
}


vec2i context_get_transformer_input(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, int input)
{
	if (!cxt)
		return ERROR_COORD;
	
	if (!transformer_id_valid(cxt, profile_id, transformer_id))
		return ERROR_COORD;
	
	if ((unsigned int)input >= cxt->profiles[profile_id].pipeline.transformers[transformer_id]->n_inputs)
		return ERROR_COORD;
	
	return cxt->profiles[profile_id].pipeline.transformers[transformer_id]->inputs[input];
}

int context_set_transformer_input(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, int input, int nx, int ny)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	if (!transformer_id_valid(cxt, profile_id, transformer_id))
		return ERR_BAD_ARGS;
	
	if ((unsigned int)input >= cxt->profiles[profile_id].pipeline.transformers[transformer_id]->n_inputs)
		return ERR_BAD_ARGS;
	
	cxt->profiles[profile_id].pipeline.transformers[transformer_id]->inputs[input].x = nx;
	cxt->profiles[profile_id].pipeline.transformers[transformer_id]->inputs[input].y = ny;
	
	return NO_ERROR;
}

vec2i context_get_transformer_output(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, int output)
{
	if (!cxt)
		return ERROR_COORD;
	
	if (!transformer_id_valid(cxt, profile_id, transformer_id))
		return ERROR_COORD;
	
	if ((unsigned int)output >= cxt->profiles[profile_id].pipeline.transformers[transformer_id]->n_outputs)
		return ERROR_COORD;
	
	return cxt->profiles[profile_id].pipeline.transformers[transformer_id]->outputs[output];
}

int context_set_transformer_output(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, int output, int nx, int ny)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	if (!transformer_id_valid(cxt, profile_id, transformer_id))
		return ERR_BAD_ARGS;
	
	if ((unsigned int)output >= cxt->profiles[profile_id].pipeline.transformers[transformer_id]->n_outputs)
		return ERR_BAD_ARGS;
	
	cxt->profiles[profile_id].pipeline.transformers[transformer_id]->outputs[output].x = nx;
	cxt->profiles[profile_id].pipeline.transformers[transformer_id]->outputs[output].y = ny;
	
	return NO_ERROR;
}

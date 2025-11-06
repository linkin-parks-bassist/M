#include "m_int.h"

IMPLEMENT_LINKED_PTR_LIST(m_int_parameter);
IMPLEMENT_LINKED_PTR_LIST(m_int_setting);

int init_m_int_parameter(m_int_parameter *param)
{
	if (!param)
		return ERR_NULL_PTR;
	
	param->val = 0.0;
	param->min = 0.0;
	param->max = 1.0;
	
	param->factor = 1.0;
	
	param->id = (m_int_parameter_id){.profile_id = 0, .transformer_id = 0, .parameter_id = 0};
	
	param->name = NULL;
	
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;
	
	param->group = -1;
	
	return NO_ERROR;
}

int init_parameter(m_int_parameter *param, char *name, float level, float min, float max)
{
	if (!param)
		return ERR_NULL_PTR;
	
	param->name = name;
	param->units = NULL;
	param->val = level;
	param->min = min;
	param->max = max;
	
	param->factor = 1.0;
	
	param->group = -1;
	
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;
	
	return NO_ERROR;
}

int init_m_int_setting(m_int_setting *setting)
{
	if (!setting)
		return ERR_NULL_PTR;
	
	setting->name = NULL;
	setting->val = 0;
	
	setting->n_settings = 0;
	setting->settings = NULL;
	
	setting->widget_type = OPTION_WIDGET_DROPDOWN;
	
	return NO_ERROR;
}

int init_setting(m_int_setting *setting, char *name, uint16_t level)
{
	if (!setting)
		return ERR_NULL_PTR;
	
	setting->name = name;
	setting->val = level;
	
	setting->n_settings = 0;
	setting->settings = NULL;
	
	setting->widget_type = OPTION_WIDGET_DROPDOWN;
	
	return NO_ERROR;
}

int parameter_set_id(m_int_parameter *param, uint16_t pid, uint16_t tid, uint16_t ppid)
{
	if (!param)
		return ERR_NULL_PTR;
	
	param->id.profile_id 	= pid;
	param->id.transformer_id = tid;
	param->id.parameter_id 	= ppid;
	
	return NO_ERROR;
}


void clone_parameter(m_int_parameter *dest, m_int_parameter *src)
{
	if (!dest || !src)
		return;
	
	m_int_parameter_id id;
	
	dest->val = src->val;
	dest->min = src->min;
	dest->max = src->max;
	
	dest->factor = src->factor;
	
	dest->widget_type = src->widget_type;
	dest->name = src->name;
	dest->units = src->units;
	
	dest->scale = src->scale;
	
	dest->group = src->group;
}

void clone_setting(m_int_setting *dest, m_int_setting *src)
{
	if (!dest || !src)
		return;
	
	dest->id = src->id;
	
	dest->val = src->val;
	
	dest->n_settings = src->n_settings;
	dest->settings = src->settings;
	
	dest->widget_type = src->widget_type;
	dest->name = src->name;
}

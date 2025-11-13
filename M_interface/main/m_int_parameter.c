#include "m_int.h"

IMPLEMENT_LINKED_PTR_LIST(m_parameter);
IMPLEMENT_LINKED_PTR_LIST(m_setting);

int init_parameter_str(m_parameter *param)
{
	if (!param)
		return ERR_NULL_PTR;
	
	param->value = 0.0;
	param->min = 0.0;
	param->max = 1.0;
	
	param->factor = 1.0;
	
	param->id = (m_parameter_id){.profile_id = 0, .transformer_id = 0, .parameter_id = 0};
	
	param->name = NULL;
	
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;
	
	param->group = -1;
	
	return NO_ERROR;
}

int init_parameter(m_parameter *param, const char *name, float level, float min, float max)
{
	if (!param)
		return ERR_NULL_PTR;
	
	param->name = name;
	param->units = NULL;
	param->value = level;
	param->min = min;
	param->max = max;
	
	param->factor = 1.0;
	
	param->group = -1;
	
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;
	
	return NO_ERROR;
}

int init_setting_str(m_setting *setting)
{
	if (!setting)
		return ERR_NULL_PTR;
	
	setting->name = NULL;
	setting->value = 0;
	
	setting->n_options = 0;
	setting->options = NULL;
	
	setting->widget_type = SETTING_WIDGET_DROPDOWN;
	
	setting->group = -1;
	
	return NO_ERROR;
}

int init_setting(m_setting *setting, const char *name, uint16_t level)
{
	if (!setting)
		return ERR_NULL_PTR;
	
	setting->name = name;
	setting->value = level;
	
	setting->n_options = 0;
	setting->options = NULL;
	
	setting->widget_type = SETTING_WIDGET_DROPDOWN;
	
	setting->group = -1;
	
	return NO_ERROR;
}

int parameter_set_id(m_parameter *param, uint16_t pid, uint16_t tid, uint16_t ppid)
{
	if (!param)
		return ERR_NULL_PTR;
	
	param->id.profile_id 	= pid;
	param->id.transformer_id = tid;
	param->id.parameter_id 	= ppid;
	
	return NO_ERROR;
}

void clone_parameter(m_parameter *dest, m_parameter *src)
{
	if (!dest || !src)
		return;
	
	m_parameter_id id;
	
	dest->value = src->value;
	dest->min = src->min;
	dest->max = src->max;
	
	dest->factor = src->factor;
	
	dest->widget_type = src->widget_type;
	dest->name 	= src->name;
	dest->units = src->units;
	
	dest->scale = src->scale;
	
	dest->group = src->group;
}

int clone_setting(m_setting *dest, m_setting *src)
{
	if (!dest || !src)
		return ERR_NULL_PTR;
	
	dest->id = src->id;
	
	dest->value = src->value;
	dest->min = src->min;
	dest->max = src->max;
	
	dest->n_options = src->n_options;
	
	if (dest->n_options)
	{
		dest->options = malloc(sizeof(m_setting_option) * dest->n_options);
		
		if (!dest->options)
		{
			return ERR_ALLOC_FAIL;
		}
		
		for (int i = 0; i < dest->n_options; i++)
		{
			if (src->options)
			{
				memcpy(&dest->options[i], &src->options[i], sizeof(m_setting_option));
			}
			else
			{
				dest->options[i].value = i;
				dest->options[i].name = "";
			}
		}
	}
	
	dest->widget_type = src->widget_type;
	dest->name = src->name;
	
	dest->group = src->group;
	
	dest->units = src->units;
	
	return NO_ERROR;
}

void gut_setting(m_setting *setting)
{
	if (!setting)
		return;
	
	if (!setting->n_options || !setting->options)
		return;
	
	m_free(setting->options);
}

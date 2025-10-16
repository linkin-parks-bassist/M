#include "em.h"

int init_em_parameter(em_parameter *param)
{
	if (!param)
		return ERR_NULL_PTR;
	
	param->val = 0.0;
	param->min = 0.0;
	param->max = 1.0;
	
	param->factor = 1.0;
	
	param->id = (em_parameter_id){.profile_id = 0, .transformer_id = 0, .parameter_id = 0};
	
	param->name = NULL;
	
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;
	
	param->group = -1;
	
	return NO_ERROR;
}

int init_parameter(em_parameter *param, char *name, float level, float min, float max)
{
	if (!param)
		return ERR_NULL_PTR;
	
	param->name = name;
	param->val = level;
	param->min = min;
	param->max = max;
	
	param->factor = 1.0;
	
	param->group = -1;
	
	return NO_ERROR;
}

int init_em_option(em_option *option)
{
	if (!option)
		return ERR_NULL_PTR;
	
	option->name = NULL;
	option->val = 0;
	
	option->n_options = 0;
	option->options = NULL;
	
	option->widget_type = OPTION_WIDGET_DROPDOWN;
	
	return NO_ERROR;
}

int init_option(em_option *option, char *name, uint16_t level)
{
	if (!option)
		return ERR_NULL_PTR;
	
	option->name = name;
	option->val = level;
	
	option->n_options = 0;
	option->options = NULL;
	
	option->widget_type = OPTION_WIDGET_DROPDOWN;
	
	return NO_ERROR;
}

int parameter_set_id(em_parameter *param, uint16_t pid, uint16_t tid, uint16_t ppid)
{
	if (!param)
		return ERR_NULL_PTR;
	
	param->id.profile_id 	= pid;
	param->id.transformer_id = tid;
	param->id.parameter_id 	= ppid;
	
	return NO_ERROR;
}


void clone_parameter(em_parameter *dest, em_parameter *src)
{
	if (!dest || !src)
		return;
	
	em_parameter_id id;
	
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

void clone_option(em_option *dest, em_option *src)
{
	if (!dest || !src)
		return;
	
	dest->id = src->id;
	
	dest->val = src->val;
	
	dest->n_options = src->n_options;
	dest->options = src->options;
	
	dest->widget_type = src->widget_type;
	dest->name = src->name;
}

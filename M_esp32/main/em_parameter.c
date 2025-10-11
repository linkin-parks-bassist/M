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
	
	option->widget_type = OPTION_WIDGET_HSLIDER;
	
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
	
	option->widget_type = OPTION_WIDGET_HSLIDER;
	
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

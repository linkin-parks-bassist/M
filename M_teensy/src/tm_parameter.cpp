#include "tm.h"

int init_option_simple(tm_option *option, int initial)
{
	if (!option)
		return ERR_NULL_PTR;
	
	option->value = initial;
	
	option->updated 	 = 1;
	option->new_value = initial;
	
	option->update_policy = PARAMETER_UPDATE_MONOBLOCK_LINEAR;
	
	return NO_ERROR;
}

int init_option_simple(tm_option *option, int initial, int update_policy)
{
	if (!option)
		return ERR_NULL_PTR;
	
	option->value = initial;
	
	option->updated 	 = 1;
	option->new_value = initial;
	
	option->update_policy = update_policy;
	
	return NO_ERROR;
}

int init_parameter_simple(tm_parameter *param, float initial)
{
	if (!param)
		return ERR_NULL_PTR;
	
	param->value = initial;
	
	param->updated 	 = 1;
	param->old_value = initial;
	param->new_value = initial;
	
	param->min = -10000000;
	param->max =  10000000;
	param->max_jump = DEFAULT_MAX_JUMP;

	param->scale = PARAMETER_SCALE_LINEAR;
	
	return NO_ERROR;
}

void init_parameter(tm_parameter *param, float initial, float min, float max, float max_jump, int scale)
{
	if (!param)
		return;
	
	param->value = initial;
	
	param->updated 	= 1;
	param->new_value = initial;
	
	param->min = min;
	param->max = max;
	param->max_jump = max_jump;
	
	param->scale = scale;
}

int update_option(tm_option *option, uint16_t new_value)
{
	if (!option)
		return ERR_NULL_PTR;
	
	option->updated = 1;
	option->old_value = option->value;
	option->new_value = new_value;
	option->update_progress = 0;
	
	return NO_ERROR;
}

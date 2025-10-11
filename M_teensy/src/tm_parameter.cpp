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
	
	return NO_ERROR;
}

int init_parameter(tm_parameter *param, float initial, float min, float max, float max_jump)
{
	if (!param)
		return ERR_NULL_PTR;
	
	param->value = initial;
	
	param->updated 	= 1;
	param->new_value = initial;
	
	param->min = min;
	param->max = max;
	param->max_jump = max_jump;
	
	return NO_ERROR;
}

int update_parameter(tm_parameter *param, float new_value)
{
	if (!param)
		return ERR_NULL_PTR;
	
	if (fabsf(new_value - param->value) < 0.0001)
		return NO_ERROR;
	
	float true_min = (param->min > param->max) ? param->max : param->min; 
	float true_max = (param->min > param->max) ? param->min : param->max;
	
	if (new_value < true_min || new_value > true_max)
	{
		return ERR_VALUE_OUT_OF_BOUNDS;
	}
	
	param->updated = 1;
	param->old_value = param->value;
	param->new_value = new_value;
	param->update_progress = 0;
	
	return NO_ERROR;
}

int update_parameter_update(tm_parameter *param, float new_value)
{
	if (!param)
		return ERR_NULL_PTR;
		
	if (fabsf(new_value - param->value) < 0.0001)
		return NO_ERROR;
	
	
	float true_min = (param->min > param->max) ? param->max : param->min; 
	float true_max = (param->min > param->max) ? param->min : param->max;
	
	if (new_value < true_min || new_value > true_max)
	{
		return ERR_VALUE_OUT_OF_BOUNDS;
	}
	
	if (!param->updated)
		param->update_progress = 0;
	
	param->updated = 1;
	param->old_value = param->value;
	param->new_value = new_value;
	
	return NO_ERROR;
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

float linear_interpolate(float x, float y, float r)
{
	return (1.0 - r) * x + r * y;
}

int parameter_update_tick(tm_parameter *param)
{
	if (!param)
		return ERR_NULL_PTR;
	
	if (!param->updated)
		return NO_ERROR;
		
	int total_samples = AUDIO_BLOCK_SAMPLES;
	
	float ratio;
	float (*interpolate)(float x, float y, float r) = linear_interpolate;
	
	param->update_progress++;
	
	switch (param->update_policy)
	{
		case PARAMETER_UPDATE_QUADBLOCK_LINEAR:
			total_samples *= 2;
		case PARAMETER_UPDATE_BIBLOCK_LINEAR:
			total_samples *= 2;
			break;
		
		case PARAMETER_UPDATE_INSTANT:
			total_samples = 2;
			break;
		
		default: break;
	}
	
	//tm_printf("Updating parameter %p. Progress: %d / %d = %.2f%%\n", param->update_progress, total_samples, 100.0 * ratio);
	ratio = (float)param->update_progress / total_samples;
	
	if (param->update_progress >= total_samples)
	{
		param->value 			= param->new_value;
		param->old_value 		= param->value;
		param->updated 			= 0;
		param->update_progress  = 0;
	}
	else
	{
		param->value = interpolate(param->old_value, param->new_value, ratio);
	}
	
	return NO_ERROR;
}

int parameter_update_finish(tm_parameter *param)
{
	if (!param)
	{
		return ERR_NULL_PTR;
	}
	
	if (!param->updated)
	{
		return NO_ERROR;
	}
	
	param->old_value 		= param->value;
	param->value 			= param->new_value;
	param->updated 			= 0;
	param->update_progress  = 0;
	
	return NO_ERROR;
}

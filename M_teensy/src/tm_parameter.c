#include "tm.h"

static const char *FNAME = "tm_parameter.c";

int init_setting_simple(tm_setting *setting, int initial)
{
	FUNCTION_START();

	if (!setting)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	setting->value = initial;
	
	setting->updated 	 = 1;
	setting->new_value = initial;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int init_parameter_simple(tm_parameter *param, float initial)
{
	FUNCTION_START();

	if (!param)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	param->value = initial;
	
	param->updated 	 = 1;
	param->old_value = initial;
	param->new_value = initial;
	
	param->min = -10000000;
	param->max =  10000000;
	param->max_jump = DEFAULT_MAX_JUMP;

	param->scale = PARAMETER_SCALE_LINEAR;
	
	RETURN_ERR_CODE(NO_ERROR);
}

void init_parameter(tm_parameter *param, float initial, float min, float max, float max_jump, int scale)
{
	FUNCTION_START();

	if (!param)
	{
		RETURN_VOID();
	}
	
	param->value = initial;
	
	param->updated 	= 1;
	param->new_value = initial;
	
	param->min = min;
	param->max = max;
	param->max_jump = max_jump;
	
	param->scale = scale;
}

int update_setting(tm_setting *setting, uint16_t new_value)
{
	FUNCTION_START();

	if (!setting)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	setting->updated = 1;
	setting->old_value = setting->value;
	setting->new_value = new_value;
	setting->update_progress = 0;
	
	RETURN_ERR_CODE(NO_ERROR);
}

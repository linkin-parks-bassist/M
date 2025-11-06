#include "m_eng.h"

static const char *FNAME = "m_eng_parameter.c";

void init_parameter(m_eng_parameter *param, float initial, float min, float max, float max_jump, int scale)
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

int init_setting(m_eng_setting *setting, int16_t initial)
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

int update_setting(m_eng_setting *setting, uint16_t new_value)
{
	FUNCTION_START();

	if (!setting)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	setting->updated = 1;
	setting->old_value = setting->value;
	setting->new_value = new_value;
	
	RETURN_ERR_CODE(NO_ERROR);
}

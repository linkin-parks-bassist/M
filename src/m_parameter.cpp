#include "M.h"

int init_parameter(m_parameter *param, const char *name, float value)
{
	if (!param)
		return ERR_NULL_PTR;
	
	if (!name)
		return ERR_BAD_ARGS;
	
	strncpy(param->name, name, PARAMETER_NAME_MAX_LENGTH - 1);
	param->value 	= value;
	param->updated 	= 1;
	
	return NO_ERROR;
}

int parameter_set_name(m_parameter *param, const char *name)
{
	if (!param)
		return ERR_NULL_PTR;
	
	if (!name)
		return ERR_BAD_ARGS;
	
	strncpy(param->name, name, PARAMETER_NAME_MAX_LENGTH - 1);
	
	return NO_ERROR;
}

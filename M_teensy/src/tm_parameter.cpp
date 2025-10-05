#include "tm.h"

int init_parameter(m_parameter *param, m_param_type type, m_param_value initial)
{
	if (!param)
		return ERR_NULL_PTR;
	
	param->type = type;
	param->val  = initial;
	
	param->updated 	= 1;
	
	return NO_ERROR;
}

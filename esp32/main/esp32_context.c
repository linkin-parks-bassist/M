#include <stdint.h>
#include "m_error_codes.h"
#include "m_parameter.h"
#include "shared_context.h"
#include "esp32_context.h"

int init_esp32_context(esp32_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	cxt->teensy.n_profiles = 1;
	cxt->teensy.active_profile = 0;
	
	return NO_ERROR;
}

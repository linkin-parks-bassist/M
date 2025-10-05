#include "em.h"


int init_esp32_context(esp32_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	init_teensy_context(&cxt->teensy);
	
	return NO_ERROR;
}

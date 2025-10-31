#include "tm.h"

static const char *FNAME = "tm_update.c";

#define WAVESHAPER_ENVELOPE_RATE (1.0/(64 * 128))

void update_all()
{
	#ifndef TM_SIMULATED
	
	NVIC_SET_PENDING(IRQ_SOFTWARE);
	#else
	
	#endif
}

int update_setup()
{
	#ifndef TM_SIMULATED
	
	if (update_scheduled)
	{
		RETURN_INT(0);
	}
	
	attachInterruptVector(IRQ_SOFTWARE, tm_software_isr);
	NVIC_SET_PRIORITY(IRQ_SOFTWARE, 208); // 255 = lowest priority
	NVIC_ENABLE_IRQ(IRQ_SOFTWARE);
	
	update_scheduled = 1;
	
	RETURN_INT(1);
	#else
	RETURN_INT(1);
	#endif
}

void update_stop()
{
	#ifndef TM_SIMULATED
	NVIC_DISABLE_IRQ(IRQ_SOFTWARE);
	update_scheduled = 0;
	#else
	
	#endif
}

void tm_software_isr()
{
	cxt_process(&global_cxt);
}

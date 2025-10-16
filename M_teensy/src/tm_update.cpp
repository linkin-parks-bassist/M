#include "tm.h"

#define WAVESHAPER_ENVELOPE_RATE (1.0/(64 * 128))

void update_all()
{
	#ifndef TM_SIMULATED
	
	NVIC_SET_PENDING(IRQ_SOFTWARE);
	#else
	
	#endif
}

bool update_setup()
{
	#ifndef TM_SIMULATED
	
	if (update_scheduled)
		return false;
	
	attachInterruptVector(IRQ_SOFTWARE, tm_software_isr);
	NVIC_SET_PRIORITY(IRQ_SOFTWARE, 208); // 255 = lowest priority
	NVIC_ENABLE_IRQ(IRQ_SOFTWARE);
	
	update_scheduled = true;
	
	return true;
	#else
	return true;
	#endif
}

void update_stop()
{
	#ifndef TM_SIMULATED
	NVIC_DISABLE_IRQ(IRQ_SOFTWARE);
	update_scheduled = false;
	#else
	
	#endif
}

void tm_software_isr()
{
	cxt_process(&global_cxt);
}

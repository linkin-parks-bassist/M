#include "m_eng.h"

static const char *FNAME = "m_eng_update.c";

#define WAVESHAPER_ENVELOPE_RATE (1.0/(64 * 128))

void update_all()
{
	#ifndef M_ENG_SIMULATED
	
	NVIC_SET_PENDING(IRQ_SOFTWARE);
	#else
	
	#endif
}

int update_setup()
{
	#ifndef M_ENG_SIMULATED
	
	if (update_scheduled)
	{
		RETURN_INT(0);
	}
	
	attachInterruptVector(IRQ_SOFTWARE, m_eng_software_isr);
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
	#ifndef M_ENG_SIMULATED
	NVIC_DISABLE_IRQ(IRQ_SOFTWARE);
	update_scheduled = 0;
	#else
	
	#endif
}

void m_eng_software_isr()
{
	cxt_process(&global_cxt);
}

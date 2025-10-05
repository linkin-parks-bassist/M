#include "tm.h"

void update_all()
{
	NVIC_SET_PENDING(IRQ_SOFTWARE);
}

bool update_setup()
{
	if (update_scheduled)
		return false;
	
	attachInterruptVector(IRQ_SOFTWARE, tm_software_isr);
	NVIC_SET_PRIORITY(IRQ_SOFTWARE, 208); // 255 = lowest priority
	NVIC_ENABLE_IRQ(IRQ_SOFTWARE);
	
	update_scheduled = true;
	
	return true;
}

void update_stop()
{
	NVIC_DISABLE_IRQ(IRQ_SOFTWARE);
	update_scheduled = false;
}

void tm_software_isr()
{
	cxt_process(&global_cxt);
}

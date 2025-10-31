#include "tm.h"

static const char *FNAME = "tm_globals.c";

uint16_t cpu_cycles_total		= 0;
uint16_t cpu_cycles_total_max	= 0;
uint16_t memory_used			= 0;
uint16_t memory_used_max		= 0;

// When an object has taken responsibility for calling update_all()
// at each block interval (approx 2.9ms), this variable is set to
// true.  Objects that are capable of calling update_all(), typically
// input and output based on interrupts, must check this variable in
// their constructors.
int update_scheduled = 0;

uint32_t trace_depth = 0;

uint64_t cycles_upper = 0;


void update_upper_cycles()
{
	static uint32_t prev_cycles = 0;
	
	if (!prev_cycles)
		prev_cycles = ARM_DWT_CYCCNT;
	uint32_t current_cycles = ARM_DWT_CYCCNT;
	
	if (current_cycles < prev_cycles)
		cycles_upper += (uint64_t)1 << 32;
	
	prev_cycles = current_cycles;
}

double cycles_to_seconds(uint64_t cycles)
{
	return (float)cycles / 6e8f;
}

uint64_t current_cycle()
{
	return cycles_upper + ARM_DWT_CYCCNT;
}

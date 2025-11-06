#include "m_eng.h"

static const char *FNAME = "m_eng_globals.c";

m_eng_context global_cxt;

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
uint32_t cycles_upper = 0;


double cycles_to_seconds(uint64_t cycles)
{
	return (float)cycles / 6e8f;
}

inline uint64_t current_cycle()
{
	static uint32_t prev_cycles = 0;
	
	if (!prev_cycles)
		prev_cycles = ARM_DWT_CYCCNT;
	
	uint64_t cycle = ARM_DWT_CYCCNT;
	
	if (cycle < prev_cycles)
		cycles_upper++;
	
	prev_cycles = cycle;
	
	return (((uint64_t)cycles_upper << 32) | ARM_DWT_CYCCNT);
}

#include "M.h"

uint16_t cpu_cycles_total		= 0;
uint16_t cpu_cycles_total_max	= 0;
uint16_t memory_used			= 0;
uint16_t memory_used_max		= 0;

// When an object has taken responsibility for calling update_all()
// at each block interval (approx 2.9ms), this variable is set to
// true.  Objects that are capable of calling update_all(), typically
// input and output based on interrupts, must check this variable in
// their constructors.
bool 					update_scheduled = false;

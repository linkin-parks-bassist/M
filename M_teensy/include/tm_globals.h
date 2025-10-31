#ifndef M_GLOBAL_VARS_H_
#define M_GLOBAL_VARS_H_

extern uint16_t cpu_cycles_total;
extern uint16_t cpu_cycles_total_max;
extern uint16_t memory_used;
extern uint16_t memory_used_max;

extern int update_scheduled;

extern uint32_t trace_depth;

extern uint64_t cycles_upper;

void update_upper_cycles();

double cycles_to_seconds(uint64_t cycles);

uint64_t current_cycle();

#endif

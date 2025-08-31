#ifndef M_GLOBAL_VARS_H_
#define M_GLOBAL_VARS_H_

extern uint16_t cpu_cycles_total;
extern uint16_t cpu_cycles_total_max;
extern uint16_t memory_used;
extern uint16_t memory_used_max;

extern m_audio_connection* 	unused_connections;
extern bool 				update_scheduled;
extern m_audio_stream*		first_update;

extern int bypass_mode;

#endif

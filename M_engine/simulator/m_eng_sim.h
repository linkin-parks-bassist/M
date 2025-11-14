#ifndef M_ENG_SIMULATOR_H_
#define M_ENG_SIMULATOR_H_

#ifndef M_SIMULATED
	#define M_SIMULATED
#endif

#include "m_eng.h"

int m_sim_get_input_block(float *dest);
int m_sim_get_output_block(float *buffer);

typedef struct
{
	m_message msg;
	int block_no;
} m_message_timed;


extern m_response teensy_i2c_response;
extern uint8_t simulated_i2c_send_buffer[M_MESSAGE_MAX_TRANSFER_LEN];

DECLARE_LINKED_LIST(m_message_timed);

#endif

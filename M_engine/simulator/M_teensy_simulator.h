#ifndef TM_SIMULATOR_H_
#define TM_SIMULATOR_H_

#include "tm.h"

int tmsim_get_input_block(int16_t *buffer);
int tmsim_send_output_block(float *buffer);

typedef struct
{
	et_msg msg;
	int block_no;
} et_msg_timed;


extern te_msg teensy_i2c_response;
extern uint8_t simulated_i2c_send_buffer[ET_MESSAGE_MAX_TRANSFER_LEN];

DECLARE_LINKED_LIST(et_msg_timed);

void transformer_dump(void *str, int transformer_type, float *out_buffer, float *in_buffer, int sample);
void profile_dump(tm_profile *profile);

#endif

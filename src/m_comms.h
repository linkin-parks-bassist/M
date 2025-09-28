#ifndef M_COMMS_H_
#define M_COMMS_H_

#include <stdint.h>

#ifndef TEENSY_ADDR
#define TEENSY_ADDR 0x08
#endif

/* Messages from ESP32 to Teensy */

#define ET_MESSAGE_MAX_DATA_LEN 32

#define ET_MESSAGE_INVALID	0
#define ET_MESSAGE_HI 		1
#define ET_MESSAGE_CHPARAM  2

#define ET_MSG_RESPONSE_REQUIRED(msg_type) (msg_type == ET_MESSAGE_HI || 0)

typedef struct
{
	uint8_t type;
	uint8_t data[ET_MESSAGE_MAX_DATA_LEN];
} et_msg;

typedef struct
{
	uint16_t profile_id;
	uint16_t transformer_id;
	uint16_t parameter_id;
	float new_value;
} et_msg_chparam_struct;

/* Messages from Teensy to ESP32 */

#define TE_MESSAGE_MAX_DATA_LEN 16

#define TE_MESSAGE_INVALID		0
#define TE_MESSAGE_NO_MESSAGE	255
#define TE_MESSAGE_HI 			1
#define TE_MESSAGE_BAD_TRANSFER 2

typedef struct
{
	uint8_t type;
	uint8_t data[TE_MESSAGE_MAX_DATA_LEN];
} te_msg;

int et_message_data_length(et_msg msg);
int encode_et_msg(uint8_t *buf, et_msg msg);
int valid_et_msg_type(uint8_t type);
et_msg decode_et_msg(uint8_t *bytes, int n);
int te_message_data_length(te_msg msg);
int encode_te_msg(uint8_t *buf, te_msg msg);
int valid_te_msg_type(uint8_t type);
te_msg decode_te_msg(uint8_t *bytes, int n);

#endif

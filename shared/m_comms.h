#ifndef M_COMMS_H_
#define M_COMMS_H_

#ifndef TEENSY_ADDR
#define TEENSY_ADDR 0x08
#endif

/* Messages from ESP32 to Teensy */

#define ET_MESSAGE_MAX_LEN 16

#define ET_MESSAGE_NO_MESSAGE				255
#define ET_MESSAGE_INVALID					0
#define ET_MESSAGE_HI 						1
#define ET_MESSAGE_RESET					2
#define ET_MESSAGE_REBOOT					3
#define ET_MESSAGE_CREATE_PROFILE 			4
#define ET_MESSAGE_APPEND_TRANSFORMER		5
#define ET_MESSAGE_MOVE_TRANSFORMER			6
#define ET_MESSAGE_REMOVE_TRANSFORMER		7
#define ET_MESSAGE_GET_N_PROFILES			8
#define ET_MESSAGE_GET_N_TRANSFORMERS		9
#define ET_MESSAGE_GET_TRANSFORMER_ID		10
#define ET_MESSAGE_GET_TRANSFORMER_TYPE		11
#define ET_MESSAGE_GET_N_PARAMETERS			12
#define ET_MESSAGE_GET_PARAM_VALUE			13
#define ET_MESSAGE_SET_PARAM_VALUE  		14
#define ET_MESSAGE_GET_N_OPTIONS			15
#define ET_MESSAGE_GET_OPTION_VALUE			16
#define ET_MESSAGE_SET_OPTION_VALUE  		17
#define ET_MESSAGE_STRING_CONTINUE			18
#define ET_MESSAGE_STRING_CONTINUING		19
#define ET_MESSAGE_SWITCH_PROFILE			20

#include "m_vec2i.h"

#define MESSAGE_LEN_VARIABLE				-2
#define TE_MESSAGE_MAX_LEN 16

typedef struct
{
	uint8_t type;
	uint8_t data[TE_MESSAGE_MAX_LEN - 1];
	void *extra;
} te_msg;

typedef struct et_msg
{
	uint8_t type;
	uint8_t data[ET_MESSAGE_MAX_LEN];
	void (*callback)(struct et_msg msg, te_msg response);
	void *cb_arg;
} et_msg;

et_msg create_et_msg_nodata(uint16_t type);
et_msg create_et_msg(uint16_t type, const char *fmt, ...);

et_msg create_et_msg_2_short(uint16_t type, uint16_t s1, uint16_t s2);
et_msg create_et_msg_3_short(uint16_t type, uint16_t s1, uint16_t s2, uint16_t s3);

et_msg create_et_msg_get_param_value(uint16_t pid, uint16_t tid, uint16_t ppid);
et_msg create_et_msg_set_param(uint16_t pid, uint16_t tid, uint16_t ppid, float new_val);

et_msg create_et_msg_new_profile();
et_msg create_et_msg_new_transformer(uint16_t pid, uint16_t type);

const char *et_msg_code_to_string(uint16_t code);

/* Messages from Teensy to ESP32 */

#define TE_MESSAGE_NO_MESSAGE			255
#define TE_MESSAGE_INVALID				0
#define TE_MESSAGE_WAIT					1
#define TE_MESSAGE_HI 					2
#define TE_MESSAGE_BAD_TRANSFER 		3
#define TE_MESSAGE_BAD_REQUEST  		4
#define TE_MESSAGE_TRY_AGAIN			5
#define TE_MESSAGE_OK					6
#define TE_MESSAGE_ERROR				7
#define TE_MESSAGE_PROFILE_ID			8
#define TE_MESSAGE_TRANSFORMER_ID		10
#define TE_MESSAGE_N_PROFILES			11
#define TE_MESSAGE_N_TRANSFORMERS		12
#define TE_MESSAGE_TRANSFORMER_TYPE		13
#define TE_MESSAGE_N_PARAMETERS			14
#define TE_MESSAGE_PARAM_VALUE			15
#define TE_MESSAGE_N_OPTIONS			16
#define TE_MESSAGE_OPTION_VALUE			17
#define TE_MESSAGE_STRING_CONTINUING	18
#define TE_MESSAGE_START_OVER			19
#define TE_MESSAGE_SWITCHING_PROFILE	20

te_msg create_te_msg_nodata(uint16_t type);
te_msg create_te_msg(uint16_t type, const char *fmt, ...);
te_msg create_te_msg_ok();

te_msg create_te_msg_error(uint16_t error_code);
te_msg create_te_msg_profile_id(uint16_t pid);
te_msg create_te_msg_transformer_id(uint16_t pid, uint16_t tid);
te_msg create_te_msg_parameter_value(uint16_t pid, uint16_t tid, uint16_t ppid, float value);
te_msg create_te_msg_transformer_vec2i(uint16_t type, uint16_t pid, uint16_t tid, uint16_t i, vec2i vec);

int et_message_data_length(et_msg msg);
int encode_et_msg(uint8_t *buf, et_msg msg);
int valid_et_msg_type(uint8_t type);
et_msg decode_et_msg(uint8_t *bytes);
int te_message_data_length(te_msg msg);
int encode_te_msg(uint8_t *buf, te_msg msg);

int valid_te_msg_type(uint8_t type);
te_msg decode_te_msg(uint8_t *bytes);

const char *te_msg_code_to_string(uint16_t code);

#endif

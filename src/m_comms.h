#ifndef M_COMMS_H_
#define M_COMMS_H_

#include <stdint.h>

#ifndef TEENSY_ADDR
#define TEENSY_ADDR 0x08
#endif

/* Messages from ESP32 to Teensy */

#define ET_MESSAGE_MAX_LEN 16

#define ET_MESSAGE_NO_MESSAGE				255
#define ET_MESSAGE_INVALID					0
#define ET_MESSAGE_HI 						1
#define ET_MESSAGE_SYNC						2
#define ET_MESSAGE_SYNCED					3
#define ET_MESSAGE_RESET					4
#define ET_MESSAGE_REBOOT					5
#define ET_MESSAGE_NEW_PROFILE 				6
#define ET_MESSAGE_NEW_TRANSFORMER 			7
#define ET_MESSAGE_GET_N_PROFILES			8
#define ET_MESSAGE_GET_N_TRANSFORMERS		9
#define ET_MESSAGE_GET_TRANSFORMER_TYPE		10
#define ET_MESSAGE_GET_N_PARAMETERS			11
#define ET_MESSAGE_GET_PARAM_TYPE			12
#define ET_MESSAGE_GET_PARAM_VALUE			13
#define ET_MESSAGE_SET_PARAM_VALUE  		14
#define ET_MESSAGE_GET_PARAM_NAME			15
#define ET_MESSAGE_SET_PARAM_NAME			16
#define ET_MESSAGE_GET_TRANSFORMER_INPUT	17
#define ET_MESSAGE_GET_TRANSFORMER_OUTPUT	18
#define ET_MESSAGE_SET_TRANSFORMER_INPUT	19
#define ET_MESSAGE_SET_TRANSFORMER_OUTPUT	20

#define MESSAGE_LEN_VARIABLE				2

typedef struct
{
	uint8_t type;
	uint8_t data[ET_MESSAGE_MAX_LEN];
	void *extra;
} et_msg;

typedef struct
{
	m_parameter_id id;
	m_param_value  new_value;
} et_msg_chparam_struct;

typedef struct
{
	m_parameter_id id;
} et_msg_rqparam_struct;

typedef struct
{
	uint16_t type;
	uint16_t profile_id;
} et_msg_mktrans_struct;

et_msg create_et_msg_no_data(uint16_t type);
et_msg create_et_msg(uint16_t type, const char *fmt, ...);

et_msg create_et_msg_2_short(uint16_t type, uint16_t s1, uint16_t s2);
et_msg create_et_msg_3_short(uint16_t type, uint16_t s1, uint16_t s2, uint16_t s3);

et_msg create_et_msg_chparam(m_parameter_id id, m_param_value new_val);
et_msg create_et_msg_chparam_from_str(et_msg_chparam_struct str);
et_msg_chparam_struct decode_et_msg_chparam(et_msg msg);

et_msg create_et_msg_rqparam(m_parameter_id id);
et_msg_rqparam_struct decode_et_msg_rqparam(et_msg msg);

et_msg create_et_msg_new_profile();
et_msg create_et_msg_new_transformer(uint16_t profile_id, uint16_t type);

/* Messages from Teensy to ESP32 */

#define TE_MESSAGE_MAX_LEN 16

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
#define TE_MESSAGE_TRANSFORMER_ID		9
#define TE_MESSAGE_PARAMETER_ID			10
#define TE_MESSAGE_N_PROFILES			11
#define TE_MESSAGE_N_TRANSFORMERS		12
#define TE_MESSAGE_TRANSFORMER_TYPE		13
#define TE_MESSAGE_N_PARAMETERS			14
#define TE_MESSAGE_PARAM_TYPE			15
#define TE_MESSAGE_PARAM_VALUE			16
#define TE_MESSAGE_PARAM_NAME			17
#define TE_MESSAGE_PARAM_NAME_LONG		18
#define TE_MESSAGE_TRANSFORMER_INPUT	19
#define TE_MESSAGE_TRANSFORMER_OUTPUT	20

typedef struct
{
	uint8_t type;
	uint8_t data[TE_MESSAGE_MAX_LEN - 1];
	void *extra;
} te_msg;

typedef struct
{
	m_parameter_id id;
} te_msg_param_value;

te_msg create_te_msg(uint16_t type, const char *fmt, ...);
te_msg create_te_msg_ok();

te_msg create_te_msg_param_value(m_parameter_id id, m_parameter *param);

te_msg create_te_msg_error(uint16_t error_code);
te_msg create_te_msg_profile_id(uint16_t id);
te_msg create_te_msg_transformer_id(uint16_t profile_id, uint16_t transformer_id);
te_msg create_te_msg_parameter_id(uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id);

int et_message_data_length(et_msg msg);
int encode_et_msg(uint8_t *buf, et_msg msg);
int valid_et_msg_type(uint8_t type);
et_msg decode_et_msg(uint8_t *bytes);
int te_message_data_length(te_msg msg);
int encode_te_msg(uint8_t *buf, te_msg msg);

int valid_te_msg_type(uint8_t type);
te_msg decode_te_msg(uint8_t *bytes);

#endif

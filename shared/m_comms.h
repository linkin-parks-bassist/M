#ifndef M_COMMS_H_
#define M_COMMS_H_

#ifndef TEENSY_ADDR
#define TEENSY_ADDR 0x08
#endif

/* Messages from ESP32 to Teensy */

#define M_MESSAGE_NO_MESSAGE				255
#define M_MESSAGE_CRC_FAIL					254
#define M_MESSAGE_INVALID					0
#define M_MESSAGE_HI 						1
#define M_MESSAGE_RESET						2
#define M_MESSAGE_REBOOT					3
#define M_MESSAGE_CREATE_PROFILE 			4
#define M_MESSAGE_APPEND_TRANSFORMER		5
#define M_MESSAGE_MOVE_TRANSFORMER			6
#define M_MESSAGE_REMOVE_TRANSFORMER		7
#define M_MESSAGE_GET_N_PROFILES			8
#define M_MESSAGE_GET_N_TRANSFORMERS		9
#define M_MESSAGE_GET_TRANSFORMER_ID		10
#define M_MESSAGE_GET_TRANSFORMER_TYPE		11
#define M_MESSAGE_GET_N_PARAMETERS			12
#define M_MESSAGE_GET_PARAM_VALUE			13
#define M_MESSAGE_SET_PARAM_VALUE  			14
#define M_MESSAGE_GET_N_SETTINGS			15
#define M_MESSAGE_GET_SETTING_VALUE			16
#define M_MESSAGE_SET_SETTING_VALUE  		17
#define M_MESSAGE_STRING_CONTINUE			18
#define M_MESSAGE_STRING_CONTINUING			19
#define M_MESSAGE_SWITCH_PROFILE			20
#define M_MESSAGE_DELETE_PROFILE			21
#define M_MESSAGE_REPEAT_MESSAGE			22
#define M_MESSAGE_ENTER_TUNER_MODE			23
#define M_MESSAGE_EXIT_TUNER_MODE			24

#define M_MESSAGE_TYPE_MAX M_MESSAGE_EXIT_TUNER_MODE

#define MESSAGE_LEN_VARIABLE				-2
#define M_MESSAGE_MAX_DATA_LEN 16
#define M_MESSAGE_MAX_TRANSFER_LEN (M_RESPONSE_MAX_DATA_LEN + 2)

#define M_RESPONSE_MAX_DATA_LEN 16
#define M_RESPONSE_MAX_TRANSFER_LEN (M_RESPONSE_MAX_DATA_LEN + 2)

typedef struct
{
	uint8_t type;
	uint8_t data[M_RESPONSE_MAX_DATA_LEN];
	void *extra;
} m_response;

typedef struct m_message
{
	uint8_t type;
	uint8_t data[M_RESPONSE_MAX_DATA_LEN];
	void (*callback)(struct m_message msg, m_response response);
	void *cb_arg;
	int retries;
} m_message;

m_message create_m_message_nodata(uint16_t type);
m_message create_m_message(uint16_t type, const char *fmt, ...);

/* Messages from Teensy to ESP32 */

#define M_RESPONSE_NO_MESSAGE			255
#define M_RESPONSE_CRC_FAIL				254
#define M_RESPONSE_INVALID				0
#define M_RESPONSE_WAIT					1
#define M_RESPONSE_HI 					2
#define M_RESPONSE_BAD_MESSAGE 			3
#define M_RESPONSE_BAD_REQUEST  		4
#define M_RESPONSE_TRY_AGAIN			5
#define M_RESPONSE_OK					6
#define M_RESPONSE_ERROR				7
#define M_RESPONSE_PROFILE_ID			8
#define M_RESPONSE_TRANSFORMER_ID		10
#define M_RESPONSE_N_PROFILES			11
#define M_RESPONSE_N_TRANSFORMERS		12
#define M_RESPONSE_TRANSFORMER_TYPE		13
#define M_RESPONSE_N_PARAMETERS			14
#define M_RESPONSE_PARAM_VALUE			15
#define M_RESPONSE_N_SETTINGS			16
#define M_RESPONSE_SETTING_VALUE		17
#define M_RESPONSE_STRING_CONTINUING	18
#define M_RESPONSE_START_OVER			19
#define M_RESPONSE_SWITCHING_PROFILE	20
#define M_RESPONSE_DELETED_PROFILE		21
#define M_RESPONSE_REPEAT_MESSAGE		22

#define M_RESPONSE_TYPE_MAX M_RESPONSE_REPEAT_MESSAGE

m_response create_m_response_nodata(uint16_t type);
m_response create_m_response(uint16_t type, const char *fmt, ...);
m_response create_m_response_ok();

m_response create_m_response_error(uint16_t error_code);
m_response create_m_response_profile_id(uint16_t pid);
m_response create_m_response_transformer_id(uint16_t pid, uint16_t tid);
m_response create_m_response_parameter_value(uint16_t pid, uint16_t tid, uint16_t ppid, float value);

int et_message_data_length(m_message msg);
int valid_m_message_type(uint8_t type);

int encode_m_message(uint8_t *buf, m_message msg);
m_message decode_m_message(uint8_t *bytes, unsigned int len);

int te_message_data_length(m_response msg);

int valid_m_response_type(uint8_t type);
int encode_m_response(uint8_t *buf, m_response msg);
m_response decode_m_response(uint8_t *bytes, unsigned int len);

const char *m_message_code_to_string(uint16_t code);
const char *m_response_code_to_string(uint16_t code);

#endif

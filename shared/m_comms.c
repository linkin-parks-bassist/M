#ifdef M_INTERFACE
#include "m_int.h"
#else
#include "m_eng.h"
#endif
#include "m_comms.h"
#include "m_error_codes.h"

static const char *FNAME = "m_comms.c";

// 8-bit cyclic redundancy check with generator
// polynomial x^8 + x^2 + x + 1
// to detect transmission errors
uint8_t crc_8(const uint8_t *data, int len)
{
    uint8_t crc = 0x00;
    
    for (int i = 0; i < len; i++)
    {
        crc ^= data[i];
        for (int j = 0; j < 8; j++)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x07;
            else
                crc <<= 1;
        }
    }
    return crc;
}

int et_message_data_length(et_msg msg)
{
	switch (msg.type)
	{
		case ET_MESSAGE_HI:
			return 0;

		case ET_MESSAGE_RESET:
			return 0;

		case ET_MESSAGE_REBOOT:
			return 0;
		
		case ET_MESSAGE_CREATE_PROFILE:
			return 0;
		
		case ET_MESSAGE_APPEND_TRANSFORMER:
			return 2 * sizeof(uint16_t);
		
		case ET_MESSAGE_MOVE_TRANSFORMER:
			return 2 * sizeof(uint16_t);
		
		case ET_MESSAGE_REMOVE_TRANSFORMER:
			return 2 * sizeof(uint16_t);

		case ET_MESSAGE_GET_N_PROFILES:
			return 0;

		case ET_MESSAGE_GET_N_TRANSFORMERS:
			return 1 * sizeof(uint16_t);
		
		case ET_MESSAGE_GET_TRANSFORMER_ID:
			return 2 * sizeof(uint16_t);
			
		case ET_MESSAGE_GET_TRANSFORMER_TYPE:
			return 2 * sizeof(uint16_t);
			
		case ET_MESSAGE_GET_N_PARAMETERS:
			return 2 * sizeof(uint16_t);

		case ET_MESSAGE_GET_PARAM_VALUE:
			return 3 * sizeof(uint16_t);
			
		case ET_MESSAGE_SET_PARAM_VALUE: 
			return 3 * sizeof(uint16_t) + sizeof(float);

		case ET_MESSAGE_STRING_CONTINUE:
			return 0;
			
		case ET_MESSAGE_STRING_CONTINUING:
			return MESSAGE_LEN_VARIABLE;
		
		case ET_MESSAGE_SWITCH_PROFILE:
			return 1 * sizeof(uint16_t);
		
		case ET_MESSAGE_DELETE_PROFILE:
			return 1 * sizeof(uint16_t);
		
		case ET_MESSAGE_REPEAT_MESSAGE:
			return 0;
		
		case ET_MESSAGE_ENTER_TUNER_MODE:
			return 0;
		
		case ET_MESSAGE_EXIT_TUNER_MODE:
			return 0;
		
		default:
			return -1;
	}
}

int et_message_default_retries(uint16_t type)
{
	return 3;
}

// Returns the transfer length
int encode_et_msg(uint8_t *buf, et_msg msg)
{
	if (!buf)
	{
		return -1;
	}
	
	buf[0] = msg.type;
	
	int len = et_message_data_length(msg);
	
	// Should not be possible. Throw a fit if it happens
	if (len > ET_MESSAGE_MAX_DATA_LEN)
	{
		buf[0] = ET_MESSAGE_INVALID;
		return -1;
	}
	
	if (len == MESSAGE_LEN_VARIABLE)
		len = ET_MESSAGE_MAX_DATA_LEN;
	
	int i;
	for (i = 1; i < len + 1 && i < ET_MESSAGE_MAX_TRANSFER_LEN; i++)
		buf[i] = msg.data[i - 1];
	
	// Insert the crc code after the message
	buf[i++] = crc_8(buf, len + 1);
	
	// Pad the rest of the message data buffer with 0xFF
	while (i < ET_MESSAGE_MAX_TRANSFER_LEN)
		buf[i++] = 0xFF;
	
	return len + 2;
}

et_msg decode_et_msg(uint8_t *bytes, unsigned int len)
{
	et_msg msg;
	msg.type = TE_MESSAGE_INVALID;
	
	// Check buffer and length bounds. Any transfer should
	// include at least a type and crc byte, so len < 2
	// means nonsense
	if (!bytes || len < 2 || len > ET_MESSAGE_MAX_TRANSFER_LEN)
	{
		return msg;
	}
	
	if (!valid_et_msg_type(bytes[0]))
	{
		return msg;
	}
	
	uint8_t received_crc = bytes[len - 1];
	uint8_t computed_crc = crc_8(bytes, len - 1);
	
	if (received_crc != computed_crc)
	{
		msg.type = ET_MESSAGE_CRC_FAIL;
		return msg;
	}
	
	msg.type = bytes[0];
	
	// Length of the transmitted body is 2 less than
	// the total transmitted length, due to type byte
	// and crc byte
	int data_len = len - 2;
	
	int i;
	for (i = 0; i < data_len && i < ET_MESSAGE_MAX_DATA_LEN; i++)
		msg.data[i] = bytes[i + 1];
	
	// Pad the rest of the buffer with 0xFF
	// That way if any later function erroneously 
	// reads past the end of the message content,
	// it sees deterministic 0xFF padding
	// rather than random garbage. Easier to
	// debug if it happens, plus less likely
	// to be interpreted as a valid but unintended
	// command
	while (i < ET_MESSAGE_MAX_DATA_LEN)
		msg.data[i++] = 0xFF;
	
	msg.callback = NULL;
	msg.cb_arg   = NULL;
	
	return msg;
}


et_msg create_et_msg_nodata(uint16_t type)
{
	et_msg msg;
	msg.type = type;
	
	for (int i = 0; i < ET_MESSAGE_MAX_DATA_LEN; i++)
		msg.data[i] = 0xFF;
	
	msg.callback = NULL;
	msg.cb_arg   = NULL;
	
	msg.retries = et_message_default_retries(msg.type);
	
	return msg;
}

et_msg create_et_msg(uint16_t type, const char *fmt, ...)
{
	et_msg msg;
	
	uint8_t  b;
	uint16_t s;
	float 	 f;
	
	int index = 0;
	
	va_list args;
	va_start(args, fmt);
	
	msg.type = type;
	
	while (*fmt && index < ET_MESSAGE_MAX_DATA_LEN)
	{
		switch (*fmt++)
		{
			case '1':
			case 'b':
				b = va_arg(args, int);
				memcpy(&msg.data[index], &b, sizeof(uint8_t));
				index += sizeof(uint8_t);
				break;
				
			case '2':
			case 's':
				s = va_arg(args, int);
				memcpy(&msg.data[index], &s, sizeof(uint16_t));
				index += sizeof(uint16_t);
				break;
				
			case 'f':
				f = va_arg(args, double);
				memcpy(&msg.data[index], &f, sizeof(float));
				index += sizeof(float);
				break;
			
			default:
				msg.type = ET_MESSAGE_INVALID;
				return msg;
		}
	}
	va_end(args);
	
	while (index < ET_MESSAGE_MAX_DATA_LEN)
		msg.data[index++] = 0xFF;
	
	msg.callback = NULL;
	msg.cb_arg   = NULL;
	
	msg.retries = et_message_default_retries(msg.type);
	
	return msg;
}

int valid_et_msg_type(uint8_t type)
{
	return (ET_MESSAGE_HI <= type && type <= ET_MESSAGE_TYPE_MAX);
}


const char *et_msg_code_to_string(uint16_t code)
{
	switch (code)
	{
		case ET_MESSAGE_INVALID:
			return "ET_MESSAGE_INVALID";
		case ET_MESSAGE_HI:
			return "ET_MESSAGE_HI";
		case ET_MESSAGE_RESET:
			return "ET_MESSAGE_RESET";
		case ET_MESSAGE_REBOOT:
			return "ET_MESSAGE_REBOOT";
		case ET_MESSAGE_CREATE_PROFILE:
			return "ET_MESSAGE_CREATE_PROFILE";
		case ET_MESSAGE_APPEND_TRANSFORMER:
			return "ET_MESSAGE_APPEND_TRANSFORMER";
		case ET_MESSAGE_MOVE_TRANSFORMER:
			return "ET_MESSAGE_MOVE_TRANSFORMER";
		case ET_MESSAGE_REMOVE_TRANSFORMER:
			return "ET_MESSAGE_REMOVE_TRANSFORMER";
		case ET_MESSAGE_GET_N_PROFILES:
			return "ET_MESSAGE_GET_N_PROFILES";
		case ET_MESSAGE_GET_N_TRANSFORMERS:
			return "ET_MESSAGE_GET_N_TRANSFORMERS";
		case ET_MESSAGE_GET_TRANSFORMER_ID:
			return "ET_MESSAGE_GET_TRANSFORMER_ID";
		case ET_MESSAGE_GET_TRANSFORMER_TYPE:
			return "ET_MESSAGE_GET_TRANSFORMER_TYPE";
		case ET_MESSAGE_GET_N_PARAMETERS:
			return "ET_MESSAGE_GET_N_PARAMETERS";
		case ET_MESSAGE_GET_PARAM_VALUE:
			return "ET_MESSAGE_GET_PARAM_VALUE";
		case ET_MESSAGE_SET_PARAM_VALUE:
			return "ET_MESSAGE_SET_PARAM_VALUE";
		case ET_MESSAGE_GET_N_OPTIONS:
			return "ET_MESSAGE_GET_N_OPTIONS";
		case ET_MESSAGE_GET_OPTION_VALUE:
			return "ET_MESSAGE_GET_OPTION_VALUE";
		case ET_MESSAGE_SET_OPTION_VALUE:
			return "ET_MESSAGE_SET_OPTION_VALUE";
		case ET_MESSAGE_STRING_CONTINUE:
			return "ET_MESSAGE_STRING_CONTINUE";
		case ET_MESSAGE_STRING_CONTINUING:
			return "ET_MESSAGE_STRING_CONTINUING";
		case ET_MESSAGE_SWITCH_PROFILE:
			return "ET_MESSAGE_SWITCH_PROFILE";
		case ET_MESSAGE_DELETE_PROFILE:
			return "ET_MESSAGE_DELETE_PROFILE";
		case ET_MESSAGE_REPEAT_MESSAGE:
			return "ET_MESSAGE_REPEAT_MESSAGE";
		default:
			return "UNKNOWN MESSAGE CODE";
	}
}

const char *te_msg_code_to_string(uint16_t code)
{
	switch (code)
	{
		
		case TE_MESSAGE_INVALID:
			return "TE_MESSAGE_INVALID";
		case TE_MESSAGE_WAIT:
			return "TE_MESSAGE_WAIT";
		case TE_MESSAGE_HI:
			return "TE_MESSAGE_HI";
		case TE_MESSAGE_BAD_MESSAGE:
			return "TE_MESSAGE_BAD_MESSAGE";
		case TE_MESSAGE_BAD_REQUEST:
			return "TE_MESSAGE_BAD_REQUEST";
		case TE_MESSAGE_TRY_AGAIN:
			return "TE_MESSAGE_TRY_AGAIN";
		case TE_MESSAGE_OK:
			return "TE_MESSAGE_OK";
		case TE_MESSAGE_ERROR:
			return "TE_MESSAGE_ERROR";
		case TE_MESSAGE_PROFILE_ID:
			return "TE_MESSAGE_PROFILE_ID";
		case TE_MESSAGE_TRANSFORMER_ID:
			return "TE_MESSAGE_TRANSFORMER_ID";
		case TE_MESSAGE_N_PROFILES:
			return "TE_MESSAGE_N_PROFILES";
		case TE_MESSAGE_N_TRANSFORMERS:
			return "TE_MESSAGE_N_TRANSFORMERS";
		case TE_MESSAGE_TRANSFORMER_TYPE:
			return "TE_MESSAGE_TRANSFORMER_TYPE";
		case TE_MESSAGE_N_PARAMETERS:
			return "TE_MESSAGE_N_PARAMETERS";
		case TE_MESSAGE_PARAM_VALUE:
			return "TE_MESSAGE_PARAM_VALUE";
		case TE_MESSAGE_N_OPTIONS:
			return "TE_MESSAGE_N_OPTIONS";
		case TE_MESSAGE_OPTION_VALUE:
			return "TE_MESSAGE_OPTION_VALUE";
		case TE_MESSAGE_STRING_CONTINUING:
			return "TE_MESSAGE_STRING_CONTINUING";
		case TE_MESSAGE_START_OVER:
			return "TE_MESSAGE_START_OVER";
		case TE_MESSAGE_SWITCHING_PROFILE:
			return "TE_MESSAGE_SWITCHING_PROFILE";
		case TE_MESSAGE_DELETED_PROFILE:
			return "TE_MESSAGE_DELETED_PROFILE";
		case TE_MESSAGE_REPEAT_MESSAGE:
			return "TE_MESSAGE_REPEAT_MESSAGE";
		default:
			return "UNKNOWN MESSAGE CODE";
	}
}

int te_message_data_length(te_msg msg)
{
	switch (msg.type)
	{
		case TE_MESSAGE_HI:
			return sizeof(uint16_t);
		
		case TE_MESSAGE_BAD_MESSAGE:
			return 0;

		case TE_MESSAGE_BAD_REQUEST:
			return 0;

		case TE_MESSAGE_TRY_AGAIN:
			return 0;

		case TE_MESSAGE_OK:
			return 0;

		case TE_MESSAGE_ERROR:
			return sizeof(int);

		case TE_MESSAGE_PROFILE_ID:
			return sizeof(uint16_t);

		case TE_MESSAGE_TRANSFORMER_ID:
			return 2 * sizeof(uint16_t);

		case TE_MESSAGE_N_PROFILES:
			return 1 * sizeof(uint16_t);
			
		case TE_MESSAGE_N_TRANSFORMERS:
			return 2 * sizeof(uint16_t);

		case TE_MESSAGE_TRANSFORMER_TYPE:
			return 3 * sizeof(uint16_t);

		case TE_MESSAGE_N_PARAMETERS:
			return 3 * sizeof(uint16_t);

		case TE_MESSAGE_PARAM_VALUE:
			return 3 * sizeof(uint16_t) + sizeof(float);
		
		case TE_MESSAGE_STRING_CONTINUING:
			return MESSAGE_LEN_VARIABLE;

		case TE_MESSAGE_START_OVER:
			return 0;

		case TE_MESSAGE_SWITCHING_PROFILE:
			return 1 * sizeof(uint16_t);

		case TE_MESSAGE_DELETED_PROFILE:
			return 1 * sizeof(uint16_t);
		
		case TE_MESSAGE_REPEAT_MESSAGE:
			return 0;

		default:
			return -1;
	}
}

// Returns the transfer length
int encode_te_msg(uint8_t *buf, te_msg msg)
{
	if (!buf)
	{
		return -1;
	}
	
	buf[0] = msg.type;
	
	int len = te_message_data_length(msg);
	
	// Should not be possible. Throw a fit if it happens
	if (len > TE_MESSAGE_MAX_DATA_LEN)
	{
		buf[0] = TE_MESSAGE_INVALID;
		return -1;
	}
	
	if (len == MESSAGE_LEN_VARIABLE)
		len = TE_MESSAGE_MAX_DATA_LEN;
	
	int i;
	for (i = 1; i < len + 1 && i < TE_MESSAGE_MAX_TRANSFER_LEN - 1; i++)
		buf[i] = msg.data[i - 1];
	
	// Pad the rest of the message data buffer with 0xFF
	while (i < TE_MESSAGE_MAX_TRANSFER_LEN - 1)
		buf[i++] = 0xFF;
	
	// Insert the crc code after the message plus padding
	buf[TE_MESSAGE_MAX_TRANSFER_LEN - 1] = crc_8(buf, TE_MESSAGE_MAX_TRANSFER_LEN - 1);
	return len + 2;
}

te_msg decode_te_msg(uint8_t *bytes, unsigned int len)
{
	te_msg msg;
	msg.type = TE_MESSAGE_INVALID;
	
	// Check buffer and length bounds. Any transfer should
	// include at least a type and crc byte, so len < 2
	// means nonsense
	if (!bytes || len < 2 || len > TE_MESSAGE_MAX_TRANSFER_LEN)
	{
		return msg;
	}
	
	if (!valid_te_msg_type(bytes[0]))
	{
		return msg;
	}
	
	uint8_t received_crc = bytes[len - 1];
	uint8_t computed_crc = crc_8(bytes, len - 1);
	
	if (received_crc != computed_crc)
	{
		msg.type = TE_MESSAGE_CRC_FAIL;
		return msg;
	}
	
	msg.type = bytes[0];
	
	// Length of the transmitted body is 2 less than
	// the total transmitted length, due to type byte
	// and crc byte
	int data_len = len - 2;
	
	int i;
	for (i = 0; i < data_len && i < TE_MESSAGE_MAX_DATA_LEN; i++)
		msg.data[i] = bytes[i + 1];
	
	// Pad the rest of the buffer with 0xFF
	// That way if any later function erroneously 
	// reads past the end of the message content,
	// it sees deterministic 0xFF padding
	// rather than random garbage. Easier to
	// debug if it happens, plus less likely
	// to be interpreted as a valid but unintended
	// command
	while (i < TE_MESSAGE_MAX_DATA_LEN)
		msg.data[i++] = 0xFF;
	
	return msg;
}

int valid_te_msg_type(uint8_t type)
{
	return (TE_MESSAGE_WAIT <= type && type <= TE_MESSAGE_TYPE_MAX);
}

te_msg create_te_msg(uint16_t type, const char *fmt, ...)
{
	te_msg msg;
	
	uint8_t  b;
	uint16_t s;
	float 	 f;
	
	int index = 0;
	
	va_list args;
	va_start(args, fmt);
	
	msg.type = type;
	
	while (*fmt && index < TE_MESSAGE_MAX_DATA_LEN)
	{
		switch (*fmt++)
		{
			case '1':
			case 'b':
				b = (uint8_t)va_arg(args, int);
				memcpy(&msg.data[index], &b, sizeof(uint8_t));
				index += sizeof(uint8_t);
				break;
				
			case '2':
			case 's':
				s = (uint16_t)va_arg(args, int);
				memcpy(&msg.data[index], &s, sizeof(uint16_t));
				index += sizeof(uint16_t);
				break;
				
			case 'f':
				f = (float)va_arg(args, double);
				memcpy(&msg.data[index], &f, sizeof(float));
				index += sizeof(float);
				break;
			
			default:
				msg.type = ET_MESSAGE_INVALID;
				break;
		}
	}
	va_end(args);
	
	while (index < TE_MESSAGE_MAX_DATA_LEN)
		msg.data[index++] = 0xFF;
	
	return msg;
}

te_msg create_te_msg_nodata(uint16_t type)
{
	te_msg msg;
	msg.type = type;
	return msg;
}

te_msg create_te_msg_ok()
{
	return create_te_msg(TE_MESSAGE_OK, "");
}

te_msg create_te_msg_parameter_value(uint16_t pid, uint16_t tid, uint16_t ppid, float val)
{
	te_msg msg;
	
	msg.type = TE_MESSAGE_PARAM_VALUE;
	memcpy(&msg.data[0], &pid, 	 	  sizeof(uint16_t));
	memcpy(&msg.data[2], &tid, 		  sizeof(uint16_t));
	memcpy(&msg.data[4], &ppid,   	  sizeof(uint16_t));
	memcpy(&msg.data[6], &val, 		  sizeof(float));
	
	return msg;
}

te_msg create_te_msg_error(uint16_t error_code)
{
	te_msg msg;
	
	msg.type = TE_MESSAGE_ERROR;
	
	memcpy(msg.data, &error_code, sizeof(uint16_t));
	
	return msg;
}

te_msg create_te_msg_profile_id(uint16_t pid)
{
	te_msg msg;
	
	msg.type = TE_MESSAGE_PROFILE_ID;
	
	memcpy(&msg.data[0], &pid, sizeof(uint16_t));
	
	return msg;
}

te_msg create_te_msg_transformer_id(uint16_t pid, uint16_t tid)
{
	te_msg msg;
	
	msg.type = TE_MESSAGE_TRANSFORMER_ID;
	
	memcpy(&msg.data[0], &pid, sizeof(uint16_t));
	memcpy(&msg.data[2], &tid, sizeof(uint16_t));
	
	return msg;
}

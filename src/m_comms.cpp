#ifdef __cplusplus
#include <cstring>
#include <cstdint>
#include <cstdarg>
#include "m_printf.h"
#else
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#endif
#include "m_parameter.h"
#include "m_comms.h"

int et_message_data_length(et_msg msg)
{
	switch (msg.type)
	{
		case ET_MESSAGE_HI:
			return 0;
			
		case ET_MESSAGE_SYNC:
			return 0;

		case ET_MESSAGE_SYNCED:
			return 0;

		case ET_MESSAGE_RESET:
			return 0;

		case ET_MESSAGE_REBOOT:
			return 0;
		
		case ET_MESSAGE_NEW_PROFILE:
			return 0;
		
		case ET_MESSAGE_NEW_TRANSFORMER:
			return 2 * sizeof(uint16_t);

		case ET_MESSAGE_GET_N_PROFILES:
			return 0;

		case ET_MESSAGE_GET_N_TRANSFORMERS:
			return 1 * sizeof(uint16_t);
			
		case ET_MESSAGE_GET_TRANSFORMER_TYPE:
			return 2 * sizeof(uint16_t);
			
		case ET_MESSAGE_GET_N_PARAMETERS:
			return 2 * sizeof(uint16_t);

		case ET_MESSAGE_GET_PARAM_TYPE:
			return 3 * sizeof(uint16_t);

		case ET_MESSAGE_GET_PARAM_VALUE:
			return 3 * sizeof(uint16_t);
			
		case ET_MESSAGE_SET_PARAM_VALUE: 
			return 3 * sizeof(uint16_t) + sizeof(m_param_value);

		case ET_MESSAGE_SET_PARAM_NAME:
			return MESSAGE_LEN_VARIABLE;

		case ET_MESSAGE_GET_TRANSFORMER_INPUT:
			return 3 * sizeof(uint16_t);

		case ET_MESSAGE_SET_TRANSFORMER_INPUT:
			return 5 * sizeof(uint16_t);

		case ET_MESSAGE_GET_TRANSFORMER_OUTPUT:
			return 3 * sizeof(uint16_t);

		case ET_MESSAGE_SET_TRANSFORMER_OUTPUT:
			return 5 * sizeof(uint16_t);
		
		default:
			return -1;
	}
}

// Returns the length
int encode_et_msg(uint8_t *buf, et_msg msg)
{
	if (!buf)
		return -1;
	
	buf[0] = msg.type;
	
	int len = et_message_data_length(msg);
	
	int i;
	for (i = 1; i < len + 1 && i < ET_MESSAGE_MAX_LEN; i++)
		buf[i] = msg.data[i - 1];
		
	while (i < ET_MESSAGE_MAX_LEN)
		buf[i++] = 0xFF;
	
	return len + 1;
}


et_msg create_et_msg_no_data(uint16_t type)
{
	et_msg msg;
	msg.type = type;
	
	for (int i = 0; i < ET_MESSAGE_MAX_LEN; i++)
		msg.data[i] = 0xFF;
	
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
	
	while (*fmt && index < ET_MESSAGE_MAX_LEN)
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
	
	while (index < ET_MESSAGE_MAX_LEN)
		msg.data[index++] = 0xFF;
	
	return msg;
}

et_msg create_et_msg_chparam(m_parameter_id id, m_param_value new_val)
{
	et_msg_chparam_struct str;
	
	str.id = id;
	str.new_value = new_val;
	
	return create_et_msg_chparam_from_str(str);
}

et_msg create_et_msg_chparam_from_str(et_msg_chparam_struct str)
{
	et_msg msg;
	msg.type = ET_MESSAGE_SET_PARAM_VALUE;
	
	memcpy(&msg.data[0], &str.id.profile_id, 		2);
	memcpy(&msg.data[2], &str.id.transformer_id, 	2);
	memcpy(&msg.data[4], &str.id.parameter_id, 		2);
	memcpy(&msg.data[6], &str.new_value, sizeof(m_param_value));
	
	return msg;
}

et_msg create_et_msg_new_profile()
{
	et_msg msg;
	
	msg.type = ET_MESSAGE_NEW_PROFILE;
	return msg;
}

et_msg create_et_msg_new_transformer(uint16_t profile_id, uint16_t type)
{
	et_msg msg;
	
	msg.type = ET_MESSAGE_NEW_TRANSFORMER;
	
	memcpy(&msg.data[0], &profile_id, 2);
	memcpy(&msg.data[2], &type, 	  2);
	
	return msg;
}

et_msg_chparam_struct decode_et_msg_chparam(et_msg msg)
{
	et_msg_chparam_struct str;
	
	str.id.profile_id 		= 0;
	str.id.transformer_id 	= 0;
	str.id.parameter_id 	= 0;
	str.new_value.level 	= 1.0;
	
	if (msg.type != ET_MESSAGE_SET_PARAM_VALUE)
		return str;
	
	memcpy(&str.id.profile_id, 		&msg.data[0], 2);
	memcpy(&str.id.transformer_id,  &msg.data[2], 2);
	memcpy(&str.id.parameter_id, 	&msg.data[4], 2);
	memcpy(&str.new_value, 			&msg.data[6], sizeof(m_param_value));
	
	return str;
}

et_msg create_et_msg_rqparam(m_parameter_id id)
{
	et_msg msg;
	
	msg.type = ET_MESSAGE_GET_PARAM_VALUE;
	memcpy(&msg.data[0], &id.profile_id, 		2);
	memcpy(&msg.data[2], &id.transformer_id, 	2);
	memcpy(&msg.data[4], &id.parameter_id, 		2);
	
	return msg;
}

et_msg_rqparam_struct decode_et_msg_rqparam(et_msg msg)
{
	et_msg_rqparam_struct str;
	
	str.id.profile_id 		= 0;
	str.id.transformer_id 	= 0;
	str.id.parameter_id 	= 0;
	
	if (msg.type != ET_MESSAGE_GET_PARAM_VALUE)
		return str;
	
	memcpy(&str.id.profile_id, 		&msg.data[0], 2);
	memcpy(&str.id.transformer_id, 	&msg.data[2], 2);
	memcpy(&str.id.parameter_id, 	&msg.data[4], 2);
	
	return str;
}

int valid_et_msg_type(uint8_t type)
{
	return (ET_MESSAGE_HI <= type && type <= ET_MESSAGE_SET_TRANSFORMER_OUTPUT);
}

et_msg decode_et_msg(uint8_t *bytes)
{
	et_msg msg;
	msg.type = TE_MESSAGE_INVALID;
	
	if (!valid_et_msg_type(bytes[0]))
		return msg;
	
	msg.type = bytes[0];
	
	for (int i = 0; i < ET_MESSAGE_MAX_LEN - 1; i++)
		msg.data[i] = bytes[i + 1];
	
	return msg;
}

int te_message_data_length(te_msg msg)
{
	switch (msg.type)
	{
		case TE_MESSAGE_HI:
			return sizeof(uint16_t);
		
		case TE_MESSAGE_BAD_TRANSFER:
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

		case TE_MESSAGE_PARAMETER_ID:
			return 3 * sizeof(uint16_t);

		case TE_MESSAGE_N_PROFILES:
			return 1 * sizeof(uint16_t);
			
		case TE_MESSAGE_N_TRANSFORMERS:
			return 2 * sizeof(uint16_t);

		case TE_MESSAGE_TRANSFORMER_TYPE:
			return 3 * sizeof(uint16_t);

		case TE_MESSAGE_N_PARAMETERS:
			return 3 * sizeof(uint16_t);

		case TE_MESSAGE_PARAM_TYPE:
			return 4 * sizeof(uint16_t);

		case TE_MESSAGE_PARAM_VALUE:
			return 3 * sizeof(uint16_t) + sizeof(m_param_value);

		case TE_MESSAGE_PARAM_NAME:
			return MESSAGE_LEN_VARIABLE;

		case TE_MESSAGE_PARAM_NAME_LONG:
			return MESSAGE_LEN_VARIABLE;

		case TE_MESSAGE_TRANSFORMER_INPUT:
			return 5 * sizeof(uint16_t);

		case TE_MESSAGE_TRANSFORMER_OUTPUT:
			return 5 * sizeof(uint16_t);

		default:
			return -1;
	}
}

int encode_te_msg(uint8_t *buf, te_msg msg)
{
	if (!buf)
		return -1;
	
	buf[0] = msg.type;
	
	int len = te_message_data_length(msg);
	
	int i;
	for (i = 1; i < len + 1 && i < ET_MESSAGE_MAX_LEN; i++)
		buf[i] = msg.data[i - 1];
	
	while (i < TE_MESSAGE_MAX_LEN)
		buf[i++] = 0xFF;
	
	return len + 1;
}

int valid_te_msg_type(uint8_t type)
{
	return (TE_MESSAGE_HI <= type && type <= TE_MESSAGE_TRANSFORMER_OUTPUT);
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
	
	while (*fmt && index < TE_MESSAGE_MAX_LEN)
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
	
	while (index < TE_MESSAGE_MAX_LEN)
		msg.data[index++] = 0xFF;
	
	return msg;
}

te_msg create_te_msg_ok()
{
	return create_te_msg(TE_MESSAGE_OK, "");
}

te_msg create_te_msg_param_value(m_parameter_id id, m_parameter *param)
{
	te_msg msg;
	
	if (!param)
	{
		msg.type = TE_MESSAGE_INVALID;
	}
	else
	{
		msg.type = TE_MESSAGE_PARAM_VALUE;
		memcpy(msg.data, &param->val, sizeof(m_param_value));
	}
	
	return msg;
}

te_msg create_te_msg_error(uint16_t error_code)
{
	te_msg msg;
	
	msg.type = TE_MESSAGE_ERROR;
	
	memcpy(msg.data, &error_code, sizeof(uint16_t));
	
	return msg;
}

te_msg create_te_msg_profile_id(uint16_t id)
{
	te_msg msg;
	
	msg.type = TE_MESSAGE_PROFILE_ID;
	
	memcpy(msg.data, &id, sizeof(uint16_t));
	
	return msg;
}

te_msg create_te_msg_transformer_id(uint16_t profile_id, uint16_t transformer_id)
{
	te_msg msg;
	
	msg.type = TE_MESSAGE_TRANSFORMER_ID;
	
	memcpy(&msg.data[0], &profile_id, 	  sizeof(uint16_t));
	memcpy(&msg.data[2], &transformer_id, sizeof(uint16_t));
	
	return msg;
}

te_msg create_te_msg_parameter_id(uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id)
{
	te_msg msg;
	
	msg.type = TE_MESSAGE_PARAMETER_ID;
	
	memcpy(&msg.data[0], &profile_id, 	  sizeof(uint16_t));
	memcpy(&msg.data[2], &transformer_id, sizeof(uint16_t));
	memcpy(&msg.data[4], &parameter_id,   sizeof(uint16_t));
	
	return msg;
}

te_msg decode_te_msg(uint8_t *bytes)
{
	te_msg msg;
	msg.type = TE_MESSAGE_INVALID;
	
	if (!valid_te_msg_type(bytes[0]))
		return msg;
	
	msg.type = bytes[0];
	
	for (int i = 0; i < TE_MESSAGE_MAX_LEN - 1; i++)
		msg.data[i] = bytes[i + 1];
	
	return msg;
}

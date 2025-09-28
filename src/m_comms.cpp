#include "m_comms.h"

int et_message_data_length(et_msg msg)
{
	switch (msg.type)
	{
		case ET_MESSAGE_HI: 	 return 0;
		case ET_MESSAGE_CHPARAM: return 10;
		default: return -1;
	}
}

// Returns the length
int encode_et_msg(uint8_t *buf, et_msg msg)
{
	if (!buf)
		return -1;
	
	buf[0] = msg.type;
	
	int len = et_message_data_length(msg);
	
	for (int i = 0; i < len && i < ET_MESSAGE_MAX_DATA_LEN; i++)
		buf[i + 1] = msg.data[i];
	
	return len + 1;
}

int valid_et_msg_type(uint8_t type)
{
	return (type == ET_MESSAGE_HI || type == ET_MESSAGE_CHPARAM);
}

et_msg decode_et_msg(uint8_t *bytes, int n)
{
	et_msg msg;
	msg.type = TE_MESSAGE_INVALID;
	
	if (!valid_et_msg_type(bytes[0]) || n > ET_MESSAGE_MAX_DATA_LEN + 1)
		return msg;
	
	msg.type = bytes[0];
	
	for (int i = 0; i < n && i < ET_MESSAGE_MAX_DATA_LEN; i++)
		msg.data[i] = bytes[i + 1];
	
	return msg;
}

int te_message_data_length(te_msg msg)
{
	switch (msg.type)
	{
		case TE_MESSAGE_HI: 	 return 0;
		default: return -1;
	}
}

int encode_te_msg(uint8_t *buf, te_msg msg)
{
	if (!buf)
		return -1;
	
	buf[0] = msg.type;
	
	int len = te_message_data_length(msg);
	
	for (int i = 0; i < len && i < ET_MESSAGE_MAX_DATA_LEN; i++)
		buf[i + 1] = msg.data[i];
	
	return len + 1;
}

int valid_te_msg_type(uint8_t type)
{
	return (type <= TE_MESSAGE_HI && TE_MESSAGE_HI <= type);
}

te_msg decode_te_msg(uint8_t *bytes, int n)
{
	te_msg msg;
	msg.type = TE_MESSAGE_INVALID;
	
	if (!valid_te_msg_type(bytes[0]) || n > TE_MESSAGE_MAX_DATA_LEN + 1)
		return msg;
	
	
	msg.type = bytes[0];
	
	for (int i = 0; i < n && i < TE_MESSAGE_MAX_DATA_LEN; i++)
		msg.data[i] = bytes[i + 1];
	
	return msg;
}

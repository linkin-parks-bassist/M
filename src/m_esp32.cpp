#include <Wire.h>
#include "M.h"
#include "m_comms.h"

te_msg response;

int et_msg_sanity_check(et_msg msg, int len)
{
	if (!valid_et_msg_type(msg.type))
		return 0;
	
	if (len != et_message_data_length(msg))
		return 0;
	
	return 1;
}

int handle_esp32_message(et_msg msg)
{
	m_printf("Recieved message type: %d\n", msg.type);
	
	switch (msg.type)
	{
		case ET_MESSAGE_HI:
			m_printf("Recieved a HI; responding in kind\n");
			response.type = TE_MESSAGE_HI;
			return NO_ERROR;
			break;
		
		case ET_MESSAGE_CHPARAM:
			et_msg_chparam_struct str;
			memcpy(&str.profile_id, 	&msg.data[0], 2);
			memcpy(&str.transformer_id, &msg.data[2], 2);
			memcpy(&str.parameter_id, 	&msg.data[4], 2);
			memcpy(&str.new_value, 		&msg.data[6], 4);
			
			m_printf("Request to change parameter %d.%d.%d to vaalue %2f\n", str.profile_id, str.transformer_id, str.parameter_id, str.new_value);
			
			if (parameter_id_valid(&global_cxt, str.profile_id, str.transformer_id, str.parameter_id))
			{
				m_printf("Valid request; applying\n");
				global_cxt.profiles[str.profile_id].pipeline.transformers[str.transformer_id]->parameters[str.parameter_id]->value = str.new_value;
			}
			else
			{
				return ERR_ET_MSG_BAD_REQUEST;
			}
			
			break;
		
		default:
			response.type = TE_MESSAGE_NO_MESSAGE;
			return ERR_BAD_ARGS;
	}
	
	return NO_ERROR;
}

void i2c_recieve_isr(int n)
{
	m_printf("i2c recieve isr\n");
	uint8_t recieve_buffer[n];
	
	for (int i = 0; i < n; i++)
		recieve_buffer[i] = Wire.read();
	
	m_printf("recieved message:\n");
	
	for (int i = 0; i < n; i++)
		m_printf("%d%s", recieve_buffer[i], (i < n - 1) ? ", " : "\n");
	
	et_msg msg = decode_et_msg(recieve_buffer, n);
	int ret_val = et_msg_sanity_check(msg, n - 1) ? handle_esp32_message(msg) : ERR_BUSTED_ET_MSG;
	
	if (ret_val != NO_ERROR)
	{
		switch (ret_val)
		{
			case ERR_BUSTED_ET_MSG:
				response.type = TE_MESSAGE_BAD_TRANSFER;
				break;
			
			default:
				break;
		}
	}
}

void i2c_request_isr()
{
	m_AudioNoInterrupts();
	m_printf("i2c request isr\n");
	
	uint8_t send_buffer[TE_MESSAGE_MAX_DATA_LEN + 2];
	
	int len = encode_te_msg(&send_buffer[1], response);
	
	send_buffer[0] = (uint8_t)len;
	
	Wire.write(send_buffer, len);
	m_AudioInterrupts();
}

int init_esp32_link()
{
	Wire.begin(TEENSY_I2C_SLAVE_ADDR);
	Wire.onReceive(i2c_recieve_isr);
	Wire.onRequest(i2c_request_isr);
	
	return NO_ERROR;
}

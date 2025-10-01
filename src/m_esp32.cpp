#include <Wire.h>
#include "M.h"
#include "m_comms.h"
#include "signal.h"

te_msg response;
et_msg recieved;

uint8_t recieve_buffer[ET_MESSAGE_MAX_LEN];
uint8_t wait_message[ET_MESSAGE_MAX_LEN];

volatile sig_atomic_t message_pending = 0;
volatile sig_atomic_t response_ready  = 0;

int et_msg_sanity_check(et_msg msg, int len)
{
	m_printf("Message sanity check. msg.type = %d. length = %d. expected length = %d.\n", msg.type, len, et_message_data_length(msg));
	if (!valid_et_msg_type(msg.type))
		return 0;
	
	if (len != et_message_data_length(msg))
		return 0;
	
	return 1;
}

typedef enum
{
	IDLE,
	SYNCING
} comms_fsm_state_t;

comms_fsm_state_t comms_fsm_state = IDLE;

void handle_esp32_message(et_msg msg)
{
	m_printf("Recieved message type: %d\n", msg.type);
	int ret_val;
	
	uint16_t arg16_1, arg16_2, arg16_3, arg16_4;
	
	memcpy(&arg16_1, &msg.data[0], sizeof(uint16_t));
	memcpy(&arg16_2, &msg.data[1], sizeof(uint16_t));
	memcpy(&arg16_3, &msg.data[2], sizeof(uint16_t));
	memcpy(&arg16_4, &msg.data[3], sizeof(uint16_t));
	
	union
	{
		et_msg_chparam_struct chstr;
		et_msg_rqparam_struct rqstr;
	} str;
	
	switch (msg.type)
	{
		case ET_MESSAGE_HI:
			response = create_te_msg(TE_MESSAGE_HI, "s", global_cxt.status_flags);
			break;
		
		case ET_MESSAGE_SYNC:
			m_printf("Time to sync !\n");
			response = create_te_msg(TE_MESSAGE_N_PROFILES, "s", global_cxt.n_profiles);
			comms_fsm_state = SYNCING;
			break;
		
		case ET_MESSAGE_SYNCED:
			comms_fsm_state = IDLE;
			global_cxt.status_flags &= ~M_STATUS_FRESH_BOOT;
			response = create_te_msg_ok();
			break;
		
		case ET_MESSAGE_RESET:
			ret_val = reset_context(&global_cxt);
			response = create_te_msg_error(ret_val);
			break;
		
		case ET_MESSAGE_REBOOT:
			m_safe_reboot(&global_cxt);
			break;
		
		case ET_MESSAGE_SET_PARAM_VALUE:
			str.chstr = decode_et_msg_chparam(msg);
			ret_val = update_paramter_value_by_id(&global_cxt, str.chstr.id, str.chstr.new_value);
			
			response = create_te_msg_error(ret_val);
			break;
		
		case ET_MESSAGE_GET_PARAM_VALUE:
			str.rqstr = decode_et_msg_rqparam(msg);
			
			m_printf("Value of parameter %d.%d.%d requested...\n", str.rqstr.id.profile_id, str.rqstr.id.transformer_id, str.rqstr.id.parameter_id);
			if (parameter_id_str_valid(&global_cxt, str.rqstr.id))
			{ 
				m_parameter *param = get_parameter_by_id(&global_cxt, str.rqstr.id);
				m_printf("Request valid. Parameter ptr: 0x%08x, value %f\n", param, param->val.level);
				response = create_te_msg_param_value(str.rqstr.id, param);
			}
			else
			{
				m_printf("Requested parameter doesn't exist !\n");
				response.type = TE_MESSAGE_BAD_REQUEST;
			}
			break;
		
		case ET_MESSAGE_NEW_PROFILE:
			m_printf("Creating new profile...\n");
			ret_val = m_context_new_profile(&global_cxt);
			
			m_printf("ret_val: %d\n", ret_val);
			if (ret_val >= 0)	// A positive return is the ID of the new profile
				response = create_te_msg_profile_id(ret_val);
			else 				// A negative return is an error code
				response = create_te_msg_error(-ret_val);
			break;
		
		case ET_MESSAGE_NEW_TRANSFORMER:
			m_printf("Creating new transformer...\n");
			
			ret_val = cxt_add_transformer_to_profile(&global_cxt, arg16_1, arg16_2);
			
			if (ret_val < 0)
				response = create_te_msg_error(-ret_val);
			else
				response = create_te_msg_transformer_id(arg16_1, ret_val);
		
		case ET_MESSAGE_INVALID:
			response.type = TE_MESSAGE_BAD_TRANSFER;
			response.type = TE_MESSAGE_NO_MESSAGE;
			break;
	}
	
	response_ready = 1;
}

void i2c_recieve_isr(int n)
{
	m_AudioNoInterrupts();
	
	if (message_pending)
	{
		response.type = TE_MESSAGE_TRY_AGAIN;
	}
	else
	{
		message_pending = 1;
		response_ready  = 0;
		
		
		int i = 0;
		
		if (n > ET_MESSAGE_MAX_LEN)
		{
			for (i = 0; i < n; i++)
			{
				Wire.read();
				if (i < ET_MESSAGE_MAX_LEN)
					recieve_buffer[i] = 0;
			}
		}
		else
		{
			for (i = 0; i < n; i++)
				recieve_buffer[i] = Wire.read();
		
			while (i < ET_MESSAGE_MAX_LEN)
				recieve_buffer[i++] = 0xFF;
		}
	}
	
	/*for (int i = 0; i < n; i++)
		m_printf("%d%s", recieve_buffer[i], (i < n - 1) ? ", " : "\n");*/
	
	m_AudioInterrupts();
}

void i2c_request_isr()
{
	m_AudioNoInterrupts();
	//m_printf("i2c request isr\n");
	
	if (response_ready)
	{
		uint8_t send_buffer[TE_MESSAGE_MAX_LEN + 1];
		
		encode_te_msg(send_buffer, response);
		
		Wire.write(send_buffer, TE_MESSAGE_MAX_LEN);
		/*m_printf("Sent response:\n\t");
		for (int i = 0; i < TE_MESSAGE_MAX_LEN; i++)
		 m_printf("0x%02x%s", send_buffer[i], (i == TE_MESSAGE_MAX_LEN - 1) ? "\n" : " ");*/
	}
	else
	{
		Wire.write(wait_message, TE_MESSAGE_MAX_LEN);
	}
	m_AudioInterrupts();
}

int init_esp32_link()
{
	Wire.begin(TEENSY_I2C_SLAVE_ADDR);
	Wire.onReceive(i2c_recieve_isr);
	Wire.onRequest(i2c_request_isr);
	
	wait_message[0] = TE_MESSAGE_WAIT;
	
	return NO_ERROR;
}

void esp32_message_check_handle()
{
	if (message_pending)
	{
		handle_esp32_message(decode_et_msg(recieve_buffer));
		message_pending = 0;
	}
}

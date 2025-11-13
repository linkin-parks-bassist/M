#include <cstdint>
#include "m_eng.h"

extern "C"
{
	#include "signal.h"
}

#ifndef M_SIMULATED
#include <Wire.h>
#include "utility/imxrt_hw.h"
#endif

static const char *FNAME = "m_eng_comms.cpp";

te_msg response;
te_msg prev_response;
et_msg received;

#ifndef M_SIMULATED
volatile 
#endif
uint8_t receive_buffer [ET_MESSAGE_MAX_TRANSFER_LEN];
uint8_t response_buffer[ET_MESSAGE_MAX_TRANSFER_LEN];
uint8_t wait_message   [ET_MESSAGE_MAX_TRANSFER_LEN];

volatile unsigned int received_length;
unsigned int response_length;

volatile sig_atomic_t message_pending = 0;
volatile sig_atomic_t response_ready  = 0;

int et_msg_sanity_check(et_msg msg, int len)
{
	FUNCTION_START();

	m_printf("Message sanity check. msg.type = %d. length = %d. expected length = %d.\n", msg.type, len, et_message_data_length(msg));
	if (!valid_et_msg_type(msg.type))
	{
		RETURN_INT(0);
	}
	
	int expected_len = et_message_data_length(msg);
	
	if (expected_len != MESSAGE_LEN_VARIABLE && len != expected_len)
	{
		RETURN_INT(0);
	}
	
	RETURN_INT(1);
}

typedef enum
{
	IDLE,
	SENDING_STRING,
	RECIEVING_NEW_PARAM_NAM_ENG_LONG
} comms_fsm_eng_state_t;

char *string_out = NULL;
int string_out_pos;

char *string_in = NULL;
int string_in_pos;

comms_fsm_eng_state_t comms_fsm_eng_state = IDLE;

void handle_esp32_message(et_msg msg)
{
	FUNCTION_START();
	
	int ret_val;
	int string_received = 0;
	
	uint16_t arg16_1, arg16_2, arg16_3, arg16_4, arg16_5;
	
	memcpy(&arg16_1, &msg.data[0],  sizeof(uint16_t));
	memcpy(&arg16_2, &msg.data[2],  sizeof(uint16_t));
	memcpy(&arg16_3, &msg.data[4],  sizeof(uint16_t));
	memcpy(&arg16_4, &msg.data[6],  sizeof(uint16_t));
	memcpy(&arg16_5, &msg.data[8],  sizeof(uint16_t));
	
	m_parameter *param;
	m_setting *setting;
	float value_f;
	int16_t value_i;
	
	int len;
	
	switch (msg.type)
	{
		case ET_MESSAGE_REPEAT_MESSAGE:
			response = prev_response;
			break;
			
		case ET_MESSAGE_CRC_FAIL:
			response.type = TE_MESSAGE_REPEAT_MESSAGE;
			break;
			
		case ET_MESSAGE_HI:
			response = create_te_msg(TE_MESSAGE_HI, "s", global_cxt.status_flags);
			break;
		
		case ET_MESSAGE_RESET:
			ret_val = reset_context(&global_cxt);
			response = create_te_msg_error(ret_val);
			break;
		
		case ET_MESSAGE_REBOOT:
			m_eng_safe_reboot(&global_cxt);
			break;
		
		case ET_MESSAGE_CREATE_PROFILE:
			m_printf("Creating new profile...\n");
			ret_val = m_eng_context_new_profile(&global_cxt);
			
			m_printf("ret_val: %d\n", ret_val);
			if (ret_val >= 0)	// A positive return is the ID of the new profile
			{
				response = create_te_msg(TE_MESSAGE_PROFILE_ID, "s", ret_val);
			}
			else 				// A negative return is an error code
			{
				response = create_te_msg_error(-ret_val);
			}
			break;
		
		case ET_MESSAGE_APPEND_TRANSFORMER:
			m_printf("Creating new transformer of type %d to profile %d...\n", arg16_2, arg16_1);
			
			ret_val = cxt_append_transformer_to_profile(&global_cxt, arg16_1, arg16_2);
			
			if (ret_val < 0)
			{
				m_printf("Appending transformer failed with error %s\n", m_error_code_to_string(-ret_val));
				response = create_te_msg_error(-ret_val);
			}
			else
			{
				m_printf("Success. Obtained transformer id %d; sending back\n", ret_val);
				response = create_te_msg_transformer_id(arg16_1, ret_val);
				m_printf("Response created\n");
			}
			break;
		
		case ET_MESSAGE_MOVE_TRANSFORMER:
			m_printf("Moving transformer...\n");
			
			ret_val = cxt_move_transformer(&global_cxt, arg16_1, arg16_2);
			
			response = create_te_msg_error(ret_val);
			break;
			
		case ET_MESSAGE_REMOVE_TRANSFORMER:
			m_printf("Removing transformer...\n");
			
			ret_val = cxt_remove_transformer_from_profile(&global_cxt, arg16_1, arg16_2);
			
			response = create_te_msg_error(ret_val);
			break;
		
		case ET_MESSAGE_GET_N_PROFILES:
			m_printf("esp32 asks: how many profiles? answer: %d\n", global_cxt.n_profiles);
			response = create_te_msg(TE_MESSAGE_N_PROFILES, "s", global_cxt.n_profiles);
			break;
		
		case ET_MESSAGE_GET_N_TRANSFORMERS:
			m_printf("esp32 asks: how many transformers in profile %d? answer: %d\n", arg16_1, cxt_get_n_profile_transformers(&global_cxt, arg16_1));
			response = create_te_msg(TE_MESSAGE_N_TRANSFORMERS, "ss", arg16_1,
									 cxt_get_n_profile_transformers(&global_cxt, arg16_1));
			break;
		
		case ET_MESSAGE_GET_TRANSFORMER_ID:
			m_printf("esp32 asks: what is the id of the transformer in position %d in profile %d? answer: %d\n", arg16_2, arg16_1, cxt_get_tid_by_pos(&global_cxt, arg16_1, arg16_2));
			response = create_te_msg(TE_MESSAGE_TRANSFORMER_TYPE, "sss", arg16_1, arg16_2,
									 cxt_get_tid_by_pos(&global_cxt, arg16_1, arg16_2));
			break;
		
		case ET_MESSAGE_GET_TRANSFORMER_TYPE:
			m_printf("esp32 asks: what is the type of transformer %d.%d? answer: %d\n", arg16_1, arg16_2, cxt_get_transformer_type(&global_cxt, arg16_1, arg16_2));
			response = create_te_msg(TE_MESSAGE_TRANSFORMER_TYPE, "sss", arg16_1, arg16_2,
									 cxt_get_transformer_type(&global_cxt, arg16_1, arg16_2));
			break;
		
		case ET_MESSAGE_GET_N_PARAMETERS:
			m_printf("esp32 asks: what is the n_parameters of transformer %d.%d? answer: %d\n", arg16_1, arg16_2, cxt_get_n_transformer_params(&global_cxt, arg16_1, arg16_2));
			response = create_te_msg(TE_MESSAGE_N_PARAMETERS, "sss", arg16_1, arg16_2,
									 cxt_get_n_transformer_params(&global_cxt, arg16_1, arg16_2));
			break;
		
		case ET_MESSAGE_GET_PARAM_VALUE:
			m_printf("Request for value of parameter %d.%d.%d...\n", arg16_1, arg16_2, arg16_3);
			
			param = cxt_get_parameter_by_id(&global_cxt, arg16_1, arg16_2, arg16_3);
			
			if (param)
			{
				m_printf("Request valid. Parameter ptr: 0x%08x, value %f\n", param, param->value);
				response = create_te_msg(TE_MESSAGE_PARAM_VALUE, "sss", arg16_1, arg16_2, arg16_3);
				memcpy(&response.data[6], &param->value, sizeof(float));
			}
			else
			{
				m_printf("Requested parameter doesn't exist !\n");
				response.type = TE_MESSAGE_BAD_REQUEST;
			}
			break;
		
		case ET_MESSAGE_SET_PARAM_VALUE:
			memcpy(&value_f, &msg.data[6], sizeof(float));
			
			m_printf("Request to set parameter %d.%d.%d to value %f\n", arg16_1, arg16_2, arg16_3, value_f);
			
			ret_val = cxt_update_parameter_value_by_id(&global_cxt, arg16_1, arg16_2, arg16_3, value_f);
			
			if (ret_val != NO_ERROR)
			{
				printf("Failed! Error: %s\n", m_error_code_to_string(ret_val));
				response = create_te_msg_error(ret_val);
			}
			else
			{
				response = create_te_msg_parameter_value(arg16_1, arg16_2, arg16_3, value_f);
			}
			
			
			break;
		
		case ET_MESSAGE_GET_N_SETTINGS:
			m_printf("esp32 asks: what is the n_settings of transformer %d.%d? answer: %d\n", arg16_1, arg16_2, cxt_get_n_transformer_settings(&global_cxt, arg16_1, arg16_2));
			response = create_te_msg(TE_MESSAGE_N_SETTINGS, "sss", arg16_1, arg16_2,
									 cxt_get_n_transformer_settings(&global_cxt, arg16_1, arg16_2));
			break;
		
		case ET_MESSAGE_GET_SETTING_VALUE:
			m_printf("Request for value of setting %d.%d.%d...\n", arg16_1, arg16_2, arg16_3);
			
			setting = cxt_get_setting_by_id(&global_cxt, arg16_1, arg16_2, arg16_3);
			
			if (setting)
			{
				m_printf("Request valid. Parameter ptr: 0x%08x, value %d\n", setting, setting->value);
				response = create_te_msg(TE_MESSAGE_SETTING_VALUE, "sss", arg16_1, arg16_2, arg16_3);
				memcpy(&response.data[6], &setting->value, sizeof(uint16_t));
			}
			else
			{
				m_printf("Requested setting doesn't exist !\n");
				response.type = TE_MESSAGE_BAD_REQUEST;
			}
			break;
		
		case ET_MESSAGE_SET_SETTING_VALUE:
			memcpy(&value_i, &msg.data[6], sizeof(int16_t));
			
			m_printf("Request to set setting %d.%d.%d to value %d\n", arg16_1, arg16_2, arg16_3, value_i);
			ret_val = cxt_update_setting_value_by_id(&global_cxt, arg16_1, arg16_2, arg16_3, value_i);
			
			response = create_te_msg_error(ret_val);
			break;
		
		case ET_MESSAGE_SWITCH_PROFILE:
			m_printf("Profile switch requested; to profile %d\n", arg16_1);
			if (arg16_1 < global_cxt.n_profiles)
			{
				ret_val = cxt_switch_to_profile(&global_cxt, arg16_1);
				
				if (ret_val != NO_ERROR)
					response = create_te_msg_error(ret_val);
				else
					response = create_te_msg(TE_MESSAGE_SWITCHING_PROFILE, "s", arg16_1);
				
				m_printf("Request valid; swwitching. Error code: %d\n", ret_val);
			}
			else
			{
				m_printf("No such profile exists!\n");
				response = create_te_msg_nodata(TE_MESSAGE_BAD_REQUEST);
			}
			break;
		
		case ET_MESSAGE_STRING_CONTINUE:
		
			break;
		
		case ET_MESSAGE_STRING_CONTINUING:
			if (!string_in)
			{
				response = create_te_msg_nodata(TE_MESSAGE_START_OVER);
			}
			else
			{
				string_received = 0;
				
				for (int i = 0; i < ET_MESSAGE_MAX_TRANSFER_LEN; i++)
				{
					string_in[string_in_pos++] = (char)msg.data[i];
					if (msg.data[i] == 0)
					{
						string_received = 1;
						break;
					}
				}
				
				response = create_te_msg_ok();
			}
			break;
			
		default:
			response.type = TE_MESSAGE_BAD_MESSAGE;
			break;
	}
	
	response_length = encode_te_msg(response_buffer, response);
	response_ready = 1;
}

void i2c_receive_isr(int n)
{
	FUNCTION_START();
	m_eng_disable_software_interrupts();
	
	if (message_pending)
	{
		response.type = TE_MESSAGE_TRY_AGAIN;
	}
	else
	{
		message_pending = 1;
		response_ready  = 0;
		
		int i = 0;
		
		if (n > ET_MESSAGE_MAX_TRANSFER_LEN)
		{
			received_length = 1;
			for (i = 0; i < n; i++)
			{
				#ifndef M_SIMULATED
				Wire1.read();
				#else
				
				#endif
				if (i < ET_MESSAGE_MAX_TRANSFER_LEN)
					receive_buffer[i] = 0xFF;
				
			}
			
			receive_buffer[0] = ET_MESSAGE_INVALID;
		}
		else
		{
			received_length = n;
			#ifndef M_SIMULATED
			for (i = 0; i < n; i++)
				receive_buffer[i] = Wire1.read();
			#else
			for (i = 0; i < n; i++)
				receive_buffer[i] = simulated_i2c_send_buffer[i];
			#endif
		
			while (i < ET_MESSAGE_MAX_TRANSFER_LEN)
				receive_buffer[i++] = 0xFF;
		}
	}
	
	//for (int i = 0; i < n; i++)
	//	m_printf("%d%s", receive_buffer[i], (i < n - 1) ? ", " : "\n");
	
	m_eng_enable_software_interrupts();
}

void i2c_request_isr()
{
	FUNCTION_START();
	m_eng_disable_software_interrupts();
	
	if (response_ready)
	{
		#ifndef M_SIMULATED
		Wire1.write(response_buffer, TE_MESSAGE_MAX_TRANSFER_LEN);
		#else
		teensy_i2c_response = response;
		#endif
		
		prev_response = response;
		#ifdef PRINT_RESPONSE_BYTES
		m_printf("Sent response:\n\t");
		for (int i = 0; i < TE_MESSAGE_MAX_TRANSFER_LEN; i++)
			m_printf("0x%02x%s", response_buffer[i], (i == TE_MESSAGE_MAX_TRANSFER_LEN - 1) ? "\n" : " ");
		#endif
	}
	else
	{
		#ifndef M_SIMULATED
		Wire1.write(wait_message, TE_MESSAGE_MAX_TRANSFER_LEN);
		#else
		teensy_i2c_response.type = TE_MESSAGE_WAIT;
		#endif
	}
	m_eng_enable_software_interrupts();
}

int init_esp32_link()
{
	FUNCTION_START();
	#ifndef M_SIMULATED
	Wire1.begin(TEENSY_I2C_SLAVE_ADDR);
	Wire1.onReceive(i2c_receive_isr);
	Wire1.onRequest(i2c_request_isr);
	#else
	
	#endif
	
	wait_message[0] = TE_MESSAGE_WAIT;
	
	RETURN_ERR_CODE(NO_ERROR);
}

void esp32_message_check_handle()
{
	FUNCTION_START();
	uint8_t current_receive_buffer[ET_MESSAGE_MAX_TRANSFER_LEN];
	unsigned int current_received_length;
	if (message_pending)
	{
		for (int i = 0; i < ET_MESSAGE_MAX_TRANSFER_LEN; i++)
			current_receive_buffer[i] = receive_buffer[i];
		current_received_length = received_length;
		
		handle_esp32_message(decode_et_msg(current_receive_buffer, current_received_length));
		message_pending = 0;
	}
}

#include "tm.h"
#include "tm_comms.h"
#include "signal.h"
#include "m_vec2i.h"
#include "tm_context.h"
#include "tm_error_codes.h"

te_msg response;
et_msg recieved;

uint8_t recieve_buffer[ET_MESSAGE_MAX_LEN];
uint8_t wait_message[ET_MESSAGE_MAX_LEN];

volatile sig_atomic_t message_pending = 0;
volatile sig_atomic_t response_ready  = 0;

int et_msg_sanity_check(et_msg msg, int len)
{
	tm_printf("Message sanity check. msg.type = %d. length = %d. expected length = %d.\n", msg.type, len, et_message_data_length(msg));
	if (!valid_et_msg_type(msg.type))
		return 0;
	
	int expected_len = et_message_data_length(msg);
	
	if (expected_len != MESSAGE_LEN_VARIABLE && len != expected_len)
		return 0;
	
	return 1;
}

typedef enum
{
	IDLE,
	SENDING_STRING,
	RECIEVING_NEW_PARAM_NAME_LONG
} comms_fstm_state_t;

char *string_out = NULL;
int string_out_pos;

char *string_in = NULL;
int string_in_pos;

m_ppid target;

comms_fstm_state_t comms_fstm_state = IDLE;

void handle_esp32_message(et_msg msg)
{
	tm_printf("Recieved message of type %s\n", et_msg_code_to_string(msg.type));
	int ret_val;
	int string_received = 0;
	
	uint16_t arg16_1, arg16_2, arg16_3, arg16_4, arg16_5;
	
	memcpy(&arg16_1, &msg.data[0],  sizeof(uint16_t));
	memcpy(&arg16_2, &msg.data[2],  sizeof(uint16_t));
	memcpy(&arg16_3, &msg.data[4],  sizeof(uint16_t));
	memcpy(&arg16_4, &msg.data[6],  sizeof(uint16_t));
	memcpy(&arg16_5, &msg.data[8],  sizeof(uint16_t));
	
	tm_parameter *param;
	tm_option *option;
	float value_f;
	uint16_t value_i;
	
	int len;
	
	switch (msg.type)
	{
		case ET_MESSAGE_HI:
			response = create_te_msg(TE_MESSAGE_HI, "s", global_cxt.status_flags);
			break;
		
		case ET_MESSAGE_RESET:
			ret_val = reset_context(&global_cxt);
			response = create_te_msg_error(ret_val);
			break;
		
		case ET_MESSAGE_REBOOT:
			tm_safe_reboot(&global_cxt);
			break;
		
		case ET_MESSAGE_CREATE_PROFILE:
			tm_printf("Creating new profile...\n");
			ret_val = tm_context_new_profile(&global_cxt);
			
			tm_printf("ret_val: %d\n", ret_val);
			if (ret_val >= 0)	// A positive return is the ID of the new profile
				response = create_te_msg_profile_id(ret_val);
			else 				// A negative return is an error code
				response = create_te_msg_error(-ret_val);
			break;
		
		case ET_MESSAGE_APPEND_TRANSFORMER:
			tm_printf("Creating new transformer of type %d...\n", arg16_2);
			
			ret_val = cxt_append_transformer_to_profile(&global_cxt, arg16_1, arg16_2);
			
			tm_printf("Obtained transformer id %d; sending back\n", ret_val);
			if (ret_val < 0)
				response = create_te_msg_error(-ret_val);
			else
				response = create_te_msg_transformer_id(arg16_1, ret_val);
			break;
		
		case ET_MESSAGE_MOVE_TRANSFORMER:
			tm_printf("Moving transformer...\n");
			
			ret_val = cxt_move_transformer(&global_cxt, arg16_1, arg16_2);
			
			response = create_te_msg_error(ret_val);
			break;
			
		case ET_MESSAGE_REMOVE_TRANSFORMER:
			tm_printf("Removing transformer...\n");
			
			ret_val = cxt_remove_transformer_from_profile(&global_cxt, arg16_1, arg16_2);
			
			response = create_te_msg_error(ret_val);
			break;
		
		case ET_MESSAGE_GET_N_PROFILES:
			tm_printf("esp32 asks: how many profiles? answer: %d\n", global_cxt.n_profiles);
			response = create_te_msg(TE_MESSAGE_N_PROFILES, "s", global_cxt.n_profiles);
			break;
		
		case ET_MESSAGE_GET_N_TRANSFORMERS:
			tm_printf("esp32 asks: how many transformers in profile %d? answer: %d\n", arg16_1, cxt_get_n_profile_transformers(&global_cxt, arg16_1));
			response = create_te_msg(TE_MESSAGE_N_TRANSFORMERS, "ss", arg16_1,
									 cxt_get_n_profile_transformers(&global_cxt, arg16_1));
			break;
		
		case ET_MESSAGE_GET_TRANSFORMER_ID:
			tm_printf("esp32 asks: what is the id of the transformer in position %d in profile %d? answer: %d\n", arg16_2, arg16_1, cxt_get_tid_by_pos(&global_cxt, arg16_1, arg16_2));
			response = create_te_msg(TE_MESSAGE_TRANSFORMER_TYPE, "sss", arg16_1, arg16_2,
									 cxt_get_tid_by_pos(&global_cxt, arg16_1, arg16_2));
			break;
		
		case ET_MESSAGE_GET_TRANSFORMER_TYPE:
			tm_printf("esp32 asks: what is the type of transformer %d.%d? answer: %d\n", arg16_1, arg16_2, cxt_get_transformer_type(&global_cxt, arg16_1, arg16_2));
			response = create_te_msg(TE_MESSAGE_TRANSFORMER_TYPE, "sss", arg16_1, arg16_2,
									 cxt_get_transformer_type(&global_cxt, arg16_1, arg16_2));
			break;
		
		case ET_MESSAGE_GET_N_PARAMETERS:
			tm_printf("esp32 asks: what is the n_parameters of transformer %d.%d? answer: %d\n", arg16_1, arg16_2, cxt_get_n_transformer_params(&global_cxt, arg16_1, arg16_2));
			response = create_te_msg(TE_MESSAGE_N_PARAMETERS, "sss", arg16_1, arg16_2,
									 cxt_get_n_transformer_params(&global_cxt, arg16_1, arg16_2));
			break;
		
		case ET_MESSAGE_GET_PARAM_VALUE:
			tm_printf("Request for value of parameter %d.%d.%d...\n", arg16_1, arg16_2, arg16_3);
			
			param = cxt_get_parameter_by_id(&global_cxt, arg16_1, arg16_2, arg16_3);
			
			if (param)
			{
				tm_printf("Request valid. Parameter ptr: 0x%08x, value %f\n", param, param->value);
				response = create_te_msg(TE_MESSAGE_PARAM_VALUE, "sss", arg16_1, arg16_2, arg16_3);
				memcpy(&response.data[6], &param->value, sizeof(float));
			}
			else
			{
				tm_printf("Requested parameter doesn't exist !\n");
				response.type = TE_MESSAGE_BAD_REQUEST;
			}
			break;
		
		case ET_MESSAGE_SET_PARAM_VALUE:
			memcpy(&value_f, &msg.data[6], sizeof(float));
			
			tm_printf("Request to set parameter %d.%d.%d to value %f\n", arg16_1, arg16_2, arg16_3, value_f);
			
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
		
		case ET_MESSAGE_GET_N_OPTIONS:
			tm_printf("esp32 asks: what is the n_options of transformer %d.%d? answer: %d\n", arg16_1, arg16_2, cxt_get_n_transformer_options(&global_cxt, arg16_1, arg16_2));
			response = create_te_msg(TE_MESSAGE_N_OPTIONS, "sss", arg16_1, arg16_2,
									 cxt_get_n_transformer_options(&global_cxt, arg16_1, arg16_2));
			break;
		
		case ET_MESSAGE_GET_OPTION_VALUE:
			tm_printf("Request for value of option %d.%d.%d...\n", arg16_1, arg16_2, arg16_3);
			
			option = cxt_get_option_by_id(&global_cxt, arg16_1, arg16_2, arg16_3);
			
			if (option)
			{
				tm_printf("Request valid. Parameter ptr: 0x%08x, value %d\n", option, option->value);
				response = create_te_msg(TE_MESSAGE_OPTION_VALUE, "sss", arg16_1, arg16_2, arg16_3);
				memcpy(&response.data[6], &option->value, sizeof(uint16_t));
			}
			else
			{
				tm_printf("Requested option doesn't exist !\n");
				response.type = TE_MESSAGE_BAD_REQUEST;
			}
			break;
		
		case ET_MESSAGE_SET_OPTION_VALUE:
			memcpy(&value_i, &msg.data[6], sizeof(uint16_t));
			
			tm_printf("Request to set option %d.%d.%d to value %d\n", arg16_1, arg16_2, arg16_3, value_i);
			option = cxt_get_option_by_id(&global_cxt, arg16_1, arg16_2, arg16_3);
			
			if (option)
			{
				tm_printf("The option exists; with address %p, and current value %d\n", option, option->value);
				update_option(option, value_i);
				tm_printf("It has been updated to value %d.\n", option->new_value);
				response = create_te_msg(TE_MESSAGE_OPTION_VALUE, "ssss", arg16_1, arg16_2, arg16_3, option->new_value);
			}
			else
			{
				tm_printf("But no such option exists!\n");
				response = create_te_msg_nodata(TE_MESSAGE_BAD_REQUEST);
			}
			break;
		
		case ET_MESSAGE_SWITCH_PROFILE:
			tm_printf("Profile switch requested; to profile %d\n", arg16_1);
			if (arg16_1 < global_cxt.n_profiles)
			{
				ret_val = cxt_switch_to_profile(&global_cxt, arg16_1);
				
				if (ret_val != NO_ERROR)
					response = create_te_msg_error(ret_val);
				else
					response = create_te_msg(TE_MESSAGE_SWITCHING_PROFILE, "s", arg16_1);
				
				tm_printf("Request valid; swwitching. Error code: %d\n", ret_val);
			}
			else
			{
				tm_printf("No such profile exists!\n");
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
				
				for (int i = 0; i < ET_MESSAGE_MAX_LEN; i++)
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
		
		case ET_MESSAGE_INVALID:
			response.type = TE_MESSAGE_BAD_TRANSFER;
			break;
	}
	
	response_ready = 1;
}

void i2c_recieve_isr(int n)
{
	printf("i2c_recieve_isr\n");
	tm_AudioNoInterrupts();
	
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
				#ifndef TM_SIMULATED
				Wire.read();
				#else
				
				#endif
				if (i < ET_MESSAGE_MAX_LEN)
					recieve_buffer[i] = 0;
			}
		}
		else
		{
			#ifndef TM_SIMULATED
			for (i = 0; i < n; i++)
				recieve_buffer[i] = Wire.read();
			#else
			for (i = 0; i < n; i++)
				recieve_buffer[i] = simulated_i2c_send_buffer[i];
			#endif
		
			while (i < ET_MESSAGE_MAX_LEN)
				recieve_buffer[i++] = 0xFF;
		}
	}
	
	//for (int i = 0; i < n; i++)
	//	tm_printf("%d%s", recieve_buffer[i], (i < n - 1) ? ", " : "\n");
	
	tm_AudioInterrupts();
}

void i2c_request_isr()
{
	tm_AudioNoInterrupts();
	tm_printf("i2c request isr\n");
	
	if (response_ready)
	{
		uint8_t send_buffer[TE_MESSAGE_MAX_LEN + 1];
		
		encode_te_msg(send_buffer, response);
		
		#ifndef TM_SIMULATED
		Wire.write(send_buffer, TE_MESSAGE_MAX_LEN);
		#else
		teensy_i2c_response = response;
		#endif
		
		tm_printf("Responding with message of type %s\n", te_msg_code_to_string(response.type));
		//tm_printf("Sent response:\n\t");
		//for (int i = 0; i < TE_MESSAGE_MAX_LEN; i++)
		//	tm_printf("0x%02x%s", send_buffer[i], (i == TE_MESSAGE_MAX_LEN - 1) ? "\n" : " ");
	}
	else
	{
		tm_printf("not ready !!\n");
		#ifndef TM_SIMULATED
		Wire.write(wait_message, TE_MESSAGE_MAX_LEN);
		#else
		teensy_i2c_response.type = TE_MESSAGE_WAIT;
		#endif
	}
	tm_AudioInterrupts();
}

int init_esp32_link()
{
	#ifndef TM_SIMULATED
	Wire.begin(TEENSY_I2C_SLAVE_ADDR);
	Wire.onReceive(i2c_recieve_isr);
	Wire.onRequest(i2c_request_isr);
	#else
	
	#endif
	
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

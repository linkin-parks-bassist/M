#include "em.h"

static const char *TAG = "TeensyComms";

#define SEND_BUFFER_LENGTH 16

QueueHandle_t et_msg_queue;

void teensy_comms_task(void *param);

#ifdef PING_TEENSY
int teensy_online = 0;
#else
int teensy_online = 1;
#endif

int queue_msg_to_teensy(et_msg msg)
{
	printf("Queueing message of type %d\n", msg.type);
	
	if (xQueueSend(et_msg_queue, (void*)&msg, (TickType_t)10) != pdPASS)
	{
		printf("Queueing failed!\n");
		return ERR_QUEUE_SEND_FAILED;
	}
	
	printf("Success.\n");
	return NO_ERROR;
}

int init_teensy_msg_queue()
{
	et_msg_queue = xQueueCreate(16, sizeof(et_msg));
	if (et_msg_queue == NULL)
		ESP_LOGE("queue", "Failed to create et_msg queue");
	
	return ERR_ALLOC_FAIL;
}

int begin_teensy_comms()
{
	xTaskCreatePinnedToCore(
		teensy_comms_task,	 		// Task function
		"Teens Comms Task",			// Name (for debugging)
		4096,			  			// Stack size (words, not bytes) — tune as needed
		NULL,			  			// Task parameters
		8,				 			// Priority — >3 if real-time, <=3 if best-effort
		NULL,			   			// Task handle (optional)
		1
	);
	
	return NO_ERROR;
}

static int send_msg_to_teensy(et_msg msg)
{
	uint8_t buf[ET_MESSAGE_MAX_LEN + 1];
	int len = encode_et_msg(buf, msg);
	
	if (len == 0)
		return ERR_ET_MSG_INVALID;
	
	ESP_LOGI(TAG, "Sending type %d message to Teensy...\n", msg.type);
	int ret_val = i2c_transmit(TEENSY_ADDR, buf, len);
	
	return ret_val;
}

void handle_teensy_response(et_msg msg, te_msg response)
{
	uint16_t arg16_1, arg16_2, arg16_3, arg16_4;
	uint16_t sarg16_1, sarg16_2, sarg16_3, sarg16_4;
	
	memcpy(&arg16_1, &response.data[0], sizeof(uint16_t));
	memcpy(&arg16_2, &response.data[1], sizeof(uint16_t));
	memcpy(&arg16_3, &response.data[2], sizeof(uint16_t));
	memcpy(&arg16_4, &response.data[3], sizeof(uint16_t));
	
	memcpy(&sarg16_1, &msg.data[0], sizeof(uint16_t));
	memcpy(&sarg16_2, &msg.data[1], sizeof(uint16_t));
	memcpy(&sarg16_3, &msg.data[2], sizeof(uint16_t));
	memcpy(&sarg16_4, &msg.data[3], sizeof(uint16_t));
	
	teensy_parameter *param;
	teensy_transformer *trans;
	
	
	et_msg follow_up;
	follow_up.type = ET_MESSAGE_NO_MESSAGE;
	//ESP_LOGI(TAG, "Recieved response of type %d", msg.type, response.type);
	
	if (msg.callback)
	{
		msg.callback(msg, response);
	}
	switch (response.type)
	{	
		case TE_MESSAGE_NO_MESSAGE:
			ESP_LOGW(TAG, "No response recieved from Teensy");
			break;
		
		case TE_MESSAGE_HI:
			teensy_online = 1;
			printf("Teensy reports status flags %d = 0b", (int)arg16_1);
			
			for (int i = 0; i < 16; i++)
			{
				printf("%d", (int)((arg16_1 >> (15 - i)) & 1));
			}
			
			printf("\n");
			break;
		
		case TE_MESSAGE_OK:
			teensy_online = 1;
			break;
		
		case TE_MESSAGE_ERROR:
			
			break;
		
		case TE_MESSAGE_PROFILE_ID:
			
			break;

		case TE_MESSAGE_PARAMETER_ID:
			
			break;

		case TE_MESSAGE_N_PROFILES:
			teensy_context_set_n_profiles(&global_cxt.teensy, arg16_1);
			break;
		
		case TE_MESSAGE_N_TRANSFORMERS:
			if (arg16_1 < global_cxt.teensy.n_profiles)
			{
				teensy_pipeline_set_n_transformers(&global_cxt.teensy.profiles[arg16_1].pipeline, arg16_2);
			}
			else
			{
				ESP_LOGE(TAG, "Something has gone terribly wrong\n");
			}
			break;
		
		case TE_MESSAGE_TRANSFORMER_ID:
			global_cxt.teensy.profiles[arg16_1].pipeline.transformers[arg16_2].transformer_id = arg16_3;
			
			break;
		
		case TE_MESSAGE_TRANSFORMER_TYPE:
			trans = cxt_get_transformer_by_id(&global_cxt.teensy, arg16_1, arg16_2);
			
			if (trans)
				trans->type = arg16_3;
			break;
		
		case TE_MESSAGE_N_PARAMETERS:
			trans = cxt_get_transformer_by_id(&global_cxt.teensy, arg16_1, arg16_2);
			
			if (trans)
				teensy_transformer_set_n_parameters(trans, arg16_3);
			break;
		
		case TE_MESSAGE_PARAM_TYPE:
			param = cxt_get_parameter_by_id(&global_cxt.teensy, arg16_1, arg16_2, arg16_3);
			trans = cxt_get_transformer_by_id(&global_cxt.teensy, arg16_1, arg16_2);
			
			if (param)
			{
				memcpy(&param->type, &response.data[6], sizeof(m_param_type));
			}
			break;
		
		case TE_MESSAGE_PARAM_VALUE:
			param = cxt_get_parameter_by_id(&global_cxt.teensy, arg16_1, arg16_2, arg16_3);
			if (param)
			{
				memcpy(&param->type, &response.data[6], sizeof(m_param_value));
			}
			break;
		
		case TE_MESSAGE_PARAM_NAME:
			teensy_transformer *trans = cxt_get_transformer_by_id(&global_cxt.teensy, arg16_1, arg16_2);
			param = cxt_get_parameter_by_id(&global_cxt.teensy, arg16_1, arg16_2, arg16_3);
			
			if (param)
			{
				if (param->name)
					free(param->name);
				
				param->name = strndup((char*)&response.data[6], TE_MESSAGE_MAX_LEN - 7);
			}
			else
			{
				ESP_LOGE(TAG, "Something has gone terribly wrong\n");
			}
			break;
		
		case TE_MESSAGE_PARAM_NAME_LONG:
			
			break;
		
		
		default:
		case TE_MESSAGE_INVALID:
			//ESP_LOGW(TAG, "Invalid response from Teensy");
			break;
	}
	
	if (follow_up.type != ET_MESSAGE_NO_MESSAGE)
	{
		//printf("Queueing follow-up !\n");
		queue_msg_to_teensy(follow_up);
	}
}

void teensy_comms_task(void *param)
{
	int ret_val;
	int response_recieved;
	
	et_msg msg;
	te_msg response;
	
	TickType_t last_hi   = xTaskGetTickCount();
	TickType_t last_wake = xTaskGetTickCount();
	
	esp_err_t err;
	
	uint8_t response_bytes[TE_MESSAGE_MAX_LEN];

	while (true)
	{
		TickType_t now = xTaskGetTickCount();
		#ifdef PING_TEENSY
		if ((now - last_hi) >= pdMS_TO_TICKS(teensy_online ? ET_PING_INTERVAL_MS_ONLINE : ET_PING_INTERVAL_MS_OFFLINE))
		{
			msg.type = ET_MESSAGE_HI;

			ret_val = send_msg_to_teensy(msg);
			
			if (ret_val == NO_ERROR)
			{
				do 
				{
					vTaskDelay(pdMS_TO_TICKS(1));
					ret_val = i2c_recieve(TEENSY_ADDR, response_bytes, TE_MESSAGE_MAX_LEN);
					
					if (ret_val != NO_ERROR)
						break;
					
					response_recieved = (response_bytes[0] != TE_MESSAGE_WAIT);
					
					#ifdef PRINT_HI_RESPONSE_BYTES
					printf("Response bytes:\n\t");
					for (int i = 0; i < TE_MESSAGE_MAX_LEN; i++)
						printf("0x%02x%s", response_bytes[i], (i == TE_MESSAGE_MAX_LEN - 1) ? "\n" : " ");
					#endif
				} while (!response_recieved);
				
				response = decode_te_msg(response_bytes);
				handle_teensy_response(msg, response);
			}
			else
			{
				teensy_online = 0;
			}

			last_hi = now;
		}
		#endif
		
		while (teensy_online && xQueueReceive(et_msg_queue, &msg, 0) == pdTRUE)
		{
			ret_val = send_msg_to_teensy(msg);
			
			if (ret_val != NO_ERROR)
				break;
			
			do 
			{
				vTaskDelay(pdMS_TO_TICKS(1));
				ret_val = i2c_recieve(TEENSY_ADDR, response_bytes, TE_MESSAGE_MAX_LEN);
				
				if (ret_val != NO_ERROR)
					break;
				
				response_recieved = (response_bytes[0] != TE_MESSAGE_WAIT);
				
				#ifdef PRINT_RESPONSE_BYTES
				printf("Response bytes:\n\t");
				for (int i = 0; i < TE_MESSAGE_MAX_LEN; i++)
					printf("0x%02x%s", response_bytes[i], (i == TE_MESSAGE_MAX_LEN - 1) ? "\n" : " ");
				
				if (!response_recieved)
					printf("Teensy asks for patience...\n");
				#endif
			} while (!response_recieved);
			
			response = decode_te_msg(response_bytes);
			handle_teensy_response(msg, response);
		}

		vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(3));
	}


	vTaskDelete(NULL);
}

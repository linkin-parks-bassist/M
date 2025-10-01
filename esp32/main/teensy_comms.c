#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "i2c.h"
#include "teensy_comms.h"
#include "m_error_codes.h"
#include "lvgl.h"
#include "lvgl_port.h"
#include "parameter_widget.h"
#include "m_status.h"

#include "shared_context.h"
#include "esp32_context.h"

static const char *TAG = "TeensyComms";

#define SEND_BUFFER_LENGTH 16

QueueHandle_t et_msg_queue;

void teensy_comms_task(void *param);

int teensy_online = 0;

int init_teensy_comms()
{
	et_msg_queue = xQueueCreate(16, sizeof(et_msg));
	if (et_msg_queue == NULL)
	{
		ESP_LOGE("queue", "Failed to create et_msg queue");
	}

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
	
	if (msg.type != ET_MESSAGE_HI)
		ESP_LOGI(TAG, "Sending type %d message to Teensy...\n", msg.type);
	int ret_val = i2c_transmit(TEENSY_ADDR, buf, len);
	
	return ret_val;
}

typedef enum
{
	IDLE,
	SYNCING
} comms_fsm_state_t;

comms_fsm_state_t comms_fsm_state = IDLE;

void handle_teensy_response(et_msg msg, te_msg response)
{
	uint16_t arg16_1, arg16_2, arg16_3, arg16_4;
	
	memcpy(&arg16_1, &response.data[0], sizeof(uint16_t));
	memcpy(&arg16_2, &response.data[1], sizeof(uint16_t));
	memcpy(&arg16_3, &response.data[2], sizeof(uint16_t));
	memcpy(&arg16_4, &response.data[3], sizeof(uint16_t));
	
	et_msg follow_up;
	follow_up.type = ET_MESSAGE_NO_MESSAGE;
	ESP_LOGI(TAG, "Sent message of type %d, recieved response of type %d", msg.type, response.type);
	switch (response.type)
	{	
		case TE_MESSAGE_NO_MESSAGE:
			ESP_LOGW(TAG, "No response recieved from Teensy");
			
			if (msg.type == ET_MESSAGE_HI)
				teensy_online = 0;
			break;
		
		case TE_MESSAGE_HI:
			teensy_online = 1;
			printf("Teensy reports status flags %d = 0b", (int)arg16_1);
			
			for (int i = 0; i < 16; i++)
			{
				printf("%d", (int)((arg16_1 >> (15 - i)) & 1));
			}
			
			printf("\n");
			
			if (arg16_1 & M_STATUS_FRESH_BOOT)
			{
				ESP_LOGW(TAG, "esp32 and teensy may be out of sync !");
				
				follow_up = create_et_msg_no_data(ET_MESSAGE_SYNC);
				comms_fsm_state = SYNCING;
			}
			break;
		
		case TE_MESSAGE_OK:
			teensy_online = 1;
			break;
		
		case TE_MESSAGE_ERROR:
			memcpy(&arg16_1, response.data, sizeof(uint16_t));
			switch (arg16_1)
			{
				case NO_ERROR:
					break;
				
				default:
					ESP_LOGE(TAG, "Teensy reports error code %d in response to message of type %d\n", arg16_1, msg.type);
					break;
			}
			break;
		
		case TE_MESSAGE_PARAM_VALUE:
			if (msg.type == ET_MESSAGE_GET_PARAM_VALUE)
			{
				if (msg.extra)
				{
					((parameter_widget*)msg.extra)->val = *((m_param_value*)response.data);
					if (((parameter_widget*)msg.extra)->obj)
					{
						while (!lvgl_port_lock(-1));
						lv_event_send(((parameter_widget*)msg.extra)->obj, LV_EVENT_REFRESH, NULL);
						lvgl_port_unlock();
					}
					else
					{
						ESP_LOGW(TAG, "No parameter widget lv_obj associated with parameter value request");
					}
				}
				else
				{
					ESP_LOGE(TAG, "No parameter widget associated with parameter value request");
				}
			}
			else
			{
				ESP_LOGW(TAG, "Teensy responded to message of type %d with parameter value", msg.type);
			}
			break;
		
		case TE_MESSAGE_PROFILE_ID:
			switch (msg.type)
			{
			}
			break;
		
		case TE_MESSAGE_TRANSFORMER_ID:
			break;

		case TE_MESSAGE_PARAMETER_ID:
			break;

		case TE_MESSAGE_N_PROFILES:
			if (arg16_1 != global_cxt.teensy.n_profiles)
			{
				follow_up = create_et_msg_no_data(ET_MESSAGE_RESET);
			}
			break;

		
		default:
		case TE_MESSAGE_INVALID:
			ESP_LOGW(TAG, "Invalid response from Teensy");
			break;
	}
	
	if (follow_up.type != ET_MESSAGE_NO_MESSAGE)
		xQueueSend(et_msg_queue, &follow_up, 10);
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
					
					printf("Response bytes:\n\t");
					for (int i = 0; i < TE_MESSAGE_MAX_LEN; i++)
						printf("0x%02x%s", response_bytes[i], (i == TE_MESSAGE_MAX_LEN - 1) ? "\n" : " ");
					
					if (!response_recieved)
						printf("Teensy asks for patience...\n");
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
		
		while (teensy_online && xQueueReceive(et_msg_queue, &msg, 0) == pdTRUE)
		{
			if (msg.type == ET_MESSAGE_GET_PARAM_VALUE)
				printf("Requesting parameter\n");
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
				
				/*printf("Response bytes:\n\t");
				for (int i = 0; i < TE_MESSAGE_MAX_LEN; i++)
					printf("0x%02x%s", response_bytes[i], (i == TE_MESSAGE_MAX_LEN - 1) ? "\n" : " ");
				
				if (!response_recieved)
					printf("Teensy asks for patience...\n");*/
			} while (!response_recieved);
			
			response = decode_te_msg(response_bytes);
			handle_teensy_response(msg, response);
		}

		vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(1));
	}


	vTaskDelete(NULL);
}

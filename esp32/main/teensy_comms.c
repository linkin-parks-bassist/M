#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "i2c.h"
#include "teensy_comms.h"
#include "m_error_codes.h"

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

	xTaskCreate(
		teensy_comms_task,	 		// Task function
		"Teens Comms Task",			// Name (for debugging)
		4096,			  			// Stack size (words, not bytes) — tune as needed
		NULL,			  			// Task parameters
		5,				 			// Priority — >3 if real-time, <=3 if best-effort
		NULL			   			// Task handle (optional)
	);
	
	return NO_ERROR;
}

static int send_msg_to_teensy(et_msg msg)
{
	uint8_t buf[ET_MESSAGE_MAX_DATA_LEN + 1];
	int len = encode_et_msg(buf, msg);
	
	int ret_val = i2c_transmit(TEENSY_ADDR, buf, len);
	
	return ret_val;
}

static te_msg get_teensy_response(et_msg msg)
{
	int ret_val;
	
	// Get the expected reponse length from Teensy
	uint8_t expected_length;
	ret_val = i2c_recieve(TEENSY_ADDR, &expected_length, 1);
	
	printf("Teensy response: length %d\n", expected_length);
	
	if (ret_val == NO_ERROR)
	{
		// Get the actual message
		uint8_t response_bytes[expected_length];
		ret_val = i2c_recieve(TEENSY_ADDR, response_bytes, expected_length);
		
		printf("Response bytes:\n\t");
		for (int i = 0; i < expected_length; i++)
			printf("0x%02x%s", response_bytes[i], (i == expected_length - 1) ? "\n" : " ");
		return decode_te_msg(response_bytes, expected_length);
	}
	else
	{
		te_msg msg;
		msg.type = TE_MESSAGE_NO_MESSAGE;
		return msg;
	}
}

void handle_teensy_response(et_msg msg, te_msg response)
{
	switch (response.type)
	{	
		case TE_MESSAGE_NO_MESSAGE:
			ESP_LOGW(TAG, "No response recieved from Teensy");
			
			if (msg.type == ET_MESSAGE_HI)
				teensy_online = 0;
			break;
		
		case TE_MESSAGE_HI:
			teensy_online = 1;
			break;
		
		default:
		case TE_MESSAGE_INVALID:
			ESP_LOGW(TAG, "Invalid response from Teensy:");
			break;
	}
}

void teensy_comms_task(void *param)
{
	int ret_val;
	
	et_msg msg;
	te_msg response;
	
	TickType_t last_hi   = xTaskGetTickCount();
	TickType_t last_wake = xTaskGetTickCount();
	
	esp_err_t err;

	while (true)
	{
		TickType_t now = xTaskGetTickCount();
		if ((now - last_hi) >= pdMS_TO_TICKS(teensy_online ? ET_PING_INTERVAL_MS_ONLINE : ET_PING_INTERVAL_MS_OFFLINE))
		{
			msg.type = ET_MESSAGE_HI;

			ret_val = send_msg_to_teensy(msg);

			if (ret_val == NO_ERROR)
			{
				response = get_teensy_response(msg);
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
			printf("Sending message of type %d\n", msg.type);
			ret_val = send_msg_to_teensy(msg);
			
			if (ret_val != NO_ERROR)
			{
				teensy_online = 0;
				break;
			}
			
			if (ET_MSG_RESPONSE_REQUIRED(msg.type))
			{
				response = get_teensy_response(msg);
				handle_teensy_response(msg, response);
			}
		}

		vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(5));
	}


	vTaskDelete(NULL);
}

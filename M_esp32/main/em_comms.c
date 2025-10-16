#include "em.h"

static const char *TAG = "TeensyComms";

#define SEND_BUFFER_LENGTH 16

QueueHandle_t et_msg_queue;

void em_comms_task(void *param);

#ifdef PING_TEENSY
int teensy_online = 0;
#else
int teensy_online = 1;
#endif

int queue_msg_to_teensy(et_msg msg)
{
	//printf("Queueing message of type %d\n", msg.type);
	
	if (xQueueSend(et_msg_queue, (void*)&msg, (TickType_t)10) != pdPASS)
	{
		printf("Queueing failed!\n");
		return ERR_QUEUE_SEND_FAILED;
	}
	
	printf("Success.\n");
	return NO_ERROR;
}

int init_em_msg_queue()
{
	et_msg_queue = xQueueCreate(16, sizeof(et_msg));
	if (et_msg_queue == NULL)
		ESP_LOGE("queue", "Failed to create et_msg queue");
	
	return ERR_ALLOC_FAIL;
}

int begin_em_comms()
{
	xTaskCreatePinnedToCore(
		em_comms_task,
		"Teens Comms Task",
		4096,
		NULL,
		8,
		NULL,
		1
	);
	
	return NO_ERROR;
}

static int send_msg_to_teensy(et_msg msg)
{
	uint8_t buf[ET_MESSAGE_MAX_LEN + 1];
	int len = encode_et_msg(buf, msg);
	
	if (len == 0)
	{
		printf("encode_et_msg returned length 0!!\n");
		return ERR_ET_MSG_INVALID;
	}
	
	//ESP_LOGI(TAG, "Sending type %d message to Teensy...\n", msg.type);
	int ret_val = i2c_transmit(TEENSY_ADDR, buf, len);
	
	return ret_val;
}

void handle_em_response(et_msg msg, te_msg response)
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
	
	em_parameter *param;
	em_transformer *trans;
	
	
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

void em_comms_task(void *param)
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
				handle_em_response(msg, response);
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
			handle_em_response(msg, response);
		}

		vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(3));
	}


	vTaskDelete(NULL);
}

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

#define ET_MESSAGE_MAX_RETRIES 5

IMPLEMENT_LINKED_PTR_LIST(et_msg);

static et_msg_ptr_linked_list *retry_queue = NULL;

int queue_message_retry(et_msg *msg)
{
	if (!msg)
		return ERR_NULL_PTR;
	
	if (msg->retries > ET_MESSAGE_MAX_RETRIES)
		msg->retries = ET_MESSAGE_MAX_RETRIES;
	
	et_msg_ptr_linked_list *nl = et_msg_ptr_linked_list_append(retry_queue, msg);
	
	if (!nl)
		return ERR_ALLOC_FAIL;
	
	retry_queue = nl;
	
	msg->retries--;
	
	return NO_ERROR;
}

int queue_msg_to_teensy(et_msg msg)
{
	printf("Queueing message of type %s\n", et_msg_code_to_string(msg.type));
	
	et_msg *msg_copy = malloc(sizeof(et_msg));
	
	if (!msg_copy)
		return ERR_ALLOC_FAIL;
	
	memcpy(msg_copy, &msg, sizeof(et_msg));
	
	if (xQueueSend(et_msg_queue, (void*)&msg_copy, (TickType_t)10) != pdPASS)
	{
		printf("Queueing failed!\n");
		return ERR_QUEUE_SEND_FAILED;
	}
	
	printf("Success.\n");
	return NO_ERROR;
}

int init_em_msg_queue()
{
	et_msg_queue = xQueueCreate(16, sizeof(et_msg*));
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

#define ET_MESSAGE_SEND_TRIES 		3
#define ET_MESSAGE_RESPONSE_TRIES 	5
#define ET_MESSAGE_I2C_SEND_TRIES 	5

static int send_msg_to_teensy(et_msg *msg, te_msg *response_ptr)
{
	if (!msg || !response_ptr)
		return ERR_NULL_PTR;
	
	printf("Sending message %s to Teensy\n", et_msg_code_to_string(msg->type));
	
	uint8_t buf[ET_MESSAGE_MAX_TRANSFER_LEN];
	uint8_t response_buf[TE_MESSAGE_MAX_TRANSFER_LEN];
	te_msg response;
	
	int len = encode_et_msg(buf, *msg);
	if (len < 2)
		return ERR_ET_MSG_INVALID;
	
	int succeeded = 0;
	int response_obtained;
	int ret_val;
	
	for (int send_tries = 0; send_tries < ET_MESSAGE_SEND_TRIES && !succeeded; send_tries++)
	{
		printf("Send try %d\n", send_tries);
		
		ret_val = i2c_transmit_persistent(TEENSY_ADDR, buf, len, ET_MESSAGE_I2C_SEND_TRIES);
		
		if (ret_val != NO_ERROR)
		{
			printf("i2c_transmit_persistent reports failure. retrying... %d tries left\n", ET_MESSAGE_SEND_TRIES - send_tries);
			continue;
		}
		
		printf("Sucessfully sent\n");
		
		response_obtained = 0;
		for (int response_tries = 0; response_tries < ET_MESSAGE_RESPONSE_TRIES && !response_obtained; response_tries++)
		{
			printf("Receive try %d\n", response_tries);
			// Give the Teensy a moment
			vTaskDelay(pdMS_TO_TICKS(1));
			
			// Ask for response
			ret_val = i2c_receive(TEENSY_ADDR, response_buf, TE_MESSAGE_MAX_TRANSFER_LEN);
			
			if (ret_val == NO_ERROR && response_buf[0] != TE_MESSAGE_WAIT)
				response_obtained = 1;
		}
		
		if (!response_obtained)
		{
			printf("Failed to obtain a response!\n");
			return ERR_NO_RESPONSE;
		}
		
		response = decode_te_msg(response_buf, TE_MESSAGE_MAX_TRANSFER_LEN);
		
		printf("Obtained teensy response.  Type = %s, data = ", te_msg_code_to_string(response.type));
	
		for (int i = 0; i < TE_MESSAGE_MAX_DATA_LEN; i++)
			printf("0x%02x ", response.data[i]);
		
		printf("\n");
		
		if (response.type != TE_MESSAGE_REPEAT_MESSAGE)
		{
			succeeded = 1;
		}
		else
		{
			printf("Teensy wants to hear that again... send!\n");
		}
	}
	
	if (succeeded)
	{
		memcpy(response_ptr, &response, sizeof(te_msg));
		return NO_ERROR;
	}
	
	return ERR_COMMS_FAIL;
}

void handle_teensy_response(et_msg msg, te_msg response)
{
	printf("Handling teensy response. Type = %s, data = ", te_msg_code_to_string(response.type));
	
	for (int i = 0; i < TE_MESSAGE_MAX_DATA_LEN; i++)
		printf("0x%02x ", response.data[i]);
	
	printf("\n");
	
	switch (response.type)
	{	
		case TE_MESSAGE_NO_MESSAGE:
			ESP_LOGW(TAG, "No response received from Teensy");
			break;
		
		case TE_MESSAGE_HI:
			teensy_online = 1;
			break;
		
		case TE_MESSAGE_INVALID:
			break;
			
		default:
			if (msg.callback)
				msg.callback(msg, response);
	}
}

static int handle_msg(et_msg *msg)
{
	if (!msg)
		return ERR_NULL_PTR;
	
	te_msg response;
	
	int ret_val = send_msg_to_teensy(msg, &response);
			
	switch (ret_val)
	{
		case NO_ERROR:
			handle_teensy_response(*msg, response);
			return NO_ERROR;
			break;
			
		case ERR_COMMS_FAIL:
			if (msg->retries > ET_MESSAGE_MAX_RETRIES)
				msg->retries = ET_MESSAGE_MAX_RETRIES;
			
			if (msg->retries > 0)
			{
				queue_message_retry(msg);
				return NO_ERROR;
			}
			else
			{
				free(msg);
				return ERR_COMMS_FAIL;
			}
			break;
			
		default:
			break;
	}
	
	return NO_ERROR;
}

void em_comms_task(void *param)
{
	int ret_val;
	int response_received;
	
	et_msg *msg;
	
	TickType_t last_hi   = xTaskGetTickCount();
	TickType_t last_wake = xTaskGetTickCount();
	
	esp_err_t err;
	
	et_msg_ptr_linked_list *retry_next;

	while (true)
	{
		TickType_t now = xTaskGetTickCount();
		#ifdef PING_TEENSY
		if ((now - last_hi) >= pdMS_TO_TICKS(teensy_online ? ET_PING_INTERVAL_MS_ONLINE : ET_PING_INTERVAL_MS_OFFLINE))
		{
			msg.type = ET_MESSAGE_HI;

			ret_val = send_msg_to_teensy(msg, &response);
			
			if (ret_val == NO_ERROR)
			{
				do 
				{
					vTaskDelay(pdMS_TO_TICKS(1));
					ret_val = i2c_receive(TEENSY_ADDR, response_bytes, TE_MESSAGE_MAX_TRANSFER_LEN);
					
					if (ret_val != NO_ERROR)
						break;
					
					response_received = (response_bytes[0] != TE_MESSAGE_WAIT);
					
					#ifdef PRINT_HI_RESPONSE_BYTES
					printf("Response bytes:\n\t");
					for (int i = 0; i < TE_MESSAGE_MAX_TRANSFER_LEN; i++)
						printf("0x%02x%s", response_bytes[i], (i == TE_MESSAGE_MAX_TRANSFER_LEN - 1) ? "\n" : " ");
					#endif
				} while (!response_received);
				
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
		
		while (teensy_online && retry_queue)
		{
			retry_next = retry_queue->next;
			
			if (retry_queue->data)
				handle_msg(retry_queue->data);
			
			free(retry_queue);
			retry_queue = retry_next;
		}
		
		if (teensy_online && xQueueReceive(et_msg_queue, &msg, 0) == pdTRUE)
			handle_msg(msg);

		vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(1));
	}


	vTaskDelete(NULL);
}

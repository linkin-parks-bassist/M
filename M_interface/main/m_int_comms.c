#include "m_int.h"

static const char *TAG = "TeensyComms";

#define SEND_BUFFER_LENGTH 16

QueueHandle_t m_message_queue;

void m_int_comms_task(void *param);

#ifdef PING_TEENSY
int teensy_online = 0;
#else
int teensy_online = 1;
#endif

#define M_MESSAGE_MAX_RETRIES 5

IMPLEMENT_LINKED_PTR_LIST(m_message);

static m_message_pll *retry_queue = NULL;

static m_message hi_msg;

int queue_message_retry(m_message *msg)
{
	if (!msg)
		return ERR_NULL_PTR;
	
	if (msg->retries > M_MESSAGE_MAX_RETRIES)
		msg->retries = M_MESSAGE_MAX_RETRIES;
	
	m_message_pll *nl = m_message_pll_append(retry_queue, msg);
	
	if (!nl)
		return ERR_ALLOC_FAIL;
	
	retry_queue = nl;
	
	msg->retries--;
	
	return NO_ERROR;
}

int queue_msg_to_teensy(m_message msg)
{
	printf("Queueing message of type %s\n", m_message_code_to_string(msg.type));
	
	m_message *msg_copy = m_alloc(sizeof(m_message));
	
	if (!msg_copy)
		return ERR_ALLOC_FAIL;
	
	memcpy(msg_copy, &msg, sizeof(m_message));
	
	if (xQueueSend(m_message_queue, (void*)&msg_copy, (TickType_t)10) != pdPASS)
	{
		printf("Queueing failed!\n");
		return ERR_QUEUE_SEND_FAILED;
	}
	
	return NO_ERROR;
}

int init_m_int_msg_queue()
{
	m_message_queue = xQueueCreate(16, sizeof(m_message*));
	if (m_message_queue == NULL)
		ESP_LOGE("queue", "Failed to create m_message queue");
	
	return ERR_ALLOC_FAIL;
}

int begin_m_int_comms()
{
	xTaskCreatePinnedToCore(
		m_int_comms_task,
		"Teens Comms Task",
		4096,
		NULL,
		8,
		NULL,
		1
	);
	
	return NO_ERROR;
}

#define M_MESSAGE_SEND_TRIES 		3
#define M_MESSAGE_RESPONSE_TRIES 	5
#define M_MESSAGE_I2C_SEND_TRIES 	5
//#define REPORT_I2C
//#define PRINT_RESPONSE_BYTES

static int send_msg_to_teensy(m_message *msg, m_response *response_ptr)
{
	if (!msg || !response_ptr)
		return ERR_NULL_PTR;
	
	#ifdef REPORT_I2C
	printf("Sending message %s to Teensy\n", m_message_code_to_string(msg->type));
	#endif
	
	uint8_t buf[M_MESSAGE_MAX_TRANSFER_LEN];
	uint8_t response_buf[M_RESPONSE_MAX_TRANSFER_LEN];
	m_response response;
	
	int len = encode_m_message(buf, *msg);
	if (len < 2)
	{
		printf("Nonsense message\n");
		return ERR_INVALID_MESSAGE;
	}
	
	int succeeded = 0;
	int response_obtained;
	int ret_val;
	
	for (int send_tries = 0; send_tries < M_MESSAGE_SEND_TRIES && !succeeded; send_tries++)
	{
		
		ret_val = i2c_transmit_persistent(TEENSY_ADDR, buf, len, M_MESSAGE_I2C_SEND_TRIES);
		
		if (ret_val != NO_ERROR)
		{
			#ifdef REPORT_I2C
			printf("i2c_transmit_persistent reports failure. retrying... %d tries left\n", M_MESSAGE_SEND_TRIES - send_tries);
			#endif
			continue;
		}
		
		response_obtained = 0;
		for (int response_tries = 0; response_tries < M_MESSAGE_RESPONSE_TRIES && !response_obtained; response_tries++)
		{
			// Give the Teensy a moment
			vTaskDelay(pdMS_TO_TICKS(1));
			
			// Ask for response
			ret_val = i2c_receive(TEENSY_ADDR, response_buf, M_RESPONSE_MAX_TRANSFER_LEN);
			
			if (ret_val == NO_ERROR && response_buf[0] != M_RESPONSE_WAIT)
			{
				response = decode_m_response(response_buf, M_RESPONSE_MAX_TRANSFER_LEN);
				
				if (response.type != M_RESPONSE_CRC_FAIL)
					response_obtained = 1;
			}
		}
		
		if (!response_obtained)
		{
			#ifdef REPORT_I2C
			printf("Failed to obtain a response!\n");
			#endif
			return ERR_NO_RESPONSE;
		}
		
		
		#ifdef REPORT_I2C
		if (response.type != M_RESPONSE_HI)
		{
			printf("Obtained teensy response. Type = %s", m_response_code_to_string(response.type));
			#ifdef PRINT_RESPONSE_BYTES
			printf(", bytes: ");
			for (int i = 0; i < M_RESPONSE_MAX_DATA_LEN; i++)
				printf("0x%02x ", response.data[i]);
			#endif
			printf("\n");
		}
		#endif
		
		if (response.type != M_RESPONSE_REPEAT_MESSAGE)
		{
			succeeded = 1;
		}
	}
	
	if (succeeded)
	{
		memcpy(response_ptr, &response, sizeof(m_response));
		return NO_ERROR;
	}
	
	return ERR_COMMS_FAIL;
}

void handle_teensy_response(m_message msg, m_response response)
{
	
	switch (response.type)
	{	
		case M_RESPONSE_NO_MESSAGE:
			ESP_LOGW(TAG, "No response received from Teensy");
			break;
		
		case M_RESPONSE_HI:
			teensy_online = 1;
			break;
		
		case M_RESPONSE_INVALID:
			break;
			
		default:
			if (msg.callback)
				msg.callback(msg, response);
	}
}

static int handle_msg(m_message *msg)
{
	if (!msg)
		return ERR_NULL_PTR;
	
	m_response response;
	
	int ret_val = send_msg_to_teensy(msg, &response);
			
	switch (ret_val)
	{
		case NO_ERROR:
			handle_teensy_response(*msg, response);
			return NO_ERROR;
			break;
			
		case ERR_COMMS_FAIL:
			if (msg->retries > M_MESSAGE_MAX_RETRIES)
				msg->retries = M_MESSAGE_MAX_RETRIES;
			
			if (msg->retries > 0)
			{
				queue_message_retry(msg);
				return NO_ERROR;
			}
			else
			{
				m_free(msg);
				return ERR_COMMS_FAIL;
			}
			break;
			
		default:
			break;
	}
	
	return NO_ERROR;
}

void m_int_comms_task(void *param)
{
	int ret_val;
	int response_received;
	
	#ifdef PING_TEENSY
	hi_msg = create_m_message_nodata(M_MESSAGE_HI);
	#endif
	
	m_message *msg;
	
	TickType_t last_hi   = xTaskGetTickCount();
	TickType_t last_wake = xTaskGetTickCount();
	
	esp_err_t err;
	
	m_message_pll *retry_next;

	while (true)
	{
		TickType_t now = xTaskGetTickCount();
		#ifdef PING_TEENSY
		if ((now - last_hi) >= pdMS_TO_TICKS(teensy_online ? ET_PING_INTERVAL_MS_ONLINE : ET_PING_INTERVAL_MS_OFFLINE))
		{
			handle_msg(&hi_msg);

			last_hi = now;
		}
		#endif
		
		if (!teensy_online)
		{
			printf("Teensy is not online :(\n");
		}
		
		while (teensy_online && retry_queue)
		{
			retry_next = retry_queue->next;
			
			if (retry_queue->data)
				handle_msg(retry_queue->data);
			
			m_free(retry_queue);
			retry_queue = retry_next;
		}
		
		if (teensy_online && xQueueReceive(m_message_queue, &msg, 0) == pdTRUE)
			handle_msg(msg);

		vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(10));
	}


	vTaskDelete(NULL);
}

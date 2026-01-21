#include "m_int.h"

static const char *TAG = "TeensyComms";

#define SEND_BUFFER_LENGTH 16

QueueHandle_t m_message_queue;

void m_int_comms_task(void *param);

static i2c_master_bus_handle_t bus_handle = NULL;
static i2c_master_dev_handle_t teensy_handle = NULL;

#define M_COMMS_I2C_PORT_NUM     0
#define M_COMMS_I2C_SDA_GPIO     20
#define M_COMMS_I2C_SCL_GPIO     21
#define M_COMMS_I2C_FREQ_HZ      100000

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
	#ifdef USE_TEENSY
	#ifdef USE_COMMS
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
	#endif
	#endif
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
	#ifdef USE_COMMS
	esp_err_t err;

    i2c_master_bus_config_t bus_cfg = {
        .i2c_port = M_COMMS_I2C_PORT_NUM,
        .sda_io_num = M_COMMS_I2C_SDA_GPIO,
        .scl_io_num = M_COMMS_I2C_SCL_GPIO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .intr_priority = 0,
        .trans_queue_depth = 8,
        .flags.enable_internal_pullup = false,
    };

    err = i2c_new_master_bus(&bus_cfg, &bus_handle);
    if (err != ESP_OK) return ERR_I2C_FAIL;

    /* 2. Bind a device (7-bit address) on that bus */
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = TEENSY_ADDR,
        .scl_speed_hz = M_COMMS_I2C_FREQ_HZ,
    };

    err = i2c_master_bus_add_device(bus_handle, &dev_cfg, &teensy_handle);
    if (err != ESP_OK) return ERR_I2C_FAIL;
    
	xTaskCreatePinnedToCore(
		m_int_comms_task,
		"Teens Comms Task",
		4096,
		NULL,
		8,
		NULL,
		0
	);
	#endif
	return NO_ERROR;
}

void deinit_teensy_i2c_link(void)
{
    if (teensy_handle)
    {
        i2c_master_bus_rm_device(teensy_handle);
        teensy_handle = NULL;
    }

    if (bus_handle)
    {
        i2c_del_master_bus(bus_handle);
        bus_handle = NULL;
    }
}

#define M_MESSAGE_SEND_TRIES 		3
#define M_MESSAGE_RESPONSE_TRIES 	5
#define M_MESSAGE_I2C_SEND_TRIES 	5
#define REPORT_I2C
#define REPORT_PINGS
#define PRINT_RESPONSE_BYTES

#define TEENSY_COMMS_TIMEOUT_MS 10

esp_err_t teensy_transmit(const uint8_t *data, size_t len)
{
    if (!teensy_handle) return ESP_ERR_INVALID_STATE;

    return i2c_master_transmit(
        teensy_handle,
        data,
        len,
        TEENSY_COMMS_TIMEOUT_MS / portTICK_PERIOD_MS
    );
}


int teensy_transmit_persistent(const uint8_t *data, size_t len, int tries)
{
	esp_err_t ret_val;
	
	int i = 0;
	do {
		ret_val = teensy_transmit(data, len);
		i++;
	} while (ret_val != ESP_OK && i < tries);
	
	if (ret_val == ESP_OK)
		return NO_ERROR;
	else
		return ERR_I2C_FAIL;
}

int teensy_recieve(uint8_t *out, size_t len)
{
    if (!teensy_handle) return ERR_BAD_ARGS;

    esp_err_t ret = i2c_master_receive(
        teensy_handle,
        out,
        len,
        TEENSY_COMMS_TIMEOUT_MS / portTICK_PERIOD_MS
    );
    
    printf("teensy_recieve. ret = %d\n", ret);
    
    int all_ffs = 1;
    for (int i = 0; i < len; i++)
	{
		if (out[i] != 0xFF)
		{
			all_ffs = 0;
			break;
		}
	}
    
    return (ret == ESP_OK) ? (all_ffs ? ERR_I2C_FAIL : NO_ERROR) : ERR_I2C_FAIL;
}

#define REPORT_I2C

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
		
		ret_val = teensy_transmit_persistent(buf, len, M_MESSAGE_I2C_SEND_TRIES);
		
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
			vTaskDelay(pdMS_TO_TICKS(5));
			
			// Ask for response
			printf("Ask for response...\n");
			ret_val = teensy_recieve(response_buf, M_RESPONSE_MAX_TRANSFER_LEN);
			
			printf("ret_val = %s\n", m_error_code_to_string(ret_val));
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
		#ifndef REPORT_PINGS
		if (response.type != M_RESPONSE_HI)
		{
		#endif
			printf("Obtained teensy response. Type = %s", m_response_code_to_string(response.type));
			#ifdef PRINT_RESPONSE_BYTES
			printf(", bytes: ");
			for (int i = 0; i < M_RESPONSE_MAX_DATA_LEN; i++)
				printf("0x%02x ", response.data[i]);
			#endif
			printf("\n");
		#ifndef REPORT_PINGS
		}
		#endif
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

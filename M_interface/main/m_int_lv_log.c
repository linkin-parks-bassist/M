#include "m_int.h"

SemaphoreHandle_t m_int_lv_log_mutex;

static char m_int_lv_log_buf[M_INT_LV_LOG_BUF_LEN];
static int m_int_lv_log_wrapped = 0;
static int m_int_lv_log_pos = 0;

char *waiting_buf = NULL;

static const char *TAG = "m_int_logging.c";

void m_int_lv_log_flush_task(void *param);

int m_int_log_init()
{
	for (int i = 0; i < M_INT_LV_LOG_BUF_LEN; i++)
		m_int_lv_log_buf[i] = 0;
	
	m_int_lv_log_mutex = xSemaphoreCreateMutex();
	assert(m_int_lv_log_mutex != NULL);
	
	xTaskCreate(
		m_int_lv_log_flush_task,
		"log_task",
		8192,
		NULL,
		5,                  
		NULL
	);
	
	return NO_ERROR;
}

void m_int_lv_log_flush()
{
	char local_buf[M_INT_LV_LOG_BUF_LEN];
	int local_buf_position = 0;
	
	if (xSemaphoreTake(m_int_lv_log_mutex, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS)) != pdTRUE)
	{
		ESP_LOGE(TAG, "Failed to obtain log mutex\n");
		return;
	}
	
	if (m_int_lv_log_wrapped)
	{
		while (local_buf_position + m_int_lv_log_pos + 2 < M_INT_LV_LOG_BUF_LEN)
		{
			local_buf[local_buf_position] = m_int_lv_log_buf[local_buf_position + m_int_lv_log_pos + 2];
			local_buf_position++;
		}
	}
	
	for (int i = 0; i < m_int_lv_log_pos && local_buf_position + 1 < M_INT_LV_LOG_BUF_LEN; i++)
		local_buf[local_buf_position++] = m_int_lv_log_buf[i];
	
	local_buf[local_buf_position++] = 0;
	
	puts(local_buf);
	
	for (int i = 0; i < M_INT_LV_LOG_BUF_LEN; i++)
		m_int_lv_log_buf[i] = 0;
	
	m_int_lv_log_pos = 0;
	m_int_lv_log_wrapped = 0;
	
	xSemaphoreGive(m_int_lv_log_mutex);
}

void m_int_lv_log_cb(const char *buf)
{
	if (!buf)
		return;
	
	if (waiting_buf)
	{
		char *local_waiting_buf = m_int_strndup(waiting_buf, M_INT_LV_LOG_BUF_LEN);
		m_free(waiting_buf);
		waiting_buf = NULL;
		m_int_lv_log_cb(local_waiting_buf);
		m_free(local_waiting_buf);
	}
	
	if (xSemaphoreTake(m_int_lv_log_mutex, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS)) != pdTRUE)
	{
		waiting_buf = m_int_strndup(buf, M_INT_LV_LOG_BUF_LEN);
		return;
	}
	
	int len = strlen(buf);
	int new_pos;
	
	for (int i = 0; i < len; i++)
	{
		m_int_lv_log_buf[m_int_lv_log_pos] = buf[i];
		
		new_pos = (m_int_lv_log_pos + 1) % M_INT_LV_LOG_BUF_LEN;
		if (new_pos < m_int_lv_log_pos)
			m_int_lv_log_wrapped = 1;
		m_int_lv_log_pos = new_pos;
	}
	
	if (m_int_lv_log_pos + 1 < M_INT_LV_LOG_BUF_LEN)
		m_int_lv_log_buf[m_int_lv_log_pos + 1] = 0;
	
	xSemaphoreGive(m_int_lv_log_mutex);
}

void m_int_lv_log_flush_task(void *param)
{
	TickType_t last_wake = xTaskGetTickCount();

	while (true)
	{
		#ifdef PRINT_LV_LOGS
		m_int_lv_log_flush();
		#endif
		vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(1000));
	}


	vTaskDelete(NULL);
}


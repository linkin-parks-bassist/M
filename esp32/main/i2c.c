#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "m_error_codes.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "i2c.h"

static const char *TAG = "I2C";

SemaphoreHandle_t i2c_mutex;

esp_err_t i2c_master_init()
{
	int i2c_master_port = I2C_MASTER_NUM;

	i2c_config_t i2c_conf = {
		.mode = I2C_MODE_MASTER,
		.sda_io_num = I2C_MASTER_SDA_IO,
		.scl_io_num = I2C_MASTER_SCL_IO,
		.sda_pullup_en = GPIO_PULLUP_ENABLE,
		.scl_pullup_en = GPIO_PULLUP_ENABLE,
		.master.clk_speed = I2C_MASTER_FREQ_HZ,
	};

	// Configure I2C parameters
	i2c_param_config(i2c_master_port, &i2c_conf);
	
	i2c_mutex = xSemaphoreCreateMutex();
	assert(i2c_mutex != NULL);

	// Install I2C driver
	return i2c_driver_install(i2c_master_port, i2c_conf.mode, 0, 0, 0);
}

int i2c_transmit(uint8_t addr, uint8_t *buf, int n)
{
	if (!buf)
		return ERR_NULL_PTR;
	
	if (n < 0)
		return ERR_BAD_ARGS;
	
	if (xSemaphoreTake(i2c_mutex, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS)) != pdTRUE)
	{
		ESP_LOGE(TAG, "Failed to obtain I2C mutex\n");
		return ERR_MUTEX_UNAVAILABLE;
	}
	
	esp_err_t ret_val = i2c_master_write_to_device(I2C_MASTER_NUM, addr, buf, n, pdMS_TO_TICKS(1000));
	
	xSemaphoreGive(i2c_mutex);
	
	if (ret_val != ESP_OK)
	{
		ESP_LOGE(TAG, "I2C write failed: %s", esp_err_to_name(ret_val));
		
		return ERR_UNKNOWN_ERR;
	}
	
	return NO_ERROR;
}

int i2c_recieve(uint8_t addr, uint8_t *buf, int n)
{
	if (!buf)
		return ERR_NULL_PTR;
	
	if (n < 0)
		return ERR_BAD_ARGS;
	
	if (xSemaphoreTake(i2c_mutex, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS)) != pdTRUE)
	{
		ESP_LOGE(TAG, "Failed to obtain I2C mutex\n");
		return ERR_MUTEX_UNAVAILABLE;
	}
	
	esp_err_t ret_val = i2c_master_read_from_device(I2C_MASTER_NUM, addr, buf, n, pdMS_TO_TICKS(1000));
	
	xSemaphoreGive(i2c_mutex);
	
	if (ret_val != ESP_OK)
	{
		ESP_LOGE(TAG, "I2C read failed: %s", esp_err_to_name(ret_val));
		
		return ERR_UNKNOWN_ERR;
	}
	
	return NO_ERROR;
}

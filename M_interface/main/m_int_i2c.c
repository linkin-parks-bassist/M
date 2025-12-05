#include "m_int.h"

static const char *TAG = "I2C";

SemaphoreHandle_t i2c_mutex;

esp_err_t i2c_master_init()
{
	#ifndef USE_5A
	
		#ifdef M_SIMULATED
			return NO_ERROR;
		#endif
		
		#ifdef USE_OLD_I2C_DRIVER
			int i2c_master_port = I2C_MASTER_NUM;

			i2c_config_t i2c_conf = {
				.mode = I2C_MODE_MASTER,
				.sda_io_num = I2C_MASTER_SDA_IO,
				.scl_io_num = I2C_MASTER_SCL_IO,
				.sda_pullup_en = GPIO_PULLUP_ENABLE,
				.scl_pullup_en = GPIO_PULLUP_ENABLE,
				.master.clk_speed = I2C_MASTER_FREQ_HZ,
			};

			// Conpfigure I2C parameters
			i2c_param_config(i2c_master_port, &i2c_conf);
			
			i2c_mutex = xSemaphoreCreateMutex();
			assert(i2c_mutex != NULL);

			// Install I2C driver
			return i2c_driver_install(i2c_master_port, i2c_conf.mode, 0, 0, 0);
		#else
		
			esp_err_t ret_val;

			i2c_mutex = xSemaphoreCreateMutex();
			assert(i2c_mutex != NULL);

			return ESP_OK;

		#endif
		return NO_ERROR;
	#endif

	return NO_ERROR;
}

int i2c_transmit(uint8_t addr, uint8_t *buf, int n)
{
	#ifndef USE_5A
	
		#ifdef M_SIMULATED
			return NO_ERROR;
		#endif
		
		#ifdef USE_OLD_I2C_DRIVER
			if (!buf)
				return ERR_NULL_PTR;
			
			if (n < 0)
				return ERR_BAD_ARGS;
			
			if (xSemaphoreTake(i2c_mutex, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS)) != pdTRUE)
			{
				ESP_LOGE(TAG, "Failed to obtain I2C mutex\n");
				return ERR_MUTEX_UNAVAILABLE;
			}
			
			esp_err_t ret_val = i2c_master_write_to_device(I2C_MASTER_NUM, addr, buf, n, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS));
			
			xSemaphoreGive(i2c_mutex);
			
			if (ret_val != ESP_OK)
			{
				ESP_LOGE(TAG, "I2C write failed: %s", esp_err_to_name(ret_val));
				
				return ERR_UNKNOWN_ERR;
			}
		#else
			if (!buf)
				return ERR_NULL_PTR;
			if (n < 0)
				return ERR_BAD_ARGS;

			if (xSemaphoreTake(i2c_mutex, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS)) != pdTRUE)
				return ERR_MUTEX_UNAVAILABLE;

			esp_err_t ret = i2c_master_transmit(ch422g_dev, buf, n, I2C_MASTER_TIMEOUT_MS);

			xSemaphoreGive(i2c_mutex);

			if (ret != ESP_OK)
			{
				ESP_LOGE(TAG, "I2C write failed: %s", esp_err_to_name(ret));
				return ERR_I2C_FAIL;
			}
		#endif
		
    #endif
    return NO_ERROR;
}

int i2c_transmit_persistent(uint8_t addr, uint8_t *buf, int n, int retries)
{
	#ifndef USE_5A
	#ifdef M_SIMULATED
	return NO_ERROR;
	#endif
	
	#ifdef USE_OLD_I2C_DRIVER
	if (!buf)
		return ERR_NULL_PTR;
	
	if (n < 0)
		return ERR_BAD_ARGS;
	
	esp_err_t transmit_ret = ESP_FAIL;
	int ret_val = NO_ERROR;
	
	for (int tries = 0; tries < retries && transmit_ret != ESP_OK; tries++)
	{
		if (xSemaphoreTake(i2c_mutex, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS)) != pdTRUE)
		{
			ESP_LOGE(TAG, "Failed to obtain I2C mutex. Retrying; tries remaining: %d\n", retries - tries);
			ret_val = ERR_MUTEX_UNAVAILABLE;
			continue;
		}
		
		transmit_ret = i2c_master_write_to_device(I2C_MASTER_NUM, addr, buf, n, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS));
		
		xSemaphoreGive(i2c_mutex);
		
		if (ret_val != ESP_OK)
		{
			ESP_LOGE(TAG, "I2C write failed: %s. Retrying; tries remaning: %d", esp_err_to_name(ret_val), retries - tries);
			ret_val = ERR_I2C_FAIL;
		}
		else
		{
			ret_val = NO_ERROR;
		}
	}
	
	return ret_val;
	#else
	if (!buf) return ERR_NULL_PTR;
    if (n < 0)  return ERR_BAD_ARGS;

    esp_err_t err = ESP_FAIL;
    int ret_val = NO_ERROR;

    for (int tries = 0; tries < retries && err != ESP_OK; tries++)
    {
        if (xSemaphoreTake(i2c_mutex, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS)) != pdTRUE)
        {
            ret_val = ERR_MUTEX_UNAVAILABLE;
            continue;
        }

        err = i2c_master_transmit(ch422g_dev, buf, n, I2C_MASTER_TIMEOUT_MS);

        xSemaphoreGive(i2c_mutex);

        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "I2C write failed: %s (tries left %d)",
                     esp_err_to_name(err), retries - tries);
            ret_val = ERR_I2C_FAIL;
        }
        else
            ret_val = NO_ERROR;
    }

    return ret_val;
    #endif
    
    #endif
    return NO_ERROR;
}

int i2c_receive(uint8_t addr, uint8_t *buf, int n)
{
	#ifndef USE_5A
	#ifdef M_SIMULATED
	return NO_ERROR;
	#endif
	
	#ifdef USE_OLD_I2C_DRIVER
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
	
	#else
	
	if (!buf)
		return ERR_NULL_PTR;
	
    if (n < 0) 
		return ERR_BAD_ARGS;

    if (xSemaphoreTake(i2c_mutex, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS)) != pdTRUE)
        return ERR_MUTEX_UNAVAILABLE;

    esp_err_t ret = i2c_master_receive(ch422g_dev, buf, n, I2C_MASTER_TIMEOUT_MS);

    xSemaphoreGive(i2c_mutex);

    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "I2C read failed: %s", esp_err_to_name(ret));
        return ERR_I2C_FAIL;
    }
    #endif
	
	return NO_ERROR;
	
	#endif
	return NO_ERROR;
}

#ifndef USE_5A
int m_ch422g_init_pull(uint8_t pull_mask)
{
	return NO_ERROR;
}

uint8_t m_ch422g_read()
{
	#ifndef M_SIMULATED
	
	if (xSemaphoreTake(i2c_mutex, portMAX_DELAY) != pdTRUE)
	{
		ESP_LOGE(TAG, "Failed to obtain I2C mutex\n");
		return 0xFF;
	}
	
	uint8_t write_byte = 0b00000010;
	esp_err_t ret_val = i2c_master_write_to_device(I2C_MASTER_NUM, CH422G_ADDR_WR_SET, &write_byte, 1, portMAX_DELAY);
	
	if (ret_val != ESP_OK)
	{
		ESP_LOGE(TAG, "I2C write failed: %s", esp_err_to_name(ret_val));
		xSemaphoreGive(i2c_mutex);
		return 0xFF;
	}
	
	uint8_t result;
	ret_val = i2c_master_read_from_device(I2C_MASTER_NUM, CH422G_ADDR_RD_IO, &result, 1, portMAX_DELAY);
	
	write_byte = 0b00000001;
	if (i2c_master_write_to_device(I2C_MASTER_NUM, CH422G_ADDR_WR_SET, &write_byte, 1, portMAX_DELAY) != ESP_OK)
	{
		ESP_LOGE(TAG, "I2C write failed: %s", esp_err_to_name(ret_val));
		xSemaphoreGive(i2c_mutex);
		return 0xFF;
	}
	
	if (ret_val != ESP_OK)
	{
		ESP_LOGE(TAG, "CH422G read failed: %s", esp_err_to_name(ret_val));
		xSemaphoreGive(i2c_mutex);
		return 0xFF;
	}
	
	xSemaphoreGive(i2c_mutex);
	
	#endif
	return result;
}
#endif

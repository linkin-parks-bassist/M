#ifndef M_ESP32_I2C_H_
#define M_ESP32_I2C_H_

#include <stdint.h>

#define I2C_MASTER_SCL_IO		   	9	   /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO		   	8	   /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM			  	0	   /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ		  	100000					 /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0						  /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0						  /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS	   	10

esp_err_t i2c_master_init();

int i2c_transmit_persistent(uint8_t addr, uint8_t *buf, int n, int retries);
int i2c_transmit(uint8_t addr, uint8_t *buf, int n);
int i2c_receive(uint8_t addr, uint8_t *buf, int n);

extern SemaphoreHandle_t i2c_mutex;


#endif


#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_rgb.h"
#include "esp_lcd_touch_gt911.h"
#include "i2c.h"

static TaskHandle_t touch_task_handle;

static void IRAM_ATTR gt911_isr_handler(void *arg)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(touch_task_handle, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken) portYIELD_FROM_ISR();
}

static void touch_task(void *arg)
{
	esp_lcd_touch_handle_t tp_handle = (esp_lcd_touch_handle_t)arg;
	
	gpio_install_isr_service(0);
    gpio_isr_handler_add(GPIO_NUM_4, gt911_isr_handler, NULL);
	
    for (;;)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // wait for IRQ
        
        if (xSemaphoreTake(i2c_mutex, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS)) == pdTRUE)
		{
			if (!gpio_get_level(GPIO_NUM_4))
				esp_lcd_touch_read_data(tp_handle);      // safe in task context
			xSemaphoreGive(i2c_mutex);
		}
    }
}

void init_touch_task(esp_lcd_touch_handle_t tp_handle)
{
	xTaskCreatePinnedToCore(
		touch_task,
		"gt911_touch",
		4096,
		tp_handle,          // task arg
		5,                  // priority
		&touch_task_handle, // <-- store handle here
		1
	);
}




#ifndef M_WAVESHARE_5A_H_
#define M_WAVESHARE_5A_H_

#include "esp_log.h"
#include "esp_heap_caps.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_lcd_touch_gt911.h"
#include <lvgl.h>

#include "esp_lcd_mipi_dsi.h"

int waveshare_dsi_touch_5_a_init(lv_disp_t **disp);

#endif

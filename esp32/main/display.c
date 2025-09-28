#include "waveshare_rgb_lcd_port.h"
#include "esp_lcd_touch_gt911.h"
#include "esp_lcd_panel_rgb.h"
#include "m_error_codes.h"
#include "driver/i2c.h"
#include "lvgl_port.h"
#include "esp_log.h"
#include "display.h"
#include "i2c.h"

int init_display()
{
	waveshare_esp32_s3_rgb_lcd_init();
	return NO_ERROR;
}

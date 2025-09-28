#include "waveshare_rgb_lcd_port.h"
#include "esp_lcd_touch_gt911.h"
#include "freertos/FreeRTOS.h"
#include "esp_lcd_panel_rgb.h"
#include "freertos/task.h"
#include "m_error_codes.h"
#include "teensy_comms.h"
#include "lvgl_port.h"
#include "display.h"
#include "esp_log.h"
#include "i2c.h"
#include "ui.h"

void app_main()
{
	init_display();
	init_teensy_comms();
	
	if (lvgl_port_lock(-1))
	{
		//example_lvgl_demo_ui();
		make_ui();
		lvgl_port_unlock();
	}
}

#include "waveshare_rgb_lcd_port.h"
#include "esp_lcd_touch_gt911.h"
#include "freertos/FreeRTOS.h"
#include "esp_lcd_panel_rgb.h"
#include "freertos/task.h"
#include "m_error_codes.h"
#include "m_parameter.h"
#include "shared_context.h"
#include "esp32_context.h"
#include "teensy_comms.h"
#include "lvgl_port.h"
#include "display.h"
#include "esp_log.h"
#include "i2c.h"
#include "ui.h"

esp32_context global_cxt;

void app_main()
{
	init_esp32_context(&global_cxt);
	
	lv_disp_t *disp;
	init_display(&disp);
	init_teensy_comms();
	
	if (lvgl_port_lock(-1))
	{
		//example_lvgl_demo_ui();
		make_ui(disp);
		lvgl_port_unlock();
	}
	
	et_msg msg = create_et_msg(ET_MESSAGE_RESET, "");
	
	xQueueSend(et_msg_queue, &msg, 0);
}

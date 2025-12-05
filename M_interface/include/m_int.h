#ifndef ESP32_M_H_
#define ESP32_M_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define M_ENABLE_LV_LOGGING
#define USE_SDCARD

#define USE_5A

#ifdef USE_5A
#include "bsp/esp32_p4_nano.h"
#endif

#ifndef M_SIMULATED
 
 #include <freertos/FreeRTOS.h>
 #include <freertos/semphr.h>
 #include <freertos/queue.h>
 
 #include <esp_lcd_touch.h>
 #ifdef USE_OLD_I2C_DRIVER
 #include <driver/i2c.h>
 #else
 #include "driver/i2c_master.h"
 #endif
 #include <esp_log.h>
 
 #ifdef USE_5A
 #include "waveshare_dsi_touch_5_a.h"
 #else
 #include "waveshare_rgb_lcd_port.h"
 #endif
 
#else
 
 #define LV_USE_SDL 1

 #define ESP_LOGE sim_esp_log
 #define ESP_LOGI sim_esp_log
 #define ESP_LOGD sim_esp_log
 #define ESP_LOGW sim_esp_log
 
 void sim_esp_log(const char *tag, const char *fmt, ...);
 
 #define xTaskCreatePinnedToCore(a1, a2, a3, a4, a5, a6, a7) xTaskCreate(a1, a2, a3, a4, a5, a6) 
 
 void app_main();
 
 #include <FreeRTOS/include/FreeRTOS.h>
 #include <FreeRTOS/include/semphr.h>
 #include <FreeRTOS/include/queue.h>
 
 #include "SDL2/SDL.h"
 
 typedef int esp_err_t;
	
#endif

#include <lvgl.h>

#ifndef M_SIMULATED
 //#include <esp_lvgl_port.h>	
#endif


#define LL_MALLOC m_alloc
#define LL_FREE   m_free

//#define LV_MM_INT_CUSTOM_ALLOC  m_int_lv_malloc
//#define LV_MM_INT_CUSTOM_FREE   m_int_lv_free

#define SETTINGS_FNAME "/sdcard/conf"

#ifndef M_INTERFACE
 #define M_INTERFACE
#endif

#ifndef m_printf
 #define m_printf printf
#endif

#define USE_COMMS

#include "m_linked_list.h"
#include "m_error_codes.h"

#include "m_int_representation.h"

#include "m_parameter.h"
#include "m_transformer.h"
#include "m_pipeline.h"
#include "m_profile.h"

#include "m_status.h"
#include "m_transformer_enum.h"
#include "m_comms.h"

#include "m_alloc.h"

#include "m_int_i2c.h"
#include "m_int_display.h"
#include "m_int_sd.h"
#include "m_int_footswitch.h"

#include "m_int_parameter.h"

#include "m_int_comms.h"

#include "m_int_button.h"
#include "m_int_ui.h"
#include "m_int_parameter_widget.h"

#include "m_int_transformer.h"
#include "m_int_transformer_init.h"
#include "m_int_transformer_table.h"
#include "m_int_transformer_view.h"
#include "m_int_transformer_settings.h"

#include "m_int_pipeline.h"
#include "m_int_profile.h"
#include "m_int_sequence.h"
#include "m_int_transformer_select.h"
#include "m_int_profile_settings.h"
#include "m_int_profile_view.h"
#include "m_int_sequence_view.h"
#include "m_int_settings.h"
#include "m_int_context.h"

#include "m_int_files.h"
#include "m_int_profile_send.h"

#include "m_int_sequence_list.h"
#include "m_int_menu.h"

#include "m_int_lv_log.h"

#define binary_max(x, y) ((x > y) ? x : y)
#define binary_min(x, y) ((x > y) ? y : x)

#define sqr(x) (x * x)

#endif

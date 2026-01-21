#ifndef ESP32_M_H_
#define ESP32_M_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define M_ENABLE_LV_LOGGING

#define USE_5A

#define USE_DISPLAY
#define USE_SDCARD
#define USE_SGTL5000
#define USE_COMMS
#define USE_FPGA
//#define USE_TEENSY

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/queue.h>

#include "driver/i2c_master.h"
#include <esp_log.h>

#include "waveshare_dsi_touch_5_a.h"

#include <lvgl.h>

#define LL_MALLOC m_alloc
#define LL_FREE   m_free

#define SETTINGS_FNAME "/sdcard/conf"

#ifndef M_INTERFACE
 #define M_INTERFACE
#endif

#ifndef m_printf
 #define m_printf printf
#endif

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
#include "drivers/m_int_sgtl5000.h"
#include "m_int_fpga.h"
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

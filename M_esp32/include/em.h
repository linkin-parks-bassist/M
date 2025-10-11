#ifndef ESP32_M_H_
#define ESP32_M_H_

#define M_ESP32

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/queue.h>

#include <esp_lcd_touch.h>
#include <driver/i2c.h>
#include <esp_log.h>

#include <lvgl.h>
#include <lvgl_port.h>

#include "m_error_codes.h"
#include "m_status.h"
#include "m_vec2i.h"
#include "m_transformer_enum.h"
#include "m_comms.h"
#include "m_linked_list.h"

#include "em_parameter.h"
#include "em_parameter_widget.h"

#include "em_i2c.h"
#include "em_display.h"

#include "em_comms.h"
#include "em_ui.h"

#include "em_transformer.h"
#include "em_transformer_init.h"
#include "em_transformer_table.h"
#include "em_transformer_view.h"
#include "em_transformer_widget.h"

#include "em_pipeline.h"
#include "em_profile.h"
#include "em_transformer_select.h"
#include "em_profile_view.h"
#include "em_context.h"

#endif

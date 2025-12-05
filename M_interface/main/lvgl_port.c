/*
 * SPDX-FileCopyrightText: 2023-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "m_int.h"

#ifndef M_SIMULATED
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "esp_lcd_panel_ops.h"

#ifdef USE_5A

#include "esp_lcd_mipi_dsi.h"
#include "esp_lcd_hx8394.h"
#else
#include "esp_lcd_panel_rgb.h"
#endif
#include "esp_lcd_touch.h"
#include "esp_timer.h"
#include "esp_log.h"
#endif

#include "lvgl.h"
#include "esp_lvgl_port.h"

static const char *TAG = "lv_port";					  // Tag for logging
static SemaphoreHandle_t lvgl_mux;					   // LVGL mutex for synchronization
static TaskHandle_t lvgl_task_handle = NULL;			 // Handle for the LVGL task

#if EXAMPLE_LVGL_PORT_ROTATION_DEGREE != 0
// Function to get the next frame buffer for double buffering
static void *get_next_frame_buffer(esp_lcd_panel_handle_t panel_handle)
{
	static void *next_fb = NULL;						  // Pointer to the next frame buffer
	static void *fb[2] = { NULL };						// Array to hold two frame buffers
	if (next_fb == NULL) {
		ESP_ERROR_CHECK(esp_lcd_rgb_panel_get_frame_buffer(panel_handle, 2, &fb[0], &fb[1])); // Get the frame buffers
		next_fb = fb[1];								  // Initialize to the second buffer
	} else {
		// Toggle between the two frame buffers
		next_fb = (next_fb == fb[0]) ? fb[1] : fb[0];
	}
	return next_fb;									   // Return the next frame buffer
}

// Function to rotate and copy pixels from one buffer to another
#ifndef M_SIMULATED
IRAM_ATTR
#endif
static void rotate_copy_pixel(const uint16_t *from, uint16_t *to, uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t w, uint16_t h, uint16_t rotation)
{
	int from_index = 0;								   // Index for source buffer
	int to_index = 0;									 // Index for destination buffer
	int to_index_const = 0;							   // Constant index for destination buffer

	switch (rotation) {
	case 90:
		to_index_const = (w - x_start - 1) * h;		  // Calculate constant index for 90-degree rotation
		for (int from_y = y_start; from_y < y_end + 1; from_y++) {
			from_index = from_y * w + x_start;		   // Calculate index in the source buffer
			to_index = to_index_const + from_y;		  // Calculate index in the destination buffer
			for (int from_x = x_start; from_x < x_end + 1; from_x++) {
				*(to + to_index) = *(from + from_index);  // Copy pixel
				from_index += 1;						  // Move to the next pixel in the source
				to_index -= h;							// Move to the next pixel in the destination
			}
		}
		break;
	case 180:
		to_index_const = h * w - x_start - 1;			// Calculate constant index for 180-degree rotation
		for (int from_y = y_start; from_y < y_end + 1; from_y++) {
			from_index = from_y * w + x_start;		   // Calculate index in the source buffer
			to_index = to_index_const - from_y * w;	  // Calculate index in the destination buffer
			for (int from_x = x_start; from_x < x_end + 1; from_x++) {
				*(to + to_index) = *(from + from_index);  // Copy pixel
				from_index += 1;						  // Move to the next pixel in the source
				to_index -= 1;							// Move to the next pixel in the destination
			}
		}
		break;
	case 270:
		to_index_const = (x_start + 1) * h - 1;		  // Calculate constant index for 270-degree rotation
		for (int from_y = y_start; from_y < y_end + 1; from_y++) {
			from_index = from_y * w + x_start;		   // Calculate index in the source buffer
			to_index = to_index_const - from_y;		  // Calculate index in the destination buffer
			for (int from_x = x_start; from_x < x_end + 1; from_x++) {
				*(to + to_index) = *(from + from_index);  // Copy pixel
				from_index += 1;						  // Move to the next pixel in the source
				to_index += h;							// Move to the next pixel in the destination
			}
		}
		break;
	default:
		break;											 // Do nothing for unsupported rotation angles
	}
}
#endif /* EXAMPLE_LVGL_PORT_ROTATION_DEGREE */



void flush_callback(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map)
{
	esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data; // Get the panel handle from driver user data
	const int offsetx1 = area->x1; // Start X coordinate of the area to flush
	const int offsetx2 = area->x2; // End X coordinate of the area to flush
	const int offsety1 = area->y1; // Start Y coordinate of the area to flush
	const int offsety2 = area->y2; // End Y coordinate of the area to flush

	/* Just copy data from the color map to the RGB frame buffer */
	esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, color_map);

	lv_disp_flush_ready(drv); // Mark the display flush as complete
}


static lv_disp_t *display_init(esp_lcd_panel_handle_t panel_handle)
{
	assert(panel_handle); // Ensure the panel handle is valid

	static lv_disp_draw_buf_t disp_buf = { 0 };	 // Contains internal graphic buffer(s) called draw buffer(s)
	static lv_disp_drv_t disp_drv = { 0 };		  // Contains LCD panel handle and callback functions

	// Allocate draw buffers used by LVGL
	void *buf1 = NULL; // Pointer for the first buffer
	void *buf2 = NULL; // Pointer for the second buffer
	int buffer_size = 0; // Size of the buffer

	ESP_LOGD(TAG, "Malloc memory for LVGL buffer");

	// Normally, for RGB LCD, just one buffer is used for LVGL rendering
	buffer_size = LVGL_PORT_H_RES * LVGL_PORT_BUFFER_HEIGHT; // Calculate buffer size
	buf1 = heap_caps_malloc(buffer_size * sizeof(lv_color_t), MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT); // Allocate memory
	assert(buf1); // Ensure allocation succeeded
	buf2 = heap_caps_malloc(buffer_size * sizeof(lv_color_t),
                        MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
	assert(buf2);
	
	ESP_LOGI(TAG, "LVGL buffer size: %dKB", buffer_size * sizeof(lv_color_t) / 1024); // Log buffer size
	
	// Initialize LVGL draw buffers
	lv_disp_draw_buf_init(&disp_buf, buf1, buf2, buffer_size); // Initialize the draw buffer

	ESP_LOGD(TAG, "Register display driver to LVGL");
	lv_disp_drv_init(&disp_drv); // Initialize the display driver

	// Always use the panel’s native timing
	disp_drv.hor_res = LVGL_PORT_H_RES; // 1024
	disp_drv.ver_res = LVGL_PORT_V_RES; // 600

	disp_drv.flush_cb = flush_callback;	// Set the flush callback
	disp_drv.draw_buf = &disp_buf;		 // Set the draw buffer
	disp_drv.user_data = panel_handle;	 // Set user data to panel handle

	// <<< Add these lines >>>
	disp_drv.sw_rotate = 1;				// Enable LVGL software rotation
	disp_drv.rotated   = LV_DISP_ROT_90;  // 90° counter-clockwise
	
	disp_drv.antialiasing = 0;

#if LVGL_PORT_FULL_REFRESH
	disp_drv.full_refresh = 1; // Enable full refresh
#elif LVGL_PORT_DIRECT_MODE
	disp_drv.direct_mode = 1; // Enable direct mode
#endif

return lv_disp_drv_register(&disp_drv); // Register the display driver
}

static void touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
	esp_lcd_touch_handle_t tp = (esp_lcd_touch_handle_t)indev_drv->user_data; // Get touchpad handle from user data
	assert(tp); // Ensure touchpad handle is valid

	uint16_t touchpad_x; // Variable for X coordinate
	uint16_t touchpad_y; // Variable for Y coordinate
	uint8_t touchpad_cnt = 0; // Variable for touch count

	/* Read data from touch controller into memory */
	#ifndef TOUCH_PANEL_USE_INTERRUPTS
	esp_lcd_touch_read_data(tp); // Read data from touch controller
	#endif

	/* Read data from touch controller */
	bool touchpad_pressed = esp_lcd_touch_get_coordinates(tp, &touchpad_x, &touchpad_y, NULL, &touchpad_cnt, 1); // Get touch coordinates
	if (touchpad_pressed && touchpad_cnt > 0) {
		data->point.x = touchpad_x; // Set the X coordinate
		data->point.y = touchpad_y; // Set the Y coordinate
		data->state = LV_INDEV_STATE_PRESSED; // Set state to pressed
		#ifndef M_SIMULATED
		ESP_LOGD(TAG, "Touch position: %d,%d", touchpad_x, touchpad_y); // Log touch position
		#endif
	} else {
		data->state = LV_INDEV_STATE_RELEASED; // Set state to released
	}
}

static lv_indev_t *indev_init(esp_lcd_touch_handle_t tp)
{
	assert(tp); // Ensure the touch panel handle is valid

	static lv_indev_drv_t indev_drv_tp; // Static input device driver

	/* Register a touchpad input device */
	lv_indev_drv_init(&indev_drv_tp); // Initialize the input device driver
	indev_drv_tp.type = LV_INDEV_TYPE_POINTER; // Set the device type to pointer (touchpad)
	indev_drv_tp.read_cb = touchpad_read; // Set the read callback function
	indev_drv_tp.user_data = tp; // Set user data to the touch panel handle

	return lv_indev_drv_register(&indev_drv_tp); // Register the input device driver
}

static void tick_increment(void *arg)
{
	/* Tell LVGL how many milliseconds have elapsed */
	lv_tick_inc(LVGL_PORT_TICK_PERIOD_MS); // Increment the LVGL tick count
}

static esp_err_t tick_init(void)
{
	// Tick interface for LVGL (using esp_timer to generate 2ms periodic event)
	const esp_timer_create_args_t lvgl_tick_timer_args = {
		.callback = &tick_increment, // Set the callback function for the timer
		.name = "LVGL tick" // Name of the timer
	};
	esp_timer_handle_t lvgl_tick_timer = NULL; // Timer handle
	ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer)); // Create the timer
	return esp_timer_start_periodic(lvgl_tick_timer, LVGL_PORT_TICK_PERIOD_MS * 1000); // Start the timer
}

static void esp_lvgl_port_task(void *arg)
{
	#ifndef M_SIMULATED
	ESP_LOGD(TAG, "Starting LVGL task"); // Log the task start
	#endif

	uint32_t task_delay_ms = LVGL_PORT_TASK_MAX_DELAY_MS; // Set initial task delay
	while (1) {
		if (esp_lvgl_port_lock(-1)) { // Try to lock the LVGL mutex
			task_delay_ms = lv_timer_handler(); // Handle LVGL timer events
			esp_lvgl_port_unlock(); // Unlock the mutex
		}
		// Ensure the delay time is within limits
		if (task_delay_ms > LVGL_PORT_TASK_MAX_DELAY_MS) {
			task_delay_ms = LVGL_PORT_TASK_MAX_DELAY_MS;
		} else if (task_delay_ms < LVGL_PORT_TASK_MIN_DELAY_MS) {
			task_delay_ms = LVGL_PORT_TASK_MIN_DELAY_MS;
		}
		vTaskDelay(pdMS_TO_TICKS(task_delay_ms)); // Delay the task for the calculated time
	}
}

esp_err_t esp_lvgl_port_init(esp_lcd_panel_handle_t lcd_handle, esp_lcd_touch_handle_t tp_handle, lv_disp_t **disp)
{
	lv_init(); // Initialize LVGL
	ESP_ERROR_CHECK(tick_init()); // Initialize the tick timer

	assert(disp);

	*disp = display_init(lcd_handle); // Initialize the display
	assert(disp); // Ensure the display initialization was successful

	if (tp_handle) {
		lv_indev_t *indev = indev_init(tp_handle); // Initialize the touchpad input device
		assert(indev); // Ensure the input device initialization was successful

		// Set touch panel orientation based on rotation
#if EXAMPLE_LVGL_PORT_ROTATION_90
		esp_lcd_touch_set_swap_xy(tp_handle, true); // Swap X and Y coordinates
		esp_lcd_touch_set_mirror_y(tp_handle, true); // Mirror Y coordinates
#elif EXAMPLE_LVGL_PORT_ROTATION_180
		esp_lcd_touch_set_mirror_x(tp_handle, true); // Mirror X coordinates
		esp_lcd_touch_set_mirror_y(tp_handle, true); // Mirror Y coordinates
#elif EXAMPLE_LVGL_PORT_ROTATION_270
		esp_lcd_touch_set_swap_xy(tp_handle, true); // Swap X and Y coordinates
		esp_lcd_touch_set_mirror_x(tp_handle, true); // Mirror X coordinates
#endif
	}

	lvgl_mux = xSemaphoreCreateRecursiveMutex(); // Create a recursive mutex for LVGL
	assert(lvgl_mux); // Ensure mutex creation was successful

	#ifndef M_SIMULATED
	ESP_LOGI(TAG, "Create LVGL task"); // Log task creation
	#endif
	BaseType_t core_id = (LVGL_PORT_TASK_CORE < 0) ? tskNO_AFFINITY : LVGL_PORT_TASK_CORE; // Determine core ID for the task
	BaseType_t ret = xTaskCreatePinnedToCore(esp_lvgl_port_task, "lvgl", LVGL_PORT_TASK_STACK_SIZE, NULL,
											 LVGL_PORT_TASK_PRIORITY, &lvgl_task_handle, core_id); // Create the LVGL task
	if (ret != pdPASS) {
		#ifndef M_SIMULATED
		ESP_LOGE(TAG, "Failed to create LVGL task"); // Log error if task creation fails
		#endif
		return ESP_FAIL; // Return failure
	}

	return ESP_OK; // Return success
}

bool esp_lvgl_port_lock(int timeout_ms)
{
	assert(lvgl_mux && "esp_lvgl_port_init must be called first"); // Ensure the mutex is initialized

	const TickType_t timeout_ticks = (timeout_ms < 0) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms); // Convert timeout to ticks
	return xSemaphoreTakeRecursive(lvgl_mux, timeout_ticks) == pdTRUE; // Try to take the mutex
}

void esp_lvgl_port_unlock(void)
{
	assert(lvgl_mux && "esp_lvgl_port_init must be called first"); // Ensure the mutex is initialized
	xSemaphoreGiveRecursive(lvgl_mux); // Release the mutex
}

bool esp_lvgl_port_notify_rgb_vsync(void)
{
	BaseType_t need_yield = pdFALSE; // Flag to check if a yield is needed
#if LVGL_PORT_FULL_REFRESH && (LVGL_PORT_LCD_RGB_BUFFER_NUMS == 3) && (EXAMPLE_LVGL_PORT_ROTATION_DEGREE == 0)
	if (esp_lvgl_port_rgb_next_buf != esp_lvgl_port_rgb_last_buf) {
		esp_lvgl_port_flush_next_buf = esp_lvgl_port_rgb_last_buf; // Set next buffer for flushing
		esp_lvgl_port_rgb_last_buf = esp_lvgl_port_rgb_next_buf; // Update the last buffer
	}
#elif LVGL_PORT_AVOID_TEAR_ENABLE
	// Notify that the current RGB frame buffer has been transmitted
	xTaskNotifyFromISR(lvgl_task_handle, ULONG_MAX, eNoAction, &need_yield); // Notify the LVGL task
#endif
	return (need_yield == pdTRUE); // Return whether a yield is needed
}

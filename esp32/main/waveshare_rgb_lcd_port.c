/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "waveshare_rgb_lcd_port.h"
#include "touch_irq.h"
#include "i2c.h"

static const char *TAG = "example";

// VSYNC event callback function
IRAM_ATTR static bool rgb_lcd_on_vsync_event(esp_lcd_panel_handle_t panel, const esp_lcd_rgb_panel_event_data_t *edata, void *user_ctx)
{
	return lvgl_port_notify_rgb_vsync();
}


void gpio_init(void)
{
    // Step 1: INT as output during reset/address selection
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pin_bit_mask = 1ULL << GPIO_NUM_4;
    io_conf.mode = GPIO_MODE_OUTPUT;
    gpio_config(&io_conf);
}

// … later, after reset but before lvgl_port_init:
void gpio_reinit_for_irq()
{
    // Step 2: reconfigure INT as input/IRQ
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_NEGEDGE;   // falling edge = touch event
    io_conf.pin_bit_mask = 1ULL << EXAMPLE_PIN_NUM_TOUCH_INT;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);
}

// Reset the touch screen
void waveshare_esp32_s3_touch_reset()
{
	uint8_t write_buf = 0x01;
	i2c_master_write_to_device(I2C_MASTER_NUM, 0x24, &write_buf, 1, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

	// Reset the touch screen. It is recommended to reset the touch screen before using it.
	write_buf = 0x2C;
	i2c_master_write_to_device(I2C_MASTER_NUM, 0x38, &write_buf, 1, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
	esp_rom_delay_us(100 * 1000);
	gpio_set_level(GPIO_INPUT_IO_4, 0);
	esp_rom_delay_us(100 * 1000);
	write_buf = 0x2E;
	i2c_master_write_to_device(I2C_MASTER_NUM, 0x38, &write_buf, 1, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
	esp_rom_delay_us(200 * 1000);
}

// Initialize RGB LCD
esp_err_t waveshare_esp32_s3_rgb_lcd_init(lv_disp_t **disp)
{
	ESP_LOGI(TAG, "Install RGB LCD panel driver"); // Log the start of the RGB LCD panel driver installation
	esp_lcd_panel_handle_t panel_handle = NULL;	// Declare a handle for the LCD panel
	esp_lcd_rgb_panel_config_t panel_config = {
		.clk_src = LCD_CLK_SRC_DEFAULT, // Set the clock source for the panel
		.timings = {
			.pclk_hz = EXAMPLE_LCD_PIXEL_CLOCK_HZ, // Pixel clock frequency
			.h_res = EXAMPLE_LCD_H_RES,			// Horizontal resolution
			.v_res = EXAMPLE_LCD_V_RES,			// Vertical resolution
			.hsync_back_porch = 144, // Horizontal sync pulse width
			.hsync_front_porch = 24, // Horizontal back porch
			.hsync_pulse_width = 136, // Horizontal front porch
			.vsync_back_porch = 23,  // Vertical sync pulse width
			.vsync_front_porch = 3,  // Vertical back porch
			.vsync_pulse_width = 6,  // Vertical front porch
			.flags = {
				.pclk_active_neg = 1, // Active low pixel clock
			},
		},
		.data_width = EXAMPLE_RGB_DATA_WIDTH,					// Data width for RGB
		.bits_per_pixel = EXAMPLE_RGB_BIT_PER_PIXEL,			 // Bits per pixel
		.num_fbs = LVGL_PORT_LCD_RGB_BUFFER_NUMS,				// Number of frame buffers
		.bounce_buffer_size_px = EXAMPLE_RGB_BOUNCE_BUFFER_SIZE, // Bounce buffer size in pixels
		.sram_trans_align = 4,								   // SRAM transaction alignment
		.psram_trans_align = 64,								 // PSRAM transaction alignment
		.hsync_gpio_num = EXAMPLE_LCD_IO_RGB_HSYNC,			  // GPIO number for horizontal sync
		.vsync_gpio_num = EXAMPLE_LCD_IO_RGB_VSYNC,			  // GPIO number for vertical sync
		.de_gpio_num = EXAMPLE_LCD_IO_RGB_DE,					// GPIO number for data enable
		.pclk_gpio_num = EXAMPLE_LCD_IO_RGB_PCLK,				// GPIO number for pixel clock
		.disp_gpio_num = EXAMPLE_LCD_IO_RGB_DISP,				// GPIO number for display
		.data_gpio_nums = {
			EXAMPLE_LCD_IO_RGB_DATA0,
			EXAMPLE_LCD_IO_RGB_DATA1,
			EXAMPLE_LCD_IO_RGB_DATA2,
			EXAMPLE_LCD_IO_RGB_DATA3,
			EXAMPLE_LCD_IO_RGB_DATA4,
			EXAMPLE_LCD_IO_RGB_DATA5,
			EXAMPLE_LCD_IO_RGB_DATA6,
			EXAMPLE_LCD_IO_RGB_DATA7,
			EXAMPLE_LCD_IO_RGB_DATA8,
			EXAMPLE_LCD_IO_RGB_DATA9,
			EXAMPLE_LCD_IO_RGB_DATA10,
			EXAMPLE_LCD_IO_RGB_DATA11,
			EXAMPLE_LCD_IO_RGB_DATA12,
			EXAMPLE_LCD_IO_RGB_DATA13,
			EXAMPLE_LCD_IO_RGB_DATA14,
			EXAMPLE_LCD_IO_RGB_DATA15,
		},
		.flags = {
			.fb_in_psram = 1, // Use PSRAM for framebuffer
		},
	};

	// Create a new RGB panel with the specified configuration
	ESP_ERROR_CHECK(esp_lcd_new_rgb_panel(&panel_config, &panel_handle));

	ESP_LOGI(TAG, "Initialize RGB LCD panel");		 // Log the initialization of the RGB LCD panel
	ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle)); // Initialize the LCD panel

	esp_lcd_touch_handle_t tp_handle = NULL; // Declare a handle for the touch panel
	ESP_LOGI(TAG, "Initialize I2C bus");   // Log the initialization of the I2C bus
	i2c_master_init();					 // Initialize the I2C master
	ESP_LOGI(TAG, "Initialize GPIO");	  // Log GPIO initialization
	gpio_init();						   // Initialize GPIO pins
	ESP_LOGI(TAG, "Initialize Touch LCD"); // Log touch LCD initialization
	waveshare_esp32_s3_touch_reset();	  // Reset the touch panel

	esp_lcd_panel_io_handle_t tp_io_handle = NULL;										  // Declare a handle for touch panel I/O
	const esp_lcd_panel_io_i2c_config_t tp_io_config = ESP_LCD_TOUCH_IO_I2C_GT911_CONFIG(); // Configure I2C for GT911 touch controller

	ESP_LOGI(TAG, "Initialize I2C panel IO");																		  // Log I2C panel I/O initialization
	ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c((esp_lcd_i2c_bus_handle_t)I2C_MASTER_NUM, &tp_io_config, &tp_io_handle)); // Create new I2C panel I/O

	ESP_LOGI(TAG, "Initialize touch controller GT911"); // Log touch controller initialization
	const esp_lcd_touch_config_t tp_cfg = {
		.x_max = EXAMPLE_LCD_H_RES,				// Set maximum X coordinate
		.y_max = EXAMPLE_LCD_V_RES,				// Set maximum Y coordinate
		.rst_gpio_num = EXAMPLE_PIN_NUM_TOUCH_RST, // GPIO number for reset
		.int_gpio_num = EXAMPLE_PIN_NUM_TOUCH_INT, // GPIO number for interrupt
		.levels = {
			.reset = 0,	 // Reset level
			.interrupt = 0, // Interrupt level
		},
		.flags = {
			.swap_xy = 0,  // No swap of X and Y
			.mirror_x = 0, // No mirroring of X
			.mirror_y = 0, // No mirroring of Y
		},
	};
	
	gpio_reinit_for_irq();
	ESP_ERROR_CHECK(esp_lcd_touch_new_i2c_gt911(tp_io_handle, &tp_cfg, &tp_handle)); // Create new I2C GT911 touch controller

	ESP_ERROR_CHECK(lvgl_port_init(panel_handle, tp_handle, disp)); // Initialize LVGL with the panel and touch handles

	// Register callbacks for RGB panel events
	esp_lcd_rgb_panel_event_callbacks_t cbs = {
#if EXAMPLE_RGB_BOUNCE_BUFFER_SIZE > 0
		.on_bounce_frame_finish = rgb_lcd_on_vsync_event, // Callback for bounce frame finish
#else
		.on_vsync = rgb_lcd_on_vsync_event, // Callback for vertical sync
#endif
	};
	ESP_ERROR_CHECK(esp_lcd_rgb_panel_register_event_callbacks(panel_handle, &cbs, NULL)); // Register event callbacks
	
	#ifdef TOUCH_PANEL_USE_INTERRUPTS
	init_touch_task(tp_handle);
	#endif
	
	return ESP_OK; // Return success
}

/******************************* Turn on the screen backlight **************************************/
esp_err_t wavesahre_rgb_lcd_bl_on()
{
	// Configure CH422G to output mode
	uint8_t write_buf = 0x01;
	i2c_master_write_to_device(I2C_MASTER_NUM, 0x24, &write_buf, 1, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

	// Pull the backlight pin high to light the screen backlight
	write_buf = 0x1E;
	i2c_master_write_to_device(I2C_MASTER_NUM, 0x38, &write_buf, 1, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
	return ESP_OK;
}

/******************************* Turn off the screen backlight **************************************/
esp_err_t wavesahre_rgb_lcd_bl_off()
{
	// Configure CH422G to output mode
	uint8_t write_buf = 0x01;
	i2c_master_write_to_device(I2C_MASTER_NUM, 0x24, &write_buf, 1, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

	// Turn off the screen backlight by pulling the backlight pin low
	write_buf = 0x1A;
	i2c_master_write_to_device(I2C_MASTER_NUM, 0x38, &write_buf, 1, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
	return ESP_OK;
}

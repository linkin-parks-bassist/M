/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "waveshare_rgb_lcd_port.h"
#include "m_int_touch_irq.h"
#include "m_int_i2c.h"

static const char *TAG = "example";

/* VSYNC event callback (RGB panel) – IRAM, as required by esp_lcd in ISR context.
 * See esp-idf 5.3 LCD RGB Panel docs for callback signature. */
IRAM_ATTR static bool rgb_lcd_on_vsync_event(esp_lcd_panel_handle_t panel,
                                             const esp_lcd_rgb_panel_event_data_t *edata,
                                             void *user_ctx)
{
    (void)panel;
    (void)edata;
    (void)user_ctx;
    return lvgl_port_notify_rgb_vsync();
}

/* -------------------------------------------------------------------------- */
/*  Touch reset / CH422G handling                                             */
/* -------------------------------------------------------------------------- */

/* Reset the touch controller.
 *
 * This follows the Waveshare reference sequence for the CH422G IO expander:
 *  - write 0x01 to 0x24 to put CH422G into output mode
 *  - pulse the TP_RST line via writes to 0x38
 *
 * The GT911 datasheet requires a reset pulse on RST and a stable INT level
 * during power-on to select the I²C address, but on this board TP_RST is
 * controlled through CH422G and the esp_lcd_touch_gt911 driver talks to the
 * GT911 at its default address, so we do not need to manipulate the INT
 * GPIO here.:contentReference[oaicite:8]{index=8}
 */
void waveshare_esp32_s3_touch_reset(void)
{
    uint8_t write_buf = 0x01;
    /* CH422G: configure as output mode (datasheet / Waveshare demo) */
    i2c_master_write_to_device(I2C_MASTER_NUM, 0x24, &write_buf, 1,
                               I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

    /* Pulse TP_RST via CH422G.
     * Note: some users change 0x2C/0x2E to 0x0C/0x0E depending on board
     * wiring; keep your board-specific values here.:contentReference[oaicite:9]{index=9}
     */
    write_buf = 0x2C;
    i2c_master_write_to_device(I2C_MASTER_NUM, 0x38, &write_buf, 1,
                               I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    esp_rom_delay_us(100 * 1000);

    /* On this design, GT911 INT is not driven here; it is left to the
     * esp_lcd_touch driver which will configure EXAMPLE_PIN_NUM_TOUCH_INT
     * as an input with the proper pull-ups and interrupt polarity.:contentReference[oaicite:10]{index=10} */

    write_buf = 0x2E;
    i2c_master_write_to_device(I2C_MASTER_NUM, 0x38, &write_buf, 1,
                               I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    esp_rom_delay_us(200 * 1000);
}

/* -------------------------------------------------------------------------- */
/*  LCD + touch init                                                          */
/* -------------------------------------------------------------------------- */

esp_err_t waveshare_esp32_s3_rgb_lcd_init(lv_disp_t **disp)
{
    esp_lcd_panel_handle_t panel_handle = NULL;

    ESP_LOGI(TAG, "Install RGB LCD panel driver");

    const esp_lcd_rgb_panel_config_t panel_config = {
        .clk_src = LCD_CLK_SRC_DEFAULT,
        .timings = {
            .pclk_hz         = EXAMPLE_LCD_PIXEL_CLOCK_HZ,
            .h_res           = EXAMPLE_LCD_H_RES,
            .v_res           = EXAMPLE_LCD_V_RES,
            .hsync_back_porch  = 144,
            .hsync_front_porch = 24,
            .hsync_pulse_width = 136,
            .vsync_back_porch  = 23,
            .vsync_front_porch = 3,
            .vsync_pulse_width = 6,
            .flags = {
                .pclk_active_neg = 1,
            },
        },
        .data_width           = EXAMPLE_RGB_DATA_WIDTH,
        .bits_per_pixel       = EXAMPLE_RGB_BIT_PER_PIXEL,
        .num_fbs              = LVGL_PORT_LCD_RGB_BUFFER_NUMS,
        .bounce_buffer_size_px = EXAMPLE_RGB_BOUNCE_BUFFER_SIZE,
        .sram_trans_align     = 4,
        .psram_trans_align    = 64,
        .hsync_gpio_num       = EXAMPLE_LCD_IO_RGB_HSYNC,
        .vsync_gpio_num       = EXAMPLE_LCD_IO_RGB_VSYNC,
        .de_gpio_num          = EXAMPLE_LCD_IO_RGB_DE,
        .pclk_gpio_num        = EXAMPLE_LCD_IO_RGB_PCLK,
        .disp_gpio_num        = EXAMPLE_LCD_IO_RGB_DISP,
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
            .fb_in_psram = 1,
        },
    };

    ESP_ERROR_CHECK(esp_lcd_new_rgb_panel(&panel_config, &panel_handle));

    ESP_LOGI(TAG, "Initialize RGB LCD panel");
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));

    /* ----------------- Touch (GT911 via esp_lcd_touch) ----------------- */

    esp_lcd_touch_handle_t tp_handle = NULL;

    ESP_LOGI(TAG, "Initialize I2C bus for touch + CH422G");
    i2c_master_init();

    ESP_LOGI(TAG, "Reset GT911 through CH422G");
    waveshare_esp32_s3_touch_reset();

    ESP_LOGI(TAG, "Create I2C panel IO for GT911");
    esp_lcd_panel_io_handle_t tp_io_handle = NULL;
    const esp_lcd_panel_io_i2c_config_t tp_io_config =
        ESP_LCD_TOUCH_IO_I2C_GT911_CONFIG();

    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c(
        (esp_lcd_i2c_bus_handle_t)I2C_MASTER_NUM,
        &tp_io_config,
        &tp_io_handle));

    ESP_LOGI(TAG, "Initialize touch controller GT911");

    const esp_lcd_touch_config_t tp_cfg = {
        .x_max       = EXAMPLE_LCD_H_RES,
        .y_max       = EXAMPLE_LCD_V_RES,
        .rst_gpio_num = EXAMPLE_PIN_NUM_TOUCH_RST,  /* usually -1 on this board */
        .int_gpio_num = EXAMPLE_PIN_NUM_TOUCH_INT,  /* GT911 INT → esp_lcd_touch owns it */
        .levels = {
            .reset     = 0,  /* active-low reset if used */
            .interrupt = 0,  /* GT911 INT is active low per datasheet:contentReference[oaicite:11]{index=11} */
        },
        .flags = {
            .swap_xy = 0,
            .mirror_x = 0,
            .mirror_y = 0,
        },
        /* We leave interrupt_callback = NULL; esp_lcd_touch will either poll
         * or set up its own internal ISR based on int_gpio_num. If you want
         * to wake a task from the GT911 IRQ, you can set .interrupt_callback
         * here instead of manually reconfiguring the GPIO.:contentReference[oaicite:12]{index=12} */
    };

    ESP_ERROR_CHECK(esp_lcd_touch_new_i2c_gt911(tp_io_handle, &tp_cfg, &tp_handle));

    ESP_ERROR_CHECK(lvgl_port_init(panel_handle, tp_handle, disp));

    /* RGB VSYNC / bounce callbacks */
    esp_lcd_rgb_panel_event_callbacks_t cbs = {
    #if EXAMPLE_RGB_BOUNCE_BUFFER_SIZE > 0
        .on_bounce_frame_finish = rgb_lcd_on_vsync_event,
    #else
        .on_vsync = rgb_lcd_on_vsync_event,
    #endif
    };
    ESP_ERROR_CHECK(esp_lcd_rgb_panel_register_event_callbacks(panel_handle, &cbs, NULL));

#ifdef TOUCH_PANEL_USE_INTERRUPTS
    /* If your m_int_touch_irq implementation expects to be called from the
     * esp_lcd_touch interrupt callback, wire it through tp_cfg.interrupt_callback
     * instead of reconfiguring the INT GPIO here. */
    init_touch_task(tp_handle);
#endif

    return ESP_OK;
}

/* -------------------------------------------------------------------------- */
/*  Backlight control via CH422G                                              */
/* -------------------------------------------------------------------------- */

esp_err_t wavesahre_rgb_lcd_bl_on(void)
{
    uint8_t write_buf = 0x01;
    i2c_master_write_to_device(I2C_MASTER_NUM, 0x24, &write_buf, 1,
                               I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

    write_buf = 0x1E;
    i2c_master_write_to_device(I2C_MASTER_NUM, 0x38, &write_buf, 1,
                               I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    return ESP_OK;
}

esp_err_t wavesahre_rgb_lcd_bl_off(void)
{
    uint8_t write_buf = 0x01;
    i2c_master_write_to_device(I2C_MASTER_NUM, 0x24, &write_buf, 1,
                               I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

    write_buf = 0x1A;
    i2c_master_write_to_device(I2C_MASTER_NUM, 0x38, &write_buf, 1,
                               I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    return ESP_OK;
}

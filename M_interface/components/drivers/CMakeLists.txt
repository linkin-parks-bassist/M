idf_component_register(SRCS "m_int_sgtl5000.c"
							"m_int_fpga.c"
							"m_int_sd.c"
							"m_int_footswitch.c"
							"waveshare_dsi_touch_5_a.c"
							"m_int_touch_irq.c"
							"m_int_i2c.c"
					REQUIRES
							driver
							esp_lcd_touch_gt911
							esp32_p4_nano
							fatfs
							core
					INCLUDE_DIRS "." "../../../shared" "../../main" "../" "../ui" "../core")

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#include "bsp/esp32_p4_nano.h"

#include "esp_task_wdt.h"

#include "m_int.h"

m_context global_cxt;

void app_main()
{
	srand(time(0));
	
	esp_task_wdt_deinit();
	
	#ifdef USE_DISPLAY
	lv_disp_t *disp;
	waveshare_dsi_touch_5_a_init(&disp);
	
	init_representation_updater();
	#endif
	
	m_init_context(&global_cxt);
	
	#ifdef USE_SGTL5000
	xTaskCreate(
		m_int_sgtl5000_init,
		NULL,
		4096,
		NULL,
		8,
		NULL
	);
	#endif
	
	#ifdef USE_FPGA
	xTaskCreate(
		m_fpga_comms_task,
		NULL,
		4096,
		NULL,
		8,
		NULL
	);
	#else
	init_m_int_msg_queue();
	begin_m_int_comms();
	#endif
	
	#ifdef USE_SDCARD
	printf("DOING THE SD CARD STUFF\n");
	init_sd_card();
	m_init_directories();
	
	if (load_settings_from_file(&global_cxt.settings, SETTINGS_FNAME) == ERR_FOPEN_FAIL)
	{
		save_settings_to_file(&global_cxt.settings, SETTINGS_FNAME);
	}
	
	load_saved_profiles(&global_cxt);
	
	context_print_profiles(&global_cxt);
	
	load_saved_sequences(&global_cxt);
	
	send_all_profiles_to_teensy(&global_cxt);
	send_settings(&global_cxt.settings);
	
	init_settings_save_task();
	#endif
	
	#ifdef M_SIMULATED
    while (1)
    {
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
	#else
	#ifdef USE_DISPLAY
	if (bsp_display_lock(0))
	{
		#ifdef M_ENABLE_LV_LOGGING
		lv_log_register_print_cb(m_int_lv_log_cb);
		m_int_log_init();
		#endif
		m_create_ui(disp);
		#ifdef M_PRINT_MEMORY_REPORT
		lv_timer_create(print_memory_report, 2000, NULL);
		#endif
		bsp_display_unlock();
	}
	#endif
	#endif
	
	init_footswitch_task();
	
	while (1);
}


#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#include "esp_task_wdt.h"

#include "m_int.h"

m_context global_cxt;

void app_main()
{
	srand(time(0));
	
	esp_task_wdt_deinit();
	
	lv_disp_t *disp;
	init_display(&disp);
	init_representation_updater();
	
	m_init_context(&global_cxt);
	
	init_m_int_msg_queue();
	begin_m_int_comms();
	
	#ifdef USE_SDCARD
	printf("DOING THE SD CARD STUFF\n");
	init_sd_card();
	
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
	
	init_footswitch_task();
}


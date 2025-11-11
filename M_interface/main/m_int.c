#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#include "esp_task_wdt.h"

#include "m_int.h"

m_int_context global_cxt;

//#define ERASE_SD_CARD

void app_main()
{
	srand(time(0));
	
	esp_task_wdt_deinit();
	
	lv_disp_t *disp;
	init_display(&disp);
	
	init_m_int_context(&global_cxt);
	init_ui_context(&global_cxt.ui_cxt);
	init_m_int_msg_queue();
	begin_m_int_comms();
	init_sd_card();
	
	#ifdef ERASE_SD_CARD
	erase_sd_card();
	#endif
	
	if (load_settings_from_file(&global_cxt.settings, SETTINGS_FNAME) == ERR_FOPEN_FAIL)
	{
		save_settings_to_file(&global_cxt.settings, SETTINGS_FNAME);
	}
	
	load_saved_profiles(&global_cxt);
	resolve_default_profile(&global_cxt);
	
	context_print_profiles(&global_cxt);
	
	if (global_cxt.default_profile)
	{
		set_active_profile(global_cxt.default_profile);
		set_working_profile(global_cxt.default_profile);
	}
	else
	{
		printf("There is no default profile!\n");
		context_no_default_profile(&global_cxt);
		
		context_print_profiles(&global_cxt);
	}
	
	send_all_profiles_to_teensy(&global_cxt);
	send_settings(&global_cxt.settings);
	
	init_settings_save_task();
	
	#ifdef M_SIMULATED
    while (1)
    {
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
	#else
	if (lvgl_port_lock(-1))
	{
		#ifdef M_ENABLE_LV_LOGGING
		lv_log_register_print_cb(m_int_lv_log_cb);
		m_int_log_init();
		#endif
		create_ui(disp);
		#ifdef M_PRINT_MEMORY_REPORT
		lv_timer_create(print_memory_report, 2000, NULL);
		#endif
		lvgl_port_unlock();
	}
	#endif
	
	init_footswitch_poll_task();
}


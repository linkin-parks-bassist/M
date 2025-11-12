#include <Wire.h>
#include "m_eng.h"

static const char *FNAME = "m_eng.cpp";

static int LED = 1;
#define LED_BLINK_MILLIS 	50
//#define DEBUG_PRINTS
#define DEBUG_PRINT_MILLIS 1000
#define PRINT_LOG
//#define PRINT_PROFILER
#define LOG_PRINT_MILLIS 10
#define PROFILER_PRINT_MILLIS 1000

#define SCHEDULED_MAINTAINANCE_MILLIS 100

//#define SGTL5000_CHECK 
#define SGTL5000_CHECK_PERIOD 100
#define SCHEDULED_MAINTAINANCE

int main()
{
	#ifdef M_ENG_PROFILER
	void m_eng_init_profiler();
	#endif
	
	Serial.begin(115200);
	delay(500);
	
	if (CrashReport)
	{
		delay(4000);
		Serial.print(CrashReport);
		exit(0);
	}
	
	m_eng_printf("Hello!\n");
		
	m_eng_printf("Initialising memory pools... ");
	init_mem_pools();
	m_eng_printf("done.\n");
	
	m_eng_printf("Initialising context struct... ");
	init_m_eng_context(&global_cxt);
	
	m_eng_printf("done.\n");
	
	
	init_i2s_dma();
	
		
	m_eng_printf("Initialising SGTL5000... ");
	
	sgtl5000_start();
	
	m_eng_printf("done.\n");
	
	
	m_eng_printf("Initialising esp32 link... ");
	init_esp32_link();
	m_eng_printf("done.\n");
		
	m_eng_printf("Initialisation complete. Entering main loop...\n");

	
	while (1)
	{
		#ifdef DEBUG_PRINTS
		static int last_debug_print = millis();
		#endif
		#ifdef PRINT_LOG
		static int last_log_print = millis();
		#endif
		#ifdef PRINT_PROFILER
		static int last_profiler_print = millis();
		#endif
		#ifdef SCHEDULED_MAINTAINANCE
		static int last_scheduled_maintainance = millis();
		#endif
		static int last_led_transition = millis();
		int time = millis();
		
		if (time - last_led_transition >= LED_BLINK_MILLIS)
		{
			digitalWrite(13, LED);
			LED = 1 - LED;
			last_led_transition = millis();
		}
		
		#ifdef PRINT_LOG
		if (time - last_log_print >= LOG_PRINT_MILLIS)
		{
			#ifdef M_ENG_LOG_LEVEL
			m_eng_print_flush_log();
			#endif
			last_log_print = millis();
		}
		#endif
		
		#ifdef PRINT_PROFILER
		if (time - last_profiler_print >= PROFILER_PRINT_MILLIS)
		{
			#ifdef M_ENG_PROFILER
			m_eng_profiler_print();
			#endif
			last_profiler_print = millis();
		}
		#endif
		
		#ifdef DEBUG_PRINTS
		if (time - last_debug_print > DEBUG_PRINT_MILLIS)
		{
			full_debug_print(&global_cxt);
			last_debug_print = millis();
		}
		#endif
		
		#ifdef SCHEDULED_MAINTAINANCE
		if (time - last_scheduled_maintainance > SCHEDULED_MAINTAINANCE_MILLIS)
		{
			cxt_run_scheduled_maintainance(&global_cxt);
			last_scheduled_maintainance = millis();
		}
		#endif
		
		#ifdef SGTL5000_CHECK
		if (!sgtl5000_healthy())
		{
			m_eng_printf("SGTL5000 died!\n");
			sgtl5000_soft_reboot();
		}
		#endif
		
		profile_update(&global_cxt.profiles[global_cxt.active_profile]);
		esp32_message_check_handle();
		
		if (((m_eng_amplifier_str*)global_cxt.output_amp.data_struct)->mode.value == M_ENG_AMPLIFIER_LINEAR && ((m_eng_amplifier_str*)global_cxt.output_amp.data_struct)->gain.value == 1.0)
		{
			((m_eng_amplifier_str*)global_cxt.output_amp.data_struct)->mode.value 	  = M_ENG_AMPLIFIER_DB;
			((m_eng_amplifier_str*)global_cxt.output_amp.data_struct)->mode.updated   = 1;
			((m_eng_amplifier_str*)global_cxt.output_amp.data_struct)->gain.value 	  = 0.0;
			((m_eng_amplifier_str*)global_cxt.output_amp.data_struct)->gain.new_value = 0.0;
			((m_eng_amplifier_str*)global_cxt.output_amp.data_struct)->gain.old_value = 0.0;
			((m_eng_amplifier_str*)global_cxt.output_amp.data_struct)->gain.updated   = 1;
		}
		
		delay(1);
	}
}

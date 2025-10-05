#include <Wire.h>
#include <ST7796_t3.h>
#include <TeensyThreads.h>
#include <SPI.h>

#include "src/tm.h"

tm_pipeline pipelines[4];

tm_audio_transformer distortion;
tm_audio_transformer compressor;

tm_context global_cxt;


void setup()
{
	Serial.begin(115200);
	delay(1000);
	
	if (CrashReport)
	{
		delay(4000);
		Serial.print(CrashReport);
		exit(0);
	}
	
	tm_printf("Hello!\n");
	
	tm_printf("sizeof(tm_context) = %d\n", sizeof(tm_context));
	
	/*global_cxt = malloc(sizeof(tm_context));
	if (!global_cxt)
	{
		tm_printf("Failed to allocate global_cxt struct! Abort!\n");
	}*/
	
	tm_printf("Initialising memory pools... ");
	init_metm_pools();
	tm_printf("done.\n");
	
	tm_printf("Initialising context struct... ");
	init_tm_context(&global_cxt);
	tm_printf("done.\n");
	
	init_i2s();
	
	tm_printf("Initialising SGTL5000... ");
	sgtl5000_enable();
	sgtl5000_line_in_level(4);
	sgtl5000_volume(0.5);
	tm_printf("done.\n");
	
	
	
	//tm_context_new_profile(&global_cxt);
	
	//set_active_pipeline(&global_cxt.profiles[1].pipeline);
	
	//init_distortion(&distortion, INPUT_NODE_COORD, (vec2i){0, 0}, DISTORTION_CLIP, 4.0, 0.1);
	//pipeline_add_transformer(&global_cxt.profiles[1].pipeline, &distortion);
	
	//init_compressor(&compressor, (vec2i){0, 0}, OUTPUT_NODE_COORD, 6.0, -24, 0.01, 0.01);
	//pipeline_add_transformer(&global_cxt.profiles[1].pipeline, &compressor);
	
	tm_printf("Initialising esp32 link... ");
	init_esp32_link();
	tm_printf("done.\n");
	
	tm_printf("Initialisation complete. Entering main loop...\n");
}

int LED = 1;
#define LED_BLINK_MILLIS 	50
#define DEBUG_PRINTS
#define DEBUG_PRINT_MILLIS 2000

void loop()
{
	#ifdef DEBUG_PRINTS
	static int last_debug_print = millis();
	#endif
	static int last_led_transition = millis();
	int time = millis();
	
	if (time - last_led_transition > LED_BLINK_MILLIS)
	{
		digitalWrite(13, LED);
		LED = 1 - LED;
		last_led_transition = millis();
	}
	
	#ifdef DEBUG_PRINTS
	if (time - last_debug_print > DEBUG_PRINT_MILLIS)
	{
		print_context_info(&global_cxt, -1);
		last_debug_print = millis();
	}
	#endif
	
	esp32_message_check_handle();
	
	if (global_cxt.unconfigured_pipeline)
	{
		int ret_val;
		tm_AudioNoInterrupts();
		ret_val = pipeline_reconfigure(global_cxt.unconfigured_pipeline);
		tm_AudioInterrupts();
		global_cxt.unconfigured_pipeline = NULL;
		
		if (ret_val)
		{
			tm_printf("ERROR configuring pipeline! returned value: %d\n", ret_val);
		}
		else
		{
			tm_printf("Sucessfully configured pipeline\n");
		}
	}
	delay(1);
}

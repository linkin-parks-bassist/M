#include <Arduino.h>
#include <Audio.h>
#include "M.h"

int m_audio_context::init()
{
	//init_audio(&audio_cxt);
	AudioMemory(160);

	// Audio shield setup
	shield.enable();
	shield.inputSelect(AUDIO_INPUT_LINEIN);
	shield.volume(0.75);
	shield.lineInLevel(5); // 0–15, higher = more sensitive
	
	line_out_connection = new AudioConnection(line_in, 0, line_out, 0);
	monitor_connection 	= new AudioConnection(line_in, peak_analyzer);
	
	return NO_ERROR;
}

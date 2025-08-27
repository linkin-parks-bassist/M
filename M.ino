#include <Wire.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <stdio.h>

#include "src/M.h"

m_context cxt;

void setup()
{
	Wire.begin();
	Serial.begin(9600);
	
	delay(2000);
	
	m_printf("Initialising...\n");
	
	int ret_val = init_audio_context(&cxt.audio_cxt);
	
	m_printf("Audio initialisation completed with return code %d\n", ret_val);
}

void loop()
{
	
}

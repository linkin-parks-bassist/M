#include <Wire.h>

#include "src/M.h"


// GUItool: begin automatically generated code
m_audio_connection 			patchCord1;
m_AudioControlSGTL5000     	sgtl5000_1;     //xy=585,488
// GUItool: end automatically generated code

void setup()
{
	delay(1000);
	
	m_printf("Initialising i2s...\n");
	init_i2s();
	
	sgtl5000_1.i2c_addr = 0x0A;
	
	m_AudioMemory(20);
	
	m_printf("Initialising sgtl5000...\n");
	sgtl5000_1.enable();
	sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
	sgtl5000_1.lineInLevel(2);
	sgtl5000_1.volume(0.5); 
	m_printf("Initialisation complete.\n");
}

void loop()
{
	
}

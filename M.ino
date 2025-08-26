#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SerialFlash.h>

#include "src/M.h"

m_context cxt;

band_splitter splitter(200.0);
audio_mixer mixer(0.5);
arctan_distortion dist(5.0);

AudioAnalyzePeak p;
AudioConnection pc(*dist.output_stream(), p);

void setup()
{

	Serial.begin(9600);
	if (CrashReport)
		Serial.print(CrashReport);
	
	//delay(4000);
	digitalWrite(13, HIGH);
	
	
	
	Serial.println("Hi :)");
	
	cxt.audio_cxt.init();
	cxt.audio_cxt.line_out_connection->disconnect();
	delete cxt.audio_cxt.line_out_connection;
	
	Serial.println("Connection 1");
	splitter.connect_input(cxt.audio_cxt.line_in, 0);
	Serial.println("Connection 2");
	splitter.connect_input(cxt.audio_cxt.line_in, 1);
	
	Serial.println("Connection 3");
	dist.connect_input(*splitter.output_stream(1), 0);
	
	Serial.println("Connection 4");
	mixer.connect_input(*splitter.output_stream(0), 0);
	Serial.println("Connection 5");
	mixer.connect_input(*dist.output_stream(0), 1);
	
	cxt.audio_cxt.line_out_connection = new AudioConnection(*mixer.output_stream(),  cxt.audio_cxt.line_out);
	
	Serial.println("Setup complete");
}

void loop()
{
	dist.refresh();
	
	float level;
	
	Serial.print("Memory used: ");
	Serial.println(AudioMemoryUsage());
	Serial.print("Memory max: ");
	Serial.println(AudioMemoryUsageMax());
	
	if (p.available())
	{
		level = p.read();
		Serial.print("Signal level: ");
		Serial.println(level, 4);
	}
}

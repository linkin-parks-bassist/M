#include <Audio.h>
#include "M.h"

AudioStream *normaliser_denormaliser::input_stream(int n)
{
	if (n == 0) return &normaliser;
	if (n == 1) return &denormaliser;
	if (n == 2) return &peak;
	else 		return NULL;
}

AudioStream *normaliser_denormaliser::output_stream(int n)
{
	if (n != 0) return NULL;
	
	return &denormaliser;
}

void normaliser_denormaliser::connect_input(AudioStream &stream, int n, int stream_out_channel, int stream_in_channel)
{
	if (n_inputs <= (unsigned int)n)
		return;
	
	if (inputs[n])
	{
		inputs[n]->disconnect();
		delete inputs[n];
	}
	
	AudioStream *is = input_stream(n);
	
	if (!is)
	{
		Serial.println("NULL INPUT STREAM");
		return;
	}
	
	inputs[n] = new AudioConnection(stream, stream_out_channel, *is, stream_in_channel);
	
	//if (n == 0)
	//	this->connect_input(normaliser, 2);
}

void normaliser_denormaliser::refresh()
{
	//Serial.println("nd.refresh()");
	/*if (!peak_connection->connect())
	{
		if (Serial.availableForWrite())
			Serial.println("Peak connection failed!");
		else
			Serial.flush();
	}*/
	if (peak.available())
	{
		if (Serial.availableForWrite())
			Serial.println("yay");
		loudness = peak.read();
		gain = loudness * 0.5 + gain * 0.5;
		normaliser.gain(1.0 / max(gain, 0.01));
		denormaliser.gain(gain);
		//Serial.print("Normaliser gain: ");
		Serial.print(1.0 / max(gain, 0.01), 4);
		Serial.print(", denormaliser gain: ");
		//Serial.println(gain, 4);
		Serial.flush();
	}
	//Serial.println("nd.refresh() finished");
}

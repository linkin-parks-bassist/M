#include <Arduino.h>
#include <Audio.h>
#include "M.h"

dsp_block::~dsp_block()
{
	for (unsigned int i = 0; i < n_inputs; i++)
	{
		if (inputs[i])
		{
			inputs[i]->disconnect();
			delete inputs[i];
		}
	}
}

AudioStream *dsp_block::input_stream(int n)
{
	return NULL;
}

AudioStream *dsp_block::output_stream(int n)
{
	return NULL;
}

void dsp_block::connect_input(AudioStream &stream, int n, int stream_out_channel, int stream_in_channel)
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
}

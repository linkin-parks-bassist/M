#include <Audio.h>
#include "M.h"

distortion_block::distortion_block()
{
	normaliser_to_waveshaper = new AudioConnection(nd.normaliser, waveshaper);
}

AudioStream *distortion_block::input_stream(int n)
{
	return &waveshaper;
	
	if (n == 0)
		return nd.input_stream();
	else
		return NULL;
}

AudioStream *distortion_block::output_stream(int n)
{
	return &waveshaper;
	
	if (n != 0)
		return NULL;
	else
		return nd.output_stream();
}

/*void distortion_block::connect_input(AudioStream &stream, int n, int stream_out_channel, int stream_in_channel)
{
	if (n != 0) return;
	
	nd.connect_input(stream, 		0);
	nd.connect_input(waveshaper, 	1);
}*/

void distortion_block::refresh()
{
	//Serial.println("dist.refresh()");
	nd.refresh();
	//Serial.println("dist.refresh() finished");
}

void distortion_block::shape(float *table)
{
	if (!table)
		return;
	
	waveshaper.shape(table, DISTORTION_TABLE_LENGTH);
}

arctan_distortion::arctan_distortion(float c) : strength {c}
{
	update_table();
}

void arctan_distortion::update_table()
{
	float table[DISTORTION_TABLE_LENGTH];
	
	for (int i = 0 ; i < DISTORTION_TABLE_LENGTH; i++)
		table[i] = atan(strength * (2.0 * ((float)i / (float)DISTORTION_TABLE_LENGTH)) - 1);
	
	shape(table);
}

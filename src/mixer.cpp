#include <Audio.h>
#include "M.h"


AudioStream *audio_mixer::input_stream(int n)
{
	if (n == 0 || n == 1) return &mixer;
	else return NULL;
}

AudioStream *audio_mixer::output_stream(int n)
{
	if (n) return NULL;
	
	return &mixer;
}

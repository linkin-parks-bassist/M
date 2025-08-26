#include <Audio.h>

#include "M.h"

AudioStream *band_splitter::input_stream(int n)
{
	if (n == 0)
		return &low_in;
	else if (n == 1)
		return &high_in;
	else
		return NULL;
}

AudioStream *band_splitter::output_stream(int n)
{
	if (n == 0)
		return &low_out;
	else if (n == 1)
		return &high_out;
	else
		return NULL;
}

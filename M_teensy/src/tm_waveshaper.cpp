#include "tm.h"

float identity_function(float x){return x;}

int init_waveshaper_str(tm_waveshaper_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	str->local_amplitude = 0.0;
	
	return NO_ERROR;
}

int calc_waveshaper(void *data_struct, float *dest, float *src, int n_samples)
{
	if (!data_struct || !dest || !src)
		return ERR_NULL_PTR;
	
	float *in_buffer  =  src ?  src : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	tm_waveshaper_str *str = (tm_waveshaper_str*)data_struct;
	
	if (!str->shape)
		return ERR_BAD_ARGS;
	
	float local_amplitude = str->local_amplitude;
	
	tm_printf("Waveshaper. coefficient = %f, local amplitude = %f. in_buffer[0] = %f\n", str->coefficient.value, local_amplitude, in_buffer[0]);
	
	// Actual computation loop
	for (int i = 0; i < n_samples; i++)
	{
		if (fabs(in_buffer[i]) > local_amplitude)
			local_amplitude = fabs(in_buffer[i]);//WAVESHAPER_ENVELOPE_ATTACK * local_amplitude + (1.0 - WAVESHAPER_ENVELOPE_ATTACK) * fabs(in_buffer[i]);
		else
			local_amplitude = WAVESHAPER_ENVELOPE_RELEASE * local_amplitude + (1.0 - WAVESHAPER_ENVELOPE_RELEASE) * fabs(in_buffer[i]);
		
		if (local_amplitude < 1e-30f)
			out_buffer[i] = 0.0;
		else
			out_buffer[i] = local_amplitude *  str->shape(str->coefficient.value * (in_buffer[i] * (1.0 / local_amplitude)));
	}
	
	str->local_amplitude = local_amplitude;
	
	return NO_ERROR;
}



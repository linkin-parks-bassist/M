#include "tm.h"

static const char *FNAME = "tm_adaptive_waveshaper.c";

int init_adaptive_waveshaper_str(tm_adaptive_waveshaper_str *str)
{
	FUNCTION_START();

	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	str->local_amplitude = 0.0;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int calc_adaptive_waveshaper(void *data_struct, float *dest, float *src, int n_samples)
{
	FUNCTION_START();

	if (!data_struct || !dest || !src)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	float *in_buffer  =  src ?  src : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	tm_adaptive_waveshaper_str *str = (tm_adaptive_waveshaper_str*)data_struct;
	
	if (!str->shape)
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	float local_amplitude = str->local_amplitude;
	
	float *local_amplitudes = allocate_buffer();
	float max_local_amplitude = 0.0;
	
	if (!local_amplitudes)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}
	
	for (int i = 0; i < n_samples; i++)
	{
		if (fabs(in_buffer[i]) > local_amplitude)
			local_amplitudes[i] = /*WAVESHAPER_ENVELOPE_ATTACK * ((i == 0) ? local_amplitude : local_amplitudes[i-1]) + (1.0 - WAVESHAPER_ENVELOPE_ATTACK) **/ fabsf(in_buffer[i]);
		else
			local_amplitudes[i] = WAVESHAPER_ENVELOPE_RELEASE * ((i == 0) ? local_amplitude : local_amplitudes[i-1]) + (1.0 - WAVESHAPER_ENVELOPE_RELEASE) * fabsf(in_buffer[i]);
		
		if (local_amplitudes[i] > max_local_amplitude)
			max_local_amplitude = local_amplitudes[i];
	}
	
	if (max_local_amplitude < 0.00000001)
	{
		for (int i = 0; i < n_samples; i++)
			out_buffer[i] = 0.0;
		
		str->local_amplitude = local_amplitudes[n_samples - 1];
		release_buffer(local_amplitudes);
		RETURN_ERR_CODE(NO_ERROR);
	}
	
	// Actual computation loop
	for (int i = 0; i < n_samples; i++)
	{
		if (local_amplitude < 1e-30f)
			out_buffer[i] = 0.0;
		else
			out_buffer[i] = local_amplitudes[i] *  str->shape(str->coefficient.value * (in_buffer[i] * (1.0 / local_amplitudes[i])));
	}
	
	str->local_amplitude = local_amplitudes[n_samples - 1];
	release_buffer(local_amplitudes);
	
	RETURN_ERR_CODE(NO_ERROR);
}



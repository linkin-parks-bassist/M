#include "tm.h"

static const char *FNAME = "tm_envelope.c";

int init_envelope_str(tm_envelope_str *str)
{
	FUNCTION_START();

	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	str->e = 0.0;
	
	init_band_pass_filter_str(&str->filter);
	reconfigure_band_pass_filter(&str->filter);
	
	RETURN_ERR_CODE(NO_ERROR);
}

int reconfigure_envelope(void *data_struct)
{
	FUNCTION_START();

	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	tm_envelope_str *str = (tm_envelope_str*)data_struct;
	
	str->alpha = expf(-1.0 / MS_TO_SAMPLES(str->speed.value));
	
	RETURN_ERR_CODE(NO_ERROR);
}

int calc_envelope(void *data_struct, float *dest, float *src, int n_samples)
{
	FUNCTION_START();

	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	tm_envelope_str *str = (tm_envelope_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	float e = str->e;
	float u;
	float cutoff;

	int chunk_size = floorf(AUDIO_BLOCK_SAMPLES * (1.0 - str->smoothness.value));
	int chunk_samples;
	
	if (chunk_size < 1)
		chunk_size = 1;

	int i = 0;
	while (i < n_samples)
	{
		chunk_samples = binary_min(chunk_size, n_samples - i);
		
		for (int j = 0; j < chunk_samples; j++)
			e = str->alpha * e + (1.0 - str->alpha) * fabsf(in_buffer[i + j]);
		
		u = binary_min(str->sensitivity.value * e, 1.0);
		
		str->filter.center.value = str->min_center.value * pow(str->max_center.value / str->min_center.value, u);
		str->filter.bandwidth.value = str->width.value * str->filter.center.value;
		
		reconfigure_band_pass_filter(&str->filter);
		
		calc_band_pass_filter(&str->filter, &out_buffer[i], &in_buffer[i], chunk_samples);
		
		i += chunk_samples;
	}
	
	str->e = e;
	
	RETURN_ERR_CODE(NO_ERROR);
}

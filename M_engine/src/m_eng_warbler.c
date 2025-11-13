#include "m_eng.h"

static const char *FNAME = "m_eng_warbler.c";

int init_warbler_str(m_eng_warbler_str *str)
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

int reconfigure_warbler(void *data_struct)
{
	FUNCTION_START();

	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_warbler_str *str = (m_eng_warbler_str*)data_struct;
	
	str->alpha = expf(-1.0 / MS_TO_SAMPLES(str->reactivity.value));
	
	RETURN_ERR_CODE(NO_ERROR);
}

int calc_warbler(void *data_struct, float *dest, float *src, int n_samples)
{
	FUNCTION_START();

	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_warbler_str *str = (m_eng_warbler_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	float e = str->e;
	float u;
	float cutoff;
	
	float rate;

	for (int i = 0; i < n_samples; i++)
	{
		e = str->alpha * e + (1.0 - str->alpha) * fabsf(in_buffer[i]);
		
		u = binary_min(str->sensitivity.value * e, 1.0);
		
		rate = str->min_rate.value + u * (str->max_rate.value - str->min_rate.value);
		
		str->filter.center.value = str->center.value * (1.0 + str->width.value * sinf(2 * PI * str->t * rate));
		str->filter.bandwidth.value = str->width.value * str->filter.center.value;
		
		reconfigure_band_pass_filter(&str->filter);
		
		calc_band_pass_filter(&str->filter, &out_buffer[i], &in_buffer[i], 1);
		
		str->t += SAMPLE_FREQUENCY;
	}
	
	str->e = e;
	
	RETURN_ERR_CODE(NO_ERROR);
}

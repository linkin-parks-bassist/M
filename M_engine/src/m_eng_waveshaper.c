#include "m_eng.h"

static const char *FNAME = "m_eng_waveshaper.c";

int init_waveshaper_str(m_eng_waveshaper_str *str)
{
	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

int calc_waveshaper(void *data_struct, float *dest, float *src, int n_samples)
{
	if (!data_struct || !dest || !src)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	float *in_buffer  =  src ?  src : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	m_eng_waveshaper_str *str = (m_eng_waveshaper_str*)data_struct;
	
	if (!str->shape)
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	// Actual computation loop
	for (int i = 0; i < n_samples; i++)
	{
		out_buffer[i] = str->shape(str->coefficient.value * in_buffer[i]);
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}



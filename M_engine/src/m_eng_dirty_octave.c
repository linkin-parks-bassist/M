#include "m_eng.h"

static const char *FNAME = "m_eng_dirty_octave.c";

int reconfigure_dirty_octave(void *data_struct)
{
	FUNCTION_START();

	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_dirty_octave_str *str = (m_eng_dirty_octave_str*)data_struct;
	
	str->lpf_alpha = exp(-2 * PI * 200 + (48 * str->fuzz.value));
	
	RETURN_ERR_CODE(NO_ERROR);
}

int calc_dirty_octave(void *data_struct, float *dest, float *src, int n_samples)
{
	FUNCTION_START();

	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_dirty_octave_str *str = (m_eng_dirty_octave_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	float out_sample = str->last_out_sample;
	float last_out_sample = str->last_out_sample;
	
	for (int i = 0; i < n_samples; i++)
	{
		out_sample = str->lpf_alpha * str->last_out_sample + (1.0 - str->lpf_alpha) * fabsf(in_buffer[i]);
		str->dc_average = DC_BLOCKER_ALPHA * str->dc_average + (1.0 - DC_BLOCKER_ALPHA) * out_sample;
		out_sample -= str->dc_average;
		out_buffer[i] = out_sample;
		last_out_sample = out_sample;
	}
	
	str->last_out_sample = out_sample;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int init_dirty_octave_str(m_eng_dirty_octave_str *str)
{
	FUNCTION_START();

	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	str->last_out_sample = 0.0;
	str->dc_average = 0.0;
	
	RETURN_ERR_CODE(NO_ERROR);
}

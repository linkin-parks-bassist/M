#include "tm.h"

int reconfigure_dirty_octave(void *data_struct)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	tm_dirty_octave_str *str = (tm_dirty_octave_str*)data_struct;
	
	str->lpf_alpha = exp(-2 * PI * 200 + (48 * str->fuzz.value));
	
	return NO_ERROR;
}

int calc_dirty_octave(void *data_struct, float **dest, float **src, int n_samples)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	tm_dirty_octave_str *str = (tm_dirty_octave_str*)data_struct;
	
	float *in_buffer  =  src ? ( src[0] ?  src[0] : zero_buffer) : zero_buffer;
	float *out_buffer = dest ? (dest[0] ? dest[0] : sink_buffer) : sink_buffer;
	
	float out_sample, last_out_sample = str->last_out_sample;
	
	for (int i = 0; i < n_samples; i++)
	{
		out_sample = str->lpf_alpha * str->last_out_sample + (1.0 - str->lpf_alpha) * fabsf(in_buffer[i]);
		str->dc_average = DC_BLOCKER_ALPHA * str->dc_average + (1.0 - DC_BLOCKER_ALPHA) * out_sample;
		out_sample -= str->dc_average;
		out_buffer[i] = out_sample;
		last_out_sample = out_sample;
	}
	
	str->last_out_sample = out_sample;
	
	return NO_ERROR;
}

int init_dirty_octave_struct_default(tm_dirty_octave_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	str->last_out_sample = 0.0;
	str->dc_average = 0.0;
	
	return NO_ERROR;
}

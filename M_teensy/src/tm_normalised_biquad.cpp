#include "tm.h"

int calc_normalised_biquad(void *data_struct, float **dest, float **src, int n_samples)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	tm_normalised_biquad_str *str = (tm_normalised_biquad_str*)data_struct;
	
	float in_sample;
	float out_sample;
	
	float *in_buffer  =  src ? ( src[0] ?  src[0] : zero_buffer) : zero_buffer;
	float *out_buffer = dest ? (dest[0] ? dest[0] : sink_buffer) : sink_buffer;
	
	for (int i = 0; i < n_samples; i++)
	{
		in_sample = in_buffer[i];
		
		out_sample = in_sample
				   + str->a1.value * str->x1
				   + str->a2.value * str->x2
				   - str->a3.value * str->y1
				   - str->a4.value * str->y2;
		
		str->dc_average = DC_BLOCKER_ALPHA * str->dc_average + (1.0 - DC_BLOCKER_ALPHA) * out_sample;
		
		out_buffer[i] = out_sample - str->dc_average;

		str->x2 = str->x1;
		str->x1 = in_sample;

		str->y2 = str->y1;
		str->y1 = out_sample;
	}
	
	return NO_ERROR;
}

int init_normalised_biquad_struct_default(tm_normalised_biquad_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	str->dc_average = 0.0;
	
	return NO_ERROR;
}

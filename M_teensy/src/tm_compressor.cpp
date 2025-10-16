#include "tm.h"
#include "tm_compressor.h"

// Small constant to avoid taking log(0)
#define EPSILON 0.00000001

int init_compressor_str(tm_compressor_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	str->e_final = 0.0;
	
	return NO_ERROR;
}

int reconfigure_compressor(void *data_struct)
{
	tm_compressor_str *str = (tm_compressor_str*)data_struct;
	
	if (!str)
		return ERR_NULL_PTR;
	
	str->alpha = exp(-1.0 / (AUDIO_SAMPLE_RATE_EXACT * str->attack.value  * 0.001));
	
	str->rho 	= exp(-1.0 / (AUDIO_SAMPLE_RATE_EXACT * str->release.value * 0.001));

	return NO_ERROR;
}

int calc_compressor(void *data_struct, float *dest, float *src, int n_samples)
{
	if (!data_struct || !dest || !src)
		return ERR_NULL_PTR;
	
	float *in_buffer  =  src ?  src : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	tm_compressor_str *str = (tm_compressor_str*)data_struct;
	
	float e = str->e_final;
	float p, L, G, g;
	
	for (int i = 0; i < n_samples; i++)
	{
		p = in_buffer[i] * in_buffer[i];
		
		if (p > e)
			e = str->alpha  * e + (1 - str->alpha)  * p;
		else
			e = str->rho * e + (1 - str->rho) * p;
		
		L = 10 * log10f(e + EPSILON);
		
		if (L > str->threshold.value)
			G = str->threshold.value + (1.0 / str->ratio.value) * (L - str->threshold.value) - L;
		else
			G = 0.0;
		
		g = pow(10, G / 20.0);
		
		out_buffer[i] = g * in_buffer[i];
	}
	
	str->e_final = e;
	
	return NO_ERROR;
}

#include "tm.h"


int reconfigure_noise_suppressor(void *data_struct)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	tm_noise_suppressor_str *str = (tm_noise_suppressor_str*)data_struct;
	
	return NO_ERROR;
}

int calc_noise_suppressor(void *data_struct, float *dest, float *src, int n_samples)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	tm_noise_suppressor_str *str = (tm_noise_suppressor_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;

	float e = str->e_final;
	float G, g, L;
	
	for (int i = 0; i < n_samples; i++)
	{
		e = 0.99 * e + 0.001 * sqr(in_buffer[i]);
		
		L = 10 * log10f(e + 1e-30);
		
		G = (L < str->threshold.value) ? str->ratio.value * binary_max(L - str->threshold.value, str->max_reduction.value) : 0.0;
		
		if (i == 127 && str->r % 64 == 0)
		{
			tm_printf("Noise suppressor: L = %.f, G = %f\n", L, G);
		}
		
		g = pow(10, G / 20.0);
		
		out_buffer[i] = g * in_buffer[i];
	}
	
	str->e_final = e;
	
	str->r++;
	
	return NO_ERROR;
}

int init_noise_suppressor_str(tm_noise_suppressor_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	str->e_final = 0.0;
	str->r = 0;
	
	return NO_ERROR;
}

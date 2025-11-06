#include "m_eng.h"

static const char *FNAME = "m_eng_noise_suppressor.c";

int reconfigure_noise_suppressor(void *data_struct)
{
	FUNCTION_START();

	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_noise_suppressor_str *str = (m_eng_noise_suppressor_str*)data_struct;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int calc_noise_suppressor(void *data_struct, float *dest, float *src, int n_samples)
{
	FUNCTION_START();

	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_noise_suppressor_str *str = (m_eng_noise_suppressor_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;

	float e = str->e_final;
	float G, g, L;
	
	for (int i = 0; i < n_samples; i++)
	{
		e = 0.99 * e + 0.001 * sqr(in_buffer[i]);
		
		L = 10 * log10f(e + 1e-30);
		
		G = (L < str->threshold.value) ? str->ratio.value * binary_max(L - str->threshold.value, str->max_reduction.value) : 0.0;
		
		g = pow(10, G / 20.0);
		
		out_buffer[i] = g * in_buffer[i];
	}
	
	str->e_final = e;
	
	str->r++;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int init_noise_suppressor_str(m_eng_noise_suppressor_str *str)
{
	FUNCTION_START();

	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	str->e_final = 0.0;
	str->r = 0;
	
	RETURN_ERR_CODE(NO_ERROR);
}

#include "tm.h"
#include "tm_compressor.h"

// Small constant to avoid taking log(0)
#define EPSILON 0.00000001

int reconfigure_compressor(void *data_struct)
{
	tm_compressor_str *str = (tm_compressor_str*)data_struct;
	
	if (!str)
		return ERR_NULL_PTR;
	
	str->alpha = exp(-1.0 / (AUDIO_SAMPLE_RATE_EXACT * str->attack.value  * 0.001));
	
	str->rho 	= exp(-1.0 / (AUDIO_SAMPLE_RATE_EXACT * str->release.value * 0.001));

	return NO_ERROR;
}

int calc_compressor(void *data_struct, float **dest, float **src, int n_samples)
{
	if (!data_struct || !dest || !src)
		return ERR_NULL_PTR;
	
	float *in_buffer  =  src[0] ?  src[0] : zero_buffer;
	float *out_buffer = dest[0] ? dest[0] : sink_buffer;
	
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

int init_compressor_struct_default(tm_compressor_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	str->e_final = 0.0;
	
	return NO_ERROR;
}

int init_compressor_struct(tm_compressor_str *data_struct, float ratio, float threshold, float attack, float release)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	init_parameter_simple(&data_struct->ratio, ratio);
	init_parameter_simple(&data_struct->threshold, threshold);
	init_parameter_simple(&data_struct->attack, attack);
	init_parameter_simple(&data_struct->release, release);
	
	data_struct->e_final	= 0.0;
	
	return NO_ERROR;
}

int init_compressor(tm_transformer *trans, vec2i input, vec2i output, float ratio, float threshold, float attack, float release)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	tm_compressor_str *data_struct = (tm_compressor_str*)malloc(sizeof(tm_compressor_str));
	
	if (!data_struct)
		return ERR_ALLOC_FAIL;
	
	init_compressor_struct(data_struct, ratio, threshold, attack, release);
	
	int ret_val = init_transformer(trans, TRANSFORMER_COMPRESSOR, 1, 1, &input, &output, 0, 4, data_struct, calc_compressor);
	
	if (ret_val != NO_ERROR)
	{
		trans->data_struct = NULL;
		free(data_struct);
		return ret_val;
	}
	
	transformer_add_parameter(trans, &data_struct->ratio);
	transformer_add_parameter(trans, &data_struct->threshold);
	transformer_add_parameter(trans, &data_struct->attack);
	transformer_add_parameter(trans, &data_struct->release);
	
	return NO_ERROR;
}

tm_transformer *alloc_compressor(vec2i input, vec2i output, float ratio, float threshold, float attack, float release)
{
	tm_transformer *trans = (tm_transformer*)malloc(sizeof(tm_transformer));
	int ret_val;
	if ((ret_val = init_compressor(trans, input, output, ratio, threshold, attack, release)) != NO_ERROR)
	{
		if (trans)
			free(trans);
		return NULL;
	}
	return trans;
}

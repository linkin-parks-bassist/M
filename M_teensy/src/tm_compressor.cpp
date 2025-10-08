#include "tm.h"
#include "tm_compressor.h"

// Small constant to avoid taking log(0)
#define EPSILON 0.00000001

int calc_compressor(float **dest, float **src, void *data_struct)
{
	if (!data_struct || !dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0] || !src[0])
		return ERR_NULL_PTR;
	
	tm_compressor_str *comp = (tm_compressor_str*)data_struct;
	
	if (comp->attack.updated)
	{
		tm_printf("updating alpha...\n");
		comp->alpha = exp(-1.0 / (AUDIO_SAMPLE_RATE_EXACT * comp->attack.value * 0.001));
		comp->attack.updated = 0;
	}

	if (comp->release.updated)
	{
		tm_printf("updating rho...\n");
		comp->rho = exp(-1.0 / (AUDIO_SAMPLE_RATE_EXACT * comp->release.value * 0.001));
		comp->release.updated = 0;
	}
	
	float e = comp->e_final;
	float p, L, G, g;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		p = src[0][i] * src[0][i];
		
		if (p > e)
			e = comp->alpha  * e + (1 - comp->alpha)  * p;
		else
			e = comp->rho * e + (1 - comp->rho) * p;
		
		L = 10 * log10f(e + EPSILON);
		
		if (L > comp->threshold.value)
			G = comp->threshold.value + (1.0 / comp->ratio.value) * (L - comp->threshold.value) - L;
		else
			G = 0.0;
		
		g = pow(10, G / 20.0);
		
		dest[0][i] = g * src[0][i];
	}
	
	comp->e_final = e;
	
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

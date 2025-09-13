#include "M.h"
#include "m_compressor.h"

// Small constant to avoid taking log(0)
#define EPSILON 0.00000001

int calc_compressor(float **dest, float **src, void *transformer_data)
{
	if (!transformer_data || !dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0] || !src[0])
		return ERR_NULL_PTR;
	
	m_compressor_data *comp = (m_compressor_data*)transformer_data;
	
	if (comp->attack.updated)
	{
		m_printf("updating alpha...\n");
		comp->alpha = exp(-1.0 / (AUDIO_SAMPLE_RATE_EXACT * comp->attack.value));
		comp->attack.updated = 0;
	}
	if (comp->release.updated)
	{
		m_printf("updating rho...\n");
		comp->rho = exp(-1.0 / (AUDIO_SAMPLE_RATE_EXACT * comp->release.value));
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


int init_compressor_struct(m_compressor_data *data_struct, float ratio, float threshold, float attack, float release)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	init_parameter(&data_struct->ratio, 		"Ratio", 	 ratio	  );
	init_parameter(&data_struct->threshold, 	"Threshold", threshold);
	init_parameter(&data_struct->attack, 		"Attack", 	 attack	  );
	init_parameter(&data_struct->release, 		"Release", 	 release  );
	
	data_struct->e_final	= 0.0;
	
	return NO_ERROR;
}

int init_compressor(m_audio_transformer *trans, vec2i input, vec2i output, float ratio, float threshold, float attack, float release)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	m_compressor_data *data_struct = (m_compressor_data*)malloc(sizeof(m_compressor_data));
	
	if (!data_struct)
		return ERR_ALLOC_FAIL;
	
	init_compressor_struct(data_struct, ratio, threshold, attack, release);
	
	int ret_val = init_transformer(trans, TRANSFORMER_COMPRESSOR, 1, 1, &input, &output, 4, data_struct, calc_compressor);
	
	if (ret_val != NO_ERROR)
	{
		trans->transformer_data = NULL;
		free(data_struct);
		return ret_val;
	}
	
	transformer_add_parameter(trans, &data_struct->ratio);
	transformer_add_parameter(trans, &data_struct->threshold);
	transformer_add_parameter(trans, &data_struct->attack);
	transformer_add_parameter(trans, &data_struct->release);
	
	return NO_ERROR;
}

m_audio_transformer *alloc_compressor(vec2i input, vec2i output, float ratio, float threshold, float attack, float release)
{
	m_audio_transformer *trans = (m_audio_transformer*)malloc(sizeof(m_audio_transformer));
	int ret_val;
	if ((ret_val = init_compressor(trans, input, output, ratio, threshold, attack, release)) != NO_ERROR)
	{
		if (trans)
			free(trans);
		return NULL;
	}
	return trans;
}

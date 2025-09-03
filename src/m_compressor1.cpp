#include "M.h"
#include "m_compressor1.h"

// Small constant to avoid taking log(0)
#define EPSILON 0.00000001

int calc_compressor1(float **dest, float **src, void *transformer_data)
{
	if (!transformer_data || !dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0] || !src[0])
		return ERR_NULL_PTR;
	
	m_trans_compressor1_data *comp = (m_trans_compressor1_data*)transformer_data;
	
	float e = comp->e_final;
	float p, L, G, g;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		p = src[0][i] * src[0][i];
		
		if (p > e)
			e = comp->attack  * e + (1 - comp->attack)  * p;
		else
			e = comp->release * e + (1 - comp->release) * p;
		
		L = 10 * log10f(e + EPSILON);
		
		if (L > comp->threshold)
			G = comp->threshold + (1.0 / comp->ratio) * (L - comp->threshold) - L;
		else
			G = 0.0;
		
		g = pow(10, G / 20.0);
		
		dest[0][i] = g * src[0][i];
	}
	
	comp->e_final = e;
	
	return NO_ERROR;
}

int init_compressor1(m_audio_transformer *trans, vec2i input, vec2i output, float ratio, float threshold, float attack, float release)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->type = TRANSFORMER_COMPRESSOR1;
	
	trans->n_inputs  = 1;
	trans->n_outputs = 1;
	
	trans->inputs[0]  = input;
	trans->outputs[0] = output;
	
	m_trans_compressor1_data *data_str = (m_trans_compressor1_data*)malloc(sizeof(m_trans_compressor1_data));
	
	data_str->ratio 	= ratio;
	data_str->threshold = threshold;
	data_str->attack 	= exp(-1.0 / (AUDIO_SAMPLE_RATE_EXACT * attack));
	data_str->release 	= exp(-1.0 / (AUDIO_SAMPLE_RATE_EXACT * release));

	data_str->e_final	= 0.0;
	
	trans->transformer_data = (void*)data_str;
	trans->compute_transformer = &calc_compressor1;
	
	return NO_ERROR;
}

m_audio_transformer *alloc_compressor1(vec2i input, vec2i output, float ratio, float threshold, float attack, float release)
{
	m_audio_transformer *trans = (m_audio_transformer*)malloc(sizeof(m_audio_transformer));
	int ret_val;
	if ((ret_val = init_compressor1(trans, input, output, ratio, threshold, attack, release)) != NO_ERROR)
	{
		if (trans)
			free(trans);
		return NULL;
	}
	return trans;
}

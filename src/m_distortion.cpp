#include "M.h"

float normalised_arctan(float x)
{
	return 0.63661977237 * atan(x);
}

float hard_clip(float x)
{
	if (x > 1.0)
		return 1.0;
	if (x < -1.0)
		return -1.0;
	else
		return x;
}

int calc_waveshaper(float **dest, float **src, void *transformer_data)
{
	if (!transformer_data || !dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0] || !src[0])
		return ERR_NULL_PTR;
	
	m_printf("Calculating arctan distortion...\n");
	m_trans_waveshaper_data *dist = (m_trans_waveshaper_data*)transformer_data;
	
	if (!dist->shape)
		return ERR_NULL_PTR;
	
	float abs_max = 0.0;
	float abs_amp;
	float ra;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		abs_amp = fabs(src[0][i]);
		if (abs_amp > abs_max)
			abs_max = abs_amp;
	}
	
	ra = abs_amp * 0.5 + dist->running_amp * 0.5;
	
	if (ra == 0.0)
	{
		for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
			dest[0][i] = 0.0;
		
		return NO_ERROR;
	}
	
	float ra_inv = 1.0 / ra;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		dest[0][i] = ra *  dist->shape(dist->coef * (src[0][i] * ra_inv));
	
	dist->running_amp = ra;
	
	return NO_ERROR;
}

int init_waveshaper(m_audio_transformer *trans, vec2i input, vec2i output, float (*shape)(float x), float coef)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->type = TRANSFORMER_ARCTAN_DIST;
	
	trans->n_inputs  = 1;
	trans->n_outputs = 1;
	
	trans->inputs[0]  = input;
	trans->outputs[0] = output;
	
	m_trans_waveshaper_data *data_str = (m_trans_waveshaper_data*)malloc(sizeof(m_trans_waveshaper_data));
	
	data_str->coef = coef;
	data_str->running_amp = 0.0;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		data_str->prev_block[i] = 0.0;
	
	data_str->shape = shape;
	
	trans->transformer_data = (void*)data_str;
	trans->compute_transformer = &calc_waveshaper;
	
	return NO_ERROR;
}

int init_arctan_distortion(m_audio_transformer *trans, vec2i input, vec2i output, float coef)
{
	return init_waveshaper(trans, input, output, &normalised_arctan, coef);
}

int init_tanh_distortion(m_audio_transformer *trans, vec2i input, vec2i output, float coef)
{
	return init_waveshaper(trans, input, output, &tanh, coef);
}

m_audio_transformer *alloc_arctan_distortion(vec2i input, vec2i output, float coef)
{
	m_audio_transformer *dist = (m_audio_transformer*)malloc(sizeof(m_audio_transformer));
	int ret_val;
	if ((ret_val = init_arctan_distortion(dist, input, output, coef)) != NO_ERROR)
	{
		if (dist)
			free(dist);
		return NULL;
	}
	return dist;
}

m_audio_transformer *alloc_tanh_distortion(vec2i input, vec2i output, float coef)
{
	m_audio_transformer *dist = (m_audio_transformer*)malloc(sizeof(m_audio_transformer));
	int ret_val;
	if ((ret_val = init_arctan_distortion(dist, input, output, coef)) != NO_ERROR) {if (dist) free(dist); return NULL;}
	
	return dist;
}

#include "tm.h"

float 	local_amplitude_weighting_table[AUDIO_BLOCK_SAMPLES];
int 	local_amplitude_weighting_table_initialised = 0;

float identity_function(float x){return x;}

void init_local_amplitude_weighting_table()
{
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		local_amplitude_weighting_table[i] = expf(-((float)i / 72.0) * ((float)i / 72.0));
	
	local_amplitude_weighting_table_initialised = 1;
}

#define RATE (1.0/(64 * 128))

int calc_waveshaper(float **dest, float **src, void *data_struct)
{
	if (!data_struct || !dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0] || !src[0])
		return ERR_NULL_PTR;
	
	tm_waveshaper_str *str = (tm_waveshaper_str*)data_struct;
	
	if (!str->shape)
	{
		for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
			dest[0][i] = src[0][i];
		return ERR_NULL_PTR;
	}
	
	if (!local_amplitude_weighting_table_initialised)
		init_local_amplitude_weighting_table();
	
	float local_amplitude = str->local_amplitude;
	/*float tmp;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		tmp = fabs(src[0][i]);
		if (tmp > local_amplitude)
			local_amplitude = tmp;
	}*/
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		if (str->coefficient.updated)
			parameter_update_tick(&str->coefficient);
		
		if (fabs(src[0][i]) > local_amplitude)
			local_amplitude = fabs(src[0][i]);
		else
			local_amplitude = (1.0 - RATE) * local_amplitude + RATE * fabs(src[0][i]);
		
		if (fabs(local_amplitude) < 1e-30f)
		{
			dest[0][i] = 0.0;
		}
		else
		{
			dest[0][i] = local_amplitude *  str->shape(str->coefficient.value * (src[0][i] * (1.0 / local_amplitude)));
		}
	}
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		str->prev_block[i] = src[0][i];
	
	str->local_amplitude = local_amplitude;
	
	return NO_ERROR;
}

int init_waveshaper_struct_default(tm_waveshaper_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	str->shape = identity_function;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		str->prev_block[i] = 0.0;
	
	str->local_amplitude = 0.0;
	
	return NO_ERROR;
}

int init_waveshaper_struct(tm_waveshaper_str *data_struct, float (*shape)(float x), float coef)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		data_struct->prev_block[i] = 0.0;
	
	data_struct->shape = shape;
	data_struct->local_amplitude = 0.0;
	
	init_parameter_simple(&data_struct->coefficient, coef);
	
	return NO_ERROR;
}

int init_waveshaper(tm_transformer *trans, vec2i input, vec2i output, float (*shape)(float x), float coef)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	if (!local_amplitude_weighting_table_initialised)
		init_local_amplitude_weighting_table();
	
	trans->type = TRANSFORMER_WAVESHAPER;
	
	trans->n_inputs  = 1;
	trans->n_outputs = 1;
	
	trans->inputs [0] = input;
	trans->outputs[0] = output;
	
	tm_waveshaper_str *data_struct = (tm_waveshaper_str*)malloc(sizeof(tm_waveshaper_str));
	
	init_waveshaper_struct(data_struct, shape, coef);
	
	trans->data_struct = (void*)data_struct;
	trans->compute_transformer = &calc_waveshaper;
	
	transformer_add_parameter(trans, &data_struct->coefficient);
	
	return NO_ERROR;
}

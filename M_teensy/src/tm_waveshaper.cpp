#include "tm.h"

float 	local_amplitude_weighting_table[AUDIO_BLOCK_SAMPLES];
int 	local_amplitude_weighting_table_initialised = 0;

float identity_function(float x){return x;}

int init_waveshaper_default(tm_audio_transformer *trans)
{
	return init_waveshaper(trans, DISCONNECTED, DISCONNECTED, DEFAULT_WAVESHAPER_FUNCTION, DEFAULT_WAVESHAPER_COEFFICIENT);
}

void init_local_amplitude_weighting_table()
{
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		local_amplitude_weighting_table[i] = expf(-((float)i / 72.0) * ((float)i / 72.0));
	
	local_amplitude_weighting_table_initialised = 1;
}

int calc_waveshaper(float **dest, float **src, void *transformer_data)
{
	if (!transformer_data || !dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0] || !src[0])
		return ERR_NULL_PTR;
	
	tm_waveshaper_data *data_struct = (tm_waveshaper_data*)transformer_data;
	
	if (!data_struct->shape)
	{
		for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
			dest[0][i] = src[0][i];
		return ERR_NULL_PTR;
	}
	
	if (!local_amplitude_weighting_table_initialised)
		init_local_amplitude_weighting_table();
	
	float local_amplitude = data_struct->local_amplitude;
	/*float tmp;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		tmp = fabs(src[0][i]);
		if (tmp > local_amplitude)
			local_amplitude = tmp;
	}*/
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		
		#define RATE (1.0/(64 * 128))
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
			dest[0][i] = local_amplitude *  data_struct->shape(data_struct->coefficient.val.level * (src[0][i] * (1.0 / local_amplitude)));
		}
	}
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		data_struct->prev_block[i] = src[0][i];
	
	data_struct->local_amplitude = local_amplitude;
	
	return NO_ERROR;
}

int init_waveshaper_struct(tm_waveshaper_data *data_struct, float (*shape)(float x), float coef)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	INIT_PARAM(data_struct->coefficient, M_PARAM_LEVEL, coef, "Coefficient");
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		data_struct->prev_block[i] = 0.0;
	
	data_struct->shape = shape;
	data_struct->local_amplitude = 0.0;
	
	return NO_ERROR;
}

int init_waveshaper(tm_audio_transformer *trans, vec2i input, vec2i output, float (*shape)(float x), float coef)
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
	
	tm_waveshaper_data *data_struct = (tm_waveshaper_data*)malloc(sizeof(tm_waveshaper_data));
	
	init_waveshaper_struct(data_struct, shape, coef);
	
	trans->transformer_data = (void*)data_struct;
	trans->compute_transformer = &calc_waveshaper;
	
	INIT_PARAM(data_struct->coefficient, M_PARAM_LEVEL, coef, "Coefficient");
	transformer_add_parameter(trans, &data_struct->coefficient);
	
	return NO_ERROR;
}

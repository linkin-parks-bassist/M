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

int calc_waveshaper(void *data_struct, float **dest, float **src, int n_samples)
{
	if (!data_struct || !dest || !src)
		return ERR_NULL_PTR;
	
	float *in_buffer  =  src[0] ?  src[0] : zero_buffer;
	float *out_buffer = dest[0] ? dest[0] : sink_buffer;
	
	tm_waveshaper_str *str = (tm_waveshaper_str*)data_struct;
	
	if (!str->shape)
		return ERR_BAD_ARGS;
	
	//if (!local_amplitude_weighting_table_initialised)
	//	init_local_amplitude_weighting_table();
	
	float local_amplitude = str->local_amplitude;
	
	// Actual computation loop
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		if (fabs(in_buffer[i]) > local_amplitude)
			local_amplitude = fabs(in_buffer[i]);
		else
			local_amplitude = (1.0 - WAVESHAPER_ENVELOPE_RATE) * local_amplitude + WAVESHAPER_ENVELOPE_RATE * fabs(in_buffer[i]);
		
		if (fabs(local_amplitude) < 1e-30f)
			out_buffer[i] = 0.0;
		else
			out_buffer[i] = local_amplitude *  str->shape(str->coefficient.value * (in_buffer[i] * (1.0 / local_amplitude)));
	}
	
	for (int i = 0; i < n_samples; i++)
	{
		// The order is important here. If str->prev_block_index for some reason
		// contains something negative or > AUDIO_BLOCK_SAMPLES, instant crash
		// unless we mod it first. Then after copying, increment, then it will
		// be modded before copying the next sample. Happy days
		str->prev_block_index = str->prev_block_index % AUDIO_BLOCK_SAMPLES;
		
		str->prev_block[str->prev_block_index] = in_buffer[i];
		
		str->prev_block_index = str->prev_block_index + 1;
	}
	
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
	str->prev_block_index = 0;
	
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
	data_struct->prev_block_index = 0;
	
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

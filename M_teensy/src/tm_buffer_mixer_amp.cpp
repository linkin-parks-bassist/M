#include "tm.h"

int init_buffer_default	(tm_audio_transformer *trans)
{
	return init_buffer(trans, DISCONNECTED, DISCONNECTED);
}

int init_amp_default(tm_audio_transformer *trans)
{
	return init_amp(trans, DISCONNECTED, DISCONNECTED, DEFAULT_AMP_GAIN);
}

int init_mixer_default(tm_audio_transformer *trans)
{
	return init_mixer(trans, NULL, DISCONNECTED, DEFAULT_MIXER_RATIO);
}

int calc_buffer(float **dest, float **src, void *transformer_data)
{
	if (!dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0] || !src[0])
		return ERR_NULL_PTR;
	
	memcpy(dest[0], src[0], AUDIO_BLOCK_SAMPLES * sizeof(float));
	
	return NO_ERROR;
}

int calc_amp(float **dest, float **src, void *transformer_data)
{
	if (!transformer_data || !dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0] || !src[0])
		return ERR_NULL_PTR;
	
	//tm_printf("Computing amp transformer...\n");
	
	tm_amp_data *amp = (tm_amp_data*)transformer_data;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		dest[0][i] = amp->gain.val.level * src[0][i];
	
	return NO_ERROR;
}

int calc_mixer(float **dest, float **src, void *transformer_data)
{
	if (!transformer_data || !dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0] || !(src[0] && src[1]))
		return ERR_NULL_PTR;
	
	tm_mixer_data *mixer = (tm_mixer_data*)transformer_data;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		dest[0][i] = mixer->ratio.val.level * src[0][i] + (1.0 - mixer->ratio.val.level) * src[1][i];
	
	return NO_ERROR;
}

int init_buffer(tm_audio_transformer *trans, vec2i input, vec2i output)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	return init_transformer(trans, TRANSFORMER_BUFFER, 1, 1, &input, &output, 0, NULL, &calc_buffer);
}

tm_audio_transformer *alloc_buffer_transformer(vec2i input, vec2i output)
{
	tm_audio_transformer *buffer = (tm_audio_transformer*)malloc(sizeof(tm_audio_transformer));
	int ret_val;
	if ((ret_val = init_buffer(buffer, input, output)) != NO_ERROR)
	{
		if (buffer)
			free(buffer);
		return NULL;
	}
	return buffer;
}

int init_amp(tm_audio_transformer *trans, vec2i input, vec2i output, m_param_level_t gain)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int ret_val = NO_ERROR;
	
	tm_amp_data *data_struct = (tm_amp_data*)malloc(sizeof(tm_amp_data));
	
	init_transformer(trans, TRANSFORMER_AMPLIFIER, 1, 1, &input, &output, 1, (void*)data_struct, &calc_amp);
	
	if (!data_struct)
	{
		ret_val = ERR_ALLOC_FAIL;
	}
	else
	{
		INIT_PARAM(data_struct->gain, M_PARAM_LEVEL, gain, "Gain");
		transformer_add_parameter(trans, &data_struct->gain);
	}
	
	return ret_val;
}

tm_audio_transformer *alloc_amp_transformer(vec2i input, vec2i output, m_param_level_t gain)
{
	tm_audio_transformer *amp = (tm_audio_transformer*)malloc(sizeof(tm_audio_transformer));
	int ret_val;
	if ((ret_val = init_amp(amp, input, output, gain)) != NO_ERROR)
	{
		if (amp)
		{
			if (amp->transformer_data)
				free(amp->transformer_data);
			free(amp);
		}
		return NULL;
	}
	return amp;
}

int init_mixer(tm_audio_transformer *trans, vec2i *inputs, vec2i output, m_param_level_t ratio)
{
	if (!trans || !inputs)
		return ERR_NULL_PTR;
	
	tm_mixer_data *data_struct = (tm_mixer_data*)malloc(sizeof(tm_mixer_data));
	
	int ret_val = NO_ERROR;
	
	init_transformer(trans, TRANSFORMER_MIXER, 2, 1, inputs, &output, 1, (void*)data_struct, &calc_mixer);
	
	if (!data_struct)
	{
		ret_val = ERR_ALLOC_FAIL;
	}
	else
	{
		INIT_PARAM(data_struct->ratio, M_PARAM_LEVEL, ratio, "Ratio");
		transformer_add_parameter(trans, &data_struct->ratio);
	}
	
	return ret_val;
}

tm_audio_transformer *alloc_mixer_transformer(vec2i *inputs, vec2i output, m_param_level_t ratio)
{
	tm_audio_transformer *mixer = (tm_audio_transformer*)malloc(sizeof(tm_audio_transformer));
	int ret_val;
	if ((ret_val = init_mixer(mixer, inputs, output, ratio)) != NO_ERROR)
	{
		if (mixer)
		{
			if (mixer->transformer_data)
				free(mixer->transformer_data);
			
			free(mixer);
		}
		return NULL;
	}
	return mixer;
}

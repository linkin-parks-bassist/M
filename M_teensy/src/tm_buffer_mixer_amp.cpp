#include "tm.h"

int calc_buffer(void *data_struct, float **dest, float **src, int n_samples)
{
	if (!dest || !src)
		return ERR_NULL_PTR;
	
	float *in_buffer  =  src[0] ?  src[0] : zero_buffer;
	float *out_buffer = dest[0] ? dest[0] : sink_buffer;
	
	memcpy(out_buffer, in_buffer, n_samples * sizeof(float));
	
	return NO_ERROR;
}

int calc_amplifier(void *data_struct, float **dest, float **src, int n_samples)
{
	if (!data_struct || !dest || !src)
		return ERR_NULL_PTR;
	
	tm_amplifier_str *amp = (tm_amplifier_str*)data_struct;
	
	float *in_buffer  =  src[0] ?  src[0] : zero_buffer;
	float *out_buffer = dest[0] ? dest[0] : sink_buffer;
	
	#ifdef NO_CMSIS
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		dest[0][i] = amp->gain.value * src[0][i];
	#else
	arm_scale_f32(in_buffer, amp->gain.value, out_buffer, n_samples);
	#endif
	
	return NO_ERROR;
}

int calc_mixer(void *data_struct, float **dest, float **src, int n_samples)
{
	if (!data_struct || !dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0] || !(src[0] && src[1]))
		return ERR_NULL_PTR;
	
	tm_mixer_str *mixer = (tm_mixer_str*)data_struct;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		dest[0][i] = mixer->ratio.value * src[0][i] + (1.0 - mixer->ratio.value) * src[1][i];
	
	return NO_ERROR;
}

int init_buffer(tm_transformer *trans, vec2i input, vec2i output)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	return init_transformer(trans, TRANSFORMER_BUFFER, 1, 1, &input, &output, 1, 0, NULL, &calc_buffer);
}

tm_transformer *alloc_buffer_transformer(vec2i input, vec2i output)
{
	tm_transformer *buffer = (tm_transformer*)malloc(sizeof(tm_transformer));
	int ret_val;
	if ((ret_val = init_buffer(buffer, input, output)) != NO_ERROR)
	{
		if (buffer)
			free(buffer);
		return NULL;
	}
	return buffer;
}

int init_amplifier_struct_default(tm_amplifier_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	return NO_ERROR;
}

int init_amplifier(tm_transformer *trans, vec2i input, vec2i output, float gain)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int ret_val = NO_ERROR;
	
	tm_amplifier_str *data_struct = (tm_amplifier_str*)malloc(sizeof(tm_amplifier_str));
	
	init_transformer(trans, TRANSFORMER_AMPLIFIER, 1, 1, &input, &output, 0, 1, (void*)data_struct, &calc_amplifier);
	
	if (!data_struct)
	{
		ret_val = ERR_ALLOC_FAIL;
	}
	else
	{
		init_parameter_simple(&data_struct->gain, gain);
		transformer_add_parameter(trans, &data_struct->gain);
	}
	
	return ret_val;
}

tm_transformer *alloc_amplifier_transformer(vec2i input, vec2i output, float gain)
{
	tm_transformer *amp = (tm_transformer*)malloc(sizeof(tm_transformer));
	int ret_val;
	if ((ret_val = init_amplifier(amp, input, output, gain)) != NO_ERROR)
	{
		if (amp)
		{
			if (amp->data_struct)
				free(amp->data_struct);
			free(amp);
		}
		return NULL;
	}
	return amp;
}

int init_mixer_struct_default(tm_mixer_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	return NO_ERROR;
}

int init_mixer(tm_transformer *trans, vec2i *inputs, vec2i output, float ratio)
{
	if (!trans || !inputs)
		return ERR_NULL_PTR;
	
	tm_mixer_str *data_struct = (tm_mixer_str*)malloc(sizeof(tm_mixer_str));
	
	int ret_val = NO_ERROR;
	
	init_transformer(trans, TRANSFORMER_MIXER, 2, 1, inputs, &output, 0, 1, (void*)data_struct, &calc_mixer);
	
	if (!data_struct)
	{
		ret_val = ERR_ALLOC_FAIL;
	}
	else
	{
		init_parameter_simple(&data_struct->ratio, ratio);
		transformer_add_parameter(trans, &data_struct->ratio);
	}
	
	return ret_val;
}

tm_transformer *alloc_mixer_transformer(vec2i *inputs, vec2i output, float ratio)
{
	tm_transformer *mixer = (tm_transformer*)malloc(sizeof(tm_transformer));
	int ret_val;
	if ((ret_val = init_mixer(mixer, inputs, output, ratio)) != NO_ERROR)
	{
		if (mixer)
		{
			if (mixer->data_struct)
				free(mixer->data_struct);
			
			free(mixer);
		}
		return NULL;
	}
	return mixer;
}

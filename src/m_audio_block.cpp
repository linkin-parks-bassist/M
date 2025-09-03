#include "M.h"

int zero_out_block_float(m_audio_block_float *block)
{
	if (!block)
		return ERR_NULL_PTR;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		block->data[i] = 0.0;
	
	return NO_ERROR;
}

#define DENORMAL_THRESHOLD 1e-20f
#define FLOAT_TO_INT16_MAX ((float) 32767 / 32768.0f)

int convert_block_int_to_float(float *dest, int16_t *src)
{
	if (!dest || !src)
		return ERR_NULL_PTR;
	
	float sample;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		sample = (float)src[i] / 32768.0f;
		
		if (fabsf(sample) < DENORMAL_THRESHOLD)
			sample = 0.0f;
		
		dest[i] = sample;
	}
	
	return NO_ERROR;
}

int convert_block_float_to_int(int16_t *dest, float *src)
{
	if (!dest || !src)
		return ERR_NULL_PTR;
	
	float sample;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		sample = src[i];
		
		if (sample > FLOAT_TO_INT16_MAX)
			sample = FLOAT_TO_INT16_MAX;
		
		if (sample < -1.0f)
			sample = -1.0f;
		
		if (fabsf(sample) < DENORMAL_THRESHOLD)
			dest[i] = 0;
		else
			dest[i] = (int16_t)(sample * 32767.0f);
	}
	
	return NO_ERROR;
}

m_audio_block_float *convert_and_allocate_int_block(m_audio_block_int block)
{
	return NULL;
}

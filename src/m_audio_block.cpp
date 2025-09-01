#include "M.h"

int zero_out_block_float(m_audio_block_float *block)
{
	if (!block)
		return ERR_NULL_PTR;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		block->data[i] = 0.0;
	
	return NO_ERROR;
}

int convert_block_int_to_float(float *dest, int16_t *src)
{
	if (!dest || !src)
		return ERR_NULL_PTR;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		dest[i] = (float)(src[i]) / 32768.0;
	
	return NO_ERROR;
}

int convert_block_float_to_int(int16_t *dest, float *src)
{
	if (!dest || !src)
		return ERR_NULL_PTR;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		dest[i] = (int16_t)(src[i] * 32768.0);
	
	return NO_ERROR;
}

m_audio_block_float *convert_and_allocate_int_block(m_audio_block_int block)
{
	return NULL;
}

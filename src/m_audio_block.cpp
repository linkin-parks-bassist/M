#include <arm_math.h>
#include "M.h"

int zero_out_block_float(m_audio_block_float *block)
{
	if (!block)
		return ERR_NULL_PTR;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		block->data[i] = 0.0;
	
	return NO_ERROR;
}

#define DENORMAL_THRESHOLD 1e-30f // Smaller threshold for denormals
#define FLOAT_TO_INT16_MAX (32767.0f / 32768.0f)
#define SCALE_FACTOR 32768.0f // Consistent scaling factor

#define MAX_INT 32768.0

int convert_block_int_to_float(float *dest, int16_t *src)
{
    if (!dest || !src)
        return ERR_NULL_PTR;
	
    for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		dest[i] = (float)src[i];
	
	arm_scale_f32(dest, 1.0 / MAX_INT, dest, AUDIO_BLOCK_SAMPLES);
    
    return NO_ERROR;
}

int convert_block_float_to_int(int16_t *dest, float *src)
{
    if (!dest || !src)
        return ERR_NULL_PTR;

    for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
    {
		dest[i] = (int16_t)(max(min((src[i] * MAX_INT), MAX_INT), -MAX_INT));
    }

    return NO_ERROR;
}

m_audio_block_float *convert_and_allocate_int_block(m_audio_block_int block)
{
	return NULL;
}

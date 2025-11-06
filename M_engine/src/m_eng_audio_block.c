#include "m_eng.h"

static const char *FNAME = "m_eng_audio_block.c";

int zero_out_block_float(m_eng_audio_block_float *block)
{
	FUNCTION_START();
	
	if (!block)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		block->data[i] = 0.0;
	
	RETURN_ERR_CODE(NO_ERROR);
}

#define DENORMAL_THRESHOLD 1e-30f
#define FLOAT_TO_INT16_MAX (32767.0f / 32768.0f)
#define SCALE_FACTOR 32768.0f

#define MAX_INT 32768.0

int convert_block_int_to_float(float *dest, int16_t *src)
{
	FUNCTION_START();
	
	if (!dest || !src)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		dest[i] = (float)src[i];
	
	#ifndef NO_CMSIS
	arm_scale_f32(dest, 1.0 / MAX_INT, dest, AUDIO_BLOCK_SAMPLES);
	#else
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		dest[i] *= 1.0 / MAX_INT;
	#endif
	
	RETURN_ERR_CODE(NO_ERROR);
}

int convert_block_float_to_int(int16_t *dest, float *src)
{
	FUNCTION_START();
	
	if (!dest || !src)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}

	float x;
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		float x = src[i] * MAX_INT;
		x = fminf(fmaxf(x, -MAX_INT), MAX_INT);
		dest[i] = (int16_t)x;
	}

	RETURN_ERR_CODE(NO_ERROR);
}

m_eng_audio_block_float *convert_and_allocate_int_block(m_eng_audio_block_int block)
{
	RETURN_PTR(NULL);
}

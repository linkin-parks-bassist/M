#include "m_eng.h"

static const char *FNAME = "m_eng_useful_functions.c";
float identity_function(float x){return x;}

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

float soft_fold(float x)
{
	return x / (1 + fabsf(x));
}

float trig_transition_function(float x)
{
	if (x > 1.0)
	{
		return 0.0;
	}
	if (x > 0.0)
	{
		float y = cos(1.57079632679 * x);
		return y * y;
	}
	
	return 1.0;
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

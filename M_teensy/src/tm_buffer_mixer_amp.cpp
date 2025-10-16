#include "tm.h"

int calc_buffer(void *data_struct, float *dest, float *src, int n_samples)
{
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	memcpy(out_buffer, in_buffer, n_samples * sizeof(float));
	
	return NO_ERROR;
}

int init_amplifier_str(tm_amplifier_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	return NO_ERROR;
}

int calc_amplifier(void *data_struct, float *dest, float *src, int n_samples)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	tm_amplifier_str *amp = (tm_amplifier_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	#ifdef NO_CMSIS
	for (int i = 0; i < n_samples; i++)
		out_buffer[i] = amp->gain.value * in_buffer[i];
	#else
	arm_scale_f32(in_buffer, amp->gain.value, out_buffer, n_samples);
	#endif
	
	return NO_ERROR;
}

/*
int init_mixer_str(tm_mixer_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	return NO_ERROR;
}


int calc_mixer(void *data_struct, float *dest, float *src, int n_samples)
{
	if (!data_struct || !dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0] || !(src[0] && src[1]))
		return ERR_NULL_PTR;
	
	tm_mixer_str *mixer = (tm_mixer_str*)data_struct;
	
	for (int i = 0; i < n_samples; i++)
		dest[0][i] = mixer->ratio.value * src[0][i] + (1.0 - mixer->ratio.value) * src[1][i];
	
	return NO_ERROR;
}*/



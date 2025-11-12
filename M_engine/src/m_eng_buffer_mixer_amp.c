#include "m_eng.h"

static const char *FNAME = "m_eng_buffer_mixer_amp.c";

int calc_buffer(void *data_struct, float *dest, float *src, int n_samples)
{
	FUNCTION_START();

	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	memcpy(out_buffer, in_buffer, n_samples * sizeof(float));
	
	RETURN_ERR_CODE(NO_ERROR);
}

int init_amplifier_str(m_eng_amplifier_str *str)
{
	FUNCTION_START();

	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

int reconfigure_amplifier(void *data_struct)
{
	FUNCTION_START();
	
	m_eng_amplifier_str *str = (m_eng_amplifier_str*)data_struct;
	
	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (str->mode.value == M_ENG_AMPLIFIER_LINEAR)
	{
		str->g = str->gain.value;
	}
	else
	{
		str->g = powf(10, str->gain.value / 20.0);
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

int calc_amplifier(void *data_struct, float *dest, float *src, int n_samples)
{
	FUNCTION_START();

	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_amplifier_str *str = (m_eng_amplifier_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	if (str->g == 1.0f)
		memcpy(out_buffer, in_buffer, sizeof(float) * n_samples);
	else
		m_scale_f32(out_buffer, in_buffer, str->g, n_samples);
	
	RETURN_ERR_CODE(NO_ERROR);
}

/*
int init_mixer_str(m_eng_mixer_str *str)
{
	FUNCTION_START();

	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}


int calc_mixer(void *data_struct, float *dest, float *src, int n_samples)
{
	FUNCTION_START();

	if (!data_struct || !dest || !src)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (!dest[0] || !(src[0] && src[1]))
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_mixer_str *mixer = (m_eng_mixer_str*)data_struct;
	
	for (int i = 0; i < n_samples; i++)
		dest[0][i] = mixer->ratio.value * src[0][i] + (1.0 - mixer->ratio.value) * src[1][i];
	
	RETURN_ERR_CODE(NO_ERROR);
}*/



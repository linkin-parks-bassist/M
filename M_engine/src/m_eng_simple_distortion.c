#include "m_eng.h"

static const char *FNAME = "m_eng_simple_distortion.c";

int init_simple_distortion_str(m_eng_simple_distortion_str *str)
{
	FUNCTION_START();

	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	
	
	RETURN_ERR_CODE(NO_ERROR);
}

int reconfigure_simple_distortion(void *data_struct)
{
	FUNCTION_START();

	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_simple_distortion_str *str = (m_eng_simple_distortion_str*)data_struct;
	
	
	
	
	RETURN_ERR_CODE(NO_ERROR);
}

int calc_simple_distortion(void *data_struct, float *dest, float *src, int n_samples)
{
	FUNCTION_START();

	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_simple_distortion_str *str = (m_eng_simple_distortion_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;

	for (int i = 0; i < n_samples; i++)
		out_buffer[i] = str->postgain.value * tanh(str->pregain.value * in_buffer[i]);
	
	RETURN_ERR_CODE(NO_ERROR);
}

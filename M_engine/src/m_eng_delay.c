#include "m_eng.h"

static const char *FNAME = "m_eng_delay.c";

int init_delay_str(m_eng_delay_str *str)
{
	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	init_delay_buffer(&str->buf);
	
	str->delay_samples = 0.0;
	str->g = 0.0;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int reconfigure_delay(void *data_struct)
{
	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_delay_str *str = (m_eng_delay_str*)data_struct;
	
	str->delay_samples = S_TO_SAMPLES(60.0 / (float)(str->tempo.value * str->note.value));
	
	m_delay_buffer_resize_samples(&str->buf, (int)(ceilf(str->delay_samples)));
	
	str->g = powf(10, str->delay_gain.value / 20.0);
	
	RETURN_ERR_CODE(NO_ERROR);
}

int calc_delay(void *data_struct, float *dest, float *src, int n_samples)
{
	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_delay_str *str = (m_eng_delay_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;

	float delay_sample;

	for (int i = 0; i < n_samples; i++)
	{
		m_delay_buffer_get_fractional_delayed_sample(&str->buf, &delay_sample, str->delay_samples);
		out_buffer[i] = in_buffer[i] + str->g * delay_sample;
		m_delay_buffer_tick(&str->buf, out_buffer[i]);
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

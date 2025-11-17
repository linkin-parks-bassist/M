#include "m_eng.h"
static const char *FNAME = "m_eng_flanger.c";

int init_flanger_str(m_eng_flanger_str *str)
{
	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	str->t = 0;
	
	init_delay_buffer(&str->buf);
	
	RETURN_ERR_CODE(NO_ERROR);
}

int reconfigure_flanger(void *data_struct)
{
	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_flanger_str *str = (m_eng_flanger_str*)data_struct;
	
	str->d = MS_TO_SAMPLES(str->depth.value);
	str->r = binary_min(str->range.value * str->d, str->d - 1);
	
	float oscillator_freq = (str->tempo.value / 60.0f) / str->note.value;
	
	str->s = 2 * PI * oscillator_freq;
	
	str->period = 1.0f / oscillator_freq;
	
	str->wet_mix = sinf(0.5f * PI * str->mix.value);
	str->dry_mix = cosf(0.5f * PI * str->mix.value);
	
	int ret_val = m_delay_buffer_resize_samples(&str->buf, ceilf(str->d + str->r));
	
	RETURN_ERR_CODE(ret_val);
}

int calc_flanger(void *data_struct, float *dest, float *src, int n_samples)
{
	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_flanger_str *str = (m_eng_flanger_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	float delay;
	float delay_sample;

	for (int i = 0; i < n_samples; i++)
	{
		delay = str->d + str->r * cosf(str->s * str->t);

		m_delay_buffer_get_fractional_delayed_sample(&str->buf, &delay_sample, delay);
		
		out_buffer[i] = str->mix.value * delay_sample + (1.0 - str->mix.value) * in_buffer[i];
		
		m_delay_buffer_tick(&str->buf, out_buffer[i]);
		
		str->t += SAMPLE_FREQUENCY;
		
		while (str->t > str->period)
			str->t -= str->period;
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

int free_flanger_struct(void *data_struct)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	m_eng_flanger_str *str = (m_eng_flanger_str*)data_struct;
	
	
	
	return NO_ERROR;
}

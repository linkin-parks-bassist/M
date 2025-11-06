#include "m_eng.h"

static const char *FNAME = "m_eng_pass_filter.c";
int reconfigure_low_pass_filter(void *data_struct)
{
	FUNCTION_START();
	
	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_low_pass_filter_str *str = (m_eng_low_pass_filter_str*)data_struct;
	
	float omega, sin_omega, cos_omega, alpha;
    float b0, b1, b2, a0, a1, a2;

    // Normalized frequency
    omega     = 2.0f * PI * str->cutoff_frequency.value / AUDIO_SAMPLE_RATE_EXACT;
    sin_omega = sinf(omega);
    cos_omega = cosf(omega);

    // Butterworth Q = 1/sqrt(2)
    alpha = sin_omega / (2.0f * 0.70710678f);

    // Coefficients
    b0 = (1.0f - cos_omega) * 0.5f;
    b1 =  1.0f - cos_omega;
    b2 = (1.0f - cos_omega) * 0.5f;
    a0 =  1.0f + alpha;
    a1 = -2.0f * cos_omega;
    a2 =  1.0f - alpha;

    // Normalise
    str->a0 = b0 / a0;
    str->a1 = b1 / a0;
    str->a2 = b2 / a0;
    str->a3 = a1 / a0;
    str->a4 = a2 / a0;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int calc_low_pass_filter(void *data_struct, float *dest, float *src, int n_samples)
{
	FUNCTION_START();
	
	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_low_pass_filter_str *str = (m_eng_low_pass_filter_str*)data_struct;
	
	float in_sample;
	float out_sample;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	for (int i = 0; i < n_samples; i++)
	{
		in_sample = in_buffer[i];
		
		out_sample = str->a0 * in_sample
				   + str->a1 * str->x1
				   + str->a2 * str->x2
				   - str->a3 * str->y1
				   - str->a4 * str->y2;
		
		str->x2 = str->x1;
		str->x1 = in_sample;
		
		str->y2 = str->y1;
		str->y1 = out_sample;
		
		out_buffer[i] = out_sample;
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

int init_low_pass_filter_str(m_eng_low_pass_filter_str *str)
{
	FUNCTION_START();
	
	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	str->x1 = 0.0;
	str->x2 = 0.0;
	str->y1 = 0.0;
	str->y2 = 0.0;
	
	RETURN_ERR_CODE(NO_ERROR);
}


int reconfigure_high_pass_filter(void *data_struct)
{
	FUNCTION_START();
	
	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_high_pass_filter_str *str = (m_eng_high_pass_filter_str*)data_struct;
	
	float omega, sin_omega, cos_omega, alpha;
    float b0, b1, b2, a0, a1, a2;

    // Normalized frequency
    omega     = 2.0f * PI * str->cutoff_frequency.value / AUDIO_SAMPLE_RATE_EXACT;
    sin_omega = sinf(omega);
    cos_omega = cosf(omega);

    // Butterworth Q = 1/sqrt(2)
    alpha = sin_omega / (2.0f * 0.70710678f);

    // Coefficients
    b0 =  (1.0f + cos_omega) * 0.5f;
    b1 = -(1.0f + cos_omega);
    b2 =  (1.0f + cos_omega) * 0.5f;
    a0 =   1.0f + alpha;
    a1 =  -2.0f * cos_omega;
    a2 =   1.0f - alpha;

    // Normalise
    str->a0 = b0 / a0;
    str->a1 = b1 / a0;
    str->a2 = b2 / a0;
    str->a3 = a1 / a0;
    str->a4 = a2 / a0;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int calc_high_pass_filter(void *data_struct, float *dest, float *src, int n_samples)
{
	FUNCTION_START();
	
	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_high_pass_filter_str *str = (m_eng_high_pass_filter_str*)data_struct;
	
	float in_sample;
	float out_sample;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	for (int i = 0; i < n_samples; i++)
	{
		in_sample = in_buffer[i];
		
		out_sample = str->a0 * in_sample
				   + str->a1 * str->x1
				   + str->a2 * str->x2
				   - str->a3 * str->y1
				   - str->a4 * str->y2;
		
		out_buffer[i] = out_sample;

		str->x2 = str->x1;
		str->x1 = in_sample;

		str->y2 = str->y1;
		str->y1 = out_sample;
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

int init_high_pass_filter_str(m_eng_high_pass_filter_str *str)
{
	FUNCTION_START();
	
	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	str->x1 = 0.0;
	str->x2 = 0.0;
	str->y1 = 0.0;
	str->y2 = 0.0;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int reconfigure_band_pass_filter(void *data_struct)
{
	FUNCTION_START();
	
	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_band_pass_filter_str *str = (m_eng_band_pass_filter_str*)data_struct;
	
	float omega0 = 2.0f * PI * str->center.value / AUDIO_SAMPLE_RATE_EXACT;
	float sin_omega = sinf(omega0);
	float cos_omega = cosf(omega0);

	float Q = str->center.value / str->bandwidth.value;
	float alpha = sin_omega / (2.0f * Q);

	float b0 =   alpha;
	float b1 =   0.0f;
	float b2 =  -alpha;
	float a0 =   1.0f + alpha;
	float a1 =  -2.0f * cos_omega;
	float a2 =   1.0f - alpha;

    // Normalise
    str->a0 = b0 / a0;
    str->a1 = b1 / a0;
    str->a2 = b2 / a0;
    str->a3 = a1 / a0;
    str->a4 = a2 / a0;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int calc_band_pass_filter(void *data_struct, float *dest, float *src, int n_samples)
{
	FUNCTION_START();
	
	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_band_pass_filter_str *str = (m_eng_band_pass_filter_str*)data_struct;
	
	float in_sample;
	float out_sample;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	for (int i = 0; i < n_samples; i++)
	{
		in_sample = in_buffer[i];
		
		out_sample = str->a0 * in_sample
				   + str->a1 * str->x1
				   + str->a2 * str->x2
				   - str->a3 * str->y1
				   - str->a4 * str->y2;
		
		out_buffer[i] = out_sample;

		str->x2 = str->x1;
		str->x1 = in_sample;

		str->y2 = str->y1;
		str->y1 = out_sample;
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

int init_band_pass_filter_str(m_eng_band_pass_filter_str *str)
{
	FUNCTION_START();
	
	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	str->x1 = 0.0;
	str->x2 = 0.0;
	str->y1 = 0.0;
	str->y2 = 0.0;
	
	RETURN_ERR_CODE(NO_ERROR);
}

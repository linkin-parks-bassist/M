#include "tm.h"

int init_lr_low_pass_filter_str(tm_lr_low_pass_filter_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	str->x_11 = 0.0;
	str->x_12 = 0.0;
	str->y_11 = 0.0;
	str->y_12 = 0.0;
	
	str->x_21 = 0.0;
	str->x_22 = 0.0;
	str->y_21 = 0.0;
	str->y_22 = 0.0;
	
	return NO_ERROR;
}

int reconfigure_lr_low_pass_filter(void *data_struct)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	tm_lr_low_pass_filter_str *str = (tm_lr_low_pass_filter_str*)data_struct;
	
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
	
	return NO_ERROR;
}

int calc_lr_low_pass_filter(void *data_struct, float *dest, float *src, int n_samples)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	tm_lr_low_pass_filter_str *str = (tm_lr_low_pass_filter_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;

	float intermediate;

	for (int i = 0; i < n_samples; i++)
	{
		intermediate = str->a0 * in_buffer[i]
				     + str->a1 * str->x_11
				     + str->a2 * str->x_12
				     - str->a3 * str->y_11
				     - str->a4 * str->y_12;

		str->x_12 = str->x_11;
		str->x_11 = in_buffer[i];

		str->y_12 = str->y_11;
		str->y_11 = intermediate;
		
		out_buffer[i] = str->a0 * intermediate
				      + str->a1 * str->x_21
				      + str->a2 * str->x_22
				      - str->a3 * str->y_21
				      - str->a4 * str->y_22;

		str->x_22 = str->x_21;
		str->x_21 = in_buffer[i];

		str->y_22 = str->y_21;
		str->y_21 = out_buffer[i];
	}
	
	return NO_ERROR;
}

int init_lr_high_pass_filter_str(tm_lr_low_pass_filter_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	str->x_11 = 0.0;
	str->x_12 = 0.0;
	str->y_11 = 0.0;
	str->y_12 = 0.0;
	
	str->x_21 = 0.0;
	str->x_22 = 0.0;
	str->y_21 = 0.0;
	str->y_22 = 0.0;
	
	return NO_ERROR;
}

int reconfigure_lr_high_pass_filter(void *data_struct)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	tm_lr_high_pass_filter_str *str = (tm_lr_high_pass_filter_str*)data_struct;
	
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
	
	return NO_ERROR;
}

int calc_lr_high_pass_filter(void *data_struct, float *dest, float *src, int n_samples)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	tm_lr_high_pass_filter_str *str = (tm_lr_high_pass_filter_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;

	float intermediate;

	for (int i = 0; i < n_samples; i++)
	{
		intermediate = str->a0 * in_buffer[i]
				     + str->a1 * str->x_11
				     + str->a2 * str->x_12
				     - str->a3 * str->y_11
				     - str->a4 * str->y_12;

		str->x_12 = str->x_11;
		str->x_11 = in_buffer[i];

		str->y_12 = str->y_11;
		str->y_11 = intermediate;
		
		out_buffer[i] = str->a0 * intermediate
				      + str->a1 * str->x_21
				      + str->a2 * str->x_22
				      - str->a3 * str->y_21
				      - str->a4 * str->y_22;

		str->x_22 = str->x_21;
		str->x_21 = in_buffer[i];

		str->y_22 = str->y_21;
		str->y_21 = out_buffer[i];
	}
	
	return NO_ERROR;
}

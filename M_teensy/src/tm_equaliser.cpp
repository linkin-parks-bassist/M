#include "tm.h"

int init_3_band_eq_str(tm_3_band_eq_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	str->control_mode = TM_EQ_CONTROL_DIRECT;
	
	str->filters[0].cutoff_frequency.value = 200.0;
	str->filters[0].cutoff_frequency.updated = 1;
	str->filters[1].cutoff_frequency.value = 4000.0;
	str->filters[1].cutoff_frequency.updated = 1;
	
	reconfigure_lr_low_pass_filter(&str->filters[0]);
	reconfigure_lr_low_pass_filter(&str->filters[1]);
	
	return NO_ERROR;
}

int reconfigure_3_band_eq(void *data_struct)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	tm_3_band_eq_str *str = (tm_3_band_eq_str*)data_struct;
	
	if (str->control_mode == TM_EQ_CONTROL_DIRECT)
	{
		str->coefs[0] = str->low.value;
		str->coefs[1] = str->mid.value;
		str->coefs[2] = str->high.value;
	}
	else
	{
		str->coefs[0] = log10f(str->low.value);
		str->coefs[1] = log10f(str->mid.value);
		str->coefs[2] = log10f(str->high.value);
	}
	
	return NO_ERROR;
}

int calc_3_band_eq(void *data_struct, float *dest, float *src, int n_samples)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	tm_3_band_eq_str *str = (tm_3_band_eq_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;

	float *low  = allocate_buffer();
	float *mid  = allocate_buffer();
	float *high = allocate_buffer();
	float *tmp1 = allocate_buffer();
	float *tmp2 = allocate_buffer();
	
	if (!low || !mid || !high || !tmp1 || !tmp2)
		goto eq_3_band_alloc_panic;
	
	//tmp1 = lows
	calc_lr_low_pass_filter(&str->filters[0], tmp1, in_buffer, n_samples);
	
	for (int i = 0; i < n_samples; i++)
	{
		// tmp2 = input - lows
		tmp2[i] = in_buffer[i] - tmp1[i];
		
		out_buffer[i] = str->coefs[0] * tmp1[i];
	}
	
	// tmp1 = lpf_mid(tmp2) = lpf_mid(input - lows) = mids
	calc_lr_low_pass_filter(&str->filters[1], tmp1, tmp2, n_samples);
	
	// tmp2 - tmp1 = input - lows - mids = highs
	for (int i = 0; i < n_samples; i++)
		out_buffer[i] += str->coefs[1] * tmp1[i] + str->coefs[2] * (tmp2[i] - tmp1[i]);
	
	release_buffer(low);
	release_buffer(mid);
	release_buffer(high);
	release_buffer(tmp1);
	release_buffer(tmp2);
	
	return NO_ERROR;

eq_3_band_alloc_panic:
	
	if (low) release_buffer(low);
	if (mid) release_buffer(mid);
	if (high) release_buffer(high);
	if (tmp1) release_buffer(tmp1);
	if (tmp2) release_buffer(tmp2);
	
	return ERR_ALLOC_FAIL;
}

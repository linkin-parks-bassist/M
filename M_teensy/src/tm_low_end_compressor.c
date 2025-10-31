#include "tm.h"

static const char *FNAME = "tm_low_end_compressor.c";
int init_low_end_compressor_str(tm_low_end_compressor_str *str)
{
	FUNCTION_START();

	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	init_compressor_str(&str->bass_comp);
	init_compressor_str(&str->mids_comp);
	
	init_lr_low_pass_filter_str(&str->low_pass);
	init_lr_low_pass_filter_str(&str->mid_pass);
	
	str->low_pass.cutoff_frequency.value = 150.0;
	str->mid_pass.cutoff_frequency.value = 150.0;
	
	reconfigure_lr_low_pass_filter(&str->low_pass);
	reconfigure_lr_low_pass_filter(&str->mid_pass);
	
	RETURN_ERR_CODE(NO_ERROR);
}

int reconfigure_low_end_compressor(void *data_struct)
{
	FUNCTION_START();

	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	tm_low_end_compressor_str *str = (tm_low_end_compressor_str*)data_struct;
	
	reconfigure_compressor(&str->bass_comp);
	reconfigure_compressor(&str->mids_comp);
	
	RETURN_ERR_CODE(NO_ERROR);
}

int calc_low_end_compressor(void *data_struct, float *dest, float *src, int n_samples)
{
	FUNCTION_START();

	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	tm_low_end_compressor_str *str = (tm_low_end_compressor_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	float *bass = NULL;
	float *temp = NULL;
	float *mids = NULL;
	float *high = NULL;
	
	if (!(bass = allocate_buffer())) goto low_end_compressor_alloc_fail;
	if (!(temp = allocate_buffer())) goto low_end_compressor_alloc_fail;
	if (!(mids = allocate_buffer())) goto low_end_compressor_alloc_fail;
	if (!(high = allocate_buffer())) goto low_end_compressor_alloc_fail;
	
	calc_lr_low_pass_filter(&str->low_pass, bass, in_buffer, n_samples);

	for (int i = 0; i < n_samples; i++)
		temp[i] = in_buffer[i] - bass[i];
	
	calc_lr_low_pass_filter(&str->mid_pass, mids, temp, n_samples);
	
	for (int i = 0; i < n_samples; i++)
		high[i] = temp[i] - mids[i];
	
	calc_compressor(&str->bass_comp, out_buffer, bass, n_samples);
	calc_compressor(&str->mids_comp, temp, mids, n_samples);
	
	for (int i = 0; i < n_samples; i++)
		out_buffer[i] += temp[i] + high[i];
	
	
	release_buffer(bass);
	release_buffer(temp);
	release_buffer(mids);
	release_buffer(high);
	
	RETURN_ERR_CODE(NO_ERROR);
	
low_end_compressor_alloc_fail:
	if (bass) release_buffer(bass);
	if (temp) release_buffer(temp);
	if (mids) release_buffer(mids);
	if (high) release_buffer(high);
	
	RETURN_ERR_CODE(ERR_ALLOC_FAIL);
}

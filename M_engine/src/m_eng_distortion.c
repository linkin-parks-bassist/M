#include "m_eng.h"

static const char *FNAME = "m_eng_distortion.c";


int init_distortion_str(m_eng_distortion_str *str)
{
	FUNCTION_START();

	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	init_waveshaper_str(&str->dist);
	
	init_lr_low_pass_filter_str(&str->low_pass);
	reconfigure_lr_low_pass_filter((void*)&str->low_pass);
	
	RETURN_ERR_CODE(NO_ERROR);
}

int reconfigure_distortion(void *data_struct)
{
	FUNCTION_START();

	m_eng_distortion_str *str = (m_eng_distortion_str*)data_struct;
	
	printf("Reconfigure_distortion. str->function.updated = %d\n", str->function.updated);
	if (str->function.updated)
	{
		switch (str->function.value)
		{
			case M_DISTORTION_CLIP:
				str->dist.shape = hard_clip;
				break;
			case M_DISTORTION_TANH:
				str->dist.shape = tanhf;
				break;
			case M_DISTORTION_ARCTAN:
				str->dist.shape = normalised_arctan;
				break;
			case M_DISTORTION_FOLD:
				str->dist.shape = soft_fold;
				break;
			default:
				str->dist.shape = hard_clip;
				break;
		}
	}
	
	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (str->low_pass.cutoff_frequency.updated)
	{
		reconfigure_lr_low_pass_filter((void*)&str->low_pass);
	}

	RETURN_ERR_CODE(NO_ERROR);
}

int calc_distortion(void *data_struct, float *dest, float *src, int n_samples)
{
	FUNCTION_START();

	if (!dest || !src || !data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_distortion_str *str = (m_eng_distortion_str*)data_struct;
	
	int ret_val = NO_ERROR;
	
	float *in_buffer  =  src ?  src : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	float *low	= NULL;
	float *high	= NULL;
	float *dist = NULL;
	
	if (!(low  = allocate_buffer())) goto distortion_alloc_fail;
	if (!(high = allocate_buffer())) goto distortion_alloc_fail;
	if (!(dist = allocate_buffer())) goto distortion_alloc_fail;
	
	calc_lr_low_pass_filter(&str->low_pass, low, in_buffer, n_samples);
	
	for (int i = 0; i < n_samples; i++)
		high[i] = in_buffer[i] - low[i];
	
	calc_waveshaper(&str->dist, dist, high, n_samples);
	
	for (int i = 0; i < n_samples; i++)
	{
		out_buffer[i] = str->wet_mix.value * (str->bass_mix.value * low[i] + (1.0 - str->bass_mix.value) * dist[i]) + (1.0 - str->wet_mix.value) * in_buffer[i]; 
	}
	
	release_buffer(low);
	release_buffer(high);
	release_buffer(dist);
	
	RETURN_ERR_CODE(NO_ERROR);
	
distortion_alloc_fail:
	if (low ) release_buffer(low );
	if (high) release_buffer(high);
	if (dist) release_buffer(dist);
	
	RETURN_ERR_CODE(ERR_ALLOC_FAIL);
}

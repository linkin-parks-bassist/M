#include "tm.h"

/* I'll need some temp buffers for computing distortion */
#ifdef USE_GLOBAL_TEMP_BUFFERS
tm_audio_block_float *tmp_block;
float *tmp;
tm_audio_block_float *low_block;
float *low;
tm_audio_block_float *mid_block;
float *mid;
tm_audio_block_float *high_block;
float *high;
tm_audio_block_float *mid_distorted_block;
float *mid_distorted;
tm_audio_block_float *high_distorted_block;
float *high_distorted;

int distortion_temp_buffers_allocated = 0;

int alloc_distortion_temp_buffers()
{
	if (!(tmp_block = allocate_block()))  return ERR_ALLOC_FAIL;
	tmp = &tmp_block->data[0];
	if (!(low_block = allocate_block()))  return ERR_ALLOC_FAIL;
	low = &low_block->data[0];
	if (!(mid_block = allocate_block()))  return ERR_ALLOC_FAIL;
	mid = &mid_block->data[0];
	if (!(high_block = allocate_block())) return ERR_ALLOC_FAIL;
	high = &high_block->data[0];

	if (!(mid_distorted_block = allocate_block())) return ERR_ALLOC_FAIL;
	mid_distorted  = &mid_distorted_block->data[0];
	if (!(high_distorted_block = allocate_block())) return ERR_ALLOC_FAIL;
	high_distorted = &high_distorted_block->data[0];

	distortion_temp_buffers_allocated = 1;
	
	return NO_ERROR;
}
#endif

float normalised_arctan(float x)
{
	return 0.63661977237 * atan(x);
}

float hard_clip(float x)
{
	if (x > 1.0)
		return 1.0;
	if (x < -1.0)
		return -1.0;
	else
		return x;
}

float soft_fold(float x)
{
	return x / (1 + fabsf(x));
}

int init_distortion_str(tm_distortion_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	init_option_simple(&str->type, DISTORTION_TANH);
	
	str->mid_distortion.coefficient.value = str->gain.value;
	str->mid_distortion.shape = tanhf;
	init_waveshaper_str(&str->mid_distortion);
	
	str->high_distortion.coefficient.value = str->gain.value * str->ratio.value;
	str->high_distortion.shape = tanhf;
	init_waveshaper_str(&str->high_distortion);
	
	str->low_pass_1.cutoff_frequency.value = str->bass_cutoff.value;
	str->low_pass_2.cutoff_frequency.value = str->bass_cutoff.value;
	
	str->mid_pass_1.center.value = sqrt(str->bass_cutoff.value * str->mid_cutoff.value);
	str->mid_pass_2.center.value = sqrt(str->bass_cutoff.value * str->mid_cutoff.value);
	
	str->mid_pass_1.bandwidth.value = str->mid_cutoff.value - str->bass_cutoff.value;
	str->mid_pass_2.bandwidth.value = str->mid_cutoff.value - str->bass_cutoff.value;
	
	str->high_pass_1.cutoff_frequency.value = str->mid_cutoff.value;
	str->high_pass_2.cutoff_frequency.value = str->mid_cutoff.value;
	
	init_low_pass_filter_str (&str->low_pass_1);
	init_low_pass_filter_str (&str->low_pass_2);
	init_band_pass_filter_str(&str->mid_pass_1);
	init_band_pass_filter_str(&str->mid_pass_2);
	init_high_pass_filter_str(&str->high_pass_1);
	init_high_pass_filter_str(&str->high_pass_2);
	
	reconfigure_low_pass_filter (&str->low_pass_1);
	reconfigure_low_pass_filter (&str->low_pass_2);
	reconfigure_band_pass_filter(&str->mid_pass_1);
	reconfigure_band_pass_filter(&str->mid_pass_2);
	reconfigure_high_pass_filter(&str->high_pass_1);
	reconfigure_high_pass_filter(&str->high_pass_2);
	
	str->total_samples = 0;
	
	return NO_ERROR;
}

int reconfigure_distortion(void *data_struct)
{
	tm_distortion_str *str = (tm_distortion_str*)data_struct;
	
	if (!str)
		return ERR_NULL_PTR;
	
	if (str->gain.updated)
		str->mid_distortion.coefficient.value = str->gain.value;
	
	if (str->gain.updated || str->ratio.updated)
		str->high_distortion.coefficient.value = str->gain.value * str->ratio.value;
	
	int update_cutoffs = 0;
	
	if (str->mid_cutoff.updated)
	{
		update_cutoffs = 1;
		str->high_pass_1.cutoff_frequency.value = str->mid_cutoff.value;
		str->high_pass_2.cutoff_frequency.value = str->mid_cutoff.value;
		
		reconfigure_high_pass_filter((void*)&str->high_pass_1);
		reconfigure_high_pass_filter((void*)&str->high_pass_2);
	}
	
	if (str->bass_cutoff.updated)
	{
		update_cutoffs = 1;
		str->low_pass_1.cutoff_frequency.value = str->bass_cutoff.value;
		str->low_pass_2.cutoff_frequency.value = str->bass_cutoff.value;
		
		reconfigure_low_pass_filter((void*)&str->low_pass_1);
		reconfigure_low_pass_filter((void*)&str->low_pass_2);
	}
	
	if (update_cutoffs)
	{
		str->mid_pass_1.center.value = sqrt(str->bass_cutoff.value * str->mid_cutoff.value);
		str->mid_pass_2.center.value = str->mid_pass_1.center.value;
		
		str->mid_pass_1.bandwidth.value = str->mid_cutoff.value - str->bass_cutoff.value;
		str->mid_pass_2.bandwidth.value = str->mid_pass_1.bandwidth.value;
		
		reconfigure_band_pass_filter((void*)&str->mid_pass_1);
		reconfigure_band_pass_filter((void*)&str->mid_pass_2);
	}
	
	return NO_ERROR;
}

int calc_distortion(void *data_struct, float *dest, float *src, int n_samples)
{
	if (!dest || !src || !data_struct)
		return ERR_NULL_PTR;
	
	tm_distortion_str *str = (tm_distortion_str*)data_struct;
	
	int ret_val = NO_ERROR;
	
	float *in_buffer  =  src ?  src : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	#ifndef NO_CMSIS
	float *tmp1 = NULL;
	float *tmp2 = NULL;
	float *tmp3 = NULL;
	#endif
	
	#ifndef USE_GLOBAL_TEMP_BUFFERS
	float *tmp = NULL;
	float *low = NULL;
	float *mid = NULL;
	float *high = NULL;
	float *mid_distorted = NULL;
	float *high_distorted = NULL;
	#endif
	
	#ifdef USE_GLOBAL_TEMP_BUFFERS
	if (!distortion_temp_buffers_allocated)
	{
		ret_val = alloc_distortion_temp_buffers();
		
		if (ret_val != NO_ERROR)
			goto distortion_cleanup;
	}
	#else
	tmp = allocate_buffer();
	low = allocate_buffer();
	mid = allocate_buffer();
	high = allocate_buffer();
	mid_distorted = allocate_buffer();
	high_distorted = allocate_buffer();
	
	if (!tmp || !low || !mid || !high || !mid_distorted || !high_distorted)
	{
		ret_val = ERR_ALLOC_FAIL;
		goto distortion_cleanup;
	}
	#endif
	float e;
	/*tm_printf("~DISTORTION~\n");
	tm_printf("Gain:        %6f\n", str->gain.value);
	tm_printf("Wet mix:     %6f\n", str->wet_mix.value);
	tm_printf("High mix:    %6f\n", str->high_mix.value);
	tm_printf("Mid mix:     %6f\n", str->mid_mix.value);
	tm_printf("Mid dist:    %6f\n", str->mid_distortion.coefficient.value);
	tm_printf("High dist:   %6f\n", str->high_distortion.coefficient.value);
	tm_printf("Bass mix:    %6f\n", str->bass_mix.value);
	tm_printf("Mid cutoff:  %6f\n", str->mid_cutoff.value);
	tm_printf("Bass cutoff: %6f\n", str->bass_cutoff.value);
	tm_printf("Ratio:       %6f\n", str->ratio.value);*/
	
	//pretty_print_block_float(src, "Input:");
	
	/*reconfigure_biquad((void*)&str->high_pass_1);
	reconfigure_biquad((void*)&str->high_pass_2);
	reconfigure_biquad((void*)&str->low_pass_1);
	reconfigure_biquad((void*)&str->low_pass_2);
	reconfigure_biquad((void*)&str->mid_pass_1);
	reconfigure_biquad((void*)&str->mid_pass_2);*/
	
	ret_val = calc_low_pass_filter((void*)&str->low_pass_1, tmp,  in_buffer, n_samples);
	if (ret_val != NO_ERROR)
		goto distortion_cleanup;
	
	ret_val = calc_low_pass_filter((void*)&str->low_pass_2, low,  tmp, n_samples);
	if (ret_val != NO_ERROR)
		goto distortion_cleanup;
	
	
	ret_val = calc_band_pass_filter((void*)&str->mid_pass_1, tmp,  in_buffer, n_samples);
	if (ret_val != NO_ERROR)
		goto distortion_cleanup;
	
	ret_val = calc_band_pass_filter((void*)&str->mid_pass_2, mid,  tmp, n_samples);
	if (ret_val != NO_ERROR)
		goto distortion_cleanup;
	
	
	ret_val = calc_high_pass_filter((void*)&str->high_pass_1, tmp,  in_buffer, n_samples);
	if (ret_val != NO_ERROR)
		goto distortion_cleanup;
	
	ret_val = calc_high_pass_filter((void*)&str->high_pass_2, high, tmp, n_samples);
	if (ret_val != NO_ERROR)
		goto distortion_cleanup;
	
	
	ret_val = calc_waveshaper((void*)&str->mid_distortion , mid_distorted,  mid, n_samples);
	if (ret_val != NO_ERROR)
		goto distortion_cleanup;
	
	ret_val = calc_waveshaper((void*)&str->high_distortion, high_distorted, high, n_samples);
	if (ret_val != NO_ERROR)
		goto distortion_cleanup;
	
	//tm_printf("Distorted high energy: %f\n", sqrt(e));
	
	//pretty_print_block_float(low, "Lows:");
	//pretty_print_block_float(mid, "Mids:");
	//pretty_print_block_float(high, "Highs:");
	//pretty_print_block_float(high, "Mids (distorted):");
	//pretty_print_block_float(high, "Highs (distorted):");
	
	#ifndef NO_CMSIS
	tmp1 = allocate_buffer();
	if (!tmp1)
		goto distortion_manual;
	tmp2 = allocate_buffer();
	if (!tmp2)
	{
		release_buffer(tmp1);
		goto distortion_manual;
	}
	tmp3 = allocate_buffer();
	if (!tmp3)
	{
		release_buffer(tmp1);
		release_buffer(tmp2);
		goto distortion_manual;
	}
	
	arm_scale_f32(low, 			 str->bass_mix.value, tmp1, n_samples);
	arm_scale_f32(mid_distorted, str->mid_mix.value,  tmp2, n_samples);
	
	arm_add_f32(tmp1, tmp2, tmp3, n_samples);
	
	arm_scale_f32(high_distorted, str->high_mix.value, tmp1, n_samples);
	
	arm_add_f32(tmp1, tmp3, tmp2, n_samples);
	
	arm_scale_f32(tmp2, str->wet_mix.value, tmp1, n_samples);
	
	arm_scale_f32(in_buffer, (1.0 - str->wet_mix.value), tmp2, n_samples);
	
	arm_add_f32(tmp1, tmp2, out_buffer, n_samples);
	
	release_buffer(tmp1);
	release_buffer(tmp2);
	release_buffer(tmp3);
	
	goto distortion_cleanup;
distortion_manual:
	#endif
	
	for (int i = 0; i < n_samples; i++)
	{
		out_buffer[i] = str->wet_mix.value * (   str->bass_mix.value    * low[i]
											   + str->mid_mix.value     * mid_distorted[i]
											   + str->high_mix.value    * high_distorted[i])
										   + (1.0 - str->wet_mix.value) * in_buffer[i];
		
		#ifdef TM_SIMULATED
		transformer_dump(data_struct, TRANSFORMER_DISTORTION, out_buffer, in_buffer, i);
		#endif
		
		str->total_samples++;
	}
	
distortion_cleanup:
	#ifndef USE_GLOBAL_TEMP_BUFFERS
	release_buffer(tmp);
	release_buffer(low);
	release_buffer(mid);
	release_buffer(high);
	release_buffer(mid_distorted);
	release_buffer(high_distorted);
	#endif
	
	return ret_val;
}

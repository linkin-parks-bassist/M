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

int init_distortion_struct_default(tm_distortion_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	init_option_simple(&str->type, DISTORTION_TANH);
	
	init_waveshaper_struct(&str->mid_distortion,  tanh, 0);
	init_waveshaper_struct(&str->high_distortion, tanh, 0);
	
	init_biquad_struct_lowpass (&str->low_pass_1,  str->bass_cutoff.value);
	init_biquad_struct_lowpass (&str->low_pass_2,  str->bass_cutoff.value);
	init_biquad_struct_bandpass(&str->mid_pass_1,  sqrt(str->bass_cutoff.value * str->mid_cutoff.value), log2f(str->mid_cutoff.value / str->bass_cutoff.value));
	init_biquad_struct_bandpass(&str->mid_pass_2,  sqrt(str->bass_cutoff.value * str->mid_cutoff.value), log2f(str->mid_cutoff.value / str->bass_cutoff.value));
	init_biquad_struct_highpass(&str->high_pass_1, str->mid_cutoff.value);
	init_biquad_struct_highpass(&str->high_pass_2, str->mid_cutoff.value);
	
	return NO_ERROR;
}

int init_distortion_struct(tm_distortion_str *data_struct, int type,
						   float bass_cutoff, float mid_cutoff, float gain, float ratio,
						   float bass_mix, float mid_mix,float high_mix, float wet_mix)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	float (*shape)(float x);
	
	init_option_simple(&data_struct->type, type);
	
	switch (type)
	{
		case DISTORTION_SOFT_FOLD:
			shape = soft_fold;
			break;
		
		case DISTORTION_ARCTAN:
			shape = normalised_arctan;
			break;
			
		case DISTORTION_TANH:
			shape = tanh;
			break;
			
		case DISTORTION_CLIP:
			shape = hard_clip;
			break;
			
		default:
			return ERR_BAD_ARGS;
	}
	
	init_waveshaper_struct(&data_struct->mid_distortion,  shape, 0);
	init_waveshaper_struct(&data_struct->high_distortion, shape, 0);
	
	init_biquad_struct_lowpass (&data_struct->low_pass_1,  bass_cutoff);
	init_biquad_struct_lowpass (&data_struct->low_pass_2,  bass_cutoff);
	init_biquad_struct_bandpass(&data_struct->mid_pass_1,  sqrt(bass_cutoff * mid_cutoff), log2f(mid_cutoff / bass_cutoff));
	init_biquad_struct_bandpass(&data_struct->mid_pass_2,  sqrt(bass_cutoff * mid_cutoff), log2f(mid_cutoff / bass_cutoff));
	init_biquad_struct_highpass(&data_struct->high_pass_1, mid_cutoff);
	init_biquad_struct_highpass(&data_struct->high_pass_2, mid_cutoff);
	
	init_parameter_simple(&data_struct->gain, gain);
	data_struct->gain.update_policy = PARAMETER_UPDATE_INSTANT;
	
	init_parameter_simple(&data_struct->wet_mix, wet_mix);
	
	init_parameter_simple(&data_struct->mid_mix, mid_mix);
	init_parameter_simple(&data_struct->bass_mix, bass_mix);
	init_parameter_simple(&data_struct->high_mix, high_mix);
	
	init_parameter_simple(&data_struct->bass_cutoff, bass_cutoff);
	init_parameter_simple(&data_struct->mid_cutoff, mid_cutoff);
	
	init_parameter_simple(&data_struct->ratio, ratio);
	data_struct->ratio.update_policy = PARAMETER_UPDATE_INSTANT;
	
	return NO_ERROR;
}

int reconfigure_distortion(void *data_struct)
{
	tm_printf("reconfigure_distortion\n");
	tm_distortion_str *str = (tm_distortion_str*)data_struct;
	
	if (!str)
		return ERR_NULL_PTR;
	
	if (str->gain.updated || str->ratio.updated)
		str->mid_distortion.coefficient.value = str->gain.value;
	
	if (str->gain.updated || str->ratio.updated)
		str->high_distortion.coefficient.value = str->gain.value * str->ratio.value;
	
	int update_cutoffs = 0;
	
	if (str->mid_cutoff.updated)
	{
		update_cutoffs = 1;
		str->high_pass_1.cutoff.value = str->mid_cutoff.value;
		str->high_pass_2.cutoff.value = str->mid_cutoff.value;
		
		reconfigure_biquad((void*)&str->high_pass_1);
		reconfigure_biquad((void*)&str->high_pass_2);
	}
	
	if (str->bass_cutoff.updated)
	{
		update_cutoffs = 1;
		str->low_pass_1.cutoff.value = str->bass_cutoff.value;
		str->low_pass_2.cutoff.value = str->bass_cutoff.value;
		
		reconfigure_biquad((void*)&str->low_pass_1);
		reconfigure_biquad((void*)&str->low_pass_2);
	}
	
	if (update_cutoffs)
	{
		str->mid_pass_1.cutoff.value = sqrt(str->bass_cutoff.value * str->mid_cutoff.value);
		str->mid_pass_2.cutoff.value = str->mid_pass_1.cutoff.value;
		
		str->mid_pass_1.bandwidth.value = log2f(str->mid_cutoff.value / str->bass_cutoff.value);
		str->mid_pass_2.bandwidth.value = str->mid_pass_1.bandwidth.value;
		
		reconfigure_biquad((void*)&str->mid_pass_1);
		reconfigure_biquad((void*)&str->mid_pass_2);
	}
	
	tm_printf("reconfigure_distortion done\n");
	return NO_ERROR;
}

int calc_distortion(void *data_struct, float **dest, float **src, int n_samples)
{
	if (!dest || !src || !data_struct)
		return ERR_NULL_PTR;
	
	tm_distortion_str *str = (tm_distortion_str*)data_struct;
	
	int ret_val = NO_ERROR;
	
	float *in_buffer  =  src[0] ?  src[0] : zero_buffer;
	float *out_buffer = dest[0] ? dest[0] : sink_buffer;
	
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
	
	//pretty_print_block_float(src[0], "Input:");
	
	/*reconfigure_biquad((void*)&str->high_pass_1);
	reconfigure_biquad((void*)&str->high_pass_2);
	reconfigure_biquad((void*)&str->low_pass_1);
	reconfigure_biquad((void*)&str->low_pass_2);
	reconfigure_biquad((void*)&str->mid_pass_1);
	reconfigure_biquad((void*)&str->mid_pass_2);*/
	
	ret_val = calc_biquad((void*)&str->low_pass_1, &tmp,  &in_buffer, n_samples);
	if (ret_val != NO_ERROR)
		goto distortion_cleanup;
	
	ret_val = calc_biquad((void*)&str->low_pass_2, &low,  &tmp, n_samples);
	if (ret_val != NO_ERROR)
		goto distortion_cleanup;
	
	
	ret_val = calc_biquad((void*)&str->mid_pass_1, &tmp,  &in_buffer, n_samples);
	if (ret_val != NO_ERROR)
		goto distortion_cleanup;
	
	ret_val = calc_biquad((void*)&str->mid_pass_2, &mid,  &tmp, n_samples);
	if (ret_val != NO_ERROR)
		goto distortion_cleanup;
	
	
	ret_val = calc_biquad((void*)&str->high_pass_1, &tmp,  &in_buffer, n_samples);
	if (ret_val != NO_ERROR)
		goto distortion_cleanup;
	
	ret_val = calc_biquad((void*)&str->high_pass_2, &high, &tmp, n_samples);
	if (ret_val != NO_ERROR)
		goto distortion_cleanup;
	
	
	ret_val = calc_waveshaper((void*)&str->mid_distortion , &mid_distorted,  &mid, n_samples);
	if (ret_val != NO_ERROR)
		goto distortion_cleanup;
	
	ret_val = calc_waveshaper((void*)&str->high_distortion, &high_distorted, &high, n_samples);
	if (ret_val != NO_ERROR)
		goto distortion_cleanup;
	
	
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

int init_distortion(tm_transformer *trans, vec2i input, vec2i output, int type, float gain, float ratio)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	tm_distortion_str *data_struct = (tm_distortion_str*)malloc(sizeof(tm_distortion_str));
	
	if (!data_struct)
		return ERR_ALLOC_FAIL;
	
	tm_printf("Init distortion struct...\n");
	init_distortion_struct(data_struct, type, 100.0, 1000.0, gain, ratio, 0.4, 0.3, 0.3, 0.7);
	
	tm_printf("Init transformer struct...\n");
	int ret_val = init_transformer(trans, TRANSFORMER_DISTORTION, 1, 1, &input, &output, 1, 10, (void*)data_struct, calc_distortion);
	
	if (ret_val != NO_ERROR)
	{
		trans->data_struct = NULL;
		free(data_struct);
		return ret_val;
	}
	
	tm_printf("Add parameters...\n");
	
	transformer_add_option(trans, &data_struct->type);
	
	transformer_add_parameter(trans, &data_struct->gain);
	tm_printf("Gain = parameter %d\n", trans->n_parameters - 1);
	transformer_add_parameter(trans, &data_struct->wet_mix);
	tm_printf("Wet mix = parameter %d\n", trans->n_parameters - 1);
	transformer_add_parameter(trans, &data_struct->high_mix);
	tm_printf("High mix = parameter %d\n", trans->n_parameters - 1);
	transformer_add_parameter(trans, &data_struct->mid_mix);
	tm_printf("Mid mix = parameter %d\n", trans->n_parameters - 1);
	transformer_add_parameter(trans, &data_struct->bass_mix);
	tm_printf("Bass mix = parameter %d\n", trans->n_parameters - 1);
	transformer_add_parameter(trans, &data_struct->mid_cutoff);
	tm_printf("Mid cutoff = parameter %d\n", trans->n_parameters - 1);
	transformer_add_parameter(trans, &data_struct->bass_cutoff);
	tm_printf("Bass cutoff = parameter %d\n", trans->n_parameters - 1);
	transformer_add_parameter(trans, &data_struct->ratio);
	tm_printf("Ratio = parameter %d\n", trans->n_parameters - 1);
	
	return NO_ERROR;
}

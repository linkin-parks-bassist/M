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

int calc_distortion(float **dest, float **src, void *data_struct)
{
	if (!dest || !src || !data_struct)
		return ERR_NULL_PTR;
	
	tm_distortion_str *str = (tm_distortion_str*)data_struct;
	
	#ifdef USE_GLOBAL_TEMP_BUFFERS
	if (!distortion_temp_buffers_allocated)
	{
		if (alloc_distortion_temp_buffers() != NO_ERROR)
		{
			for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
				dest[0][i] = src[0][i];
		}
	}
	#else
	float *tmp = allocate_buffer();
	float *low = allocate_buffer();
	float *mid = allocate_buffer();
	float *high = allocate_buffer();
	float *mid_distorted = allocate_buffer();
	float *high_distorted = allocate_buffer();
	#endif
	
	if (!tmp || !low || !mid || !high || !mid_distorted || !high_distorted)
	{
		tm_printf("ALLOC FAIL\n");
		return ERR_ALLOC_FAIL;
	}
	
	if (str->gain.updated || str->ratio.updated)
	{
		parameter_update_finish(&str->gain);
		update_parameter_update(&str->mid_distortion.coefficient, str->gain.new_value);
	}
	
	if (str->gain.updated || str->ratio.updated)
	{
		parameter_update_finish(&str->ratio);
		update_parameter_update(&str->high_distortion.coefficient, str->gain.value * str->ratio.value);
	}
	
	int update_cutoffs = 0;
	
	if (str->mid_cutoff.updated)
	{
		update_cutoffs = 1;
		parameter_update_finish(&str->mid_cutoff);
		update_parameter_update(&str->high_pass_1.cutoff, str->mid_cutoff.value);
		update_parameter_update(&str->high_pass_2.cutoff, str->mid_cutoff.value);
	}
	
	if (str->bass_cutoff.updated)
	{
		update_cutoffs = 1;
		parameter_update_finish(&str->bass_cutoff);
		update_parameter_update(&str->low_pass_1.cutoff, str->bass_cutoff.value);
		update_parameter_update(&str->low_pass_2.cutoff, str->bass_cutoff.value);
	}
	
	if (update_cutoffs)
	{
		update_parameter_update(&str->mid_pass_1.cutoff, sqrt(str->bass_cutoff.value * str->mid_cutoff.value));
		update_parameter_update(&str->mid_pass_2.cutoff, sqrt(str->bass_cutoff.value * str->mid_cutoff.value));
		
		update_parameter_update(&str->mid_pass_1.bandwidth, log2f(str->mid_cutoff.value / str->bass_cutoff.value));
		update_parameter_update(&str->mid_pass_2.bandwidth, log2f(str->mid_cutoff.value / str->bass_cutoff.value));
	}
	
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
	
	
	
	calc_biquad(&tmp,  src,  (void*)&str->low_pass_1);
	calc_biquad(&low,  &tmp, (void*)&str->low_pass_2);
	
	calc_biquad(&tmp,  src,  (void*)&str->mid_pass_1);
	calc_biquad(&mid,  &tmp, (void*)&str->mid_pass_2);
	
	calc_biquad(&tmp,  src,  (void*)&str->high_pass_1);
	calc_biquad(&high, &tmp, (void*)&str->high_pass_2);
	
	calc_waveshaper(&mid_distorted,  &mid,  (void*)&str->mid_distortion );
	calc_waveshaper(&high_distorted, &high, (void*)&str->high_distortion);
	
	//pretty_print_block_float(low, "Lows:");
	//pretty_print_block_float(mid, "Mids:");
	//pretty_print_block_float(high, "Highs:");
	//pretty_print_block_float(high, "Mids (distorted):");
	//pretty_print_block_float(high, "Highs (distorted):");
	
	// 1800
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		parameter_update_tick(&str->wet_mix);
		parameter_update_tick(&str->bass_mix);
		parameter_update_tick(&str->mid_mix);
		parameter_update_tick(&str->high_mix);
		
		dest[0][i] = str->wet_mix.value * (str->bass_mix.value * low[i]
													 + str->mid_mix.value   * mid_distorted[i]
													 + str->high_mix.value  * high_distorted[i])
				   + (1.0 - str->wet_mix.value) * src[0][i];
	}
	
	// 1850
	
	//pretty_print_block_float(dest[0], "Output:");
	
	#ifndef USE_GLOBAL_TEMP_BUFFERS
	release_buffer(tmp);
	release_buffer(low);
	release_buffer(mid);
	release_buffer(high);
	release_buffer(mid_distorted);
	release_buffer(high_distorted);
	#endif
	
	return NO_ERROR;
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

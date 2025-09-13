#include "M.h"

m_audio_block_float *tmp_block;
float *tmp;

m_audio_block_float *low_block;
float *low;

m_audio_block_float *mid_block;
float *mid;

m_audio_block_float *high_block;
float *high;


m_audio_block_float *mid_distorted_block;
float *mid_distorted;

m_audio_block_float *high_distorted_block;
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

int init_distortion_struct(m_distortion_data *data_struct, int type, float bass_cutoff, float mid_cutoff,
						   float gain, float ratio, float bass_mix, float mid_mix, float high_mix, float wet_mix)
{
	if (!data_struct)
		return ERR_NULL_PTR;
		
	float (*shape)(float x);
	
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
	
	init_parameter(&data_struct->gain,  "Gain", gain);
	init_parameter(&data_struct->ratio, "Ratio", ratio);
	
	init_parameter(&data_struct->bass_cutoff, "Bass cutoff", bass_cutoff);
	init_parameter(&data_struct->mid_cutoff,  "Mid cutoff",  mid_cutoff);
	init_parameter(&data_struct->bass_mix,	  "Bass mix", 	 bass_mix);
	init_parameter(&data_struct->mid_mix,	  "Mid mix", 	 mid_mix);
	init_parameter(&data_struct->high_mix,	  "High mix", 	 high_mix);
	init_parameter(&data_struct->wet_mix,	  "Wet mix", 	 wet_mix);
	
	return NO_ERROR;
}

int calc_distortion(float **dest, float **src, void *transformer_data)
{
	if (!dest || !src || !transformer_data)
		return ERR_NULL_PTR;
	
	m_distortion_data *data_struct = (m_distortion_data*)transformer_data;
	
	if (!distortion_temp_buffers_allocated)
	{
		if (alloc_distortion_temp_buffers() != NO_ERROR)
		{
			for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
				dest[0][i] = src[0][i];
		}
	}
	
	if (data_struct->gain.updated || data_struct->ratio.updated)
	{
		data_struct->mid_distortion.coefficient.value  = data_struct->gain.value;
		data_struct->high_distortion.coefficient.value = data_struct->gain.value * data_struct->ratio.value;
	}
	
	#ifdef PRINT_TRANSFORMER_INFO
	m_printf("Gain: %6f, ratio: %6f\n", data_struct->gain.value, data_struct->ratio.value);
	#endif
	
	calc_biquad(&tmp,  src,  (void*)&data_struct->low_pass_1);
	calc_biquad(&low,  &tmp, (void*)&data_struct->low_pass_2);
	
	calc_biquad(&tmp,  src,  (void*)&data_struct->mid_pass_1);
	calc_biquad(&mid,  &tmp, (void*)&data_struct->mid_pass_2);
	
	calc_biquad(&tmp,  src,  (void*)&data_struct->high_pass_1);
	calc_biquad(&high, &tmp, (void*)&data_struct->high_pass_2);
	
	calc_waveshaper(&mid_distorted,  &mid,  (void*)&data_struct->mid_distortion );
	calc_waveshaper(&high_distorted, &high, (void*)&data_struct->high_distortion);
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		dest[0][i] = data_struct->wet_mix.value * (data_struct->bass_mix.value * low[i]
												 + data_struct->mid_mix.value  * mid_distorted[i]
												 + data_struct->high_mix.value * high_distorted[i])
					+ (1.0 - data_struct->wet_mix.value) * src[0][i];
	}
	
	return NO_ERROR;
}

int init_distortion_transformer(m_audio_transformer *trans, vec2i input, vec2i output, int type, float gain, float ratio)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	m_distortion_data *data_struct = (m_distortion_data*)malloc(sizeof(m_distortion_data));
	
	if (!data_struct)
		return ERR_ALLOC_FAIL;
	
	m_printf("Init distortion struct...\n");
	init_distortion_struct(data_struct, type, 100.0, 1000.0, gain, ratio, 0.4, 0.3, 0.3, 0.7);
	
	m_printf("Init transformer struct...\n");
	int ret_val = init_transformer(trans, TRANSFORMER_DISTORTION, 1, 1, &input, &output, 10, (void*)data_struct, calc_distortion);
	
	if (ret_val != NO_ERROR)
	{
		trans->transformer_data = NULL;
		free(data_struct);
		return ret_val;
	}
	
	m_printf("Add parameters...\n");
	
	parameter_set_name(&data_struct->mid_distortion.coefficient,  "Mid gain");
	parameter_set_name(&data_struct->high_distortion.coefficient, "High gain");
	
	transformer_add_parameter(trans, &data_struct->mid_distortion.coefficient);
	transformer_add_parameter(trans, &data_struct->high_distortion.coefficient);
	
	transformer_add_parameter(trans, &data_struct->gain);
	transformer_add_parameter(trans, &data_struct->ratio);
	transformer_add_parameter(trans, &data_struct->bass_cutoff);
	transformer_add_parameter(trans, &data_struct->mid_cutoff);
	transformer_add_parameter(trans, &data_struct->bass_mix);
	transformer_add_parameter(trans, &data_struct->mid_mix);
	transformer_add_parameter(trans, &data_struct->high_mix);
	transformer_add_parameter(trans, &data_struct->wet_mix);
	
	return NO_ERROR;
}

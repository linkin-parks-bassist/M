#include "tm.h"

int calc_biquad(float **dest, float **src, void *data_struct)
{
	if (!data_struct || !dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0] || !src[0])
		return ERR_NULL_PTR;
	
	tm_biquad_str *biquad = (tm_biquad_str*)data_struct;
	
	
	float a0_delta = 0.0;
	float a1_delta = 0.0;
	float a2_delta = 0.0;
	float a3_delta = 0.0;
	float a4_delta = 0.0;
	
	int ret_val;
	
	//tm_printf("Calculating biquad transform... updatedness = (%d, %d, %d, %d)\n",
	//	biquad->type.updated, biquad->cutoff.updated, biquad->bandwidth.updated, biquad->db_gain.updated);
	
	int parameters_updated = 0;
	
	parameters_updated |= biquad->type.updated;
	parameters_updated |= biquad->cutoff.updated;
	parameters_updated |= biquad->bandwidth.updated;
	parameters_updated |= biquad->db_gain.updated;
	
	if (parameters_updated)
	{
		biquad->type.updated = 0;
		
		parameter_update_finish(&biquad->cutoff);
		parameter_update_finish(&biquad->bandwidth);
		parameter_update_finish(&biquad->db_gain);
		
		float a0_old = biquad->a0;
		float a1_old = biquad->a1;
		float a2_old = biquad->a2;
		float a3_old = biquad->a3;
		float a4_old = biquad->a4;
		
		if ((ret_val = compute_biquad_coefficients(biquad)) != NO_ERROR)
		{
			tm_printf("ERROR configuring biquad !\n");
			return ret_val;
		}
		
		a0_delta = (biquad->a0 - a0_old) / AUDIO_BLOCK_SAMPLES;
		a1_delta = (biquad->a1 - a1_old) / AUDIO_BLOCK_SAMPLES;
		a2_delta = (biquad->a2 - a2_old) / AUDIO_BLOCK_SAMPLES;
		a3_delta = (biquad->a3 - a3_old) / AUDIO_BLOCK_SAMPLES;
		a4_delta = (biquad->a4 - a4_old) / AUDIO_BLOCK_SAMPLES;
		
		tm_printf("Updating biquad exponents; deltas = (%6f, %6f, %6f, %6f, %6f)\n", a0_delta, a1_delta, a2_delta, a3_delta, a4_delta);
		biquad->a0 = a0_old;
		biquad->a1 = a1_old;
		biquad->a2 = a2_old;
		biquad->a3 = a3_old;
		biquad->a4 = a4_old;
	}
	
	//tm_printf("Coefficients: a0 = %4f, a1 = %4f,  a2 = %4f,  a3 = %4f, a4 = %4f, x1 = %4f, x2 = %4f, y1 = %4f, y2 = %4f.\n",
	//	biquad->a0, biquad->a1, biquad->a2, biquad->a3, biquad->a4, biquad->x1, biquad->x2, biquad->y1, biquad->y2);
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{	
		if (parameters_updated)
		{
			biquad->a0 += a0_delta;
			biquad->a1 += a1_delta;
			biquad->a2 += a2_delta;
			biquad->a3 += a3_delta;
			biquad->a4 += a4_delta;
		}
		
		dest[0][i] = biquad->a0 * src[0][i]
				   + biquad->a1 * biquad->x1
				   + biquad->a2 * biquad->x2
				   - biquad->a3 * biquad->y1
				   - biquad->a4 * biquad->y2;

		biquad->x2 = biquad->x1;
		biquad->x1 = src[0][i];

		biquad->y2 = biquad->y1;
		biquad->y1 = dest[0][i];
	}
	
	
	
	return NO_ERROR;
}

int init_biquad_struct_lowpass(tm_biquad_str *biquad, float cutoff)
{
	return init_biquad_struct(biquad, low_pass, cutoff, 0.707, 1.0);
}

int init_biquad_struct_highpass(tm_biquad_str *biquad, float cutoff)
{
	return init_biquad_struct(biquad, high_pass, cutoff, 0.707, 1.0);
}

int init_biquad_struct_bandpass(tm_biquad_str *biquad, float center, float bandwidth)
{
	return init_biquad_struct(biquad, band_pass, center, bandwidth, 1.0);
}

int compute_biquad_coefficients(tm_biquad_str *biquad)
{
	if (!biquad)
		return ERR_NULL_PTR;
	
	float A, omega, sin_omega, cos_omega, alpha, beta;
	float a0, a1, a2, b0, b1, b2;
	
	A 			= pow(10, biquad->db_gain.value / 40);
	omega 		= 2 * PI * biquad->cutoff.value / AUDIO_SAMPLE_RATE_EXACT;
	sin_omega 	= sin(omega);
	cos_omega 	= cos(omega);
	alpha 		= sin_omega * sinh(((LN_2 / 2) * biquad->bandwidth.value * omega) / sin_omega);
	beta 		= sqrt(A + A);

	switch (biquad->type.value)
	{
		case low_pass:
			b0 = (1 - cos_omega) / 2;
			b1 =  1 - cos_omega;
			b2 = (1 - cos_omega) / 2;
			a0 =  1 + alpha;
			a1 = -2 * cos_omega;
			a2 =  1 - alpha;
			break;
			
		case high_pass:
			b0 =  (1 + cos_omega) /2;
			b1 = -(1 + cos_omega);
			b2 =  (1 + cos_omega) /2;
			a0 =   1 + alpha;
			a1 =  -2 * cos_omega;
			a2 =   1 - alpha;
			break;
			
		case band_pass:
			b0 =  alpha;
			b1 =  0;
			b2 = -alpha;
			a0 =  1 + alpha;
			a1 = -2 * cos_omega;
			a2 =  1 - alpha;
			break;
			
		case notch:
			b0 =  1;
			b1 = -2 * cos_omega;
			b2 =  1;
			a0 =  1 + alpha;
			a1 = -2 * cos_omega;
			a2 =  1 - alpha;
			break;
			
		case peaking_band_eq:
			b0 =  1 + (alpha * A);
			b1 = -2 * cos_omega;
			b2 =  1 - (alpha * A);
			a0 =  1 + (alpha /A);
			a1 = -2 * cos_omega;
			a2 =  1 - (alpha /A);
			break;
			
		case low_shelf:
			b0 =  A * ((A + 1)	   - (A - 1) * cos_omega + beta * sin_omega);
			b1 =  2 * A * ((A - 1) - (A + 1) * cos_omega);
			b2 =  A * ((A + 1)	   - (A - 1) * cos_omega - beta * sin_omega);
			a0 = (A + 1)		   + (A - 1) * cos_omega + beta * sin_omega;
			a1 = -2 * ((A - 1)	   + (A + 1) * cos_omega);
			a2 = (A + 1)		   + (A - 1) * cos_omega - beta * sin_omega;
			break;
			
		case high_shelf:
			b0 =  A * ((A + 1)	   + (A - 1) * cos_omega + beta * sin_omega);
			b1 = -2 * A * ((A - 1) + (A + 1) * cos_omega);
			b2 =  A * ((A + 1)	   + (A - 1) * cos_omega - beta * sin_omega);
			a0 = (A + 1)		   - (A - 1) * cos_omega + beta * sin_omega;
			a1 =  2 * ((A - 1)	   - (A + 1) * cos_omega);
			a2 = (A + 1)		   - (A - 1) * cos_omega - beta * sin_omega;
			break;
			
		default:
			return ERR_BAD_ARGS;
	}
	
	biquad->a0 = b0 / a0;
	biquad->a1 = b1 / a0;
	biquad->a2 = b2 / a0;
	biquad->a3 = a1 / a0;
	biquad->a4 = a2 / a0;
	
	return NO_ERROR;
}

int init_biquad_struct_default(tm_biquad_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	str->type.value = band_pass;
	
	compute_biquad_coefficients(str);
	
	str->x1 = 0.0;
	str->x2 = 0.0;
	str->y1 = 0.0;
	str->y2 = 0.0;
	
	return NO_ERROR;
}

int init_biquad_struct(tm_biquad_str *biquad, biquad_type type, float cutoff, float bandwidth, float db_gain)
{
	if (!biquad)
		return ERR_NULL_PTR;
	
	init_option_simple(&biquad->type, type);

	init_parameter_simple(&biquad->cutoff, cutoff);
	init_parameter_simple(&biquad->bandwidth, bandwidth);
	init_parameter_simple(&biquad->db_gain, db_gain);
	
	compute_biquad_coefficients(biquad);
	
	biquad->x1 = 0.0;
	biquad->x2 = 0.0;
	biquad->y1 = 0.0;
	biquad->y2 = 0.0;
	
	return NO_ERROR;
}

int init_biquad(tm_transformer *trans, vec2i input, vec2i output, biquad_type type, float cutoff, float bandwidth, float db_gain)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->type = TRANSFORMER_BIQUAD;
	trans->bypass = 0;
	
	trans->n_inputs  = 1;
	trans->n_outputs = 1;
	
	trans->inputs [0] = input;
	trans->outputs[0] = output;
	
	tm_biquad_str *data_struct = (tm_biquad_str*)malloc(sizeof(tm_biquad_str));
	
	int ret_val = init_biquad_struct(data_struct, type, cutoff, bandwidth, db_gain);
	
	if (ret_val != NO_ERROR)
	{
		free(data_struct);
		return ret_val;
	}
	
	trans->data_struct = (void*)data_struct;
	
	trans->compute_transformer = &calc_biquad;
	
	transformer_add_option(trans, &data_struct->type);
	
	transformer_add_parameter(trans, &data_struct->cutoff);
	transformer_add_parameter(trans, &data_struct->bandwidth);
	transformer_add_parameter(trans, &data_struct->db_gain);
	
	return NO_ERROR;
}

tm_transformer *alloc_biquad_transformer(vec2i input, vec2i output, biquad_type type, float cutoff, float bandwidth, float db_gain)
{
	tm_transformer *biquad = (tm_transformer*)malloc(sizeof(tm_transformer));
	int ret_val;
	if ((ret_val = init_biquad(biquad, input, output, type, cutoff, bandwidth, db_gain)) != NO_ERROR)
	{
		if (biquad)
			free(biquad);
		return NULL;
	}
	return biquad;
}

int init_low_pass(tm_transformer *trans, vec2i input, vec2i output, float cutoff)
{
	return init_biquad(trans, input, output, low_pass, cutoff, 0.707, 1.0);
}

int init_high_pass(tm_transformer *trans, vec2i input, vec2i output, float cutoff)
{
	return init_biquad(trans, input, output, high_pass, cutoff, 0.707, 1.0);
}

int init_band_pass(tm_transformer *trans, vec2i input, vec2i output, float center, float bandwidth)
{
	return init_biquad(trans, input, output, band_pass, center, bandwidth, 1.0);
}


tm_transformer *alloc_low_pass_transformer(vec2i input, vec2i output, float cutoff)
{
	tm_transformer *biquad = (tm_transformer*)malloc(sizeof(tm_transformer));
	int ret_val;
	if ((ret_val = init_low_pass(biquad, input, output, cutoff)) != NO_ERROR)
	{
		if (biquad)
			free(biquad);
		return NULL;
	}
	return biquad;
}

tm_transformer *alloc_high_pass_transformer(vec2i input, vec2i output, float cutoff)
{
	tm_transformer *biquad = (tm_transformer*)malloc(sizeof(tm_transformer));
	int ret_val;
	if ((ret_val = init_high_pass(biquad, input, output, cutoff)) != NO_ERROR)
	{
		if (biquad)
			free(biquad);
		return NULL;
	}
	return biquad;
}

tm_transformer *alloc_band_pass_transformer(vec2i input, vec2i output, float center, float bandwidth)
{
	tm_transformer *biquad = (tm_transformer*)malloc(sizeof(tm_transformer));
	int ret_val;
	if ((ret_val = init_band_pass(biquad, input, output, center, bandwidth)) != NO_ERROR)
	{
		if (biquad)
			free(biquad);
		return NULL;
	}
	return biquad;
}

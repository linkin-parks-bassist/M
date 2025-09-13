#include "M.h"

int calc_biquad(float **dest, float **src, void *transformer_data)
{
	if (!transformer_data || !dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0] || !src[0])
		return ERR_NULL_PTR;
	
	//m_printf("Calculating biquad transform...\n");
	m_biquad_data *biquad = (m_biquad_data*)transformer_data;
	
	//m_printf("Coefficients: a0 = %4f, a1 = %4f,  a2 = %4f,  a3 = %4f, a4 = %4f, x1 = %4f, x2 = %4f, y1 = %4f, y2 = %4f.\n",
	//	biquad->a0, biquad->a1, biquad->a2, biquad->a3, biquad->a4, biquad->x1, biquad->x2, biquad->y1, biquad->y2);
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
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

int init_biquad_struct_lowpass(m_biquad_data *biquad, float cutoff)
{
	return init_biquad_struct(biquad, low_pass, cutoff, 0.707, 1.0);
}

int init_biquad_struct_highpass(m_biquad_data *biquad, float cutoff)
{
	return init_biquad_struct(biquad, high_pass, cutoff, 0.707, 1.0);
}

int init_biquad_struct_bandpass(m_biquad_data *biquad, float center, float bandwidth)
{
	return init_biquad_struct(biquad, band_pass, center, bandwidth, 1.0);
}

int compute_biquad_coefficients(m_biquad_data *biquad, int type, float cutoff, float bandwidth, float db_gain)
{
	if (!biquad)
		return ERR_NULL_PTR;
	
	biquad->type = type;
	
	float A, omega, sin_omega, cos_omega, alpha, beta;
	float a0, a1, a2, b0, b1, b2;
	
	A 			= pow(10, db_gain / 40);
	omega 		= 2 * PI * cutoff / AUDIO_SAMPLE_RATE_EXACT;
	sin_omega 	= sin(omega);
	cos_omega 	= cos(omega);
	alpha 		= sin_omega * sinh(((LN_2 / 2) * bandwidth * omega) / sin_omega);
	beta 		= sqrt(A + A);

	switch (type)
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
			b0 =  A * ((A + 1)     - (A - 1) * cos_omega + beta * sin_omega);
			b1 =  2 * A * ((A - 1) - (A + 1) * cos_omega);
			b2 =  A * ((A + 1)     - (A - 1) * cos_omega - beta * sin_omega);
			a0 = (A + 1)           + (A - 1) * cos_omega + beta * sin_omega;
			a1 = -2 * ((A - 1)     + (A + 1) * cos_omega);
			a2 = (A + 1)           + (A - 1) * cos_omega - beta * sin_omega;
			break;
			
		case high_shelf:
			b0 =  A * ((A + 1)     + (A - 1) * cos_omega + beta * sin_omega);
			b1 = -2 * A * ((A - 1) + (A + 1) * cos_omega);
			b2 =  A * ((A + 1)     + (A - 1) * cos_omega - beta * sin_omega);
			a0 = (A + 1)           - (A - 1) * cos_omega + beta * sin_omega;
			a1 =  2 * ((A - 1)     - (A + 1) * cos_omega);
			a2 = (A + 1)           - (A - 1) * cos_omega - beta * sin_omega;
			break;
			
		default:
			return ERR_BAD_ARGS;
	}
	
	biquad->a0 = b0 / a0;
	biquad->a1 = b1 / a0;
	biquad->a2 = b2 / a0;
	biquad->a3 = a1 / a0;
	biquad->a4 = a2 / a0;

	biquad->x1 = biquad->x2 = 0;
	biquad->y1 = biquad->y2 = 0;
	
	return NO_ERROR;
}

int init_biquad_struct(m_biquad_data *biquad, int type, float cutoff, float bandwidth, float db_gain)
{
	int ret_val = compute_biquad_coefficients(biquad, type, cutoff, bandwidth, db_gain);
	
	if (ret_val != NO_ERROR)
		return ret_val;
	
	return NO_ERROR;
}

int init_biquad(m_audio_transformer *trans, vec2i input, vec2i output, int type, float cutoff, float bandwidth, float db_gain)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->type = TRANSFORMER_BIQUAD;
	
	trans->n_inputs  = 1;
	trans->n_outputs = 1;
	
	trans->inputs [0] = input;
	trans->outputs[0] = output;
	
	m_biquad_data *data_struct = (m_biquad_data*)malloc(sizeof(m_biquad_data));
	
	int ret_val = init_biquad_struct(data_struct, type, cutoff, bandwidth, db_gain);
	
	if (ret_val != NO_ERROR)
	{
		free(data_struct);
		return ret_val;
	}
	
	trans->transformer_data = (void*)data_struct;
	
	trans->compute_transformer = &calc_biquad;
	
	return NO_ERROR;
}

m_audio_transformer *alloc_biquad_transformer(vec2i input, vec2i output, int type, float cutoff, float bandwidth, float db_gain)
{
	m_audio_transformer *biquad = (m_audio_transformer*)malloc(sizeof(m_audio_transformer));
	int ret_val;
	if ((ret_val = init_biquad(biquad, input, output, type, cutoff, bandwidth, db_gain)) != NO_ERROR)
	{
		if (biquad)
			free(biquad);
		return NULL;
	}
	return biquad;
}

int init_low_pass(m_audio_transformer *trans, vec2i input, vec2i output, float cutoff)
{
	return init_biquad(trans, input, output, low_pass, cutoff, 0.707, 1.0);
}

int init_high_pass(m_audio_transformer *trans, vec2i input, vec2i output, float cutoff)
{
	return init_biquad(trans, input, output, high_pass, cutoff, 0.707, 1.0);
}

int init_band_pass(m_audio_transformer *trans, vec2i input, vec2i output, float center, float bandwidth)
{
	return init_biquad(trans, input, output, band_pass, center, bandwidth, 1.0);
}


m_audio_transformer *alloc_low_pass_transformer(vec2i input, vec2i output, float cutoff)
{
	m_audio_transformer *biquad = (m_audio_transformer*)malloc(sizeof(m_audio_transformer));
	int ret_val;
	if ((ret_val = init_low_pass(biquad, input, output, cutoff)) != NO_ERROR)
	{
		if (biquad)
			free(biquad);
		return NULL;
	}
	return biquad;
}

m_audio_transformer *alloc_high_pass_transformer(vec2i input, vec2i output, float cutoff)
{
	m_audio_transformer *biquad = (m_audio_transformer*)malloc(sizeof(m_audio_transformer));
	int ret_val;
	if ((ret_val = init_high_pass(biquad, input, output, cutoff)) != NO_ERROR)
	{
		if (biquad)
			free(biquad);
		return NULL;
	}
	return biquad;
}

m_audio_transformer *alloc_band_pass_transformer(vec2i input, vec2i output, float center, float bandwidth)
{
	m_audio_transformer *biquad = (m_audio_transformer*)malloc(sizeof(m_audio_transformer));
	int ret_val;
	if ((ret_val = init_band_pass(biquad, input, output, center, bandwidth)) != NO_ERROR)
	{
		if (biquad)
			free(biquad);
		return NULL;
	}
	return biquad;
}

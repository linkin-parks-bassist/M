#include "m_eng.h"

static const char *FNAME = "m_eng_biquad.c";

int calc_biquad(void *data_struct, float *dest, float *src, int n_samples)
{
	FUNCTION_START();

	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_biquad_str *biquad = (m_eng_biquad_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	float in_sample, out_sample;
	
	/*m_printf("Biquad coefficients: [%s%3f, %s%3f, %s%3f, %s%3f, %s%3f], state: [[%s%3f, %s%3f], [%s%3f, %s%3f]]\n",
		(biquad->a0 < 0) ? "" : " ", biquad->a0,
		 (biquad->a1 < 0) ? "" : " ", biquad->a1,
		 (biquad->a2 < 0) ? "" : " ", biquad->a2,
		 (biquad->a3 < 0) ? "" : " ", biquad->a3,
		 (biquad->a4 < 0) ? "" : " ", biquad->a4,
		 (biquad->x1 < 0) ? "" : " ", biquad->x1,
		 (biquad->x2 < 0) ? "" : " ", biquad->x2,
		 (biquad->y1 < 0) ? "" : " ", biquad->y1,
		 (biquad->y2 < 0) ? "" : " ", biquad->y2);*/
	
	for (int i = 0; i < n_samples; i++)
	{
		in_sample = in_buffer[i];
		
		out_sample = biquad->a0 * in_sample
				   + biquad->a1 * biquad->x1
				   + biquad->a2 * biquad->x2
				   - biquad->a3 * biquad->y1
				   - biquad->a4 * biquad->y2;
		
		out_buffer[i] = out_sample;

		biquad->x2 = biquad->x1;
		biquad->x1 = in_sample;

		biquad->y2 = biquad->y1;
		biquad->y1 = out_sample;
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

int reconfigure_biquad(void *data_struct)
{
	FUNCTION_START();

	m_eng_biquad_str *biquad = (m_eng_biquad_str*)data_struct;
	
	if (!biquad)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
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
			RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	biquad->a0 = b0 / a0;
	biquad->a1 = b1 / a0;
	biquad->a2 = b2 / a0;
	biquad->a3 = a1 / a0;
	biquad->a4 = a2 / a0;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int init_biquad_str(m_eng_biquad_str *str)
{
	FUNCTION_START();

	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	str->x1 = 0.0;
	str->x2 = 0.0;
	str->y1 = 0.0;
	str->y2 = 0.0;
	
	RETURN_ERR_CODE(NO_ERROR);
}

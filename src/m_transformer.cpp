#include "M.h"

int calc_buffer(float **dest, float **src, void *transformer_data)
{
	if (!dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0] || !src[0])
		return ERR_NULL_PTR;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		dest[0][i] = src[0][i];
	
	return NO_ERROR;
}

int calc_amp(float **dest, float **src, void *transformer_data)
{
	if (!transformer_data || !dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0] || !src[0])
		return ERR_NULL_PTR;
	
	//m_printf("Computing amp transformer...\n");
	
	m_trans_amp_data *amp = (m_trans_amp_data*)transformer_data;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		dest[0][i] = amp->gain * src[0][i];
		////m_printf("dest[0][%03d] = amp->gain * src[0][%03d] = %04f * %04f = %04f = %04f\n", i, i, amp->gain, src[0][i], amp->gain * src[0][i], dest[0][i]);
	}
	
	return NO_ERROR;
}

int calc_mixer(float **dest, float **src, void *transformer_data)
{
	if (!transformer_data || !dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0])
		return ERR_NULL_PTR;
	
	m_trans_mixer_data *mixer = (m_trans_mixer_data*)transformer_data;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		dest[0][i] = 0.0;
		for (int j = 0; j < mixer->n_inputs; j++)
			dest[0][i] += mixer->gains[j] * src[j][i];
	}
	
	return NO_ERROR;
}

int calc_fader(float **dest, float **src, void *transformer_data)
{
	if (!transformer_data || !dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0] || !src[0])
		return ERR_NULL_PTR;
	
	m_trans_fader_data *fader = (m_trans_fader_data*)transformer_data;
	
	float sgn    = (fader->fade_type == FADER_FADE_OUT) ? -1 : 1;
	float offset = (fader->fade_type == FADER_FADE_OUT) ?  1 : 0;
	
	float gain;
	
	int i = 0;
	while (i < AUDIO_BLOCK_SAMPLES && fader->sample_progress < fader->duration_samples)
	{
		gain = offset + sgn * ((float)fader->sample_progress++ / (float)fader->duration_samples);
		
		dest[0][i] = gain * src[0][i];
		
		i++;
	}
	
	while (i < AUDIO_BLOCK_SAMPLES)
	{
		dest[0][i] = (fader->fade_type == FADER_FADE_OUT) ? 0 : src[0][i];
		i++;
	}
	
	return NO_ERROR;
}

int calc_biquad(float **dest, float **src, void *transformer_data)
{
	if (!transformer_data || !dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0] || !src[0])
		return ERR_NULL_PTR;
	
	//m_printf("Calculating biquad transform...\n");
	m_trans_biquad_data *biquad = (m_trans_biquad_data*)transformer_data;
	
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

int calc_arctan_distortion(float **dest, float **src, void *transformer_data)
{
	if (!transformer_data || !dest || !src)
		return ERR_NULL_PTR;
	
	if (!dest[0] || !src[0])
		return ERR_NULL_PTR;
	
	m_printf("Calculating arctan distortion...\n");
	m_trans_arctan_dist_data *dist = (m_trans_arctan_dist_data*)transformer_data;
	
	float abs_max = 0.0;
	float abs_amp;
	float ra;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		abs_amp = fabs(src[0][i]);
		if (abs_amp > abs_max)
			abs_max = abs_amp;
	}
	
	ra = abs_amp * 0.5 + dist->running_amp * 0.5;
	
	float tmp[AUDIO_BLOCK_SAMPLES];
	
	if (ra == 0.0)
	{
		for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
			dest[0][i] = 0.0;
		
		return NO_ERROR;
	}
	
	m_printf("running amplitude: %4f\n", ra);
	float ra_inv = 1.0 / ra;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		tmp[i] = src[0][i] * ra_inv;
	
	abs_max = 0.0;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		abs_amp = fabs(tmp[i]);
		if (abs_amp > abs_max)
			abs_max = abs_amp;
	}
	
	m_printf("Renormalised input to peak amplitude of %4f\n", abs_max);
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		tmp[i] = atan(dist->coef * tmp[i]);
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		dest[0][i] = tmp[i] * ra *  0.63661977237;
	
	dist->running_amp = ra;
	
	return NO_ERROR;
}


int init_buffer_transformer(m_audio_transformer *trans, vec2i input, vec2i output)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->type = TRANSFORMER_BUFFER;
	
	trans->n_inputs  = 1;
	trans->n_outputs = 1;
	
	trans->inputs [0] = input;
	trans->outputs[0] = output;
	
	trans->transformer_data = NULL;
	trans->compute_transformer = &calc_buffer;
	
	return NO_ERROR;
}

m_audio_transformer *alloc_buffer_transformer(vec2i input, vec2i output)
{
	m_audio_transformer *buffer = (m_audio_transformer*)malloc(sizeof(m_audio_transformer));
	int ret_val;
	if ((ret_val = init_buffer_transformer(buffer, input, output)) != NO_ERROR)
	{
		if (buffer)
			free(buffer);
		return NULL;
	}
	return buffer;
}

int init_amp_transformer(m_audio_transformer *trans, vec2i input, vec2i output, float gain)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->type = TRANSFORMER_AMPLIFIER;
	
	trans->n_inputs  = 1;
	trans->n_outputs = 1;
	
	trans->inputs [0] = input;
	trans->outputs[0] = output;
	
	trans->transformer_data = (m_trans_amp_data*)malloc(sizeof(m_trans_amp_data));
	
	((m_trans_amp_data*)(trans->transformer_data))->gain = gain;
	
	trans->compute_transformer = &calc_amp;
	
	return NO_ERROR;
}

m_audio_transformer *alloc_amp_transformer(vec2i input, vec2i output, float gain)
{
	m_audio_transformer *amp = (m_audio_transformer*)malloc(sizeof(m_audio_transformer));
	int ret_val;
	if ((ret_val = init_amp_transformer(amp, input, output, gain)) != NO_ERROR)
	{
		if (amp)
			free(amp);
		return NULL;
	}
	return amp;
}

int init_mixer_transformer(m_audio_transformer *trans, vec2i *inputs, int n_inputs, vec2i output, float *gains)
{
	if (!trans || !inputs)
		return ERR_NULL_PTR;
	
	trans->type = TRANSFORMER_BUFFER;
	
	trans->n_inputs  = n_inputs;
	trans->n_outputs = 1;
	
	for (int i = 0; i < n_inputs; i++)
		trans->inputs[i] = inputs[i];
	
	trans->outputs[0] = output;
	
	m_trans_mixer_data *data_str = (m_trans_mixer_data*)malloc(sizeof(m_trans_mixer_data));
	
	data_str->n_inputs = n_inputs;
	data_str->gains = (float*)malloc(sizeof(float) * n_inputs);
	
	if (gains)
	{
		for (int i = 0; i < n_inputs; i++)
		{
			data_str->gains[i] = gains[i];
		}
	}
	else
	{
		// By default, just transmit first input
		for (int i = 0; i < n_inputs; i++)
		{
			if (i)
				data_str->gains[i] = 0.0;
			else
				data_str->gains[i] = 1.0;
		}
	}
	
	trans->transformer_data = (void*)data_str;
	trans->compute_transformer = &calc_mixer;
	
	return NO_ERROR;
}

m_audio_transformer *alloc_mixer_transformer(vec2i *inputs, int n_inputs, vec2i output, float *gains)
{
	m_audio_transformer *mixer = (m_audio_transformer*)malloc(sizeof(m_audio_transformer));
	int ret_val;
	if ((ret_val = init_mixer_transformer(mixer, inputs, n_inputs, output, gains)) != NO_ERROR)
	{
		if (mixer)
			free(mixer);
		return NULL;
	}
	return mixer;
}

int init_fader_transformer(m_audio_transformer *trans, vec2i input, vec2i output, int fade_type, uint32_t duration_samples)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->type = TRANSFORMER_AMPLIFIER;
	
	trans->n_inputs  = 1;
	trans->n_outputs = 1;
	
	trans->inputs [0] = input;
	trans->outputs[0] = output;
	
	m_trans_fader_data *data_str = (m_trans_fader_data*)malloc(sizeof(m_trans_fader_data));
	
	data_str->fade_type 		= fade_type;
	data_str->duration_samples 	= duration_samples;
	data_str->sample_progress 	= 0;
	
	trans->transformer_data = (void*)data_str;
	
	trans->compute_transformer = &calc_fader;
	
	return NO_ERROR;
}

m_audio_transformer *alloc_fader_transformer(vec2i input, vec2i output, int fade_type, uint32_t duration_samples)
{
	m_audio_transformer *fader = (m_audio_transformer*)malloc(sizeof(m_audio_transformer));
	int ret_val;
	if ((ret_val = init_fader_transformer(fader, input, output, fade_type, duration_samples)) != NO_ERROR)
	{
		if (fader)
			free(fader);
		return NULL;
	}
	return fader;
}

int init_biquad_transformer(m_audio_transformer *trans, vec2i input, vec2i output, int type, float cutoff, float bandwidth, float db_gain)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->type = TRANSFORMER_BIQUAD;
	
	trans->n_inputs  = 1;
	trans->n_outputs = 1;
	
	trans->inputs [0] = input;
	trans->outputs[0] = output;
	
	m_trans_biquad_data *data_str = (m_trans_biquad_data*)malloc(sizeof(m_trans_biquad_data));
	
	data_str->type = type;
	
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
			free(data_str);
			return ERR_BAD_ARGS;
	}
	
	data_str->a0 = b0 / a0;
	data_str->a1 = b1 / a0;
	data_str->a2 = b2 / a0;
	data_str->a3 = a1 / a0;
	data_str->a4 = a2 / a0;

	data_str->x1 = data_str->x2 = 0;
	data_str->y1 = data_str->y2 = 0;
	
	trans->transformer_data = (void*)data_str;
	
	trans->compute_transformer = &calc_biquad;
	
	return NO_ERROR;
}

m_audio_transformer *alloc_biquad_transformer(vec2i input, vec2i output, int type, float cutoff, float bandwidth, float db_gain)
{
	m_audio_transformer *biquad = (m_audio_transformer*)malloc(sizeof(m_audio_transformer));
	int ret_val;
	if ((ret_val = init_biquad_transformer(biquad, input, output, type, cutoff, bandwidth, db_gain)) != NO_ERROR)
	{
		if (biquad)
			free(biquad);
		return NULL;
	}
	return biquad;
}

int init_arctan_dist_transformer(m_audio_transformer *trans, vec2i input, vec2i output, float coef)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->type = TRANSFORMER_ARCTAN_DIST;
	
	trans->n_inputs  = 1;
	trans->n_outputs = 1;
	
	trans->inputs[0]  = input;
	trans->outputs[0] = output;
	
	m_trans_arctan_dist_data *data_str = (m_trans_arctan_dist_data*)malloc(sizeof(m_trans_arctan_dist_data));
	
	data_str->coef = coef;
	data_str->running_amp = 0.0;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		data_str->prev_block[i] = 0.0;
	
	trans->transformer_data = (void*)data_str;
	trans->compute_transformer = &calc_arctan_distortion;
	
	return NO_ERROR;
}


m_audio_transformer *alloc_arctan_dist_transformer(vec2i input, vec2i output, float coef)
{
	m_audio_transformer *dist = (m_audio_transformer*)malloc(sizeof(m_audio_transformer));
	int ret_val;
	if ((ret_val = init_arctan_dist_transformer(dist, input, output, coef)) != NO_ERROR)
	{
		if (dist)
			free(dist);
		return NULL;
	}
	return dist;
}

int init_low_pass_transformer(m_audio_transformer *trans, vec2i input, vec2i output, float cutoff)
{
	return init_biquad_transformer(trans, input, output, high_pass, cutoff, 0.707, 1.0);
}

int init_high_pass_transformer(m_audio_transformer *trans, vec2i input, vec2i output, float cutoff)
{
	return init_biquad_transformer(trans, input, output, low_pass, cutoff, 0.707, 1.0);
}

int init_band_pass_transformer(m_audio_transformer *trans, vec2i input, vec2i output, float center, float bandwidth)
{
	return init_biquad_transformer(trans, input, output, band_pass, center, bandwidth, 1.0);
}


m_audio_transformer *alloc_low_pass_transformer(vec2i input, vec2i output, float cutoff)
{
	m_audio_transformer *biquad = (m_audio_transformer*)malloc(sizeof(m_audio_transformer));
	int ret_val;
	if ((ret_val = init_low_pass_transformer(biquad, input, output, cutoff)) != NO_ERROR)
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
	if ((ret_val = init_high_pass_transformer(biquad, input, output, cutoff)) != NO_ERROR)
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
	if ((ret_val = init_band_pass_transformer(biquad, input, output, center, bandwidth)) != NO_ERROR)
	{
		if (biquad)
			free(biquad);
		return NULL;
	}
	return biquad;
}

int propagate_transformer(m_pipeline *pipeline, m_audio_transformer *trans)
{
	if (!pipeline || !trans)
		return ERR_NULL_PTR;
	
	m_pipeline_node *inputs [MAX_TRANSFORMER_INPUTS ];
	m_pipeline_node *outputs[MAX_TRANSFORMER_OUTPUTS];
	
	int  input_valid[MAX_TRANSFORMER_INPUTS];
	int output_valid[MAX_TRANSFORMER_INPUTS];
	
	float  *src[MAX_TRANSFORMER_INPUTS];
	float *dest[MAX_TRANSFORMER_INPUTS];
	
	unsigned int i;
	
	for (i = 0; i < trans->n_inputs; i++)
	{
		inputs[i] = pipeline_get_node(pipeline, trans->inputs[i]);
		input_valid[i] = (inputs[i] && inputs[i]->active && inputs[i]->block);
		
		if (input_valid[i])
			src[i] = inputs[i]->block->data;
		else
			src[i] = NULL;
	}
	
	while (i < MAX_TRANSFORMER_INPUTS)
	{
		src[i] 			= NULL;
		inputs[i] 		= NULL;
		input_valid[i] 	= 0;
		i++;
	}
	
	#ifdef PRINT_TRANSFORMER_INFO
	for (i = 0; i < MAX_TRANSFORMER_INPUTS; i++)
		m_printf("Input %d: coordinates (%d, %d). Validity: %d. Buffer pointer: 0x%08x\n", i, trans->inputs[i].x, trans->inputs[i].y, input_valid[i], src[i]);
	#endif
	
	for (i = 0; i < trans->n_outputs; i++)
	{
		outputs[i] = pipeline_get_node(pipeline, trans->outputs[i]);
		output_valid[i] = (outputs[i] && outputs[i]->block);
		
		if (output_valid[i])
			dest[i] = outputs[i]->block->data;
		else
			dest[i] = NULL;
	}
	
	while (i < MAX_TRANSFORMER_OUTPUTS)
	{
		dest[i] 		= NULL;
		outputs[i] 		= NULL;
		output_valid[i] = 0;
		i++;
	}
	
	#ifdef PRINT_TRANSFORMER_INFO
	for (i = 0; i < MAX_TRANSFORMER_INPUTS; i++)
		m_printf("Output %d: coordinates (%d, %d). Validity: %d. Buffer pointer: 0x%08x\n", i, trans->outputs[i].x, trans->outputs[i].y, output_valid[i], dest[i]);
	#endif
	
	int ret_val;
	
	if (trans->compute_transformer)
		ret_val = trans->compute_transformer(dest, src, trans->transformer_data);
	else
		ret_val = ERR_TRANSFORMER_MALFORMED;
	
	#ifdef PRINT_TRANSFORMER_INFO
	m_printf("Transformer type: ");
	switch (trans->type)
	{
		case TRANSFORMER_BUFFER:
			m_printf("buffer.\n");
			break;
			
		case TRANSFORMER_AMPLIFIER:
			m_printf("amplifier.\n");
			break;
		
		case TRANSFORMER_MIXER:
			m_printf("mixer.\n");
			break;
		
		case TRANSFORMER_BIQUAD:
			m_printf("biquad.\n");
			break;
		
		case TRANSFORMER_ARCTAN_DIST:
			m_printf("arctan distortion.\n");
			break;
		
		default:
			m_printf("unknown !\n");
			return ERR_TRANSFORMER_MALFORMED;
	}
	
	if (ret_val == NO_ERROR)
		m_printf("Computed sucessfully\n");
	else
		m_printf("Error %d\n", ret_val);
	
	float amp_abs_max = 0.0;
	
	for (int i = 0; i < MAX_TRANSFORMER_OUTPUTS; i++)
	{
		if (!output_valid[i] || !dest[i])
			continue;
		
		for (int j = 0; j < AUDIO_BLOCK_SAMPLES; j++)
		{
			if (fabs(dest[i][j]) > amp_abs_max)
				amp_abs_max = fabs(dest[i][j]);
		}
		
		m_printf("Output %d peak amplitude: %4f\n", i, amp_abs_max);
	}
	#endif
	
	return ret_val;
}

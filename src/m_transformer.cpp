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

int init_buffer(m_audio_transformer *trans, vec2i input, vec2i output)
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
	if ((ret_val = init_buffer(buffer, input, output)) != NO_ERROR)
	{
		if (buffer)
			free(buffer);
		return NULL;
	}
	return buffer;
}

int init_amp(m_audio_transformer *trans, vec2i input, vec2i output, float gain)
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
	if ((ret_val = init_amp(amp, input, output, gain)) != NO_ERROR)
	{
		if (amp)
			free(amp);
		return NULL;
	}
	return amp;
}

int init_mixer(m_audio_transformer *trans, vec2i *inputs, int n_inputs, vec2i output, float *gains)
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
	if ((ret_val = init_mixer(mixer, inputs, n_inputs, output, gains)) != NO_ERROR)
	{
		if (mixer)
			free(mixer);
		return NULL;
	}
	return mixer;
}

int init_fader(m_audio_transformer *trans, vec2i input, vec2i output, int fade_type, uint32_t duration_samples)
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
	if ((ret_val = init_fader(fader, input, output, fade_type, duration_samples)) != NO_ERROR)
	{
		if (fader)
			free(fader);
		return NULL;
	}
	return fader;
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
		
		case TRANSFORMER_COMPRESSOR1:
			m_printf("compression.\n");
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

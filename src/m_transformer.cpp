#include "M.h"

int init_buffer_transformer(m_audio_transformer *trans, vec2i input, vec2i output)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->type = TRANSFORMER_BUFFER;
	
	trans->n_inputs  = 1;
	trans->n_outputs = 1;
	
	trans->inputs [0] = input;
	trans->outputs[0] = output;
	
	trans->data = NULL;
	
	return NO_ERROR;
}

int init_amp_transformer(m_audio_transformer *trans, float gain, vec2i input, vec2i output)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->type = TRANSFORMER_AMPLIFIER;
	
	trans->n_inputs  = 1;
	trans->n_outputs = 1;
	
	trans->inputs [0] = input;
	trans->outputs[0] = output;
	
	trans->data = malloc(sizeof(m_trans_amp_data));
	
	((m_trans_amp_data*)(trans->data))->gain = gain;
	
	return NO_ERROR;
}

int calc_amp(m_trans_amp_data *amp, float *dest, float *src)
{
	if (!amp || !dest || !src)
		return ERR_NULL_PTR;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		dest[i] = amp->gain * src[i];
	
	return NO_ERROR;
}

int calc_mixer(m_trans_mixer_data *mixer, float *dest, float *src1, float *src2)
{
	if (!mixer || !dest || !src1 || !src2)
		return ERR_NULL_PTR;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		dest[i] = mixer->gains[0] * src1[i] + mixer->gains[1] * src2[i];
	
	return NO_ERROR;
}

int calc_fader(m_trans_fader_data *fader, float *dest, float *src)
{
	if (!fader || !dest || !src)
		return ERR_NULL_PTR;
	
	float sgn    = (fader->fade_type == FADER_FADE_OUT) ? -1 : 1;
	float offset = (fader->fade_type == FADER_FADE_OUT) ?  1 : 0;
	
	float gain;
	
	int i = 0;
	while (i < AUDIO_BLOCK_SAMPLES && fader->sample_progress < fader->duration_samples)
	{
		gain = offset + sgn * ((float)fader->sample_progress++ / (float)fader->duration_samples);
		
		dest[i] = gain * src[i];
		
		i++;
	}
	
	while (i < AUDIO_BLOCK_SAMPLES)
	{
		dest[i] = (fader->fade_type == FADER_FADE_OUT) ? 0 : src[i];
		i++;
	}
	
	return NO_ERROR;
}


int propagate_transformer(m_pipeline *pipeline, m_audio_transformer *trans)
{
	if (!pipeline || !trans)
		return ERR_NULL_PTR;
	
	float data[AUDIO_BLOCK_SAMPLES];
	
	m_pipeline_node *inputs [MAX_TRANSFER_INPUTS ];
	m_pipeline_node *outputs[MAX_TRANSFER_OUTPUTS];
	
	int  input_valid[trans->n_inputs ];
	int output_valid[trans->n_outputs];
	
	for (unsigned int i = 0; i < trans->n_inputs; i++)
	{
		inputs[i] = pipeline_get_node(pipeline, trans->inputs[i]);
		input_valid[i] = (inputs[i] && inputs[i]->active && inputs[i]->updated && inputs[i]->block);
	}
	
	for (unsigned int i = 0; i < trans->n_outputs; i++)
	{
		outputs[i] = pipeline_get_node(pipeline, trans->outputs[i]);
		output_valid[i] = (outputs[i] && outputs[i]->block);
	}
	
	m_printf("Input goodness: [");
	for (int i = 0; i < trans->n_inputs; i++)
	{
		m_printf("%d", input_valid[i]);
		if (i < trans->n_inputs - 1)
			m_printf(", ");
	}
	m_printf("]\n");
	m_printf("Output goodness: [");
	for (int i = 0; i < trans->n_outputs; i++)
	{
		m_printf("%d", output_valid[i]);
		if (i < trans->n_outputs - 1)
			m_printf(", ");
	}
	m_printf("]\n");
	
	int ret_val;
	
	m_printf("Transformer type: ");
	switch (trans->type)
	{
		case TRANSFORMER_BUFFER:
			m_printf("buffer.\n");
			if (input_valid[0] && output_valid[0])
				write_node(outputs[0], inputs[0]->block->data);
			break;
			
		case TRANSFORMER_AMPLIFIER:
			m_printf("amplifier.\n");
			if (input_valid[0] && output_valid[0])
			{
				if ((ret_val = calc_amp((m_trans_amp_data*)trans->data, data, inputs[0]->block->data)) == NO_ERROR)
				{
					m_printf("Computed sucessfully. Writing data to output node...\n");
					write_node(outputs[0], data);
				}
			}
			break;
		
		case TRANSFORMER_MIXER:
			m_printf("mixer.\n");
			if (input_valid[0] && input_valid[1] && output_valid[0])
			{
				if ((ret_val = calc_mixer((m_trans_mixer_data*)trans->data, data, inputs[0]->block->data, inputs[1]->block->data)) == NO_ERROR)
					write_node(outputs[0], data);
			}
			break;
		
		default:
			m_printf("unknown !\n");
			return ERR_TRANSFORMER_MALFORMED;
	}
	
	return NO_ERROR;
}

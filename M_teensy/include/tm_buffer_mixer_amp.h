#ifndef M_BMA_H_
#define M_BMA_H_

typedef struct
{
	m_parameter gain;
} tm_amp_data;

typedef struct
{
	m_parameter ratio;
} tm_mixer_data;

int init_buffer(tm_audio_transformer *trans, vec2i input, vec2i output);
tm_audio_transformer *alloc_buffer_transformer(vec2i input, vec2i output);

int init_amp(tm_audio_transformer *trans, vec2i input, vec2i output, m_param_level_t gain);
tm_audio_transformer *alloc_amp_transformer(vec2i input, vec2i output, m_param_level_t gain);

int init_mixer(tm_audio_transformer *trans, vec2i *inputs, vec2i output, m_param_level_t gain_1);
tm_audio_transformer *alloc_mixer_transformer(vec2i *inputs, vec2i output, m_param_level_t gain_2);

int init_buffer_default	(tm_audio_transformer *trans);
int init_amp_default	(tm_audio_transformer *trans);
int init_mixer_default	(tm_audio_transformer *trans);

#endif

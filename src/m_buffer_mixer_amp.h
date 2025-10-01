#ifndef M_BMA_H_
#define M_BMA_H_

#define DEFAULT_AMP_GAIN 	1.0
#define DEFAULT_MIXER_RATIO 0.5

typedef struct
{
	m_parameter gain;
} m_amp_data;

typedef struct
{
	m_parameter ratio;
} m_mixer_data;

int init_buffer(m_audio_transformer *trans, vec2i input, vec2i output);
m_audio_transformer *alloc_buffer_transformer(vec2i input, vec2i output);

int init_amp(m_audio_transformer *trans, vec2i input, vec2i output, m_param_level_t gain);
m_audio_transformer *alloc_amp_transformer(vec2i input, vec2i output, m_param_level_t gain);

int init_mixer(m_audio_transformer *trans, vec2i *inputs, vec2i output, m_param_level_t gain_1);
m_audio_transformer *alloc_mixer_transformer(vec2i *inputs, vec2i output, m_param_level_t gain_2);

int init_buffer_default	(m_audio_transformer *trans);
int init_amp_default	(m_audio_transformer *trans);
int init_mixer_default	(m_audio_transformer *trans);

#endif

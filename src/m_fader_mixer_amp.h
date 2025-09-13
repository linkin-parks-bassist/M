#ifndef M_FMA_H_
#define M_FMA_H_

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

int init_amp(m_audio_transformer *trans, vec2i input, vec2i output, float gain);
m_audio_transformer *alloc_amp_transformer(vec2i input, vec2i output, float gain);

int init_mixer(m_audio_transformer *trans, vec2i *inputs, vec2i output, float gain_1);
m_audio_transformer *alloc_mixer_transformer(vec2i *inputs, vec2i output, float gain_2);

#endif

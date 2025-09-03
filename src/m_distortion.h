#ifndef M_DISTORTION_H_
#define M_DISTORTION_H_

typedef struct
{
	float coef;
	
	float (*shape)(float x);
	
	float running_amp;
	float prev_block[AUDIO_BLOCK_SAMPLES];
} m_trans_waveshaper_data;

int calc_waveshaper(float **dest, float **src, void *transformer_data);
int init_waveshaper(m_audio_transformer *trans, vec2i input, vec2i output, float (*shape)(float x), float coef);

int init_arctan_distortion(m_audio_transformer *trans, vec2i input, vec2i output, float coef);
int init_tanh_distortion(m_audio_transformer *trans, vec2i input, vec2i output, float coef);

m_audio_transformer *alloc_arctan_distortion(vec2i input, vec2i output, float coef);
m_audio_transformer *alloc_tanh_distortion(vec2i input, vec2i output, float coef);

#endif

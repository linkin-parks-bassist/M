#ifndef M_WAVESHAPER_H_
#define M_WAVESHAPER_H_

typedef struct
{
	m_parameter coefficient;
	
	float (*shape)(float x);
	
	float local_amplitude;
	float prev_block[AUDIO_BLOCK_SAMPLES];
} m_waveshaper_data;

int calc_waveshaper(float **dest, float **src, void *transformer_data);
int init_waveshaper(m_audio_transformer *trans, vec2i input, vec2i output, float (*shape)(float x), float coef);

int init_waveshaper_struct(m_waveshaper_data *data_struct, float (*shape)(float x), float coef);

#endif

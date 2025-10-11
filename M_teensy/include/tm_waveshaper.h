#ifndef M_WAVESHAPER_H_
#define M_WAVESHAPER_H_

#define WAVESHAPER_ENVELOPE_RATE (1.0/(64 * 128))

typedef struct
{
	tm_parameter coefficient;
	
	float (*shape)(float x);
	
	float local_amplitude;
	
	int prev_block_index;
	float prev_block[AUDIO_BLOCK_SAMPLES];
} tm_waveshaper_str;

int calc_waveshaper(void *data_struct, float **dest, float **src, int n_samples);
int init_waveshaper(tm_transformer *trans, vec2i input, vec2i output, float (*shape)(float x), float coef);

int init_waveshaper_struct_default(tm_waveshaper_str *str);
int init_waveshaper_struct(tm_waveshaper_str *data_struct, float (*shape)(float x), float coef);

int init_waveshaper_default(tm_transformer *trans);

#endif

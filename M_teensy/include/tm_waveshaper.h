#ifndef M_WAVESHAPER_H_
#define M_WAVESHAPER_H_

typedef struct
{
	tm_parameter coefficient;
	
	float (*shape)(float x);
	
	float local_amplitude;
	float prev_block[AUDIO_BLOCK_SAMPLES];
} tm_waveshaper_str;

int calc_waveshaper(float **dest, float **src, void *data_struct);
int init_waveshaper(tm_transformer *trans, vec2i input, vec2i output, float (*shape)(float x), float coef);

int init_waveshaper_struct_default(tm_waveshaper_str *str);
int init_waveshaper_struct(tm_waveshaper_str *data_struct, float (*shape)(float x), float coef);

int init_waveshaper_default(tm_transformer *trans);

#endif

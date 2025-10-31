#ifndef M_WAVESHAPER_H_
#define M_WAVESHAPER_H_

#define WAVESHAPER_ENVELOPE_ATTACK 	expf(-7.0/8.0)
#define WAVESHAPER_ENVELOPE_RELEASE expf(-7.0/2048.0)

typedef struct
{
	tm_parameter coefficient;
	
	float (*shape)(float x);
} tm_waveshaper_str;

int init_waveshaper_str(tm_waveshaper_str *str);
int calc_waveshaper(void *data_struct, float *dest, float *src, int n_samples);


#endif

#ifndef M_WAVESHAPER_H_
#define M_WAVESHAPER_H_

#define WAVESHAPER_ENVELOPE_ATTACK 	expf(-7.0/64.0)
#define WAVESHAPER_ENVELOPE_RELEASE expf(-7.0/128.0)

typedef struct
{
	tm_parameter coefficient;
	
	float (*shape)(float x);
	
	float local_amplitude;
} tm_waveshaper_str;

int init_waveshaper_str(tm_waveshaper_str *str);
int calc_waveshaper(void *data_struct, float *dest, float *src, int n_samples);


#endif

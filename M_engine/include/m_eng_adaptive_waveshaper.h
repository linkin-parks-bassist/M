#ifndef M_ADAPTIVE_WAVESHAPER_H_
#define M_ADAPTIVE_WAVESHAPER_H_

#define ADAPTIVE_WAVESHAPER_ENVELOPE_ATTACK 	expf(-7.0/8.0)
#define ADAPTIVE_WAVESHAPER_ENVELOPE_RELEASE expf(-7.0/2048.0)

typedef struct
{
	m_parameter coefficient;
	
	float (*shape)(float x);
	
	float local_amplitude;
} m_eng_adaptive_waveshaper_str;

int init_adaptive_waveshaper_str(m_eng_adaptive_waveshaper_str *str);
int calc_adaptive_waveshaper(void *data_struct, float *dest, float *src, int n_samples);


#endif

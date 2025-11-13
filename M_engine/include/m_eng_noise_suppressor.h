#ifndef M_ENG_NOISE_SUPRESSOR_H_
#define M_ENG_NOISE_SUPRESSOR_H_

typedef struct
{
	m_parameter threshold;
	m_parameter ratio;
	m_parameter max_reduction;
	float e_final;
	
	int r;
} m_eng_noise_suppressor_str;

int reconfigure_noise_suppressor(void *data_struct);
int calc_noise_suppressor(void *data_struct, float *dest, float *src, int n_samples);
int init_noise_suppressor_str(m_eng_noise_suppressor_str *str);

#endif

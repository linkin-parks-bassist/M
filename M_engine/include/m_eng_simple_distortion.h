#ifndef M_ENG_SIMPLE_DISTORTION_H_
#define M_ENG_SIMPLE_DISTORTION_H_

typedef struct
{
	m_eng_parameter pregain;
	m_eng_parameter postgain;
	
} m_eng_simple_distortion_str;

int init_simple_distortion_str(m_eng_simple_distortion_str *str);
int reconfigure_simple_distortion(void *data_struct);
int calc_simple_distortion(void *data_struct, float *dest, float *src, int n_samples);

#endif

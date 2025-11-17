#ifndef M_ENG_DELAY_H_
#define M_ENG_DELAY_H_

typedef struct
{
	m_setting tempo;
	m_setting note;
	m_parameter delay_gain;
	
	float delay_samples;
	float g;
	
	m_delay_buffer buf;
} m_eng_delay_str;

int init_delay_str(m_eng_delay_str *str);
int reconfigure_delay(void *data_struct);
int calc_delay(void *data_struct, float *dest, float *src, int n_samples);

#endif

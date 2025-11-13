#ifndef M_BIQUAD_H_
#define M_BIQUAD_H_

typedef struct
{
	float a0, a1, a2, a3, a4;
	float x1, x2, y1, y2;
	
	m_setting type;
	m_parameter cutoff;
	m_parameter bandwidth;
	m_parameter db_gain;
} m_eng_biquad_str;

int init_biquad_str(m_eng_biquad_str *str);
int reconfigure_biquad(void *data_struct);
int calc_biquad(void *data_struct, float *dest, float *src, int n_samples);

#endif

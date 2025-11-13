#ifndef M_ENG_WARBLER_H_
#define M_ENG_WARBLER_H_

typedef struct
{
	m_parameter center;
	m_parameter width;
	m_parameter reactivity;
	m_parameter sensitivity;
	m_parameter max_rate;
	m_parameter min_rate;
	
	float alpha;
	float e;
	
	float t;
	float rate;
	
	m_eng_band_pass_filter_str filter;
} m_eng_warbler_str;

int init_warbler_str(m_eng_warbler_str *str);
int reconfigure_warbler(void *data_struct);
int calc_warbler(void *data_struct, float *dest, float *src, int n_samples);

#endif

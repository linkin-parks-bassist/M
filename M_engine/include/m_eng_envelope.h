#ifndef M_ENG_ENVELOPE_H_
#define M_ENG_ENVELOPE_H_

typedef struct
{
	m_eng_parameter min_center;
	m_eng_parameter max_center;
	m_eng_parameter width;
	m_eng_parameter speed;
	m_eng_parameter sensitivity;
	m_eng_parameter smoothness;
	
	float alpha;
	float e;
	
	int chunk_size;
	
	m_eng_band_pass_filter_str filter;
} m_eng_envelope_str;

int init_envelope_str(m_eng_envelope_str *str);
int reconfigure_envelope(void *data_struct);
int calc_envelope(void *data_struct, float *dest, float *src, int n_samples);

#endif

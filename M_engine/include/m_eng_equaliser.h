#ifndef M_ENG_EQUALISER_H_
#define M_ENG_EQUALISER_H_

#define M_ENG_EQ_CONTROL_DIRECT 	0
#define M_ENG_EQ_CONTROL_DB_GAIN	1

typedef struct
{
	m_eng_parameter low;
	m_eng_parameter mid;
	m_eng_parameter high;
	
	float coefs[3];
	int control_mode;
	
	m_eng_lr_low_pass_filter_str filters[2];
} m_eng_3_band_eq_str;

int init_3_band_eq_str(m_eng_3_band_eq_str *str);
int reconfigure_3_band_eq(void *data_struct);
int calc_3_band_eq(void *data_struct, float *dest, float *src, int n_samples);

#endif

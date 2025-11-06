#ifndef M_ENG_LOW_PASS_H_
#define M_ENG_LOW_PASS_H_

typedef struct
{
	m_eng_parameter cutoff_frequency;
	
	float a0, a1, a2, a3, a4;
	float x1, x2, y1, y2;
} m_eng_low_pass_filter_str;

int init_low_pass_filter_str(m_eng_low_pass_filter_str *str);
int reconfigure_low_pass_filter(void *data_struct);
int calc_low_pass_filter(void *data_struct, float *dest, float *src, int n_samples);

typedef struct
{
	m_eng_parameter cutoff_frequency;
	
	float a0, a1, a2, a3, a4;
	float x1, x2, y1, y2;
} m_eng_high_pass_filter_str;

int init_high_pass_filter_str(m_eng_high_pass_filter_str *str);
int reconfigure_high_pass_filter(void *data_struct);
int calc_high_pass_filter(void *data_struct, float *dest, float *src, int n_samples);

typedef struct
{
	m_eng_parameter center;
	m_eng_parameter bandwidth;
	
	float a0, a1, a2, a3, a4;
	float x1, x2, y1, y2;
} m_eng_band_pass_filter_str;

int init_band_pass_filter_str(m_eng_band_pass_filter_str *str);
int reconfigure_band_pass_filter(void *data_struct);
int calc_band_pass_filter(void *data_struct, float *dest, float *src, int n_samples);

#endif


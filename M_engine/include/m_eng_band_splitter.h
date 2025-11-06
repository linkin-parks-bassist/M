#ifndef M_ENG_TRANSFORMER_H_
#define M_ENG_TRANSFORMER_H_

typedef struct
{
	m_eng_lr_low_pass_filter_str filters[3];
} m_eng_3_band_splitter_str;

int init_3_band_splitter_str(m_eng_3_band_splitter_str *str);
int reconfigure_3_band_splitter(void *data_struct);
int calc_3_band_splitter(void *data_struct, float **dest, float **src, int n_samples);

typedef struct
{
	m_eng_lr_low_pass_filter_str *filters;
} m_eng_n_band_splitter_str;

int init_n_band_splitter_str(m_eng_n_band_splitter_str *str);
int reconfigure_n_band_splitter(void *data_struct);
int calc_n_band_splitter(void *data_struct, float **dest, float **src, int n_samples);

#endif


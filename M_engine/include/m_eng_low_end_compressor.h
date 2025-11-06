#ifndef M_ENG_LOW_END_COMPRESSOR_H_
#define M_ENG_LOW_END_COMPRESSOR_H_

typedef struct
{
	m_eng_compressor_str bass_comp;
	m_eng_compressor_str mids_comp;
	
	m_eng_lr_low_pass_filter_str low_pass;
	m_eng_lr_low_pass_filter_str mid_pass;
	
} m_eng_low_end_compressor_str;

int init_low_end_compressor_str(m_eng_low_end_compressor_str *str);
int reconfigure_low_end_compressor(void *data_struct);
int calc_low_end_compressor(void *data_struct, float *dest, float *src, int n_samples);

#endif

#ifndef M_DISTORTION_H_
#define M_DISTORTION_H_

#define USE_GLOBAL_TEMP_BUFFERS

typedef struct
{
	m_setting type;
	
	m_lr_low_pass_filter_str  low_pass;
	
	m_eng_waveshaper_str dist;
	
	m_parameter wet_mix;
	m_parameter bass_mix;
	m_parameter bass_cutoff;
} m_eng_distortion_str;

int init_distortion_str(m_eng_distortion_str *str);
int reconfigure_distortion(void *data_struct);
int calc_distortion(void *data_struct, float *dest, float *src, int n_samples);

#endif

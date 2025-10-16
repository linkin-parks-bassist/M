#ifndef M_DISTORTION_H_
#define M_DISTORTION_H_

#define USE_GLOBAL_TEMP_BUFFERS

typedef struct
{
	tm_option type;
	
	tm_low_pass_filter_str  low_pass_1;
	tm_low_pass_filter_str  low_pass_2;
	tm_band_pass_filter_str mid_pass_1;
	tm_band_pass_filter_str mid_pass_2;
	tm_high_pass_filter_str high_pass_1;
	tm_high_pass_filter_str high_pass_2;
	
	tm_waveshaper_str mid_distortion;
	tm_waveshaper_str high_distortion;
	
	tm_parameter gain;
	tm_parameter wet_mix;
	tm_parameter high_mix;
	tm_parameter mid_mix;
	tm_parameter bass_mix;
	tm_parameter bass_cutoff;
	tm_parameter mid_cutoff;
	tm_parameter ratio;
	
	uint32_t total_samples;
} tm_distortion_str;

int init_distortion_str(tm_distortion_str *str);
int reconfigure_distortion(void *data_struct);
int calc_distortion(void *data_struct, float *dest, float *src, int n_samples);

#endif

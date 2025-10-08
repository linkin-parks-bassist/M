#ifndef M_DISTORTION_H_
#define M_DISTORTION_H_

#define USE_GLOBAL_TEMP_BUFFERS

typedef struct
{
	tm_option type;
	
	tm_biquad_str low_pass_1;
	tm_biquad_str low_pass_2;
	tm_biquad_str mid_pass_1;
	tm_biquad_str mid_pass_2;
	tm_biquad_str high_pass_1;
	tm_biquad_str high_pass_2;
	
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
} tm_distortion_str;

int init_distortion_struct(tm_distortion_str *data_struct, int type,
						   float bass_cutoff, float mid_cutoff, float gain,
						   float bass_mix,float mid_mix, float high_mix, float wet_mix);

int init_distortion(tm_transformer *trans, vec2i input, vec2i output, int type, float mid_gain, float high_gain);

int init_distortion_struct_default(tm_distortion_str *str);

int calc_distortion(float **dest, float **src, void *data_struct);

#endif

#ifndef M_BIQUAD_H_
#define M_BIQUAD_H_

typedef struct
{
	float a0, a1, a2, a3, a4;
	float x1, x2, y1, y2;
	
	tm_option type;
	tm_parameter cutoff;
	tm_parameter bandwidth;
	tm_parameter db_gain;
} tm_biquad_str;

int reconfigure_biquad(void *data_struct);
int calc_biquad(void *data_struct, float **dest, float **src, int n_samples);

int init_biquad_struct_default(tm_biquad_str *str);
int init_biquad_struct(tm_biquad_str *biquad, biquad_type type, float cutoff, float bandwidth, float db_gain);

int init_biquad_struct_lowpass (tm_biquad_str *biquad, float cutoff);
int init_biquad_struct_highpass(tm_biquad_str *biquad, float cutoff);
int init_biquad_struct_bandpass(tm_biquad_str *biquad, float center, float bandwidth);

int init_biquad(tm_transformer *trans,   vec2i input, vec2i output, biquad_type type, float cutoff, float bandwidth, float db_gain);
tm_transformer *alloc_biquad_transformer(vec2i input, vec2i output, biquad_type type, float cutoff, float bandwidth, float db_gain);

int init_low_pass (tm_transformer *trans,   vec2i input, vec2i output, float cutoff);
int init_high_pass(tm_transformer *trans,   vec2i input, vec2i output, float cutoff);
int init_band_pass(tm_transformer *trans,   vec2i input, vec2i output, float center, float bandwidth);
tm_transformer *alloc_low_pass_transformer (vec2i input, vec2i output, float cutoff);
tm_transformer *alloc_high_pass_transformer(vec2i input, vec2i output, float cutoff);
tm_transformer *alloc_band_pass_transformer(vec2i input, vec2i output, float center, float bandwidth);

#endif

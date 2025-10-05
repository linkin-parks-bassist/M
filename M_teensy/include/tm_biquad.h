#ifndef M_BIQUAD_H_
#define M_BIQUAD_H_

typedef struct
{
	float a0, a1, a2, a3, a4;
	float x1, x2, y1, y2;
	
	m_parameter type;
	m_parameter cutoff;
	m_parameter bandwidth;
	m_parameter db_gain;
} tm_biquad_data;

int calc_biquad(float **dest, float **src, void *transformer_data);

int compute_biquad_coefficients(tm_biquad_data *biquad);
int init_biquad_struct(tm_biquad_data *biquad, biquad_type type, float cutoff, float bandwidth, float db_gain);

int init_biquad_struct_lowpass (tm_biquad_data *biquad, float cutoff);
int init_biquad_struct_highpass(tm_biquad_data *biquad, float cutoff);
int init_biquad_struct_bandpass(tm_biquad_data *biquad, float center, float bandwidth);

int init_biquad(tm_audio_transformer *trans,   vec2i input, vec2i output, biquad_type type, float cutoff, float bandwidth, float db_gain);
tm_audio_transformer *alloc_biquad_transformer(vec2i input, vec2i output, biquad_type type, float cutoff, float bandwidth, float db_gain);

int init_low_pass (tm_audio_transformer *trans,   vec2i input, vec2i output, float cutoff);
int init_high_pass(tm_audio_transformer *trans,   vec2i input, vec2i output, float cutoff);
int init_band_pass(tm_audio_transformer *trans,   vec2i input, vec2i output, float center, float bandwidth);
tm_audio_transformer *alloc_low_pass_transformer (vec2i input, vec2i output, float cutoff);
tm_audio_transformer *alloc_high_pass_transformer(vec2i input, vec2i output, float cutoff);
tm_audio_transformer *alloc_band_pass_transformer(vec2i input, vec2i output, float center, float bandwidth);

int init_biquad_default(tm_audio_transformer *trans);

#endif

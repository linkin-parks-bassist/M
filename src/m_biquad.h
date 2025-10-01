#ifndef M_BIQUAD_H_
#define M_BIQUAD_H_

#define DEFAULT_BIQUAD_TYPE 		low_pass
#define DEFAULT_BIQUAD_CUTOFF		440.0
#define DEFAULT_BIQUAD_BANDWIDTH	100.0
#define DEFAULT_BIQUAD_DB_GAIN		0.0

typedef enum
{
	low_pass,
	high_pass,
	band_pass,
	notch,
	peaking_band_eq,
	low_shelf,
	high_shelf
} biquad_type;

typedef struct
{
	float a0, a1, a2, a3, a4;
	float x1, x2, y1, y2;
	
	m_parameter type;
	m_parameter cutoff;
	m_parameter bandwidth;
	m_parameter db_gain;
} m_biquad_data;

int calc_biquad(float **dest, float **src, void *transformer_data);

int compute_biquad_coefficients(m_biquad_data *biquad);
int init_biquad_struct(m_biquad_data *biquad, biquad_type type, float cutoff, float bandwidth, float db_gain);

int init_biquad_struct_lowpass (m_biquad_data *biquad, float cutoff);
int init_biquad_struct_highpass(m_biquad_data *biquad, float cutoff);
int init_biquad_struct_bandpass(m_biquad_data *biquad, float center, float bandwidth);

int init_biquad(m_audio_transformer *trans,   vec2i input, vec2i output, biquad_type type, float cutoff, float bandwidth, float db_gain);
m_audio_transformer *alloc_biquad_transformer(vec2i input, vec2i output, biquad_type type, float cutoff, float bandwidth, float db_gain);

int init_low_pass (m_audio_transformer *trans,   vec2i input, vec2i output, float cutoff);
int init_high_pass(m_audio_transformer *trans,   vec2i input, vec2i output, float cutoff);
int init_band_pass(m_audio_transformer *trans,   vec2i input, vec2i output, float center, float bandwidth);
m_audio_transformer *alloc_low_pass_transformer (vec2i input, vec2i output, float cutoff);
m_audio_transformer *alloc_high_pass_transformer(vec2i input, vec2i output, float cutoff);
m_audio_transformer *alloc_band_pass_transformer(vec2i input, vec2i output, float center, float bandwidth);

int init_biquad_default(m_audio_transformer *trans);

#endif

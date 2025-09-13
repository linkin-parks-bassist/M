#ifndef M_DISTORTION_H_
#define M_DISTORTION_H_

#define DISTORTION_SOFT_FOLD 	1
#define DISTORTION_ARCTAN		2
#define DISTORTION_TANH			3
#define DISTORTION_CLIP			4

typedef struct
{
	int type;
	
	m_biquad_data low_pass_1;
	m_biquad_data low_pass_2;
	m_biquad_data mid_pass_1;
	m_biquad_data mid_pass_2;
	m_biquad_data high_pass_1;
	m_biquad_data high_pass_2;
	
	m_waveshaper_data mid_distortion;
	m_waveshaper_data high_distortion;
	
	m_parameter gain;
	m_parameter ratio;
	m_parameter bass_cutoff;
	m_parameter mid_cutoff;
	m_parameter bass_mix;
	m_parameter mid_mix;
	m_parameter high_mix;
	m_parameter wet_mix;
} m_distortion_data;

int init_distortion_struct(m_distortion_data *data_struct, int type, float bass_cutoff, float mid_cutoff,
						   float gain, float bass_mix, float mid_mix, float high_mix, float wet_mix);

int init_distortion_transformer(m_audio_transformer *trans, vec2i input, vec2i output, int type, float mid_gain, float high_gain);

#endif

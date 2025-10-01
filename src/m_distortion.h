#ifndef M_DISTORTION_H_
#define M_DISTORTION_H_

#define DISTORTION_SOFT_FOLD 	0
#define DISTORTION_ARCTAN		1
#define DISTORTION_TANH			2
#define DISTORTION_CLIP			3

#define DEFAULT_DISTORTION_TYPE  		DISTORTION_TANH
#define DEFAULT_DISTORTION_GAIN	 		3.0
#define DEFAULT_DISTORTION_RATIO 		0.1
#define DEFAULT_DISTORTION_BASS_CUTOFF 	100.0
#define DEFAULT_DISTORTION_MID_CUTOFF 	1500.0
#define DEFAULT_DISTORTION_BASS_MIX		1.0/3.0
#define DEFAULT_DISTORTION_MID_MIX		1.0/3.0
#define DEFAULT_DISTORTION_HIGH_MIX		1.0/3.0
#define DEFAULT_DISTORTION_WET_MIX		0.7

typedef struct
{
	m_parameter type;
	
	m_biquad_data low_pass_1;
	m_biquad_data low_pass_2;
	m_biquad_data mid_pass_1;
	m_biquad_data mid_pass_2;
	m_biquad_data high_pass_1;
	m_biquad_data high_pass_2;
	
	m_waveshaper_data mid_distortion;
	m_waveshaper_data high_distortion;
	
	m_parameter gain;
	m_parameter wet_mix;
	m_parameter high_mix;
	m_parameter mid_mix;
	m_parameter bass_mix;
	m_parameter bass_cutoff;
	m_parameter mid_cutoff;
	m_parameter ratio;
} m_distortion_data;

int init_distortion_struct(m_distortion_data *data_struct, int type,
						   m_param_level_t bass_cutoff, m_param_level_t mid_cutoff, m_param_level_t gain,
						   m_param_level_t bass_mix,m_param_level_t mid_mix, m_param_level_t high_mix, m_param_level_t wet_mix);

int init_distortion(m_audio_transformer *trans, vec2i input, vec2i output, int type, m_param_level_t mid_gain, m_param_level_t high_gain);

int init_distortion_default(m_audio_transformer *trans);

#endif

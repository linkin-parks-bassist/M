#ifndef M_DISTORTION_H_
#define M_DISTORTION_H_

typedef struct
{
	m_parameter type;
	
	tm_biquad_data low_pass_1;
	tm_biquad_data low_pass_2;
	tm_biquad_data mid_pass_1;
	tm_biquad_data mid_pass_2;
	tm_biquad_data high_pass_1;
	tm_biquad_data high_pass_2;
	
	tm_waveshaper_data mid_distortion;
	tm_waveshaper_data high_distortion;
	
	m_parameter gain;
	m_parameter wet_mix;
	m_parameter high_mix;
	m_parameter mid_mix;
	m_parameter bass_mix;
	m_parameter bass_cutoff;
	m_parameter mid_cutoff;
	m_parameter ratio;
} tm_distortion_data;

int init_distortion_struct(tm_distortion_data *data_struct, int type,
						   m_param_level_t bass_cutoff, m_param_level_t mid_cutoff, m_param_level_t gain,
						   m_param_level_t bass_mix,m_param_level_t mid_mix, m_param_level_t high_mix, m_param_level_t wet_mix);

int init_distortion(tm_audio_transformer *trans, vec2i input, vec2i output, int type, m_param_level_t mid_gain, m_param_level_t high_gain);

int init_distortion_default(tm_audio_transformer *trans);

#endif

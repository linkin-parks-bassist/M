#ifndef M_COMPRESSOR1_H_
#define M_COMPRESSOR1_H_

typedef struct
{
	m_parameter ratio;
	m_parameter threshold;
	m_parameter attack;
	m_parameter release;
	
	float alpha;
	float rho;
	
	float e_final;
} m_compressor_data;

int init_compressor_struct(m_compressor_data *data_struct, float ratio, float threshold, float attack, float release);

int init_compressor(m_audio_transformer *trans, vec2i input, vec2i output, float ratio, float threshold, float attack, float release);
m_audio_transformer *alloc_compressor(vec2i input, vec2i output, float ratio, float threshold, float attack, float release);

#endif

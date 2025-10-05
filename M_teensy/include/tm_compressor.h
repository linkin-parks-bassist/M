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
} tm_compressor_data;

int init_compressor_struct(tm_compressor_data *data_struct, float ratio, float threshold, float attack, float release);

int init_compressor(tm_audio_transformer *trans, vec2i input, vec2i output, float ratio, float threshold, float attack, float release);
tm_audio_transformer *alloc_compressor(vec2i input, vec2i output, float ratio, float threshold, float attack, float release);

int init_compressor_default(tm_audio_transformer *trans);

#endif

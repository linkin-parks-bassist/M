#ifndef M_COMPRESSOR1_H_
#define M_COMPRESSOR1_H_

#define DEFAULT_COMPRESSOR_RATIO 		 3.0
#define DEFAULT_COMPRESSOR_THRESHOLD 	16.0
#define DEFAULT_COMPRESSOR_ATTACK		0.01
#define DEFAULT_COMPRESSOR_RELEASE		0.03

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

int init_compressor_default(m_audio_transformer *trans);

#endif

#ifndef M_COMPRESSOR1_H_
#define M_COMPRESSOR1_H_

typedef struct
{
	float ratio;
	float threshold;
	float attack;
	float release;
	
	float e_final;
} m_trans_compressor1_data;

int init_compressor1(m_audio_transformer *trans, vec2i input, vec2i output, float ratio, float threshold, float attack, float release);
m_audio_transformer *alloc_compressor1(vec2i input, vec2i output, float ratio, float threshold, float attack, float release);

#endif

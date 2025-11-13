#ifndef M_ENG_FLANGER_H_
#define M_ENG_FLANGER_H_

typedef struct
{
	m_parameter range;
	m_parameter tempo;
	m_parameter depth;
	m_parameter mix;
	
	m_setting note;
	
	float r;
	float s;
	float d;
	
	float wet_mix;
	float dry_mix;
	
	float period;
	
	float t;
	
	float **block_memory;
	int num_blocks;
	int block_position;
	int block_index;
} m_eng_flanger_str;

int init_flanger_str(m_eng_flanger_str *str);
int reconfigure_flanger(void *data_struct);
int calc_flanger(void *data_struct, float *dest, float *src, int n_samples);

#endif

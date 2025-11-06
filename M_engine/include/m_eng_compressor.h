#ifndef M_COMPRESSOR1_H_
#define M_COMPRESSOR1_H_

typedef struct
{
	m_eng_parameter ratio;
	m_eng_parameter threshold;
	m_eng_parameter attack;
	m_eng_parameter release;
	
	float alpha;
	float rho;
	
	float e_final;
} m_eng_compressor_str;

int init_compressor_str(m_eng_compressor_str *str);
int reconfigure_compressor(void *data_struct);
int calc_compressor(void *data_struct, float *dest, float *src, int n_samples);

#endif

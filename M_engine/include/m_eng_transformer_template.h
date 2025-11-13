#ifndef M_ENG_TRANSFORMER_H_
#define M_ENG_TRANSFORMER_H_

typedef struct
{
	m_parameter param;
	
} m_transformer_str;

int init_transformer_str(m_transformer_str *str);
int reconfigure_transformer(void *data_struct);
int calc_transformer(void *data_struct, float *dest, float *src, int n_samples);

#endif

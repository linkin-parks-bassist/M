#ifndef TM_TRANSFORMER_H_
#define TM_TRANSFORMER_H_

typedef struct
{
	tm_parameter param;
	
} tm_transformer_str;

int init_transformer_str(tm_transformer_str *str);
int reconfigure_transformer(void *data_struct);
int calc_transformer(void *data_struct, float *dest, float *src, int n_samples);

#endif

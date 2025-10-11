#ifndef TM_TRANSFORMER_H_
#define TM_TRANSFORMER_H_

typedef struct
{
	tm_parameter param;
	
} tm_transformer_str;

int reconfigure_transformer(void *data_struct);
int calc_transformer(void *data_struct, float **dest, float **src, int n_samples);
int init_transformer_struct_default(tm_transformer_str *str);

#endif

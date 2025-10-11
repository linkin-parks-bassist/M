#ifndef M_COMPRESSOR1_H_
#define M_COMPRESSOR1_H_

typedef struct
{
	tm_parameter ratio;
	tm_parameter threshold;
	tm_parameter attack;
	tm_parameter release;
	
	float alpha;
	float rho;
	
	float e_final;
} tm_compressor_str;

int init_compressor_struct_default(tm_compressor_str *str);
int init_compressor_struct(tm_compressor_str *data_struct, float ratio, float threshold, float attack, float release);

int init_compressor(tm_transformer *trans, vec2i input, vec2i output, float ratio, float threshold, float attack, float release);
tm_transformer *alloc_compressor(vec2i input, vec2i output, float ratio, float threshold, float attack, float release);

int init_compressor_default(tm_transformer *trans);

int reconfigure_compressor(void *data_struct);
int calc_compressor(void *data_struct, float **dest, float **src, int n_samples);

#endif

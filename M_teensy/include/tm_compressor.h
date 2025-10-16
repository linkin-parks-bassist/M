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

int init_compressor_str(tm_compressor_str *str);
int reconfigure_compressor(void *data_struct);
int calc_compressor(void *data_struct, float *dest, float *src, int n_samples);

#endif

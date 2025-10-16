#ifndef TM_NOISE_SUPRESSOR_H_
#define TM_NOISE_SUPRESSOR_H_

typedef struct
{
	tm_parameter threshold;
	tm_parameter ratio;
	tm_parameter max_reduction;
	float e_final;
	
	int r;
} tm_noise_suppressor_str;

int reconfigure_noise_suppressor(void *data_struct);
int calc_noise_suppressor(void *data_struct, float *dest, float *src, int n_samples);
int init_noise_suppressor_str(tm_noise_suppressor_str *str);

#endif

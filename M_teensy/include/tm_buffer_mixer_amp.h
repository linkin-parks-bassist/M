#ifndef M_BMA_H_
#define M_BMA_H_

typedef struct
{
	tm_parameter gain;
} tm_amplifier_str;

typedef struct
{
	tm_parameter ratio;
} tm_mixer_str;


int calc_buffer(void *data_struct, float *dest, float *src, int n_samples);

int init_amplifier_str(tm_amplifier_str *str);
int calc_amplifier(void *data_struct, float *dest, float *src, int n_samples);

/*
int init_mixer_str(tm_mixer_str *str);
int calc_mixer(void *data_struct, float **dest, float **src, int n_samples);
*/

#endif

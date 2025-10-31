#ifndef TM_SIMPLE_DISTORTION_H_
#define TM_SIMPLE_DISTORTION_H_

typedef struct
{
	tm_parameter pregain;
	tm_parameter postgain;
	
} tm_simple_distortion_str;

int init_simple_distortion_str(tm_simple_distortion_str *str);
int reconfigure_simple_distortion(void *data_struct);
int calc_simple_distortion(void *data_struct, float *dest, float *src, int n_samples);

#endif

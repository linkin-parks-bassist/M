#ifndef TM_NORMALISED_BIQUAD_H_
#define TM_NORMALISED_BIQUAD_H_

typedef struct
{
	tm_parameter a1, a2, a3, a4;
	float x1, x2, y1, y2;
	
	float dc_average;
} tm_normalised_biquad_str;

int calc_normalised_biquad(void *data_struct, float **dest, float **src, int n_samples);

int init_normalised_biquad_struct_default(tm_normalised_biquad_str *str);

#endif

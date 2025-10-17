#ifndef TM_EQUALISER_H_
#define TM_EQUALISER_H_

#define TM_EQ_CONTROL_DIRECT 	0
#define TM_EQ_CONTROL_DB_GAIN	1

typedef struct
{
	tm_parameter low;
	tm_parameter mid;
	tm_parameter high;
	
	float coefs[3];
	int control_mode;
	
	tm_lr_low_pass_filter_str filters[2];
} tm_3_band_eq_str;

int init_3_band_eq_str(tm_3_band_eq_str *str);
int reconfigure_3_band_eq(void *data_struct);
int calc_3_band_eq(void *data_struct, float *dest, float *src, int n_samples);

#endif

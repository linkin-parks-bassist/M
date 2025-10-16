#ifndef TM_LOW_PASS_H_
#define TM_LOW_PASS_H_

typedef struct
{
	tm_parameter cutoff_frequency;
	
	float a0, a1, a2, a3, a4;
	float x1, x2, y1, y2;
} tm_low_pass_filter_str;

int init_low_pass_filter_str(tm_low_pass_filter_str *str);
int reconfigure_low_pass_filter(void *data_struct);
int calc_low_pass_filter(void *data_struct, float *dest, float *src, int n_samples);

typedef struct
{
	tm_parameter cutoff_frequency;
	
	float a0, a1, a2, a3, a4;
	float x1, x2, y1, y2;
} tm_high_pass_filter_str;

int init_high_pass_filter_str(tm_high_pass_filter_str *str);
int reconfigure_high_pass_filter(void *data_struct);
int calc_high_pass_filter(void *data_struct, float *dest, float *src, int n_samples);

typedef struct
{
	tm_parameter center;
	tm_parameter bandwidth;
	
	float a0, a1, a2, a3, a4;
	float x1, x2, y1, y2;
} tm_band_pass_filter_str;

int init_band_pass_filter_str(tm_band_pass_filter_str *str);
int reconfigure_band_pass_filter(void *data_struct);
int calc_band_pass_filter(void *data_struct, float *dest, float *src, int n_samples);

#endif


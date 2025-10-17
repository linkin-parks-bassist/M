#ifndef TM_LR_FILTER_H_
#define TM_LR_FILTER_H_

typedef struct
{
	tm_parameter cutoff_frequency;
	
	float a0, a1, a2, a3, a4;
	float x_11, x_12, y_11, y_12;
	float x_21, x_22, y_21, y_22;
	
} tm_lr_low_pass_filter_str;

int init_lr_low_pass_filter_str(tm_lr_low_pass_filter_str *str);
int reconfigure_lr_low_pass_filter(void *data_struct);
int calc_lr_low_pass_filter(void *data_struct, float *dest, float *src, int n_samples);

typedef struct
{
	tm_parameter cutoff_frequency;
	
	float a0, a1, a2, a3, a4;
	float x_11, x_12, y_11, y_12;
	float x_21, x_22, y_21, y_22;
	
} tm_lr_high_pass_filter_str;

int init_lr_high_pass_filter_str(tm_lr_high_pass_filter_str *str);
int reconfigure_lr_high_pass_filter(void *data_struct);
int calc_lr_high_pass_filter(void *data_struct, float *dest, float *src, int n_samples);

#endif

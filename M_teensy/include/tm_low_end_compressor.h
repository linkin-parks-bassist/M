#ifndef TM_LOW_END_COMPRESSOR_H_
#define TM_LOW_END_COMPRESSOR_H_

typedef struct
{
	tm_compressor_str bass_comp;
	tm_compressor_str mids_comp;
	
	tm_lr_low_pass_filter_str low_pass;
	tm_lr_low_pass_filter_str mid_pass;
	
} tm_low_end_compressor_str;

int init_low_end_compressor_str(tm_low_end_compressor_str *str);
int reconfigure_low_end_compressor(void *data_struct);
int calc_low_end_compressor(void *data_struct, float *dest, float *src, int n_samples);

#endif

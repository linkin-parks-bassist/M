#ifndef TM_TRANSFORMER_H_
#define TM_TRANSFORMER_H_

typedef struct
{
	tm_lr_low_pass_filter_str filters[3];
} tm_3_band_splitter_str;

int init_3_band_splitter_str(tm_3_band_splitter_str *str);
int reconfigure_3_band_splitter(void *data_struct);
int calc_3_band_splitter(void *data_struct, float **dest, float **src, int n_samples);

typedef struct
{
	tm_lr_low_pass_filter_str *filters;
} tm_n_band_splitter_str;

int init_n_band_splitter_str(tm_n_band_splitter_str *str);
int reconfigure_n_band_splitter(void *data_struct);
int calc_n_band_splitter(void *data_struct, float **dest, float **src, int n_samples);

#endif


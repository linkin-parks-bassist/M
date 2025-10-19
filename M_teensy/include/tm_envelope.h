#ifndef TM_ENVELOPE_H_
#define TM_ENVELOPE_H_

typedef struct
{
	tm_parameter min_center;
	tm_parameter max_center;
	tm_parameter width;
	tm_parameter speed;
	tm_parameter sensitivity;
	tm_parameter smoothness;
	
	float alpha;
	float e;
	
	int chunk_size;
	
	tm_band_pass_filter_str filter;
} tm_envelope_str;

int init_envelope_str(tm_envelope_str *str);
int reconfigure_envelope(void *data_struct);
int calc_envelope(void *data_struct, float *dest, float *src, int n_samples);

#endif

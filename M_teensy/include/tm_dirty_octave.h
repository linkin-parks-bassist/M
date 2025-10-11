#ifndef TM_DIRTY_OCTAVE_H_
#define TM_DIRTY_OCTAVE_H_

typedef struct
{
	tm_parameter fuzz;
	
	float dc_average;
	
	float lpf_alpha;
	float last_out_sample;
} tm_dirty_octave_str;

int reconfigure_dirty_octave(void *data_struct);
int calc_dirty_octave(void *data_struct, float **dest, float **src, int n_samples);
int init_dirty_octave_struct_default(tm_dirty_octave_str *str);

#endif

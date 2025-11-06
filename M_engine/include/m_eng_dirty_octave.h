#ifndef M_ENG_DIRTY_OCTAVE_H_
#define M_ENG_DIRTY_OCTAVE_H_

typedef struct
{
	m_eng_parameter fuzz;
	
	float dc_average;
	
	float lpf_alpha;
	float last_out_sample;
} m_eng_dirty_octave_str;

int init_dirty_octave_str(m_eng_dirty_octave_str *str);
int reconfigure_dirty_octave(void *data_struct);
int calc_dirty_octave(void *data_struct, float *dest, float *src, int n_samples);

#endif

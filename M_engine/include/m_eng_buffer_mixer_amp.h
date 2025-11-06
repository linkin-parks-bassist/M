#ifndef M_BMA_H_
#define M_BMA_H_

#define M_ENG_AMPLIFIER_LINEAR		0
#define M_ENG_AMPLIFIER_DB		 	1

typedef struct
{
	m_eng_parameter gain;
	float g;
		
	m_eng_setting mode;
	int db;
} m_eng_amplifier_str;

typedef struct
{
	m_eng_parameter ratio;
} m_eng_mixer_str;


int calc_buffer(void *data_struct, float *dest, float *src, int n_samples);

int init_amplifier_str(m_eng_amplifier_str *str);
int reconfigure_amplifier(void *data_struct);
int calc_amplifier(void *data_struct, float *dest, float *src, int n_samples);

/*
int init_mixer_str(m_eng_mixer_str *str);
int calc_mixer(void *data_struct, float **dest, float **src, int n_samples);
*/

#endif

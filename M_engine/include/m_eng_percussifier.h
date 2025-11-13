#ifndef M_ENG_PERCUSSIFIER_H_
#define M_ENG_PERCUSSIFIER_H_

#define PERCUSSIFIER_MUTE 	  	0
#define PERCUSSIFIER_FADE_IN  	1
#define PERCUSSIFIER_HOLD	  	2
#define PERCUSSIFIER_FADE_OUT 	3
#define PERCUSSIFIER_REFRACTORY 4

typedef struct
{
	m_parameter tempo;
	m_parameter note;
	m_parameter trigger_threshold;
	m_parameter arm_threshold;
	m_parameter refractory_period;
	m_parameter fade_in;
	m_parameter fade_out;
	
	int state;
	int fade_in_samples;
	int hold_samples;
	int refractory_samples;
	
	int timer;
	
	float decay_rate;
	float rms_short;
	float rms_long;
	
	float alpha_short;
	float alpha_long;
	
	float gain;
	float fade_alpha;
	
	int r;
} m_eng_percussifier_str;

int init_percussifier_str(m_eng_percussifier_str *str);
int reconfigure_percussifier(void *data_struct);
int calc_percussifier(void *data_struct, float *dest, float *src, int n_samples);

#endif

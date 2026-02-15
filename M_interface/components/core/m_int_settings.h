#ifndef M_INT_SETTINGS_H_
#define M_INT_SETTINGS_H_

#define CONTEXT_PROFILE_ID  0xFFFF
#define INPUT_GAIN_PID		0x0000
#define OUTPUT_GAIN_PID		0x0001

typedef struct
{
	m_parameter input_gain;
	m_parameter output_gain;
	
	const char *default_profile;
	uint16_t default_profile_id;
	
	int changed;
} m_settings;

int send_settings(m_settings *settings);

int init_settings_save_task();

int settings_set_default_profile(m_profile *profile);

int init_settings(m_settings *settings);

extern SemaphoreHandle_t settings_mutex;

#endif

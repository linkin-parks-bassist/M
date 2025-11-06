#ifndef M_INT_SETTINGS_H_
#define M_INT_SETTINGS_H_

typedef struct
{
	m_int_parameter global_volume;
	
	const char *default_profile;
	uint16_t default_profile_id;
	
	int changed;
} m_int_settings;

int send_settings(m_int_settings *settings);

int init_settings_save_task();

int settings_set_default_profile(m_int_profile *profile);

int init_settings(m_int_settings *settings);

extern SemaphoreHandle_t settings_mutex;

#endif

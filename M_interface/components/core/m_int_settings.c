#include "m_int.h"

SemaphoreHandle_t settings_mutex;

int init_settings(m_settings *settings)
{
	if (!settings)
		return ERR_NULL_PTR;
	
	settings->changed = 0;
	settings->default_profile = NULL;
	settings->default_profile_id = 0;
	
	
	init_parameter(&settings->input_gain, "Input Gain", 0.0, -24.0, 24.0);
	settings->input_gain.units = " dB";
	settings->input_gain.id = (m_parameter_id){.profile_id = 0xFFFF, .transformer_id = 0, .parameter_id = 0};
	
	init_parameter(&settings->output_gain, "Output Gain", -60.0, -24.0, 24.0);
	settings->output_gain.units = " dB";
	settings->output_gain.id = (m_parameter_id){.profile_id = 0xFFFF, .transformer_id = 0, .parameter_id = 1};
	
	
	settings_mutex = xSemaphoreCreateMutex();
	assert(settings_mutex != NULL);
	
	return NO_ERROR;
}

int send_settings(m_settings *settings)
{
	if (!settings)
		return ERR_NULL_PTR;
	
	xSemaphoreTake(settings_mutex, portMAX_DELAY);
	queue_msg_to_teensy(create_m_message(M_MESSAGE_SET_PARAM_VALUE, "sssf", 0xFFFF, 0, 0, settings->input_gain.value));
	queue_msg_to_teensy(create_m_message(M_MESSAGE_SET_PARAM_VALUE, "sssf", 0xFFFF, 0, 1, settings->output_gain.value));
	xSemaphoreGive(settings_mutex);
	
	return NO_ERROR;
}

int copy_settings_struct(m_settings *dest, m_settings *src)
{
	if (!dest || !src)
		return ERR_NULL_PTR;
	
	dest->input_gain.value = src->input_gain.value;
	dest->output_gain.value = src->output_gain.value;
	dest->default_profile = src->default_profile;
	
	return NO_ERROR;
}

#define SETTINGS_SAVE_TRIES 3

void settings_save_task(void *arg)
{
	TickType_t last_wake = xTaskGetTickCount();
	int ret_val;
	int i = 0;
	
	m_settings local_copy;

	while (true)
	{
		if (global_cxt.settings.changed)
		{
			xSemaphoreTake(settings_mutex, portMAX_DELAY);
			copy_settings_struct(&local_copy, &global_cxt.settings);
			global_cxt.settings.changed = 0;
			xSemaphoreGive(settings_mutex);
			
			printf("Settings change detected!\n");
			
			i = 0;
			do {
				ret_val = safe_file_write((int (*)(void*, const char*))save_settings_to_file, &local_copy, SETTINGS_FNAME);
				i++;
			} while (ret_val != NO_ERROR && i < SETTINGS_SAVE_TRIES);
			
		}
		vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(100));
	}

	vTaskDelete(NULL);
}

int init_settings_save_task()
{
	xTaskCreatePinnedToCore(
		settings_save_task,
		"Teens Comms Task",
		4096,
		NULL,
		8,
		NULL,
		1
	);
	
	return NO_ERROR;
}

int settings_set_default_profile(m_profile *profile)
{
	xSemaphoreTake(settings_mutex, portMAX_DELAY);
	global_cxt.settings.default_profile = profile->fname;
	global_cxt.settings.changed = 1;
	xSemaphoreGive(settings_mutex);
	
	return NO_ERROR;
}

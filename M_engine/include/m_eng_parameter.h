#ifndef M_PARAMETER_H_
#define M_PARAMETER_H_

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

#define PARAM_NAM_ENG_MAX_LEN 16

#define PARAMETER_UPDATE_INSTANT			0
#define PARAMETER_UPDATE_MONOBLOCK_LINEAR 	1
#define PARAMETER_UPDATE_BIBLOCK_LINEAR 	2
#define PARAMETER_UPDATE_QUADBLOCK_LINEAR 	3

#define PARAMETER_SCALE_LINEAR		0
#define PARAMETER_SCALE_LOGARITHMIC	1

#define DEFAULT_MAX_JUMP 0.01

/* At first, I tried doing this with unions and a type enum but...
 * I just didn't like it. So I'm just separating them */

typedef struct
{
	float value;
	float min;
	float max;
	
	int updated;
	float old_value;
	float new_value;
	
	float max_jump;
	
	int scale;
} m_eng_parameter;

typedef struct
{
	int16_t value;
	
	int updated;
	int16_t old_value;
	int16_t new_value;
	
} m_eng_setting;

typedef struct
{
	uint16_t pid;
	uint16_t tid;
	uint16_t ppid;
} m_ppid;

void init_parameter(m_eng_parameter *param, float initial, float min, float max, float max_jump, int scale);
int init_setting(m_eng_setting *setting, int16_t initial);

int update_parameter(m_eng_parameter *param, float new_value);
int update_parameter_update(m_eng_parameter *param, float new_value);
int update_setting(m_eng_setting *setting, uint16_t new_value);

#endif

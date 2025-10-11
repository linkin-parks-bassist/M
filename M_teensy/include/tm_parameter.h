#ifndef M_PARAMETER_H_
#define M_PARAMETER_H_

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

#define PARAM_NAME_MAX_LEN 16

#define PARAMETER_UPDATE_INSTANT			0
#define PARAMETER_UPDATE_MONOBLOCK_LINEAR 	1
#define PARAMETER_UPDATE_BIBLOCK_LINEAR 	2
#define PARAMETER_UPDATE_QUADBLOCK_LINEAR 	3

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
	
	int update_policy;
	int update_progress;
} tm_parameter;

typedef struct
{
	uint16_t value;
	
	int updated;
	uint16_t old_value;
	uint16_t new_value;
	
	int update_policy;
	int update_progress;
} tm_option;

typedef struct
{
	uint16_t pid;
	uint16_t tid;
	uint16_t ppid;
} m_ppid;

int init_option_simple(tm_option *option, int initial);
int init_option(tm_option *option, int initial, int update_policy);

int init_parameter_simple(tm_parameter *param, float initial);
int init_parameter(tm_parameter *param, float initial, float min, float max, float max_jump);

int update_parameter(tm_parameter *param, float new_value);
int update_parameter_update(tm_parameter *param, float new_value);
int update_option(tm_option *option, uint16_t new_value);

int parameter_update_tick(tm_parameter *param);
int parameter_update_finish(tm_parameter *param);
int option_update_tick(tm_parameter *param);

#endif

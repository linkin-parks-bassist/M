#ifndef M_ENG_PARAMETER_H_
#define M_ENG_PARAMETER_H_

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

#define DEFAULT_MAX_JUMP 0.01

#include "m_parameter.h"

void init_parameter(m_parameter *param, float initial, float min, float max, float max_jump, int scale);
int init_setting(m_setting *setting, int16_t initial);

#endif

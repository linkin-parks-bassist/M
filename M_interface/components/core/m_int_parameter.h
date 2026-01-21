#ifndef M_INT_PARAMETER_H_
#define M_INT_PARAMETER_H_

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

#define PARAM_NAM_ENG_MAX_LEN 254

typedef m_setting_pll setting_ll;

int init_parameter_str(m_parameter *param);
int init_parameter(m_parameter *param, const char *name, float level, float min, float max);

int init_setting_str(m_setting *setting);
int init_setting(m_setting *setting, const char *name, uint16_t level);

void clone_parameter(m_parameter *dest, m_parameter *src);
int clone_setting(m_setting *dest, m_setting *src);
void gut_setting(m_setting *setting);

#endif

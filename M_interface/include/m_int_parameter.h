#ifndef M_PARAMETER_H_
#define M_PARAMETER_H_

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

#define PARAM_NAM_ENG_MAX_LEN 254

#define PARAMETER_SCALE_LINEAR		0
#define PARAMETER_SCALE_LOGARITHMIC	1

typedef struct
{
	uint16_t profile_id;
	uint16_t transformer_id;
	uint16_t parameter_id;
} m_int_parameter_id;

typedef m_int_parameter_id m_int_setting_id;

typedef struct
{
	m_int_parameter_id id;
	
	float val;
	float min;
	float max;
	
	float factor;
	
	int widget_type;
	char *name;
	char *units;
	
	int scale;
	
	int group;
} m_int_parameter;

DECLARE_LINKED_PTR_LIST(m_int_parameter);

typedef m_int_parameter_ptr_linked_list parameter_ll;

typedef struct
{
	uint16_t value;
	char *name;
} m_int_setting_setting;

typedef struct
{
	m_int_setting_id id;
	
	uint16_t val;
	
	int n_settings;
	m_int_setting_setting **settings;
	
	int widget_type;
	char *name;
} m_int_setting;

DECLARE_LINKED_PTR_LIST(m_int_setting);

typedef m_int_setting_ptr_linked_list setting_ll;

int init_m_int_parameter(m_int_parameter *param);
int init_parameter(m_int_parameter *param, char *name, float level, float min, float max);

int init_m_int_setting(m_int_setting *setting);
int init_setting(m_int_setting *setting, char *name, uint16_t level);

void clone_parameter(m_int_parameter *dest, m_int_parameter *src);
void clone_setting(m_int_setting *dest, m_int_setting *src);

#endif

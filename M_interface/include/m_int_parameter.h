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

typedef m_int_parameter_id m_int_parameter_id;

typedef struct
{
	m_int_parameter_id id;
	
	float val;
	float min;
	float max;
	
	float factor;
	
	int widget_type;
	const char *name;
	const char *units;
	
	int scale;
	
	int group;
} m_int_parameter;

DECLARE_LINKED_PTR_LIST(m_int_parameter);

typedef m_int_parameter_ptr_linked_list parameter_ll;

typedef struct
{
	uint16_t value;
	const char *name;
} m_int_setting_option;

#define TRANSFORMER_SETTING_ENUM 	0
#define TRANSFORMER_SETTING_BOOL 	1
#define TRANSFORMER_SETTING_INT 	2

typedef struct
{
	int type;
	
	m_int_parameter_id id;
	
	uint16_t val;
	uint16_t min;
	uint16_t max;
	
	int n_options;
	m_int_setting_option *options;
	
	int widget_type;
	const char *name;
	const char *units;
	
	int group;
} m_int_setting;

DECLARE_LINKED_PTR_LIST(m_int_setting);

typedef m_int_setting_ptr_linked_list setting_ll;

int init_parameter_str(m_int_parameter *param);
int init_parameter(m_int_parameter *param, const char *name, float level, float min, float max);

int init_setting_str(m_int_setting *setting);
int init_setting(m_int_setting *setting, const char *name, uint16_t level);

void clone_parameter(m_int_parameter *dest, m_int_parameter *src);
int clone_setting(m_int_setting *dest, m_int_setting *src);
void gut_setting(m_int_setting *setting);

#endif

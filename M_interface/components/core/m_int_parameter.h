#ifndef M_INT_PARAMETER_H_
#define M_INT_PARAMETER_H_

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
#else
#include <stddef.h>
#include <stdint.h>
#endif

#include "m_linked_list.h"
#include "m_int_representation.h"

#define PARAM_NAM_ENG_MAX_LEN 254

#define PARAMETER_SCALE_LINEAR		0
#define PARAMETER_SCALE_LOGARITHMIC	1

typedef struct m_parameter_id
{
	uint16_t profile_id;
	uint16_t transformer_id;
	uint16_t parameter_id;
} m_parameter_id;

typedef struct m_parameter
{
	float value;
	float min;
	float max;
	
	int scale;
	
	int updated;
	float old_value;
	float new_value;
	
	float max_velocity;
	
	m_parameter_id id;
	
	float factor;
	
	int widget_type;
	const char *name;
	const char *name_internal;
	const char *units;
	
	int group;
	
	m_representation_pll *reps;
} m_parameter;

typedef struct m_setting_option
{
	uint16_t value;
	const char *name;
} m_setting_option;

typedef struct m_setting_id
{
	uint16_t profile_id;
	uint16_t transformer_id;
	uint16_t setting_id;
} m_setting_id;

#define TRANSFORMER_SETTING_ENUM 	0
#define TRANSFORMER_SETTING_BOOL 	1
#define TRANSFORMER_SETTING_INT 	2

#define TRANSFORMER_SETTING_PAGE_SETTINGS 0
#define TRANSFORMER_SETTING_PAGE_MAIN 	  1

typedef struct m_setting
{
	int value;
	
	int updated;
	int old_value;
	int new_value;
	
	int type;
	int page;
	
	m_setting_id id;
	
	int min;
	int max;
	
	int n_options;
	m_setting_option *options;
	
	int widget_type;
	const char *name;
	const char *units;
	
	int group;
	
	m_representation_pll *reps;
} m_setting;

DECLARE_LINKED_PTR_LIST(m_parameter);
DECLARE_LINKED_PTR_LIST(m_setting);

typedef m_setting_pll setting_ll;

int init_parameter_str(m_parameter *param);
int init_parameter(m_parameter *param, const char *name, float level, float min, float max);
int init_parameter_wni(m_parameter *param, const char *name, const char *name_internal, float level, float min, float max);

m_parameter *new_m_parameter_wni(const char *name, const char *name_internal, float level, float min, float max);

int init_setting_str(m_setting *setting);
int init_setting(m_setting *setting, const char *name, uint16_t level);

void clone_parameter(m_parameter *dest, m_parameter *src);
m_parameter *m_parameter_make_clone(m_parameter *src);

int clone_setting(m_setting *dest, m_setting *src);
m_setting *m_setting_make_clone(m_setting *src);
void gut_setting(m_setting *setting);

#endif

#ifndef M_PARAMETER_H_
#define M_PARAMETER_H_

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
	
	#if defined(M_ENGINE)
	
	float max_jump;
	
	#elif defined(M_INTERFACE)
	
	m_parameter_id id;
	
	float factor;
	
	int widget_type;
	const char *name;
	const char *units;
	
	int group;
	
	#endif
} m_parameter;

#if defined(M_INTERFACE)

typedef struct m_setting_option
{
	uint16_t value;
	const char *name;
} m_setting_option;

#endif

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
	int16_t value;
	
	int updated;
	int16_t old_value;
	int16_t new_value;
	
	#if defined(M_ENGINE)
	
	
	#elif defined(M_INTERFACE)
	
	int type;
	int page;
	
	m_setting_id id;
	
	uint16_t min;
	uint16_t max;
	
	int n_options;
	m_setting_option *options;
	
	int widget_type;
	const char *name;
	const char *units;
	
	int group;
	
	#endif
} m_setting;

DECLARE_LINKED_PTR_LIST(m_parameter);
DECLARE_LINKED_PTR_LIST(m_setting);

#endif

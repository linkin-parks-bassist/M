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

#ifndef M_ENGINE
typedef float m_parameter_t;
#endif

typedef int16_t m_setting_t;

typedef struct m_parameter
{
	m_parameter_t value;
	m_parameter_t min;
	m_parameter_t max;
	
	int scale;
	
	int updated;
	m_parameter_t old_value;
	m_parameter_t new_value;
	
	#if defined(M_ENGINE)
	
	m_parameter_t max_jump;
	
	#elif defined(M_INTERFACE)
	
	m_parameter_id id;
	
	m_parameter_t factor;
	
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
	m_setting_t value;
	
	int updated;
	m_setting_t old_value;
	m_setting_t new_value;
	
	#if defined(M_ENGINE)
	
	
	#elif defined(M_INTERFACE)
	
	int type;
	int page;
	
	m_setting_id id;
	
	m_setting_t min;
	m_setting_t max;
	
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

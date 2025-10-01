#ifndef M_PARAMETER_H_
#define M_PARAMETER_H_

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

#define PARAM_NAME_MAX_LEN 254

typedef float 	 m_param_level_t;
typedef uint16_t m_param_option_t;
typedef uint8_t	 m_param_switch_t;

typedef enum
{
	M_PARAM_LEVEL,
	M_PARAM_OPTION,
	M_PARAM_SWITCH,
	M_PARAM_ERR
} m_param_type;

typedef union
{
	m_param_level_t  level;
	m_param_option_t option;
	m_param_switch_t active;
	uint8_t bytes[4];
} m_param_value;

typedef struct
{
	m_param_type type;
	m_param_value val;
	
	int updated;
	char *name;
} m_parameter;

typedef struct
{
	uint16_t profile_id;
	uint16_t transformer_id;
	uint16_t parameter_id;
} m_parameter_id;

#define INIT_PARAM(p, t, v, n) 											\
	p.type = t; 														\
	switch (t) 															\
	{ 																	\
		case M_PARAM_OPTION: p.val.option = (m_param_option_t)v; break;	\
		case M_PARAM_SWITCH: p.val.active = (m_param_switch_t)v; break;	\
		default:			 p.val.level  = (m_param_level_t )v; break;	\
	}																	\
	p.name = n ? strdup(n) : NULL;										\
	p.updated = 1;

int init_parameter(m_parameter *param, m_param_type type, m_param_value initial);

size_t m_param_val_size(m_param_type type);

#endif

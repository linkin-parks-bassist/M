#ifndef M_PARAMETER_H_
#define M_PARAMETER_H_

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

#define PARAM_NAME_MAX_LEN 254

#define PARAM_WIDGET_VIRTUAL_POT 0

#define OPTION_WIDGET_HSLIDER 	 0
#define OPTION_WIDGET_VSLIDER 	 1
#define OPTION_WIDGET_SWITCH 	 2

typedef struct
{
	uint16_t profile_id;
	uint16_t transformer_id;
	uint16_t parameter_id;
} em_parameter_id;

typedef em_parameter_id em_option_id;

typedef struct
{
	em_parameter_id id;
	
	float val;
	float min;
	float max;
	
	float factor;
	
	int widget_type;
	char *name;
} em_parameter;

typedef struct
{
	uint16_t value;
	char *name;
} em_option_option;

typedef struct
{
	em_option_id id;
	
	uint16_t val;
	
	int n_options;
	em_option_option **options;
	
	int widget_type;
	char *name;
} em_option;

int init_em_parameter(em_parameter *param);
int init_parameter(em_parameter *param, char *name, float level, float min, float max);

int init_em_option(em_option *option);
int init_option(em_option *option, char *name, uint16_t level);

#endif

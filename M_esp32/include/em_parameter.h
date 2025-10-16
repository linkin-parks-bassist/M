#ifndef M_PARAMETER_H_
#define M_PARAMETER_H_

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

#define PARAM_NAME_MAX_LEN 254

#define PARAMETER_SCALE_LINEAR		0
#define PARAMETER_SCALE_LOGARITHMIC	1

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
	char *units;
	
	int scale;
	
	int group;
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

void clone_parameter(em_parameter *dest, em_parameter *src);
void clone_option(em_option *dest, em_option *src);

#endif

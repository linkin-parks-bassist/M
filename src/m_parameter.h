#ifndef M_PARAMETER_H_
#define M_PARAMETER_H_

#define PARAMETER_NAME_MAX_LENGTH 32

typedef struct
{
	char name[PARAMETER_NAME_MAX_LENGTH];
	float value;
	
	int updated;
} m_parameter;

int init_parameter(m_parameter *param, const char *name, float value);
int parameter_set_name(m_parameter *param, const char *name);

#endif

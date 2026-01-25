#ifndef M_INT_PARAM_UPDATE_H_
#define M_INT_PARAM_UPDATE_H_

#define MAX_CONCURRENT_PARAM_UPDATES 16

typedef struct {
	m_parameter_id id;
	m_parameter *p;
	m_transformer *t;
	float target;
	int send;
} m_parameter_update;

void m_param_update_task(void *arg);

int m_parameter_trigger_update(m_parameter *param, float target);

#endif

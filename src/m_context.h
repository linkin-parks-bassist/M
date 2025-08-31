#ifndef M_CONTEXT_H_
#define M_CONTEXT_H_

#define N_PIPELINES 	 	2
#define BYPASS_PIPELINE 	N_PIPELINES
#define M_STATE_SWITCHING 	1

#define SWITCH_TIME 3.9

typedef struct
{	
	int state;
	
	m_pipeline pipeline;
} m_context;

int init_context(m_context *cxt);
int update(m_context *cxt);

int in_bypass_mode(m_context *cxt);

int connect_pipeline(m_context *cxt, int pipeline);
int trigger_pipeline_switch(m_context *cxt, int new_pipeline, float switch_time);

#endif


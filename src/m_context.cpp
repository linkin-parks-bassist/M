#include "M.h"

int init_context(m_context *cxt)
{
	if (!cxt) return ERR_NULL_PTR;
	
	
	init_bypass_pipeline(&cxt->pipeline);
	
	return NO_ERROR;
}


int update(m_context *cxt)
{
	if (!cxt) return ERR_NULL_PTR;
	
	return NO_ERROR;
}

int connect_pipeline(m_context *cxt, int pipeline)
{
	if (!cxt) return ERR_NULL_PTR;
	
	return NO_ERROR;
}

int disconnect_pipeline(m_context *cxt, int pipeline)
{
	if (!cxt) return ERR_NULL_PTR;
	
	return NO_ERROR;
}

int trigger_pipeline_switch(m_context *cxt, int new_pipeline, float switch_time)
{
	if (!cxt) return ERR_NULL_PTR;
	
	
	
	return NO_ERROR;
}

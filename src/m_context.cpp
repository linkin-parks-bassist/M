#include "M.h"

int init_m_context(m_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	cxt->n_profiles = 1;
	cxt->active_profile = 0;
	
	init_bypass_profile(&cxt->profiles[0]);
	cxt->active_pipeline = &cxt->profiles[0].pipeline;
	
	for (int i = 1; i < MAX_N_PROFILES; i++)
		nullify_profile(&cxt->profiles[i]);
	
	return NO_ERROR;
}

/* Returns error codes in negative; otherwise, returns the index (ID) of the new profile */
int m_context_new_profile(m_context *cxt)
{
	if (!cxt)
		return -ERR_NULL_PTR;
	
	if (cxt->n_profiles >= MAX_N_PROFILES)
		return -ERR_FIXED_ARRAY_FULL;
	
	init_profile(&cxt->profiles[cxt->n_profiles++]);
	
	return cxt->n_profiles - 1;
}

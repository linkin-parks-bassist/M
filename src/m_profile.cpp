#include "M.h"

int nullify_profile(m_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	nullify_pipeline(&profile->pipeline);
	
	return NO_ERROR;
}

int init_profile(m_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	init_pipeline(&profile->pipeline, 16, 4);
	
	return NO_ERROR;
}

int init_bypass_profile(m_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	init_bypass_pipeline(&profile->pipeline);
	
	return NO_ERROR;
}

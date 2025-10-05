#include "tm.h"

int nullify_profile(tm_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	nullify_pipeline(&profile->pipeline);
	init_pipe_line(&profile->pipe_line);
	
	return NO_ERROR;
}

int init_profile(tm_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	init_pipeline(&profile->pipeline, 16, 4);
	init_pipe_line(&profile->pipe_line);
	
	return NO_ERROR;
}

int init_bypass_profile(tm_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	init_bypass_pipeline(&profile->pipeline);
	init_pipe_line(&profile->pipe_line);
	
	return NO_ERROR;
}

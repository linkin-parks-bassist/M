#ifndef M_PROFILE_H_
#define M_PROFILE_H_

typedef struct
{
	tm_pipeline pipeline;
	tm_pipe_line pipe_line;
} tm_profile;

int nullify_profile(tm_profile *profile);
int init_profile(tm_profile *profile);
int init_bypass_profile(tm_profile *profile);

#endif

#if 0
#include "tm.h"

int init_transformer_str(tm_transformer_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	
	
	return NO_ERROR;
}

int reconfigure_transformer(void *data_struct)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	tm_transformer_str *str = (tm_transformer_str*)data_struct;
	
	
	
	
	return NO_ERROR;
}

int calc_transformer(void *data_struct, float *dest, float *src, int n_samples)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	tm_transformer_str *str = (tm_transformer_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;

	for (int i = 0; i < n_samples; i++)
	{
		out_buffer[i] = 0.0;
	}
	
	return NO_ERROR;
}


#endif

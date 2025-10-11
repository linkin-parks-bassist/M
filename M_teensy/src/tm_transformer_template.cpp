#if 0
#include "tm.h"


int reconfigure_transformer(void *data_struct)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	tm_transformer_str *str = (tm_transformer_str*)data_struct;
	
	return NO_ERROR;
}

int calc_transformer(void *data_struct, float **dest, float **src, int n_samples)
{
	if (!data_struct)
		return ERR_NULL_PTR;
	
	tm_transformer_str *str = (tm_transformer_str*)data_struct;
	
	float *in_buffer  =  src ? ( src[0] ?  src[0] : zero_buffer) : zero_buffer;
	float *out_buffer = dest ? (dest[0] ? dest[0] : sink_buffer) : sink_buffer;

	
	return NO_ERROR;
}

int init_transformer_struct_default(tm_transformer_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	

	
	return NO_ERROR;
}
#endif

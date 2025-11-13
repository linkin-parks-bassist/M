#if 0
#include "m_eng.h"
static const char *FNAME = "m_transformer_template.c";

int init_transformer_str(m_transformer_str *str)
{
	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	
	
	RETURN_ERR_CODE(NO_ERROR);
}

int reconfigure_transformer(void *data_struct)
{
	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_transformer_str *str = (m_transformer_str*)data_struct;
	
	
	
	
	RETURN_ERR_CODE(NO_ERROR);
}

int calc_transformer(void *data_struct, float *dest, float *src, int n_samples)
{
	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_transformer_str *str = (m_transformer_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;

	for (int i = 0; i < n_samples; i++)
	{
		out_buffer[i] = 0.0;
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}


#endif

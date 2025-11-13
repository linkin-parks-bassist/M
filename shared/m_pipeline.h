#ifndef M_PIPELINE_H_
#define M_PIPELINE_H_

typedef struct
{
	#if defined(M_ENGINE)
	
	int n_transformers;
	int transformer_array_length;
	m_transformer **transformers;
	
	uint16_t next_id;
	
	int transition_policy;
	
	#elif defined(M_INTERFACE)
	
	m_transformer_pll *transformers;
	
	#endif
} m_pipeline;

#endif

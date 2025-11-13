#include "m_int.h"

int init_m_pipeline(m_pipeline *pipeline)
{
	if (!pipeline)
		return ERR_NULL_PTR;
	
	pipeline->transformers = NULL;
	
	return NO_ERROR;
}

m_transformer *m_pipeline_append_transformer_type(m_pipeline *pipeline, uint16_t type)
{
	if (!pipeline)
		return NULL;
	
	m_transformer *trans = m_alloc(sizeof(m_transformer));
	
	if (!trans)
		return NULL;
	
	init_transformer_of_type(trans, type);
	
	pipeline->transformers = m_transformer_pll_append(pipeline->transformers, trans);
	
	return trans;
}

int m_pipeline_remove_transformer(m_pipeline *pipeline, uint16_t id)
{
	printf("m_pipeline_remove_transformer\n");
	if (!pipeline)
		return ERR_NULL_PTR;
	
	m_transformer_pll *current = pipeline->transformers;
	m_transformer_pll *prev = NULL;
	
	while (current)
	{
		if (current->data && current->data->id == id)
		{
			if (current->data)
				free_transformer(current->data);
			
			if (prev)
				prev->next = current->next;
			else
				pipeline->transformers = current->next;
			
			m_free(current);
			
			printf("m_pipeline_remove_transformer found and vanquished the transformer\n");
			return NO_ERROR;
		}
		
		prev = current;
		current = current->next;
	}
	
	printf("m_pipeline_remove_transformer finished without finding the transformer\n");
	return ERR_INVALID_TRANSFORMER_ID;
}

int m_pipeline_get_n_transformers(m_pipeline *pipeline)
{
	if (!pipeline)
		return -ERR_NULL_PTR;
	
	int n = 0;
	
	m_transformer_pll *current = pipeline->transformers;
	
	while (current)
	{
		if (current->data)
			n++;
		current = current->next;
	}
	
	return n;
}

int clone_pipeline(m_pipeline *dest, m_pipeline *src)
{
	if (!src || !dest)
		return ERR_NULL_PTR;
	
	printf("Cloning pipeline...\n");
	
	m_transformer_pll *current = src->transformers;
	m_transformer_pll *nl;
	m_transformer *trans = NULL;
	
	int i = 0;
	while (current)
	{
		printf("Cloning transformer %d... current = %p, current->next = %p\n", i, current, current->next);
		if (current->data)
		{
			trans = m_alloc(sizeof(m_transformer));
			
			if (!trans)
				return ERR_ALLOC_FAIL;
			
			clone_transformer(trans, current->data);
			
			nl = m_transformer_pll_append(dest->transformers, trans);
		
			if (nl)
				dest->transformers = nl;
		}
		
		current = current->next;
		i++;
	}
	
	return NO_ERROR;
}

void gut_pipeline(m_pipeline *pipeline)
{
	if (!pipeline)
		return;
	
	destructor_free_m_transformer_pll(pipeline->transformers, free_transformer);
	pipeline->transformers = NULL;
}

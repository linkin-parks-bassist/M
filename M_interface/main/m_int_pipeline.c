#include "m_int.h"

int init_m_int_pipeline(m_int_pipeline *pipeline)
{
	if (!pipeline)
		return ERR_NULL_PTR;
	
	pipeline->transformers = NULL;
	
	return NO_ERROR;
}

m_int_transformer *m_int_pipeline_append_transformer_type(m_int_pipeline *pipeline, uint16_t type)
{
	if (!pipeline)
		return NULL;
	
	m_int_transformer *trans = m_int_malloc(sizeof(m_int_transformer));
	
	if (!trans)
		return NULL;
	
	init_transformer_of_type(trans, type);
	
	pipeline->transformers = m_int_transformer_ptr_linked_list_append(pipeline->transformers, trans);
	
	return trans;
}

int m_int_pipeline_remove_transformer(m_int_pipeline *pipeline, uint16_t id)
{
	printf("m_int_pipeline_remove_transformer\n");
	if (!pipeline)
		return ERR_NULL_PTR;
	
	m_int_transformer_ptr_linked_list *current = pipeline->transformers;
	m_int_transformer_ptr_linked_list *prev = NULL;
	
	while (current)
	{
		if (current->data && current->data->transformer_id == id)
		{
			if (current->data)
				free_transformer(current->data);
			
			if (prev)
				prev->next = current->next;
			else
				pipeline->transformers = current->next;
			
			m_int_free(current);
			
			printf("m_int_pipeline_remove_transformer found and vanquished the transformer\n");
			return NO_ERROR;
		}
		
		prev = current;
		current = current->next;
	}
	
	printf("m_int_pipeline_remove_transformer finished without finding the transformer\n");
	return ERR_INVALID_TRANSFORMER_ID;
}

int m_int_pipeline_get_n_transformers(m_int_pipeline *pipeline)
{
	if (!pipeline)
		return -ERR_NULL_PTR;
	
	int n = 0;
	
	m_int_transformer_ll *current = pipeline->transformers;
	
	while (current)
	{
		if (current->data)
			n++;
		current = current->next;
	}
	
	return n;
}

int clone_pipeline(m_int_pipeline *dest, m_int_pipeline *src)
{
	if (!src || !dest)
		return ERR_NULL_PTR;
	
	printf("Cloning pipeline...\n");
	
	m_int_transformer_ll *current = src->transformers;
	m_int_transformer_ll *nl;
	m_int_transformer *trans = NULL;
	
	int i = 0;
	while (current)
	{
		printf("Cloning transformer %d... current = %p, current->next = %p\n", i, current, current->next);
		if (current->data)
		{
			trans = m_int_malloc(sizeof(m_int_transformer));
			
			if (!trans)
				return ERR_ALLOC_FAIL;
			
			clone_transformer(trans, current->data);
			
			nl = m_int_transformer_ptr_linked_list_append(dest->transformers, trans);
		
			if (nl)
				dest->transformers = nl;
		}
		
		current = current->next;
		i++;
	}
	
	return NO_ERROR;
}

void gut_pipeline(m_int_pipeline *pipeline)
{
	if (!pipeline)
		return;
	
	destructor_free_m_int_transformer_ptr_linked_list(pipeline->transformers, free_transformer);
	pipeline->transformers = NULL;
}

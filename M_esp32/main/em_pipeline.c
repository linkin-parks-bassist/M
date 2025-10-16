#include "em.h"

int init_em_pipeline(em_pipeline *pipeline)
{
	if (!pipeline)
		return ERR_NULL_PTR;
	
	pipeline->transformers = NULL;
	
	return NO_ERROR;
}

em_transformer *em_pipeline_append_transformer_type(em_pipeline *pipeline, uint16_t type)
{
	if (!pipeline)
		return NULL;
	
	em_transformer *trans = malloc(sizeof(em_transformer));
	
	if (!trans)
		return NULL;
	
	init_transformer_of_type(trans, type);
	
	pipeline->transformers = em_transformer_ptr_linked_list_append(pipeline->transformers, trans);
	
	return trans;
}

int em_pipeline_remove_transformer(em_pipeline *pipeline, uint16_t id)
{
	printf("em_pipeline_remove_transformer\n");
	if (!pipeline)
		return ERR_NULL_PTR;
	
	em_transformer_ptr_linked_list *current = pipeline->transformers;
	em_transformer_ptr_linked_list *prev = NULL;
	
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
			
			free(current);
			
			printf("em_pipeline_remove_transformer found and vanquished the transformer\n");
			return NO_ERROR;
		}
		
		prev = current;
		current = current->next;
	}
	
	printf("em_pipeline_remove_transformer finished without finding the transformer\n");
	return ERR_INVALID_TRANSFORMER_ID;
}

int em_pipeline_get_n_transformers(em_pipeline *pipeline)
{
	if (!pipeline)
		return -ERR_NULL_PTR;
	
	int n = 0;
	
	em_transformer_ll *current = pipeline->transformers;
	
	while (current)
	{
		if (current->data)
			n++;
		current = current->next;
	}
	
	return n;
}

int clone_pipeline(em_pipeline *dest, em_pipeline *src)
{
	if (!src || !dest)
		return ERR_NULL_PTR;
	
	printf("Cloning pipeline...\n");
	
	em_transformer_ll *current = src->transformers;
	em_transformer_ll *nl;
	em_transformer *trans = NULL;
	
	int i = 0;
	while (current)
	{
		printf("Cloning transformer %d... current = %p, current->next = %p\n", i, current, current->next);
		if (current->data)
		{
			trans = malloc(sizeof(em_transformer));
			
			if (!trans)
				return ERR_ALLOC_FAIL;
			
			clone_transformer(trans, current->data);
			
			nl = em_transformer_ptr_linked_list_append(dest->transformers, trans);
		
			if (nl)
				dest->transformers = nl;
		}
		
		current = current->next;
		i++;
	}
	
	return NO_ERROR;
}

void gut_pipeline(em_pipeline *pipeline)
{
	if (!pipeline)
		return;
	
	destructor_free_em_transformer_ptr_linked_list(pipeline->transformers, free_transformer);
	pipeline->transformers = NULL;
}

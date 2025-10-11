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

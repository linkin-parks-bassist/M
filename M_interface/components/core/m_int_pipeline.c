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

m_transformer *m_pipeline_append_transformer_eff(m_pipeline *pipeline, m_effect_desc *eff)
{
	if (!pipeline || !eff)
		return NULL;
	
	m_transformer *trans = m_alloc(sizeof(m_transformer));
	
	if (!trans)
		return NULL;
	
	m_transformer_pll *node = m_alloc(sizeof(m_transformer_pll));
	
	if (!node)
		return NULL;
	
	node->data = trans;
	node->next = NULL;
	
	init_transformer_from_effect_desc(trans, eff);
	
	if (!pipeline->transformers)
	{
		trans->id = 0;
		pipeline->transformers = node;
	}
	else
	{
		int least_free_id = 0;
		m_transformer_pll *current = pipeline->transformers;
		
		while (current)
		{
			if (current->data)
			{
				if (current->data->id >= least_free_id)
					least_free_id = current->data->id + 1;
			}
			
			if (current->next)
				current = current->next;
			else
				break;
		}
		
		trans->id = least_free_id;
		current->next = node;
	}
	
	printf("Created transformer with id %d\n", trans->id);
	
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

m_fpga_transfer_batch m_pipeline_create_fpga_transfer_batch(m_pipeline *pipeline)
{
	m_fpga_transfer_batch result;
	
	result.buf 		= NULL;
	result.buf_len 	= 0;
	result.len 		= 0;
	
	if (!pipeline)
		return result;
	
	m_fpga_resource_report res   = m_empty_fpga_resource_report();
	m_fpga_resource_report local = m_empty_fpga_resource_report();
	
	result = m_new_fpga_transfer_batch();
		
	m_transformer_pll *current = pipeline->transformers;
	m_transformer *trans;
	
	while (current)
	{
		trans = current->data;
		
		if (trans)
		{
			m_fpga_transfer_batch_append_transformer(trans, &res, &local, &result);
			m_fpga_resource_report_integrate(&res, &local);
		}
		
		current = current->next;
	}
	
	return result;
}

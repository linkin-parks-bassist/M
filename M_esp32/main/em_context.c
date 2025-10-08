#include "em.h"

#define INITIAL_PROFILE_ARRAY_LENGTH 8
#define PROFILE_ARRAY_CHUNK_SIZE	 8

int init_em_context(em_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	cxt->n_profiles = 1;
	cxt->active_profile = 0;
	
	cxt->profile_array_length = INITIAL_PROFILE_ARRAY_LENGTH;
	cxt->profiles = malloc(sizeof(em_profile) * cxt->profile_array_length);
	
	if (!cxt->profiles)
		return ERR_ALLOC_FAIL;
	
	for (int i = 0; i < cxt->profile_array_length; i++)
	{
		init_em_profile(&cxt->profiles[i]);
		cxt->profiles[i].id = i;
		
		em_profile_set_default_name_from_id(&cxt->profiles[i]);
	}
	
	return NO_ERROR;
}

int em_context_add_profile(em_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	int ret_val;
	
	if (cxt->n_profiles >= cxt->profile_array_length)
	{
		ret_val = em_context_enlarge_profile_array(cxt);
		
		if (ret_val != NO_ERROR)
			return ret_val;
	}
	
	cxt->n_profiles++;
	
	return NO_ERROR;
}

int em_context_enlarge_profile_array(em_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	
	int try_size = PROFILE_ARRAY_CHUNK_SIZE;
	em_profile *new_ptr;
	
	do
	{
		new_ptr = malloc(sizeof(em_profile) * (cxt->profile_array_length + try_size));
		
		if (!new_ptr)
			try_size /= 2;
	} while (!new_ptr && try_size);
	
	if (!new_ptr)
		return ERR_ALLOC_FAIL;
	
	if (cxt->profiles)
	{
		memcpy(new_ptr, cxt->profiles, cxt->profile_array_length * sizeof(em_profile));
		free(cxt->profiles);
	}
	
	for (int i = 0; i < try_size; i++)
		init_em_profile(&new_ptr[cxt->profile_array_length + i]);
	
	cxt->profile_array_length = cxt->profile_array_length + try_size;
	cxt->profiles = new_ptr;
	
	return NO_ERROR;
}

int em_context_set_n_profiles(em_context *cxt, int n)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	int tries = 0;
	
	while (cxt->profile_array_length < n && tries < 32)
	{
		em_context_enlarge_profile_array(cxt);
		tries++;
	}
	
	if (cxt->profile_array_length < n)
		return ERR_ALLOC_FAIL;
	
	cxt->n_profiles = n;
	
	return NO_ERROR;
}

em_transformer *cxt_get_transformer_by_id(em_context *cxt, uint16_t profile_id, uint16_t transformer_id)
{
	if (!cxt)
		return NULL;
	
	if (cxt->n_profiles <= profile_id)
		return NULL;
	
	for (int i = 0; i < cxt->profiles[profile_id].pipeline.n_transformers; i++)
	{
		if (cxt->profiles[profile_id].pipeline.transformers[i].transformer_id == transformer_id)
			return &cxt->profiles[profile_id].pipeline.transformers[i];
	}
	
	return NULL;
}

em_parameter *cxt_get_parameter_by_id(em_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id)
{
	if (!cxt)
		return NULL;
	
	em_transformer *trans = cxt_get_transformer_by_id(cxt, profile_id, transformer_id);
	
	if (!trans)
		return NULL;
	
	if (parameter_id >= trans->n_parameters)
		return NULL;
	
	return &trans->parameters[parameter_id];
}

em_option *cxt_get_option_by_id(em_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t option_id)
{
	if (!cxt)
		return NULL;
	
	em_transformer *trans = cxt_get_transformer_by_id(cxt, profile_id, transformer_id);
	
	if (!trans)
		return NULL;
	
	if (option_id >= trans->n_options)
		return NULL;
	
	return &trans->options[option_id];
}

int cxt_transformer_id_to_position(em_context *cxt, uint16_t profile_id, uint16_t transformer_id)
{
	if (!cxt)
		return -1;
	
	if (profile_id >= cxt->n_profiles)
		return -1;
	
	int ret_val = -1;
	
	for (int i = 0; i < cxt->profiles[profile_id].pipeline.n_transformers; i++)
	{
		if (cxt->profiles[profile_id].pipeline.transformers[i].transformer_id == transformer_id)
		{
			ret_val = i;
			break;
		}
	}
	
	return ret_val;
}

int cxt_transformer_position_to_id(em_context *cxt, uint16_t profile_id, uint16_t transformer_pos)
{
	if (!cxt)
		return -1;
	
	if (profile_id >= cxt->n_profiles)
		return -1;
	
	if (transformer_pos >= cxt->profiles[profile_id].pipeline.n_transformers)
		return -1;
	
	return cxt->profiles[profile_id].pipeline.transformers[transformer_pos].transformer_id;
}

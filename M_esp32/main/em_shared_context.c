#include "em.h"


#define INITIAL_PROFILE_ARRAY_LENGTH 8
#define PROFILE_ARRAY_CHUNK_SIZE	 8

int init_teensy_context(teensy_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	cxt->n_profiles = 0;
	cxt->active_profile = 0;
	
	cxt->profile_array_length = INITIAL_PROFILE_ARRAY_LENGTH;
	cxt->profiles = malloc(sizeof(teensy_profile) * cxt->profile_array_length);
	
	if (!cxt->profiles)
		return ERR_ALLOC_FAIL;
	
	for (int i = 0; i < cxt->profile_array_length; i++)
		init_teensy_profile(&cxt->profiles[i]);
	
	return NO_ERROR;
}

int teensy_context_enlarge_profile_array(teensy_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	
	int try_size = PROFILE_ARRAY_CHUNK_SIZE;
	teensy_profile *new_ptr;
	
	do
	{
		new_ptr = malloc(sizeof(teensy_profile) * (cxt->profile_array_length + try_size));
		
		if (!new_ptr)
			try_size /= 2;
	} while (!new_ptr && try_size);
	
	if (!new_ptr)
		return ERR_ALLOC_FAIL;
	
	if (cxt->profiles)
	{
		memcpy(new_ptr, cxt->profiles, cxt->profile_array_length * sizeof(teensy_profile));
		free(cxt->profiles);
	}
	
	for (int i = 0; i < try_size; i++)
		init_teensy_profile(&new_ptr[cxt->profile_array_length + i]);
	
	cxt->profile_array_length = cxt->profile_array_length + try_size;
	cxt->profiles = new_ptr;
	
	return NO_ERROR;
}

int teensy_context_set_n_profiles(teensy_context *cxt, int n)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	int tries = 0;
	
	while (cxt->profile_array_length < n && tries < 32)
	{
		teensy_context_enlarge_profile_array(cxt);
		tries++;
	}
	
	if (cxt->profile_array_length < n)
		return ERR_ALLOC_FAIL;
	
	cxt->n_profiles = n;
	
	return NO_ERROR;
}

int init_teensy_profile(teensy_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	profile->id = 0;
	
	int ret_val = init_teensy_pipeline(&profile->pipeline);
	
	if (ret_val != NO_ERROR)
		return ret_val;
	
	return NO_ERROR;
}

int teensy_profile_set_default_name_from_id(teensy_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	// Compute the digits in the ID. 
	int id_digits;
	int id_div = profile->id;
	
	for (id_digits = 0; id_div || !id_digits; id_div = id_div / 10)
		id_digits++;
	
	profile->name = malloc(9 + id_digits);
	
	if (!profile->name)
		return ERR_ALLOC_FAIL;
	
	sprintf(profile->name, "Profile %d\n", id_digits);
	
	return NO_ERROR;
}

#define INITIAL_TRANSFORMER_ARRAY_LENGTH 8
#define TRANSFORMER_ARRAY_CHUNK_SIZE	 8

int init_teensy_pipeline(teensy_pipeline *pipeline)
{
	if (!pipeline)
		return ERR_NULL_PTR;
	
	pipeline->n_transformers = 0;
	
	pipeline->transformer_array_length = INITIAL_TRANSFORMER_ARRAY_LENGTH;
	pipeline->transformers = malloc(sizeof(teensy_transformer) * pipeline->transformer_array_length);
	
	if (!pipeline->transformers)
	{
		pipeline->transformer_array_length = 0;
		return ERR_ALLOC_FAIL;
	}
	
	for (int i = 0; i < pipeline->transformer_array_length; i++)
		init_teensy_transformer(&pipeline->transformers[i]);
	
	return NO_ERROR;
}

int teensy_pipeline_enlarge_transformer_array(teensy_pipeline *pipeline)
{
	if (!pipeline)
		return ERR_NULL_PTR;
	
	int try_size = TRANSFORMER_ARRAY_CHUNK_SIZE;
	teensy_transformer *new_ptr;
	
	do
	{
		new_ptr = malloc(sizeof(teensy_transformer) * (pipeline->transformer_array_length + try_size));
		
		if (!new_ptr)
			try_size /= 2;
	} while (!new_ptr && try_size);
	
	if (!new_ptr)
		return ERR_ALLOC_FAIL;
	
	if (pipeline->transformers)
	{
		memcpy(new_ptr, pipeline->transformers, pipeline->transformer_array_length * sizeof(teensy_transformer));
		free(pipeline->transformers);
	}
	
	for (int i = 0; i < try_size; i++)
		init_teensy_transformer(&new_ptr[pipeline->transformer_array_length + i]);
	
	pipeline->transformer_array_length = pipeline->transformer_array_length + try_size;
	pipeline->transformers = new_ptr;
	
	return NO_ERROR;
}

int teensy_pipeline_set_n_transformers(teensy_pipeline *pipeline, int n)
{
	if (!pipeline)
		return ERR_NULL_PTR;
	
	int tries = 0;
	
	while (pipeline->transformer_array_length < n && tries < 32)
	{
		teensy_pipeline_enlarge_transformer_array(pipeline);
		tries++;
	}
	
	if (pipeline->transformer_array_length < n)
		return ERR_ALLOC_FAIL;
	
	pipeline->n_transformers = n;
	
	return NO_ERROR;
}

#define INITIAL_PARAMETER_ARRAY_LENGTH 	8
#define PARAMETER_ARRAY_CHUNK_SIZE	 	8

int init_teensy_transformer(teensy_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->profile_id = 0;
	trans->transformer_id = 0;
	
	trans->n_parameters = 0;
	
	trans->position = 0;
	
	trans->parameter_array_length = INITIAL_TRANSFORMER_ARRAY_LENGTH;
	trans->parameters = malloc(sizeof(teensy_parameter) * trans->parameter_array_length);
	
	if (!trans->parameters)
	{
		trans->parameter_array_length = 0;
		return ERR_ALLOC_FAIL;
	}
	
	for (int i = 0; i < trans->parameter_array_length; i++)
		init_teensy_parameter(&trans->parameters[i]);
	
	return NO_ERROR;
}

int teensy_transformer_enlarge_parameter_array(teensy_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int try_size = TRANSFORMER_ARRAY_CHUNK_SIZE;
	teensy_parameter *new_ptr;
	
	do
	{
		new_ptr = malloc(sizeof(teensy_parameter) * (trans->parameter_array_length + try_size));
		
		if (!new_ptr)
			try_size /= 2;
	} while (!new_ptr && try_size);
	
	if (!new_ptr)
		return ERR_ALLOC_FAIL;
	
	if (trans->parameters)
	{
		memcpy(new_ptr, trans->parameters, sizeof(teensy_parameter) * trans->parameter_array_length);
		free(trans->parameters);
	}
	
	for (int i = 0; i < try_size; i++)
		init_teensy_parameter(&new_ptr[trans->parameter_array_length + i]);
	
	trans->parameter_array_length = trans->parameter_array_length + try_size;
	trans->parameters = new_ptr;
	
	return NO_ERROR;
}

int init_teensy_parameter(teensy_parameter *param)
{
	if (!param)
		return ERR_NULL_PTR;
	
	param->type = M_PARAM_LEVEL;
	
	param->val.level = 0.0;
	param->min.level = 0.0;
	param->max.level = 1.0;
	
	param->id = (m_parameter_id){.profile_id = 0, .transformer_id = 0, .parameter_id = 0};
	
	param->name = NULL;
	
	return NO_ERROR;
}

int teensy_context_add_profile(teensy_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	int ret_val;
	
	if (cxt->n_profiles >= cxt->profile_array_length)
	{
		ret_val = teensy_context_enlarge_profile_array(cxt);
		
		if (ret_val != NO_ERROR)
			return ret_val;
	}
	
	cxt->n_profiles++;
	
	return NO_ERROR;
}

int teensy_pipeline_append_transformer_type (teensy_pipeline *pipeline, uint16_t type)
{
	if (!pipeline)
		return ERR_NULL_PTR;
	
	int ret_val;
	
	if (pipeline->n_transformers >= pipeline->transformer_array_length)
	{
		ret_val = teensy_pipeline_enlarge_transformer_array(pipeline);
		
		if (ret_val != NO_ERROR)
			return ret_val;
	}
	
	init_teensy_transformer(&pipeline->transformers[pipeline->n_transformers]);
	pipeline->transformers[pipeline->n_transformers++].type = type;
	
	return NO_ERROR;
}

int teensy_pipeline_insert_transformer_type (teensy_pipeline *pipeline, uint16_t type, int position)
{
	if (!pipeline)
		return ERR_NULL_PTR;
	
	int ret_val;
	
	if (pipeline->n_transformers >= pipeline->transformer_array_length)
	{
		ret_val = teensy_pipeline_enlarge_transformer_array(pipeline);
		
		if (ret_val != NO_ERROR)
			return ret_val;
	}
	
	for (int i = pipeline->n_transformers - 1; i >= position && i >= 0; i--)
		pipeline->transformers[i + 1] = pipeline->transformers[i];
	
	init_teensy_transformer(&pipeline->transformers[pipeline->n_transformers]);
	
	pipeline->transformers[pipeline->n_transformers++].type = type;
	
	return NO_ERROR;
}

int teensy_pipeline_prepend_transformer_type(teensy_pipeline *pipeline, uint16_t type)
{
	return teensy_pipeline_insert_transformer_type(pipeline, type, 0);
}

int teensy_transformer_add_parameter(teensy_transformer *trans, teensy_parameter *param)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int ret_val;
	
	if (trans->n_parameters >= trans->parameter_array_length)
	{
		ret_val = teensy_transformer_enlarge_parameter_array(trans);
		
		if (ret_val != NO_ERROR)
			return ret_val;
	}
	
	trans->parameters[trans->n_parameters++] = *param;
	
	return NO_ERROR;
}

int teensy_transformer_set_n_parameters(teensy_transformer *trans, int n)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int tries = 0;
	
	while (trans->parameter_array_length < n && tries < 32)
	{
		teensy_transformer_enlarge_parameter_array(trans);
		tries++;
	}
	
	if (trans->parameter_array_length < n)
		return ERR_ALLOC_FAIL;
	
	trans->n_parameters = n;
	
	return NO_ERROR;
}

teensy_transformer *cxt_get_transformer_by_id(teensy_context *cxt, uint16_t profile_id, uint16_t transformer_id)
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

teensy_parameter *cxt_get_parameter_by_id(teensy_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id)
{
	if (!cxt)
		return NULL;
	
	teensy_transformer *trans = cxt_get_transformer_by_id(cxt, profile_id, transformer_id);
	
	if (!trans)
		return NULL;
	
	if (parameter_id >= trans->n_parameters)
		return NULL;
	
	return &trans->parameters[parameter_id];
}

int cxt_transformer_id_to_position(teensy_context *cxt, uint16_t profile_id, uint16_t transformer_id)
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

int cxt_transformer_position_to_id(teensy_context *cxt, uint16_t profile_id, uint16_t transformer_pos)
{
	if (!cxt)
		return -1;
	
	if (profile_id >= cxt->n_profiles)
		return -1;
	
	if (transformer_pos >= cxt->profiles[profile_id].pipeline.n_transformers)
		return -1;
	
	return cxt->profiles[profile_id].pipeline.transformers[transformer_pos].transformer_id;
}

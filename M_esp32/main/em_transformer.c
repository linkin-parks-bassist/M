#include "em.h"

#define INITIAL_PARAMETER_ARRAY_LENGTH 	8
#define PARAMETER_ARRAY_CHUNK_SIZE	 	8

#define INITIAL_OPTION_ARRAY_LENGTH 	8
#define OPTION_ARRAY_CHUNK_SIZE	 		8

IMPLEMENT_LINKED_PTR_LIST(em_transformer);

char *transformer_type_name(uint16_t type)
{
	for (int i = 0; i < N_TRANSFORMER_TYPES; i++)
	{
		if (transformer_table[i].type == type)
			return transformer_table[i].name;
	}
	
	return NULL;
}

const char *TAG = "Transformer";

int init_transformer(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->profile_id 	  = 0;
	trans->transformer_id = 0;
	trans->type 		  = 0;
	
	trans->position = 0;
	
	int ret_val;
	
	ret_val = init_transformer_option_array(trans);
	
	if (ret_val != NO_ERROR)
		return ret_val;
	
	ret_val = init_transformer_parameter_array(trans);
	
	if (ret_val != NO_ERROR)
		return ret_val;
	
	trans->view_page = NULL;
	
	return NO_ERROR;
}

int init_transformer_parameter_array(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->n_parameters = 0;
	trans->parameter_array_length = INITIAL_PARAMETER_ARRAY_LENGTH;
	trans->parameters = malloc(sizeof(em_parameter) * trans->parameter_array_length);
	if (!trans->parameters)
	{
		trans->parameter_array_length = 0;
		return ERR_ALLOC_FAIL;
	}
	for (int i = 0; i < trans->parameter_array_length; i++)
		init_em_parameter(&trans->parameters[i]);
	
	return NO_ERROR;
}

int init_transformer_option_array(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->n_options = 0;
	trans->option_array_length = INITIAL_OPTION_ARRAY_LENGTH;
	trans->options = malloc(sizeof(em_option) * trans->option_array_length);
	if (!trans->options)
	{
		trans->option_array_length = 0;
		return ERR_ALLOC_FAIL;
	}
	for (int i = 0; i < trans->option_array_length; i++)
		init_em_option(&trans->options[i]);
	
	return NO_ERROR;
}

int transformer_rectify_param_ids(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	for (int i = 0; i < trans->n_parameters; i++)
	{
		trans->parameters[i].id.profile_id = trans->profile_id;
		trans->parameters[i].id.transformer_id = trans->transformer_id;
	}
	
	return NO_ERROR;
}

int transformer_set_id(em_transformer *trans, uint16_t profile_id, uint16_t transformer_id)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->profile_id = profile_id;
	trans->transformer_id = transformer_id;
	
	transformer_rectify_param_ids(trans);
	
	return NO_ERROR;
}


int em_transformer_enlarge_parameter_array(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int try_size = PARAMETER_ARRAY_CHUNK_SIZE;
	em_parameter *new_ptr;
	
	do
	{
		new_ptr = malloc(sizeof(em_parameter) * (trans->parameter_array_length + try_size));
		
		if (!new_ptr)
			try_size /= 2;
	} while (!new_ptr && try_size);
	
	if (!new_ptr)
		return ERR_ALLOC_FAIL;
	
	if (trans->parameters)
	{
		memcpy(new_ptr, trans->parameters, sizeof(em_parameter) * trans->parameter_array_length);
		free(trans->parameters);
	}
	
	for (int i = 0; i < try_size; i++)
		init_em_parameter(&new_ptr[trans->parameter_array_length + i]);
	
	trans->parameter_array_length = trans->parameter_array_length + try_size;
	trans->parameters = new_ptr;
	
	return NO_ERROR;
}


int em_transformer_enlarge_option_array(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int try_size = OPTION_ARRAY_CHUNK_SIZE;
	em_option *new_ptr;
	
	do
	{
		new_ptr = malloc(sizeof(em_option) * (trans->option_array_length + try_size));
		
		if (!new_ptr)
			try_size /= 2;
	} while (!new_ptr && try_size);
	
	if (!new_ptr)
		return ERR_ALLOC_FAIL;
	
	if (trans->options)
	{
		memcpy(new_ptr, trans->options, sizeof(em_option) * trans->option_array_length);
		free(trans->options);
	}
	
	for (int i = 0; i < try_size; i++)
		init_em_option(&new_ptr[trans->option_array_length + i]);
	
	trans->option_array_length = trans->option_array_length + try_size;
	trans->options = new_ptr;
	
	return NO_ERROR;
}

int request_append_transformer(uint16_t type, em_transformer *local)
{
	if (!local)
		return ERR_NULL_PTR;
	
	et_msg msg = create_et_msg(ET_MESSAGE_APPEND_TRANSFORMER, "ss", local->profile_id, local->type);
	msg.callback = transformer_receive_id;
	msg.cb_arg = local;
	
	return queue_msg_to_teensy(msg);
}

void transformer_receive_id(et_msg message, te_msg response)
{
	printf("Transformer receive ID!\n");
	em_transformer *trans = message.cb_arg;
	
	if (!trans)
		return;
	
	uint16_t pid, tid;
	
	memcpy(&pid, &response.data[0], sizeof(uint16_t));
	memcpy(&tid, &response.data[2], sizeof(uint16_t));
	
	if (pid != trans->profile_id)
	{
		ESP_LOGE(TAG, "Transformer ID for transformer in profile %d sent to transformer in %d\n", pid, trans->profile_id);
	}
	else
	{
		printf("Transformer %p obtains id %d.%d\n", trans, pid, tid);
		trans->profile_id = pid;
		trans->transformer_id = tid;
		
		transformer_rectify_param_ids(trans);
	}
}

int transformer_add_parameter(em_transformer *trans, em_parameter *param)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int ret_val;
	
	if (trans->n_parameters >= trans->parameter_array_length)
	{
		ret_val = em_transformer_enlarge_parameter_array(trans);
		
		if (ret_val != NO_ERROR)
			return ret_val;
	}
	
	trans->parameters[trans->n_parameters++] = *param;
	
	return NO_ERROR;
}

em_parameter *transformer_add_parameter_rp(em_transformer *trans)
{
	if (!trans)
		return NULL;
	
	int ret_val;
	
	if (trans->n_parameters >= trans->parameter_array_length)
	{
		ret_val = em_transformer_enlarge_parameter_array(trans);
		
		if (ret_val != NO_ERROR)
			return NULL;
	}
	
	trans->n_parameters++;
	
	return &trans->parameters[trans->n_parameters - 1];
}

int em_transformer_set_n_parameters(em_transformer *trans, int n)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int tries = 0;
	
	while (trans->parameter_array_length < n && tries < 32)
	{
		em_transformer_enlarge_parameter_array(trans);
		tries++;
	}
	
	if (trans->parameter_array_length < n)
		return ERR_ALLOC_FAIL;
	
	trans->n_parameters = n;
	
	return NO_ERROR;
}


int em_transformer_set_n_options(em_transformer *trans, int n)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int tries = 0;
	
	while (trans->option_array_length < n && tries < 32)
	{
		em_transformer_enlarge_option_array(trans);
		tries++;
	}
	
	if (trans->option_array_length < n)
		return ERR_ALLOC_FAIL;
	
	trans->n_options = n;
	
	return NO_ERROR;
}

int transformer_add_option(em_transformer *trans, em_option *option)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int ret_val;
	
	if (trans->n_options >= trans->option_array_length)
	{
		ret_val = em_transformer_enlarge_option_array(trans);
		
		if (ret_val != NO_ERROR)
			return ret_val;
	}
	
	trans->options[trans->n_options++] = *option;
	
	return NO_ERROR;
}

int transformer_init_ui_page(em_transformer *trans, em_ui_page *parent)
{
	printf("transformer_init_ui_page...\n");
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->view_page = malloc(sizeof(em_ui_page));
	
	if (!trans->view_page)
		return ERR_NULL_PTR;
	
	init_ui_page(trans->view_page);
	init_transformer_view(trans->view_page);
	configure_transformer_view(trans->view_page, trans);
	trans->view_page->parent = parent;
	
	printf("done transformer_init_ui_page\n");
	return NO_ERROR;
}

int clone_transformer(em_transformer *dest, em_transformer *src)
{
	if (!src || !dest)
		return ERR_NULL_PTR;
	
	printf("Cloning transformer...\n");
	uint16_t profile_id;
	uint16_t transformer_id;
	
	init_transformer(dest);
	
	dest->type = src->type;
	dest->position = src->position;
	
	for(int i = 0; i < src->n_parameters; i++)
		transformer_add_parameter(dest, &src->parameters[i]);
	
	for (int i = 0; i < src->n_options; i++)
		transformer_add_option(dest, &src->options[i]);
	
	src->view_page = NULL;
	
	printf("Clone transformer done\n");
	
	return NO_ERROR;
}


void gut_transformer(em_transformer *trans)
{
	if (!trans)
		return;
	
	free(trans->parameters);
	trans->parameters = NULL;
	free(trans->options);
	trans->options = NULL;
	
	free_transformer_view(trans->view_page);
	trans->view_page = NULL;
	
	trans->profile_id 	  = 0;
	trans->transformer_id = 0;
	trans->type 		  = 0;
	trans->position 	  = 0;
	
	trans->n_parameters = 0;
	trans->parameter_array_length = 0;
	trans->n_options = 0;
	trans->option_array_length = 0;
}


void free_transformer(em_transformer *trans)
{
	if (!trans)
		return;
	
	free(trans->parameters);
	free(trans->options);
	
	free_transformer_view(trans->view_page);
	
	free(trans);
}

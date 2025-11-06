#include "m_int.h"

#define INITIAL_PARAMETER_ARRAY_LENGTH 	8
#define PARAMETER_ARRAY_CHUNK_SIZE	 	8

#define INITIAL_OPTION_ARRAY_LENGTH 	8
#define OPTION_ARRAY_CHUNK_SIZE	 		8

IMPLEMENT_LINKED_PTR_LIST(m_int_transformer);

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

int init_transformer(m_int_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->profile_id 	  = 0;
	trans->transformer_id = 0;
	trans->type 		  = 0;
	
	trans->position = 0;
	
	trans->parameters = NULL;
	
	int ret_val;
	
	ret_val = init_transformer_setting_array(trans);
	
	if (ret_val != NO_ERROR)
		return ret_val;
	
	/*ret_val = init_transformer_parameter_array(trans);
	
	if (ret_val != NO_ERROR)
		return ret_val;*/
	
	trans->view_page = NULL;
	trans->profile = NULL;
	
	return NO_ERROR;
}

int init_transformer_setting_array(m_int_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->n_settings = 0;
	trans->setting_array_length = INITIAL_OPTION_ARRAY_LENGTH;
	trans->settings = m_int_malloc(sizeof(m_int_setting) * trans->setting_array_length);
	if (!trans->settings)
	{
		trans->setting_array_length = 0;
		return ERR_ALLOC_FAIL;
	}
	for (int i = 0; i < trans->setting_array_length; i++)
		init_m_int_setting(&trans->settings[i]);
	
	return NO_ERROR;
}

int transformer_rectify_param_ids(m_int_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	parameter_ll *current = trans->parameters;
	
	while (current)
	{
		if (current->data)
		{
			current->data->id.profile_id = trans->profile_id;
			current->data->id.transformer_id = trans->transformer_id;
		}
		
		current = current->next;
	}
	
	return NO_ERROR;
}

int transformer_set_id(m_int_transformer *trans, uint16_t profile_id, uint16_t transformer_id)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->profile_id = profile_id;
	trans->transformer_id = transformer_id;
	
	transformer_rectify_param_ids(trans);
	
	return NO_ERROR;
}

int m_int_transformer_enlarge_setting_array(m_int_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int try_size = OPTION_ARRAY_CHUNK_SIZE;
	m_int_setting *new_ptr;
	
	do
	{
		new_ptr = m_int_malloc(sizeof(m_int_setting) * (trans->setting_array_length + try_size));
		
		if (!new_ptr)
			try_size /= 2;
	} while (!new_ptr && try_size);
	
	if (!new_ptr)
		return ERR_ALLOC_FAIL;
	
	if (trans->settings)
	{
		memcpy(new_ptr, trans->settings, sizeof(m_int_setting) * trans->setting_array_length);
		m_int_free(trans->settings);
	}
	
	for (int i = 0; i < try_size; i++)
		init_m_int_setting(&new_ptr[trans->setting_array_length + i]);
	
	trans->setting_array_length = trans->setting_array_length + try_size;
	trans->settings = new_ptr;
	
	return NO_ERROR;
}

int request_append_transformer(uint16_t type, m_int_transformer *local)
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
	m_int_transformer *trans = message.cb_arg;
	
	if (!trans)
		return;
	
	uint16_t pid, tid;
	
	memcpy(&pid, &response.data[0], sizeof(uint16_t));
	memcpy(&tid, &response.data[2], sizeof(uint16_t));
	
	if (pid != trans->profile_id)
	{
		#ifndef M_SIMULATED
		ESP_LOGE(TAG, "Transformer ID for transformer in profile %d sent to transformer in %d\n", pid, trans->profile_id);
		#endif
	}
	else
	{
		printf("Transformer %p obtains id %d.%d\n", trans, pid, tid);
		trans->profile_id = pid;
		trans->transformer_id = tid;
		
		transformer_rectify_param_ids(trans);
	}
}

m_int_parameter *transformer_add_parameter(m_int_transformer *trans)
{
	if (!trans)
		return NULL;
	
	int ret_val;
	
	m_int_parameter *param = m_int_malloc(sizeof(m_int_parameter));
	
	if (!param)
		return NULL;
	
	parameter_ll *nl = m_int_parameter_ptr_linked_list_append(trans->parameters, param);
	
	if (!nl)
	{
		m_int_free(param);
		return NULL;
	}
	
	trans->parameters = nl;
	
	return param;
}


int m_int_transformer_set_n_settings(m_int_transformer *trans, int n)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int tries = 0;
	
	while (trans->setting_array_length < n && tries < 32)
	{
		m_int_transformer_enlarge_setting_array(trans);
		tries++;
	}
	
	if (trans->setting_array_length < n)
		return ERR_ALLOC_FAIL;
	
	trans->n_settings = n;
	
	return NO_ERROR;
}

int transformer_add_setting(m_int_transformer *trans, m_int_setting *setting)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int ret_val;
	
	if (trans->n_settings >= trans->setting_array_length)
	{
		ret_val = m_int_transformer_enlarge_setting_array(trans);
		
		if (ret_val != NO_ERROR)
			return ret_val;
	}
	
	trans->settings[trans->n_settings++] = *setting;
	
	return NO_ERROR;
}

int transformer_init_ui_page(m_int_transformer *trans, m_int_ui_page *parent)
{
	printf("transformer_init_ui_page...\n");
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->view_page = m_int_malloc(sizeof(m_int_ui_page));
	
	if (!trans->view_page)
		return ERR_NULL_PTR;
	
	init_ui_page(trans->view_page);
	init_transformer_view(trans->view_page);
	configure_transformer_view(trans->view_page, trans);
	trans->view_page->parent = parent;
	
	printf("done transformer_init_ui_page\n");
	return NO_ERROR;
}

int clone_transformer(m_int_transformer *dest, m_int_transformer *src)
{
	if (!src || !dest)
		return ERR_NULL_PTR;
	
	printf("Cloning transformer...\n");
	uint16_t profile_id;
	uint16_t transformer_id;
	
	init_transformer(dest);
	
	dest->type = src->type;
	dest->position = src->position;
	
	parameter_ll *current = src->parameters;
	m_int_parameter *param;
	
	while (current)
	{
		if(current->data)
		{
			param = transformer_add_parameter(dest);
			
			if (param)
			{
				memcpy(param, current->data, sizeof(m_int_parameter));
			}
		}
		
		current = current->next;
	}
	
	for (int i = 0; i < src->n_settings; i++)
		transformer_add_setting(dest, &src->settings[i]);
	
	src->view_page = NULL;
	
	printf("Clone transformer done\n");
	
	return NO_ERROR;
}


void gut_transformer(m_int_transformer *trans)
{
	if (!trans)
		return;
	
	m_int_free(trans->parameters);
	trans->parameters = NULL;
	m_int_free(trans->settings);
	trans->settings = NULL;
	
	free_transformer_view(trans->view_page);
	trans->view_page = NULL;
	
	trans->profile_id 	  = 0;
	trans->transformer_id = 0;
	trans->type 		  = 0;
	trans->position 	  = 0;
	
	trans->n_settings = 0;
	trans->setting_array_length = 0;
}


void free_transformer(m_int_transformer *trans)
{
	if (!trans)
		return;
	
	m_int_free(trans->parameters);
	m_int_free(trans->settings);
	
	free_transformer_view(trans->view_page);
	
	m_int_free(trans);
}

m_int_parameter *transformer_get_parameter(m_int_transformer *trans, int n)
{
	if (!trans)
		return NULL;
	
	parameter_ll *current = trans->parameters;
	int i = 0;
	
	while (current && i < n)
	{
		current = current->next;
		i++;
	}
	
	return current ? current->data : NULL;
}

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
	trans->settings = NULL;
	
	trans->view_page = NULL;
	trans->profile = NULL;
	
	init_parameter(&trans->wet_mix, "Wet Mix", 1.0, 0.0, 1.0);
	trans->wet_mix.id.parameter_id = TRANSFORMER_WET_MIX_PID;
	
	init_setting(&trans->band_mode, "Apply to", TRANSFORMER_MODE_FULL_SPECTRUM);
	trans->band_mode.id.parameter_id = TRANSFORMER_BAND_MODE_SID;
	
	trans->band_mode.n_options = 4;
	trans->band_mode.options = malloc(sizeof(m_int_setting_option) * trans->band_mode.n_options);
	
	if (!trans->band_mode.options)
		return ERR_ALLOC_FAIL;
	
	trans->band_mode.options[0].value = TRANSFORMER_MODE_FULL_SPECTRUM;
	trans->band_mode.options[0].name  = "All freq";
	
	trans->band_mode.options[1].value = TRANSFORMER_MODE_UPPER_SPECTRUM;
	trans->band_mode.options[1].name  = "Freq > cutoff";
	
	trans->band_mode.options[2].value = TRANSFORMER_MODE_LOWER_SPECTRUM;
	trans->band_mode.options[2].name  = "Freq < cutoff";
	
	trans->band_mode.options[3].value = TRANSFORMER_MODE_BAND;
	trans->band_mode.options[3].name  = "Freq in band";
	
	init_parameter(&trans->lp_cutoff_freq, "Cutoff", 4000.0, 1, 4000);
	trans->lp_cutoff_freq.scale = PARAMETER_SCALE_LOGARITHMIC;
	trans->lp_cutoff_freq.id.parameter_id = TRANSFORMER_BAND_LP_CUTOFF_PID;
	
	init_parameter(&trans->hp_cutoff_freq, "Cutoff", 1.0, 1, 4000);
	trans->hp_cutoff_freq.scale = PARAMETER_SCALE_LOGARITHMIC;
	trans->hp_cutoff_freq.id.parameter_id = TRANSFORMER_BAND_HP_CUTOFF_PID;
	
	return NO_ERROR;
}

int transformer_rectify_param_ids(m_int_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	parameter_ll *current_param = trans->parameters;
	
	while (current_param)
	{
		if (current_param->data)
		{
			current_param->data->id.profile_id = trans->profile_id;
			current_param->data->id.transformer_id = trans->transformer_id;
		}
		
		current_param = current_param->next;
	}
	
	setting_ll *current_setting = trans->settings;
	
	while (current_setting)
	{
		if (current_setting->data)
		{
			current_setting->data->id.profile_id = trans->profile_id;
			current_setting->data->id.transformer_id = trans->transformer_id;
		}
		
		current_setting = current_setting->next;
	}
	
	trans->band_mode.id.profile_id = trans->profile_id;
	trans->band_mode.id.transformer_id = trans->transformer_id;
	
	trans->lp_cutoff_freq.id.profile_id = trans->profile_id;
	trans->lp_cutoff_freq.id.transformer_id = trans->transformer_id;
	
	trans->hp_cutoff_freq.id.profile_id = trans->profile_id;
	trans->hp_cutoff_freq.id.transformer_id = trans->transformer_id;
	
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
	
	init_parameter_str(param);
	
	parameter_ll *nl = m_int_parameter_ptr_linked_list_append(trans->parameters, param);
	
	if (!nl)
	{
		m_int_free(param);
		return NULL;
	}
	
	trans->parameters = nl;
	
	return param;
}

m_int_setting *transformer_add_setting(m_int_transformer *trans)
{
	if (!trans)
		return NULL;
	
	int ret_val;
	
	m_int_setting *setting = m_int_malloc(sizeof(m_int_setting));
	
	if (!setting)
		return NULL;
	
	init_setting_str(setting);
	
	setting_ll *nl = m_int_setting_ptr_linked_list_append(trans->settings, setting);
	
	if (!nl)
	{
		m_int_free(setting);
		return NULL;
	}
	
	trans->settings = nl;
	
	return setting;
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
	
	parameter_ll *current_param = src->parameters;
	m_int_parameter *param;
	
	while (current_param)
	{
		if(current_param->data)
		{
			param = transformer_add_parameter(dest);
			
			if (param)
			{
				memcpy(param, current_param->data, sizeof(m_int_parameter));
			}
			else
			{
				return ERR_ALLOC_FAIL;
			}
		}
		
		current_param = current_param->next;
	}
	
	setting_ll *current_setting = src->settings;
	m_int_setting *setting;
	
	while (current_setting)
	{
		if(current_setting->data)
		{
			setting = transformer_add_setting(dest);
			
			if (setting)
			{
				clone_setting(setting, current_setting->data);
			}
			else
			{
				return ERR_ALLOC_FAIL;
			}
		}
		
		current_setting = current_setting->next;
	}
	
	src->view_page = NULL;
	
	printf("Clone transformer done\n");
	
	return NO_ERROR;
}


void gut_transformer(m_int_transformer *trans)
{
	if (!trans)
		return;
	
	free_m_int_parameter_ptr_linked_list(trans->parameters);
	destructor_free_m_int_setting_ptr_linked_list(trans->settings, gut_setting);
	trans->parameters = NULL;
	trans->settings = NULL;
	
	gut_setting(&trans->band_mode);
	
	free_transformer_view(trans->view_page);
	trans->view_page = NULL;
	
	trans->profile_id 	  = 0;
	trans->transformer_id = 0;
	trans->type 		  = 0;
	trans->position 	  = 0;
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


m_int_setting *transformer_get_setting(m_int_transformer *trans, int n)
{
	if (!trans)
		return NULL;
	
	setting_ll *current = trans->settings;
	int i = 0;
	
	while (current && i < n)
	{
		current = current->next;
		i++;
	}
	
	return current ? current->data : NULL;
}

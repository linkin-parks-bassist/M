#include "m_int.h"

#define INITIAL_PARAMETER_ARRAY_LENGTH 	8
#define PARAMETER_ARRAY_CHUNK_SIZE	 	8

#define INITIAL_OPTION_ARRAY_LENGTH 	8
#define OPTION_ARRAY_CHUNK_SIZE	 		8

const char *TAG = "Transformer";

IMPLEMENT_LINKED_PTR_LIST(m_transformer);

char *transformer_type_name(uint16_t type)
{
	for (int i = 0; i < N_TRANSFORMER_TYPES; i++)
	{
		if (transformer_table[i].type == type)
			return transformer_table[i].name;
	}
	
	return NULL;
}

const char *m_transformer_name(m_transformer *trans)
{
	if (!trans)
		return NULL;
	
	if (trans->eff)
	{
		if (trans->eff->name)
			return trans->eff->name;
	}
	
	return transformer_type_name(trans->type);
}


int init_transformer(m_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->id = 0;
	trans->type = 0;
	
	trans->position = 0;
	
	trans->parameters = NULL;
	trans->settings = NULL;
	
	trans->view_page = NULL;
	trans->profile = NULL;
	
	init_parameter(&trans->wet_mix, "Wet Mix", 1.0, 0.0, 1.0);
	trans->wet_mix.id.parameter_id = TRANSFORMER_WET_MIX_PID;
	
	init_setting(&trans->band_mode, "Apply to", TRANSFORMER_MODE_FULL_SPECTRUM);
	trans->band_mode.id.setting_id = TRANSFORMER_BAND_MODE_SID;
	
	trans->band_mode.n_options = 4;
	trans->band_mode.options = malloc(sizeof(m_setting_option) * trans->band_mode.n_options);
	
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
	
	init_parameter(&trans->band_lp_cutoff, "Cutoff", 4000.0, 1, 4000);
	trans->band_lp_cutoff.scale = PARAMETER_SCALE_LOGARITHMIC;
	trans->band_lp_cutoff.id.parameter_id = TRANSFORMER_BAND_LP_CUTOFF_PID;
	
	init_parameter(&trans->band_hp_cutoff, "Cutoff", 1.0, 1, 4000);
	trans->band_hp_cutoff.scale = PARAMETER_SCALE_LOGARITHMIC;
	trans->band_hp_cutoff.id.parameter_id = TRANSFORMER_BAND_HP_CUTOFF_PID;
	
	trans->eff = NULL;
	
	return NO_ERROR;
}

int init_transformer_from_effect_desc(m_transformer *trans, m_effect_desc *eff)
{
	printf("init_transformer_from_effect_desc. trans = %p, eff = %p\n", trans, eff);
	init_transformer(trans);
	trans->eff = eff;
	
	m_parameter_pll *nl;
	m_parameter *param;
	
	if (eff->params)
	{
		printf("Cloning parameters. n_params = %d\n", eff->n_params);
		for (int i = 0; i < eff->n_params; i++)
		{
			if (eff->params[i])
			{
				printf("Parameter %d = %p\n", i, eff->params[i]);
				param = m_parameter_make_clone(eff->params[i]);
				
				if (!param)
					return ERR_ALLOC_FAIL;
				
				nl = m_parameter_pll_append(trans->parameters, param);
				
				if (!nl)
					return ERR_ALLOC_FAIL;
				
				trans->parameters = nl;
				
				printf("Added sucessfully. trans->parameters = %p\n", trans->parameters);
			}
		}
	}
	
	return NO_ERROR;
}

int transformer_rectify_param_ids(m_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	m_parameter_pll *current_param = trans->parameters;
	
	while (current_param)
	{
		if (current_param->data)
		{
			if (trans->profile)
				current_param->data->id.profile_id = trans->profile->id;
			current_param->data->id.transformer_id = trans->id;
		}
		
		current_param = current_param->next;
	}
	
	setting_ll *current_setting = trans->settings;
	
	while (current_setting)
	{
		if (current_setting->data)
		{
			if (trans->profile)
				current_setting->data->id.profile_id = trans->profile->id;
			current_setting->data->id.transformer_id = trans->id;
		}
		
		current_setting = current_setting->next;
	}
	
	if (trans->profile)
		trans->band_mode.id.profile_id = trans->profile->id;
	trans->band_mode.id.transformer_id = trans->id;
	
	if (trans->profile)
		trans->band_lp_cutoff.id.profile_id = trans->profile->id;
	trans->band_lp_cutoff.id.transformer_id = trans->id;
	
	if (trans->profile)
		trans->band_hp_cutoff.id.profile_id = trans->profile->id;
	trans->band_hp_cutoff.id.transformer_id = trans->id;
	
	return NO_ERROR;
}

int transformer_set_id(m_transformer *trans, uint16_t profile_id, uint16_t transformer_id)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->id = transformer_id;
	
	transformer_rectify_param_ids(trans);
	
	return NO_ERROR;
}

int request_append_transformer(uint16_t type, m_transformer *local)
{
	if (!local)
		return ERR_NULL_PTR;
	
	if (!local->profile)
		return ERR_BAD_ARGS;
	
	m_message msg = create_m_message(M_MESSAGE_APPEND_TRANSFORMER, "ss", local->profile->id, local->type);
	msg.callback = transformer_receive_id;
	msg.cb_arg = local;
	
	return queue_msg_to_teensy(msg);
}

void transformer_receive_id(m_message message, m_response response)
{
	printf("Transformer receive ID!\n");
	m_transformer *trans = message.cb_arg;
	
	if (!trans)
		return;
	
	uint16_t pid, tid;
	
	memcpy(&pid, &response.data[0], sizeof(uint16_t));
	memcpy(&tid, &response.data[2], sizeof(uint16_t));
	
	if (!trans->profile || pid != trans->profile->id)
	{
		ESP_LOGE(TAG, "Transformer ID for transformer in profile %d sent to transformer in %d\n", pid, trans->profile->id);
	}
	else
	{
		printf("Transformer %p obtains id %d.%d\n", trans, pid, tid);
		trans->id = tid;
		
		transformer_rectify_param_ids(trans);
	}
}

m_parameter *transformer_add_parameter(m_transformer *trans)
{
	if (!trans)
		return NULL;
	
	int ret_val;
	
	m_parameter *param = m_alloc(sizeof(m_parameter));
	
	if (!param)
		return NULL;
	
	init_parameter_str(param);
	
	m_parameter_pll *nl = m_parameter_pll_append(trans->parameters, param);
	
	if (!nl)
	{
		m_free(param);
		return NULL;
	}
	
	trans->parameters = nl;
	
	return param;
}

m_setting *transformer_add_setting(m_transformer *trans)
{
	if (!trans)
		return NULL;
	
	int ret_val;
	
	m_setting *setting = m_alloc(sizeof(m_setting));
	
	if (!setting)
		return NULL;
	
	init_setting_str(setting);
	
	setting_ll *nl = m_setting_pll_append(trans->settings, setting);
	
	if (!nl)
	{
		m_free(setting);
		return NULL;
	}
	
	trans->settings = nl;
	
	return setting;
}

int transformer_init_ui_page(m_transformer *trans, m_ui_page *parent)
{
	printf("transformer_init_ui_page. trans = %p, parent = %p\n", trans, parent);
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->view_page = m_alloc(sizeof(m_ui_page));
	
	if (!trans->view_page)
		return ERR_ALLOC_FAIL;
	
	printf("init_ui_page(%p)...\n", trans->view_page);
	init_ui_page(trans->view_page);
	printf("init_transformer_view(%p)...\n", trans->view_page);
	init_transformer_view(trans->view_page);
	printf("configure_transformer_view(%p, %p)...\n", trans->view_page, trans);
	configure_transformer_view(trans->view_page, trans);
	trans->view_page->parent = parent;
	
	printf("done transformer_init_ui_page\n");
	return NO_ERROR;
}

int clone_transformer(m_transformer *dest, m_transformer *src)
{
	if (!src || !dest)
		return ERR_NULL_PTR;
	
	printf("Cloning transformer...\n");
	uint16_t profile_id;
	uint16_t transformer_id;
	
	init_transformer(dest);
	
	dest->type = src->type;
	dest->position = src->position;
	
	m_parameter_pll *current_param = src->parameters;
	m_parameter *param;
	
	while (current_param)
	{
		if(current_param->data)
		{
			param = transformer_add_parameter(dest);
			
			if (param)
			{
				memcpy(param, current_param->data, sizeof(m_parameter));
			}
			else
			{
				return ERR_ALLOC_FAIL;
			}
		}
		
		current_param = current_param->next;
	}
	
	setting_ll *current_setting = src->settings;
	m_setting *setting;
	
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


void gut_transformer(m_transformer *trans)
{
	if (!trans)
		return;
	
	free_m_parameter_pll(trans->parameters);
	destructor_free_m_setting_pll(trans->settings, gut_setting);
	trans->parameters = NULL;
	trans->settings = NULL;
	
	gut_setting(&trans->band_mode);
	
	free_transformer_view(trans->view_page);
	trans->view_page = NULL;
	
	trans->id 		= 0;
	trans->type 	= 0;
	trans->position = 0;
}


void free_transformer(m_transformer *trans)
{
	if (!trans)
		return;
	
	m_free(trans->parameters);
	m_free(trans->settings);
	
	free_transformer_view(trans->view_page);
	
	m_free(trans);
}

m_parameter *transformer_get_parameter(m_transformer *trans, int n)
{
	if (!trans)
		return NULL;
	
	m_parameter_pll *current = trans->parameters;
	int i = 0;
	
	while (current && i < n)
	{
		current = current->next;
		i++;
	}
	
	return current ? current->data : NULL;
}


m_setting *transformer_get_setting(m_transformer *trans, int n)
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

int m_fpga_transfer_batch_append_transformer(
		m_transformer *trans,
		const m_fpga_resource_report *cxt,
		m_fpga_resource_report *report,
		m_fpga_transfer_batch *batch
	)
{
	if (!trans || !cxt || !report || !batch)
		return ERR_NULL_PTR;
	
	trans->block_position = cxt->blocks;
	
	return m_fpga_transfer_batch_append_effect(trans->eff, cxt, report, trans->parameters, batch);
}

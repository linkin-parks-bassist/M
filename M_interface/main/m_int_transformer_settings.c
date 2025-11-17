#include "m_int.h"

int init_transformer_settings_page(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	init_ui_page(page);
	
	page->configure = configure_transformer_settings_page;
	page->create_ui = create_transformer_settings_page_ui;
	
	page->panel = new_panel();
	
	if (!page->panel)
		return ERR_NULL_PTR;
	
	page->data_struct = malloc(sizeof(trans_settings_page_str));
	
	if (!page->data_struct)
		return ERR_ALLOC_FAIL;
	
	trans_settings_page_str *str = (trans_settings_page_str*)page->data_struct;
	
	str->text = NULL;
	
	nullify_parameter_widget(&str->band_lp_cutoff);
	nullify_parameter_widget(&str->band_hp_cutoff);
	nullify_setting_widget(&str->band_mode);
	
	str->band_control_cont = NULL;
	
	return NO_ERROR;
}

int configure_transformer_settings_page(m_ui_page *page, void *data)
{
	printf("configure_transformer_settings_page\n");
	
	if (!page)
		return ERR_NULL_PTR;
	
	ui_page_add_back_button(page);
	
	m_transformer *trans = (m_transformer*)data;
	
	if (!data)
		return ERR_NULL_PTR;
	
	char title_buf[128];
	
	snprintf(title_buf, 128, "%s Settings", transformer_type_name(trans->type));
	page->panel->text = m_strndup(title_buf, 128);
	
	trans_settings_page_str *str = (trans_settings_page_str*)page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	configure_parameter_widget(&str->band_lp_cutoff, &trans->band_lp_cutoff, trans->profile, page);
	configure_parameter_widget(&str->band_hp_cutoff, &trans->band_hp_cutoff, trans->profile, page);
	configure_setting_widget(&str->band_mode, &trans->band_mode, trans->profile, page);
	
	page->configured = 1;
	
	printf("configure_transformer_settings_page done\n");
	return NO_ERROR;
}

void band_control_value_changed_cb(lv_event_t *e)
{
	m_ui_page *page = lv_event_get_user_data(e);
	
	if (!page)
		return;
	
	trans_settings_page_str *str = (trans_settings_page_str*)page->data_struct;
	
	if (!str)
		return;
	
	if (!str->band_mode.setting || !str->band_mode.setting->options || !str->band_mode.obj)
		return;
	
	m_setting *setting = str->band_mode.setting;
	
	uint16_t value;
	char dd_value[128];
	
	lv_dropdown_get_selected_str(str->band_mode.obj, dd_value, 128);
	
	printf("Selected band mode: %s\n", dd_value);
	
	int found = 0;
	for (int i = 0; i < setting->n_options; i++)
	{
		if (strncmp(dd_value, setting->options[i].name, 128) == 0)
		{
			found = 1;
			value = setting->options[i].value;
		}
	}
	
	if (!found)
	{
		// something
		return;
	}
	
	printf("The associated value is %d\n", value);
	setting->value = value;
	
	refresh_transformer_settings_page(page);
	
	m_message msg = create_m_message(M_MESSAGE_SET_SETTING_VALUE, "ssss", setting->id.profile_id, setting->id.transformer_id, setting->id.setting_id, value);
	
	queue_msg_to_teensy(msg);
}

int create_transformer_settings_page_ui(m_ui_page *page)
{
	printf("create_transformer_settings_page_ui\n");
	if (!page)
		return ERR_NULL_PTR;
	
	ui_page_create_base_ui(page);
	
	lv_obj_set_layout(page->container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(page->container, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(page->container, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_START);
	
	trans_settings_page_str *str = (trans_settings_page_str*)page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	printf("page->container = %p\n", page->container);
	
	//parameter_widget_create_ui(&str->cutoff_freq, page->container);
	
	setting_widget_create_ui_no_callback(&str->band_mode, page->container);
	
	lv_obj_add_event_cb(str->band_mode.obj, band_control_value_changed_cb, LV_EVENT_VALUE_CHANGED, page);
	
	str->band_control_cont = lv_obj_create(page->container);
	lv_obj_remove_style_all(str->band_control_cont);
	
	lv_obj_set_layout(str->band_control_cont, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(str->band_control_cont, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(str->band_control_cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_SPACE_EVENLY);
	//lv_obj_set_flex_grow(str->band_control_cont, 1);
	
	parameter_widget_create_ui(&str->band_hp_cutoff, global_cxt.ui_cxt.backstage);
	parameter_widget_create_ui(&str->band_lp_cutoff, global_cxt.ui_cxt.backstage);
	
	refresh_transformer_settings_page(page);
	
	page->ui_created = 1;
	
	printf("create_transformer_settings_page_ui done\n");
	return NO_ERROR;
}


int refresh_transformer_settings_page(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	trans_settings_page_str *str = (trans_settings_page_str*)page->data_struct;
	
	if (!str)
		return ERR_NULL_PTR;
	
	if (str->band_mode.setting && str->band_control_cont)
	{
		switch (str->band_mode.setting->value)
		{
			case TRANSFORMER_MODE_FULL_SPECTRUM:
				if (str->band_lp_cutoff.container)
				{
					lv_obj_set_parent(str->band_lp_cutoff.container, global_cxt.ui_cxt.backstage);
				}
				
				if (str->band_hp_cutoff.container)
				{
					lv_obj_set_parent(str->band_hp_cutoff.container, global_cxt.ui_cxt.backstage);
				}
				
				break;
				
			case TRANSFORMER_MODE_UPPER_SPECTRUM:
				if (str->band_lp_cutoff.container)
				{
					lv_obj_set_parent(str->band_lp_cutoff.container, global_cxt.ui_cxt.backstage);
				}
				
				if (str->band_hp_cutoff.container)
				{
					lv_obj_set_parent(str->band_hp_cutoff.container, str->band_control_cont);
				}
				
				break;
			
			case TRANSFORMER_MODE_LOWER_SPECTRUM:
				if (str->band_lp_cutoff.container)
				{
					lv_obj_set_parent(str->band_lp_cutoff.container, str->band_control_cont);
				}
				
				if (str->band_hp_cutoff.container)
				{
					lv_obj_set_parent(str->band_hp_cutoff.container, global_cxt.ui_cxt.backstage);
				}
				
				break;
				
			case TRANSFORMER_MODE_BAND:
				if (str->band_hp_cutoff.container)
				{
					lv_obj_set_parent(str->band_hp_cutoff.container, str->band_control_cont);
				}
				
				if (str->band_lp_cutoff.container)
				{
					lv_obj_set_parent(str->band_lp_cutoff.container, str->band_control_cont);
				}
				
				
				break;
			
			default:
				return ERR_BAD_ARGS;

		}
		
		lv_obj_set_size(str->band_control_cont, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
		lv_obj_update_layout(str->band_control_cont);
	}
	
	lv_obj_update_layout(page->container);
	lv_obj_update_layout(page->screen);
	
	return NO_ERROR;
}


int free_transformer_settings_page_ui(m_ui_page *page)
{
	return ERR_UNIMPLEMENTED;
	
	if (!page)
		return ERR_NULL_PTR;
		
	return NO_ERROR;
}


int transformer_settings_page_free_all(m_ui_page *page)
{
	return ERR_UNIMPLEMENTED;
	
	if (!page)
		return ERR_NULL_PTR;
		
	return NO_ERROR;
}

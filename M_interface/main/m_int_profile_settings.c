#include "m_int.h"

int init_profile_settings_page(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_profile_settings_str *str = malloc(sizeof(m_profile_settings_str));
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	init_ui_page(page);
	page->panel = new_panel();
	
	if (!page->panel)
		return ERR_NULL_PTR;
	
	page->data_struct = str;
	
	str->profile = NULL;
	page->container = NULL;
	
	page->configure 			= configure_profile_settings_page;
	page->create_ui 			= create_profile_settings_page_ui;
	page->free_ui				= free_profile_settings_page_ui;
	page->free_all				= profile_settings_page_free_all;
	page->enter_page			= NULL;//enter_profile_settings_page;
	page->enter_page_forward 	= enter_profile_settings_page_forward;
	page->enter_page_back 		= enter_profile_settings_page_back;
	page->refresh				= refresh_profile_settings_page;
	
	page->panel = new_panel();
	
	if (!page->panel)
		return ERR_ALLOC_FAIL;
	
	return NO_ERROR;
}

int configure_profile_settings_page(m_int_ui_page *page, void *data)
{
	if (!page)
		return ERR_NULL_PTR;
	
	ui_page_add_back_button(page);
	
	m_int_profile *profile = (m_int_profile*)data;
	
	if (!profile)
		return ERR_BAD_ARGS;
	
	if (!profile->name)
	{
		m_int_profile_set_default_name_from_id(profile);
	}
	
	char buf[128];
	snprintf(buf, 128, "%s Settings", profile->name);
	
	page->panel->text = m_int_strndup(buf, 128);
	
	m_profile_settings_str *str = (m_profile_settings_str*)page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	str->volume_widget.profile = profile;
	str->volume_widget.param = &profile->volume;
	str->volume_widget.id = profile->volume.id;
	
	str->profile = profile;
	
	if (profile)
	{
		page->parent = profile->view_page;
	}
	
	page->configured = 1;
	
	return NO_ERROR;
}

void profile_settings_save_button_cb(lv_event_t *e)
{
	m_int_ui_page *page = lv_event_get_user_data(e);
	
	if (!page)
		return;
	
	m_profile_settings_str *str = (m_profile_settings_str*)page->data_struct;
	
	if (!str)
		return;
	
	save_profile(str->profile);
	
	lv_obj_add_flag(str->save_button, LV_OBJ_FLAG_HIDDEN);
}

void default_profile_button_cb(lv_event_t *e)
{
	m_int_ui_page *page = lv_event_get_user_data(e);
	
	if (!page)
		return;
	
	m_profile_settings_str *str = (m_profile_settings_str*)page->data_struct;
	
	if (!str)
		return;
	
	set_profile_as_default(&global_cxt, str->profile);
	
	lv_obj_add_flag(str->default_button, LV_OBJ_FLAG_HIDDEN);
}

int create_profile_settings_page_ui(m_int_ui_page *page)
{
	printf("create_profile_settings_page_ui\n");
	if (!page)
		return ERR_NULL_PTR;
	
	if (page->ui_created)
	{
		printf("Profile settings page: UI already created...\n");
		return NO_ERROR;
	}
	
	m_profile_settings_str *str = (m_profile_settings_str*)page->data_struct;
	
	if (!str)
	{
		printf("Error! Profile settings page has no data struct!\n");
		return ERR_BAD_ARGS;
	}
		
	if (!str->profile)
	{
		printf("Error! Profile settings page has no profile!\n");
		return ERR_BAD_ARGS;
	}
	
	ui_page_create_base_ui(page);
	
	parameter_widget_create_ui(&str->volume_widget, page->container);
	
	str->default_button = lv_btn_create(page->screen);
    lv_obj_set_size(str->default_button, PROFILE_VIEW_BUTTON_WIDTH / 3, PROFILE_VIEW_BUTTON_HEIGHT);
	lv_obj_align(str->default_button, LV_ALIGN_BOTTOM_MID, -PROFILE_VIEW_TRANSFORMER_LIST_WIDTH / 3, -50);
    
	str->default_button_label = lv_label_create(str->default_button);
	lv_label_set_text(str->default_button_label, "Set Default");
	lv_obj_center(str->default_button_label);
	
	if (str->profile->default_profile)
	{
		lv_obj_add_flag(str->default_button, LV_OBJ_FLAG_HIDDEN);
	}
	
	lv_obj_add_event_cb(str->default_button, default_profile_button_cb, LV_EVENT_CLICKED, page);
	
    /*str->plus_button = lv_btn_create(page->screen);
    lv_obj_set_size(str->plus_button, PROFILE_VIEW_BUTTON_WIDTH / 3, PROFILE_VIEW_BUTTON_HEIGHT);
	lv_obj_align(str->plus_button, LV_ALIGN_BOTTOM_MID, 0, -50);
    
	str->plus_button_label = lv_label_create(str->plus_button);
	lv_label_set_text(str->plus_button_label, "+");
	lv_obj_center(str->plus_button_label);
	
	lv_obj_add_event_cb(str->plus_button, enter_transformer_selector_cb, LV_EVENT_CLICKED, page);
	
	str->save_button = lv_btn_create(page->screen);
    lv_obj_set_size(str->save_button, PROFILE_VIEW_BUTTON_WIDTH / 3, PROFILE_VIEW_BUTTON_HEIGHT);
	lv_obj_align(str->save_button, LV_ALIGN_BOTTOM_MID, PROFILE_VIEW_TRANSFORMER_LIST_WIDTH / 3, -50);
    
	str->save_button_label = lv_label_create(str->save_button);
	lv_label_set_text(str->save_button_label, "Save");
	lv_obj_center(str->save_button_label);
	
	lv_obj_add_event_cb(str->save_button, profile_settings_save_button_cb, LV_EVENT_CLICKED, page);*/
	
	page->ui_created = 1;
	
	return NO_ERROR;
}


int free_profile_settings_page_ui(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	return NO_ERROR;
}

int profile_settings_page_free_all(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	return NO_ERROR;
}

int enter_profile_settings_page(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	return NO_ERROR;
}

int enter_profile_settings_page_forward(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	return NO_ERROR;
}

int enter_profile_settings_page_back(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	return NO_ERROR;
}

int refresh_profile_settings_page(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	return NO_ERROR;
}

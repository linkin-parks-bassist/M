#include "m_int.h"

static const char *TAG = "m_profile_view.c";

m_ui_page *create_profile_view_for(m_profile *profile)
{
	if (!profile)
		return NULL;
	
	m_ui_page *page = m_alloc(sizeof(m_ui_page));
	
	if (!page)
		return NULL;
	
	init_ui_page(page);
	
	int ret_val = init_profile_view(page);
	
	if (ret_val != NO_ERROR)
	{
		free_profile_view(page);
		return NULL;
	}
	
	ret_val = configure_profile_view(page, profile);
	
	if (ret_val != NO_ERROR)
	{
		free_profile_view(page);
		return NULL;
	}
	
	profile->view_page = page;
	
	return page;
}

int profile_view_transformer_click_cb(m_active_button *button)
{
	if (!button)
		return ERR_NULL_PTR;
	
	if (!button->data)
		return ERR_BAD_ARGS;
	
	enter_ui_page(((m_transformer*)button->data)->view_page);
	
	return NO_ERROR;
}

int profile_view_transformer_moved_cb(m_active_button *button)
{
	if (!button)
		return ERR_NULL_PTR;
	
	m_transformer *trans = button->data;
	
	if (!trans)
		return ERR_BAD_ARGS;
	
	queue_msg_to_teensy(create_m_message(M_MESSAGE_MOVE_TRANSFORMER, "sss", trans->profile->id, trans->id, button->index));
	
	return NO_ERROR;
}

int init_profile_view(m_ui_page *page)
{
	//printf("init_profile_view...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	init_ui_page(page);
	
	m_profile_view_str *str = m_alloc(sizeof(m_profile_view_str));
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	str->settings_page = malloc(sizeof(m_ui_page));
	
	if (!str->settings_page)
	{
		m_free(str);
		return ERR_ALLOC_FAIL;
	}
	
	int ret_val = init_profile_settings_page(str->settings_page);
	
	if (ret_val != NO_ERROR)
	{
		return ret_val;
	}
	
	page->data_struct = (void*)str;
	
	str->profile 			= NULL;

	page->configure  			= configure_profile_view;
	page->create_ui  			= create_profile_view_ui;
	page->enter_page 			= enter_profile_view;
	page->free_all				= free_profile_view;
	
	str->save 		= NULL;
	str->plus		= NULL;
	str->play 		= NULL;
	
	str->menu_button 		= NULL;
	str->menu_button_label 	= NULL;
	
	page->panel = new_panel();
	
	str->array = m_active_button_array_new();
	
	m_active_button_array_set_length(str->array, 32);
	
	str->array->flags |= M_ACTIVE_BUTTON_ARRAY_FLAG_DELETEABLE;
	str->array->flags |= M_ACTIVE_BUTTON_ARRAY_FLAG_MOVEABLE;
	
	str->array->clicked_cb = profile_view_transformer_click_cb;
	str->array->moved_cb   = profile_view_transformer_moved_cb;
	
	str->rep.representee = NULL;
	str->rep.representer = page;
	str->rep.update = profile_view_rep_update;
	
	return NO_ERROR;
}

static void save_button_cb(lv_event_t *e)
{
	m_ui_page *page = lv_event_get_user_data(e);
	
	if (!page)
		return;
	
	m_profile_view_str *str = (m_profile_view_str*)page->data_struct;
	
	if (!str)
		return;
	
	//printf("Saving profile...\n");
	m_profile_save(str->profile);
}

int profile_view_save_name(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_profile_view_str *str = (m_profile_view_str*)page->data_struct;
	
	const char *new_name = lv_textarea_get_text(page->panel->title);
	
	if (str->profile->name)
		m_free(str->profile->name);
	
	str->profile->name = m_strndup(new_name, PROFILE_NAM_ENG_MAX_LEN);
	
	lv_obj_clear_state(page->panel->title, LV_STATE_FOCUSED);
	lv_obj_add_state(page->container, LV_STATE_FOCUSED);
	
	hide_keyboard();
	
	str->profile->unsaved_changes = 1;
	lv_obj_clear_flag(str->save->obj, LV_OBJ_FLAG_HIDDEN);
	
	return NO_ERROR;
}


void profile_view_save_name_cb(lv_event_t *e)
{
	m_ui_page *page = (m_ui_page*)lv_event_get_user_data(e);
	profile_view_save_name(page);
}

void profile_view_revert_name(lv_event_t *e)
{
	m_ui_page *page = (m_ui_page*)lv_event_get_user_data(e);
	m_profile_view_str *str = (m_profile_view_str*)page->data_struct;
	
	lv_textarea_set_text(page->panel->title, str->profile->name);
	
	lv_obj_clear_state(page->panel->title, LV_STATE_FOCUSED);
	lv_obj_add_state(page->container, LV_STATE_FOCUSED);
	
	hide_keyboard();
}

void profile_view_enter_settings_page_cb(lv_event_t *e)
{
	m_ui_page *page = (m_ui_page*)lv_event_get_user_data(e);
	
	if (!page)
		return;
	
	m_profile_view_str *str = (m_profile_view_str*)page->data_struct;
	
	if (!str)
		return;
	
	enter_ui_page(str->settings_page);
}

void profile_view_enter_main_menu_cb(lv_event_t *e)
{
	enter_ui_page(&global_cxt.pages.main_menu);
}

void profile_view_activate_profile_cb(lv_event_t *e)
{
	printf("profile_view_activate_profile_cb\n");
	m_ui_page *page = (m_ui_page*)lv_event_get_user_data(e);
	
	if (!page)
		return;
	
	m_profile_view_str *str = (m_profile_view_str*)page->data_struct;
	
	if (str->profile)
	{
		set_active_profile(str->profile);
	}
	else
	{
		ESP_LOGE("profile_view_activate_profile_cb", "str->profile is NULL");
	}
	
	printf("done\n");
}

int configure_profile_view(m_ui_page *page, void *data)
{
	//printf("configure_profile_view...\n");
	if (!page || !data)
		return ERR_NULL_PTR;
	
	if (page->configured)
		return NO_ERROR;
	
	m_profile *profile = (m_profile*)data;
	
	m_profile_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	page->data_struct = str;
	
	str->profile = profile;
	
	profile->view_page = page;
	
	int ret_val;
	int alloc_fail = 0;
	
	m_transformer *trans;
	
	int i = 0;
	m_transformer_pll *current = profile->pipeline.transformers;
	
	while (current)
	{
		trans = current->data;
		
		m_active_button_array_append_new(str->array, trans, transformer_type_name(trans->type));
		
		/*
		tw = m_alloc(sizeof(m_transformer_widget));
		
		if (!tw)
			return ERR_ALLOC_FAIL;
		
		ret_val = init_transformer_widget(tw, page, trans, i);
		
		if (ret_val != NO_ERROR)
			return ret_val;
		
		nl = m_transformer_widget_pll_append(str->tws, tw);
		
		if (!nl)
		{
			free_m_transformer_widget_pll(str->tws);
			str->tws = NULL;
			return ERR_ALLOC_FAIL;
		}
		str->tws = nl;
		
		str->n_transformer_widgets++;
		
		if (trans && !trans->view_page)
		{
			ret_val = transformer_init_ui_page(trans, page);
			
			if (ret_val != NO_ERROR)
			{
				if (ret_val == ERR_ALLOC_FAIL)
				{
					alloc_fail = 1;
				}
				else
				{
					#ifndef M_SIMULATED
					ESP_LOGE(TAG, "Erroe code %d encountered initialising transformer view page for transformer %d.%d\n", profile->id, i);
					#endif
				}
			}
			else
			{
				trans->view_page->create_ui(trans->view_page);
			}
		}
		
		current = current->next;
		i++;*/
	}
	
	configure_profile_settings_page(str->settings_page, profile);
	
	str->play = ui_page_add_bottom_button(page, LV_SYMBOL_PLAY, profile_view_activate_profile_cb);
	str->plus = ui_page_add_bottom_button(page, LV_SYMBOL_PLUS, enter_transformer_selector_cb);
	str->save = ui_page_add_bottom_button(page, LV_SYMBOL_SAVE, save_button_cb);
	
	ui_page_set_title_rw(page, profile_view_save_name_cb, profile_view_revert_name);
	
	ui_page_add_left_panel_button(page, LV_SYMBOL_LIST, enter_parent_page_cb);
	ui_page_add_right_panel_button(page, LV_SYMBOL_SETTINGS, profile_view_enter_settings_page_cb);
	
	str->rep.representee = profile;
	
	m_profile_add_representation(profile, &str->rep);
	
	page->configured = 1;
	return alloc_fail ? ERR_ALLOC_FAIL : NO_ERROR;
}

int create_profile_view_ui(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	if (page->ui_created)
		return NO_ERROR;
	
	page->parent = &global_cxt.pages.main_menu;
	
	m_profile_view_str *str = (m_profile_view_str*)page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	m_profile *profile = str->profile;
	
	if (!profile)
		return ERR_BAD_ARGS;
	
	if (page->panel->text)
	{
		// Prevent a minor memory leak
		// After I figure out ownership/nullification
	}
	
	if (!profile->name)
	{
		printf("create_profile_view_ui. profile->name = NULL\n");
		m_profile_set_default_name_from_id(profile);
	}
	
	printf("create_profile_view_ui. profile->name = %s\n", profile->name);
	
	page->panel->text = profile->name;
	
	ui_page_create_base_ui(page);
	m_active_button_array_create_ui(str->array, page->container);
	
	printf("profile->active = %d\n", profile->active);
	
	if (profile->active)
	{
		m_button_disable(str->play);
	}
	
	if (!str->profile->unsaved_changes)
	{
		m_button_disable(str->save);
	}
	
	page->ui_created = 1;
	
	return NO_ERROR;
}

int enter_profile_view(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_profile_view_str *str = (m_profile_view_str*)page->data_struct;
	
	lv_scr_load(page->screen);
	
	if (str)
		global_cxt.working_profile = str->profile;
	
	global_cxt.pages.transformer_selector.parent = page;
	
	profile_view_refresh_play_button(page);
	profile_view_refresh_save_button(page);
	
	return NO_ERROR;
}

int enter_profile_view_from(m_ui_page *page, m_ui_page *prev)
{
	if (!page)
		return ERR_NULL_PTR;
	
	if (prev)
	{
		switch (prev->type)
		{
			case M_UI_PAGE_MAIN_MENU:
				page->parent = NULL;
				break;
			
			default:
				break;
		}
	}
	
	enter_profile_view(page);
	
	return NO_ERROR;
}

int enter_profile_view_forward(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_profile_view_str *str = page->data_struct;
	
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	if (str)
		global_cxt.working_profile = str->profile;
	
	global_cxt.pages.transformer_selector.parent = page;
	global_cxt.pages.main_menu.parent = page;
	
	profile_view_refresh_play_button(page);
	profile_view_refresh_save_button(page);
	
	//printf("All good\n");
	return NO_ERROR;
}

int enter_profile_view_back(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_profile_view_str *str = page->data_struct;
	
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	if (str)
		global_cxt.working_profile = str->profile;
	
	global_cxt.pages.transformer_selector.parent = page;
	global_cxt.pages.main_menu.parent = page;
	
	profile_view_refresh_play_button(page);
	profile_view_refresh_save_button(page);
	
	return NO_ERROR;
}

int profile_view_reorder_tw_list(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_profile_view_str *str = page->data_struct;
	
	
	
	return NO_ERROR;
}

int profile_view_print_tw_list(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_profile_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	

	
	return NO_ERROR;
}

int profile_view_append_transformer(m_ui_page *page, m_transformer *trans)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_profile_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	m_active_button *button = m_active_button_array_append_new(str->array, trans, transformer_type_name(trans->type));
	
	if (page->ui_created)
	{
		m_active_button_create_ui(button, page->container);
	}
	
	
	
	
	return NO_ERROR;
}

int profile_view_recalculate_indices(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	
	
	return NO_ERROR;
}


int free_profile_view(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_profile_view_str *str = page->data_struct;
	
	return ERR_UNIMPLEMENTED;
	
	return NO_ERROR;
}

int profile_view_refresh_play_button(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	
	
	return NO_ERROR;
}


int profile_view_refresh_save_button(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	
	return NO_ERROR;
}

int profile_view_change_name(m_ui_page *page, char *name)
{
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->panel)
		return ERR_BAD_ARGS;
	

	
	return NO_ERROR;
}

int profile_view_set_left_button_mode(m_ui_page *page, int mode)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_profile_view_str *str = (m_profile_view_str*)page->data_struct;
	
	
	
	return NO_ERROR;
}

void profile_view_rep_update(void *representer, void *representee)
{
	printf("profile_view_rep_update. representer = %p, representee = %p\n", representer, representee);
	
	m_ui_page *page = (m_ui_page*)representer;
	m_profile *profile = (m_profile*)representee;
	
	if (!page || !profile)
		return;
	
	ui_page_set_title(page, profile->name);
	
	m_profile_view_str *str = (m_profile_view_str*)page->data_struct;
	printf("profile->active = %d,  str = %p, \n", profile->active, str);
	if (!str)
		return;
	
	if (profile->active)
	{
		printf("profile is active! disabling play button,,,\n");
		m_button_disable(str->play);
	}
	else
	{
		m_button_enable(str->play);
	}
	
	if (profile->unsaved_changes)
	{
		m_button_disable(str->save);
	}
	else
	{
		m_button_enable(str->save);
	}
	
	printf("profile_view_rep_update done\n");
}

#include "m_int.h"

static const char *TAG = "m_int_profile_view.c";

m_int_ui_page *create_profile_view_for(m_int_profile *profile)
{
	if (!profile)
		return NULL;
	
	m_int_ui_page *page = m_int_malloc(sizeof(m_int_ui_page));
	
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

int init_profile_view(m_int_ui_page *page)
{
	//printf("init_profile_view...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_profile_view_str *str = m_int_malloc(sizeof(m_int_profile_view_str));
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	str->settings_page = malloc(sizeof(m_int_ui_page));
	
	if (!str->settings_page)
	{
		m_int_free(str);
		return ERR_ALLOC_FAIL;
	}
	
	int ret_val = init_profile_settings_page(str->settings_page);
	
	if (ret_val != NO_ERROR)
	{
		return ret_val;
	}
	
	page->data_struct = (void*)str;
	
	str->n_transformer_widgets = 0;
	str->left_button_mode = LEFT_BUTTON_MENU;
	
	str->profile 			= NULL;
	page->container 		= NULL;
	str->profile 			= NULL;
	str->tws 				= NULL;

	
	page->configure  			= configure_profile_view;
	page->create_ui  			= create_profile_view_ui;
	page->enter_page 			= enter_profile_view;
	page->enter_page_forward 	= enter_profile_view_forward;
	page->enter_page_back 		= enter_profile_view_back;
	page->free_all				= free_profile_view;
	
	str->save 		= NULL;
	str->plus		= NULL;
	str->play 		= NULL;
	
	str->accessed_from = NULL;
	
	str->menu_button 		= NULL;
	str->menu_button_label 	= NULL;
	
	page->panel = new_panel();
	
	//printf("success\n");
	return NO_ERROR;
}

static void save_button_cb(lv_event_t *e)
{
	m_int_ui_page *page = lv_event_get_user_data(e);
	
	if (!page)
		return;
	
	m_int_profile_view_str *str = (m_int_profile_view_str*)page->data_struct;
	
	if (!str)
		return;
	
	//printf("Saving profile...\n");
	save_profile(str->profile);
	
	lv_obj_add_flag(str->save->obj, LV_OBJ_FLAG_HIDDEN);
}

void profile_view_set_name(lv_event_t *e)
{
	m_int_ui_page *page = (m_int_ui_page*)lv_event_get_user_data(e);
	m_int_profile_view_str *str = (m_int_profile_view_str*)page->data_struct;
	
	const char *new_name = lv_textarea_get_text(page->panel->title);
	
	if (str->profile->name)
		m_int_free(str->profile->name);
	
	str->profile->name = m_int_strndup(new_name, PROFILE_NAM_ENG_MAX_LEN);
	
	lv_obj_clear_state(page->panel->title, LV_STATE_FOCUSED);
	lv_obj_add_state(page->container, LV_STATE_FOCUSED);
	
	hide_keyboard();
	
	str->profile->unsaved_changes = 1;
	lv_obj_clear_flag(str->save->obj, LV_OBJ_FLAG_HIDDEN);
}

void profile_view_revert_name(lv_event_t *e)
{
	m_int_ui_page *page = (m_int_ui_page*)lv_event_get_user_data(e);
	m_int_profile_view_str *str = (m_int_profile_view_str*)page->data_struct;
	
	lv_textarea_set_text(page->panel->title, str->profile->name);
	
	lv_obj_clear_state(page->panel->title, LV_STATE_FOCUSED);
	lv_obj_add_state(page->container, LV_STATE_FOCUSED);
	
	hide_keyboard();
}

void profile_view_enter_settings_page_cb(lv_event_t *e)
{
	m_int_ui_page *page = (m_int_ui_page*)lv_event_get_user_data(e);
	
	if (!page)
		return;
	
	m_int_profile_view_str *str = (m_int_profile_view_str*)page->data_struct;
	
	if (!str)
		return;
	
	enter_ui_page(str->settings_page);
}

void profile_view_enter_main_menu_cb(lv_event_t *e)
{
	enter_ui_page(global_cxt.ui_cxt.main_menu);
}

void profile_view_activate_profile_cb(lv_event_t *e)
{
	printf("profile_view_activate_profile_cb\n");
	m_int_ui_page *page = (m_int_ui_page*)lv_event_get_user_data(e);
	
	if (!page)
		return;
	
	m_int_profile_view_str *str = (m_int_profile_view_str*)page->data_struct;
	
	if (str->profile)
	{
		set_active_profile(str->profile);
		profile_view_refresh_play_button(page);
	}
	else
	{
		ESP_LOGE("profile_view_activate_profile_cb", "str->profile is NULL");
	}
	
	printf("done\n");
}

int configure_profile_view(m_int_ui_page *page, void *data)
{
	//printf("configure_profile_view...\n");
	if (!page || !data)
		return ERR_NULL_PTR;
	
	if (page->configured)
		return NO_ERROR;
	
	m_int_profile *profile = (m_int_profile*)data;
	
	if (!profile->name)
	{
		m_int_profile_set_default_name_from_id(profile);
	}
	
	page->panel->text = profile->name;
	
	m_int_profile_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	page->data_struct = str;
	
	str->profile = profile;
	
	profile->view_page = page;
	
	m_int_transformer_widget *tw;
	
	m_int_transformer_widget_ptr_linked_list *nl;
	
	int ret_val;
	int alloc_fail = 0;
	
	m_int_transformer *trans;
	
	int i = 0;
	m_int_transformer_ptr_linked_list *current = profile->pipeline.transformers;
	
	while (current)
	{
		trans = current->data;
		
		tw = m_int_malloc(sizeof(m_int_transformer_widget));
		
		if (!tw)
			return ERR_ALLOC_FAIL;
		
		ret_val = init_transformer_widget(tw, page, trans, i);
		
		if (ret_val != NO_ERROR)
			return ret_val;
		
		nl = m_int_transformer_widget_ptr_linked_list_append(str->tws, tw);
		
		if (!nl)
		{
			free_m_int_transformer_widget_ptr_linked_list(str->tws);
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
		i++;
	}
	
	configure_profile_settings_page(str->settings_page, profile);
	
	
	str->play = ui_page_add_bottom_button(page, LV_SYMBOL_PLAY, profile_view_activate_profile_cb);
	str->plus = ui_page_add_bottom_button(page, LV_SYMBOL_PLUS, enter_transformer_selector_cb);
	str->save = ui_page_add_bottom_button(page, LV_SYMBOL_SAVE, save_button_cb);
	
	ui_page_set_title_rw(page, profile_view_set_name, profile_view_revert_name);
	
	ui_page_add_left_panel_button(page, LV_SYMBOL_LIST, enter_parent_page_cb);
	ui_page_add_right_panel_button(page, LV_SYMBOL_SETTINGS, profile_view_enter_settings_page_cb);
	
	page->configured = 1;
	return alloc_fail ? ERR_ALLOC_FAIL : NO_ERROR;
}

int create_profile_view_ui(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	if (page->ui_created)
		return NO_ERROR;
	
	page->parent = global_cxt.ui_cxt.main_menu;
	
	m_int_profile_view_str *str = (m_int_profile_view_str*)page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
		
	if (!str->profile)
		return ERR_BAD_ARGS;
	
	ui_page_create_base_ui(page);
    
    m_int_transformer_widget_ptr_linked_list *current = str->tws;
    
    int i = 0;
    while (current)
    {
		create_transformer_widget_ui(current->data, page->container);
		current = current->next;
		i++;
	}
	
	printf("%d transformer widgets\n", i);
	
	if (!str->profile->unsaved_changes)
		lv_obj_add_flag(str->save->obj, LV_OBJ_FLAG_HIDDEN);
	
	page->ui_created = 1;
	
	return NO_ERROR;
}

int enter_profile_view(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_profile_view_str *str = (m_int_profile_view_str*)page->data_struct;
	
	//printf("Entering profile view. Profile: %p. Profile name: %s\n", str->profile, str->profile->name);
	
	transformer_ll *current = str->profile->pipeline.transformers;
	
	int i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	
	//printf("Profile has %d transformers. The view page has %d transformer widgets\n", i, str->n_transformer_widgets);
	
	lv_scr_load(page->screen);
	
	if (str)
		global_cxt.working_profile = str->profile;
	
	global_cxt.ui_cxt.transformer_selector.parent = page;
	
	profile_view_refresh_play_button(page);
	profile_view_refresh_save_button(page);
	
	return NO_ERROR;
}

int enter_profile_view_forward(m_int_ui_page *page)
{
	//printf("Entering profile view...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_profile_view_str *str = page->data_struct;
	
	//printf("Load page...\n");
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	if (str)
		global_cxt.working_profile = str->profile;
	
	global_cxt.ui_cxt.transformer_selector.parent = page;
	global_cxt.ui_cxt.main_menu->parent = page;
	
	profile_view_refresh_play_button(page);
	profile_view_refresh_save_button(page);
	
	//printf("All good\n");
	return NO_ERROR;
}

int enter_profile_view_back(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_profile_view_str *str = page->data_struct;
	
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	if (str)
		global_cxt.working_profile = str->profile;
	
	global_cxt.ui_cxt.transformer_selector.parent = page;
	global_cxt.ui_cxt.main_menu->parent = page;
	
	profile_view_refresh_play_button(page);
	profile_view_refresh_save_button(page);
	
	return NO_ERROR;
}

int profile_view_reorder_tw_list(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_profile_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	m_int_transformer_widget_ptr_linked_list *current;
	m_int_transformer_widget_ptr_linked_list **current_ptr;
	m_int_transformer_widget_ptr_linked_list *list_array[str->n_transformer_widgets];
	
	current = str->tws;
	
	int i = 0;
	while (current && i < str->n_transformer_widgets)
	{
		list_array[i] = current;
		current = current->next;
		i++;
	}
	
	int j;
	current_ptr = &str->tws;
	for (int index = 0; index < str->n_transformer_widgets; index++)
	{
		j = -1;
		for (i = 0; i < str->n_transformer_widgets; i++)
		{
			if (list_array[i]->data->index == index)
				j = i;
		}
		
		if (j == -1)
			return ERR_BAD_ARGS;
		
		*current_ptr = list_array[j];
		current_ptr = &((*current_ptr)->next);
	}
	
	*current_ptr = NULL;
	
	return NO_ERROR;
}

int profile_view_print_tw_list(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_profile_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	m_int_transformer_widget_ptr_linked_list *current = str->tws;
	
	//printf("Printing transformer widget linked list. n_tramsformer_widgets = %d\n", str->n_transformer_widgets);
	
	int i = 0;
	while (current)
	{
		//printf("Transformer widget %d. pointer: %p.\n", i, current->data);
		//printf("Transformer ptr %p, index %d, y_pos %d\n",
		//	current->data->trans, current->data->index, (int)current->data->pos_y);
		current = current->next;
		i++;
	}
	
	return NO_ERROR;
}

int profile_view_append_transformer(m_int_ui_page *page, m_int_transformer *trans)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_profile_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	//printf("profile_view_append_transformer... n_transformer_widgets = %d\n", str->n_transformer_widgets);
	
	m_int_transformer_widget *tw = m_int_malloc(sizeof(m_int_transformer_widget));
	
	if (!tw)
		return ERR_ALLOC_FAIL;
	
	init_transformer_widget(tw, page, trans, str->n_transformer_widgets++);
	create_transformer_widget_ui(tw, page->container);
	
	str->tws = m_int_transformer_widget_ptr_linked_list_append(str->tws, tw);
	
	str->n_transformer_widgets = 0;
	tw_ll *current = str->tws;
	while (current)
	{
		current = current->next;
		str->n_transformer_widgets++;
	}
	
	profile_view_print_tw_list(page);
	
	return NO_ERROR;
}

int profile_view_index_y_position(int index)
{
	return PROFILE_VIEW_BUTTON_BASE_Y + index * PROFILE_VIEW_BUTTON_DISTANCE;
}

int profile_view_remove_tw_from_list(m_int_ui_page *page, m_int_transformer_widget *tw)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_profile_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	m_int_transformer_widget_ptr_linked_list *current = str->tws;
	m_int_transformer_widget_ptr_linked_list *prev = NULL;
	
	while (current)
	{
		if (current->data == tw)
		{
			if (prev)
				prev->next = current->next;
			else
				str->tws = current->next;
			
			m_int_free(current);
			break;
		}
		
		prev = current;
		current = current->next;
	}
	
	str->n_transformer_widgets = 0;
	current = str->tws;
	while (current)
	{
		current = current->next;
		str->n_transformer_widgets++;
	}
	
	profile_view_recalculate_indices(page);
	
	return NO_ERROR;
}

int profile_view_recalculate_indices(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_profile_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	m_int_transformer_widget_ptr_linked_list *current = str->tws;
	m_int_transformer_widget_ptr_linked_list *other;
	
	int j = 0;
	while (current)
	{
		int i = 0;
		other = str->tws;
		
		while (other)
		{
			if (current != other && other->data->pos_y < current->data->pos_y)
				i++;
			
			other = other->next;
		}
		
		transformer_widget_set_index(current->data, i);
		
		current = current->next;
		j++;
	}
	
	return NO_ERROR;
}


int free_profile_view(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_profile_view_str *str = page->data_struct;
	
	if (str)
	{
		if (str->tws)
			destructor_free_m_int_transformer_widget_ptr_linked_list(str->tws, free_transformer_widget);
	}
	
	if (page->screen)
		lv_obj_del(page->screen);
	
	m_int_free(page);
	
	return NO_ERROR;
}

int profile_view_refresh_play_button(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_profile_view_str *str = page->data_struct;
	
	if (str)
	{
		if (str->profile)
		{
			if (str->save->obj)
			{
				if (str->profile->active)
				{
					lv_obj_add_flag(str->play->obj, LV_OBJ_FLAG_HIDDEN);
				}
				else
				{
					lv_obj_clear_flag(str->play->obj, LV_OBJ_FLAG_HIDDEN);
				}
			}
			else
			{
				return ERR_BAD_ARGS;
			}
		}
		else
		{
			return ERR_BAD_ARGS;
		}
	}
	else
	{
		return ERR_BAD_ARGS;
	}
	
	return NO_ERROR;
}


int profile_view_refresh_save_button(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_profile_view_str *str = page->data_struct;
	
	if (str)
	{
		if (str->profile)
		{
			if (str->save->obj)
			{
				if (str->profile->unsaved_changes)
				{
					lv_obj_clear_flag(str->save->obj, LV_OBJ_FLAG_HIDDEN);
				}
				else
				{
					lv_obj_add_flag(str->save->obj, LV_OBJ_FLAG_HIDDEN);
				}
			}
			else
			{
				return ERR_BAD_ARGS;
			}
		}
		else
		{
			return ERR_BAD_ARGS;
		}
	}
	else
	{
		return ERR_BAD_ARGS;
	}
	
	return NO_ERROR;
}

int profile_view_change_name(m_int_ui_page *page, char *name)
{
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->panel)
		return ERR_BAD_ARGS;
	
	printf("Setting profile view name to %s\n", name);
	page->panel->text = name;
	
	if (page->ui_created && page->panel->title)
	{
		lv_textarea_set_text(page->panel->title, name);
	}
	
	return NO_ERROR;
}

int profile_view_set_left_button_mode(m_int_ui_page *page, int mode)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_profile_view_str *str = (m_int_profile_view_str*)page->data_struct;
	
	if (str)
	{
		str->left_button_mode = mode;
	}
	
	if (page->panel && page->panel->lb)
	{
		lv_obj_remove_event_cb(page->panel->lb->obj, page->panel->lb->clicked_cb);
		if (mode == LEFT_BUTTON_MENU)
		{
			page->panel->lb->label_text = LV_SYMBOL_LEFT;
			page->panel->lb->clicked_cb = enter_main_menu_cb;
		}
		else
		{
			page->panel->lb->label_text = LV_SYMBOL_LEFT;
			page->panel->lb->clicked_cb = enter_parent_page_cb;
		}
		
		if (page->panel->lb->obj && page->panel->lb->label)
		{
			lv_label_set_text(page->panel->lb->label, page->panel->lb->label_text);
			lv_obj_add_event_cb(page->panel->lb->obj, page->panel->lb->clicked_cb, LV_EVENT_CLICKED, page);
		}
	}
	
	return NO_ERROR;
}

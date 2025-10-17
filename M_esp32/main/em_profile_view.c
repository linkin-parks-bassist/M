#include "em.h"

static const char *TAG = "em_profile_view.c";

em_ui_page *make_profile_view_for(em_profile *profile)
{
	if (!profile)
		return NULL;
	
	em_ui_page *page = malloc(sizeof(em_ui_page));
	
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

int init_profile_view(em_ui_page *page)
{
	//printf("init_profile_view...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *str = malloc(sizeof(em_profile_view_str));
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	page->data_struct = (void*)str;
	
	str->n_transformer_widgets = 0;
	
	str->profile 			= NULL;
	str->transformer_list 	= NULL;
	str->profile 			= NULL;
	str->tws 				= NULL;
	str->drag_state			= 0;

	
	page->configure  			= configure_profile_view;
	page->create_ui  			= create_profile_view_ui;
	page->enter_page 			= enter_profile_view;
	page->enter_page_forward 	= enter_profile_view_forward;
	page->enter_page_back 		= enter_profile_view_back;
	page->free_all				= free_profile_view;
	
	str->save_button = NULL;
	str->save_button_label = NULL;
	
	str->play_button = NULL;
	str->play_button_label = NULL;
	
	str->menu_button = NULL;
	str->menu_button_label = NULL;
	
	//printf("success\n");
	return NO_ERROR;
}

int configure_profile_view(em_ui_page *page, void *data)
{
	//printf("configure_profile_view...\n");
	if (!page || !data)
		return ERR_NULL_PTR;
	
	if (page->configured)
		return NO_ERROR;
	
	em_profile *profile = (em_profile*)data;
	
	em_profile_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	page->data_struct = str;
	
	str->profile = profile;
	
	em_transformer_widget *tw;
	
	em_transformer_widget_ptr_linked_list *nl;
	
	int ret_val;
	int alloc_fail = 0;
	
	em_transformer *trans;
	
	int i = 0;
	em_transformer_ptr_linked_list *current = profile->pipeline.transformers;
	
	while (current)
	{
		trans = current->data;
		
		tw = malloc(sizeof(em_transformer_widget));
		
		if (!tw)
			return ERR_ALLOC_FAIL;
		
		ret_val = init_transformer_widget(tw, page, trans, i);
		
		if (ret_val != NO_ERROR)
			return ret_val;
		
		nl = em_transformer_widget_ptr_linked_list_append(str->tws, tw);
		
		if (!nl)
		{
			free_em_transformer_widget_ptr_linked_list(str->tws);
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
					ESP_LOGE(TAG, "Erroe code %d encountered initialising transformer view page for transformer %d.%d\n", profile->id, i);
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
	
	page->configured = 1;
	
	//printf("success\n");
	return alloc_fail ? ERR_ALLOC_FAIL : NO_ERROR;
}

void save_button_cb(lv_event_t *e)
{
	em_ui_page *page = lv_event_get_user_data(e);
	
	if (!page)
		return;
	
	em_profile_view_str *str = (em_profile_view_str*)page->data_struct;
	
	if (!str)
		return;
	
	//printf("Saving profile...\n");
	save_profile(str->profile);
	
	lv_obj_add_flag(str->save_button, LV_OBJ_FLAG_HIDDEN);
}

void profile_view_set_name(lv_event_t *e)
{
	em_ui_page *page = (em_ui_page*)lv_event_get_user_data(e);
	em_profile_view_str *str = (em_profile_view_str*)page->data_struct;
	
	const char *new_name = lv_textarea_get_text(page->top_panel->title);
	
	if (str->profile->name)
		free(str->profile->name);
	
	str->profile->name = strndup(new_name, PROFILE_NAME_MAX_LEN);
	
	lv_obj_clear_state(page->top_panel->title, LV_STATE_FOCUSED);
	lv_obj_add_state(str->transformer_list, LV_STATE_FOCUSED);
	
	hide_keyboard();
	
	str->profile->unsaved_changes = 1;
	lv_obj_clear_flag(str->save_button, LV_OBJ_FLAG_HIDDEN);
}

void profile_view_revert_name(lv_event_t *e)
{
	em_ui_page *page = (em_ui_page*)lv_event_get_user_data(e);
	em_profile_view_str *str = (em_profile_view_str*)page->data_struct;
	
	lv_textarea_set_text(page->top_panel->title, str->profile->name);
	
	lv_obj_clear_state(page->top_panel->title, LV_STATE_FOCUSED);
	lv_obj_add_state(str->transformer_list, LV_STATE_FOCUSED);
	
	hide_keyboard();
}

void profile_view_edit_name(lv_event_t *e)
{
	em_ui_page *page = (em_ui_page*)lv_event_get_user_data(e);
	
	if (!page)
		return;
	
	spawn_keyboard(page->screen, page->top_panel->title, profile_view_set_name, page, profile_view_revert_name, page);
	lv_obj_add_state(page->top_panel->title, LV_STATE_FOCUSED);
}

void profile_view_enter_main_menu_cb(lv_event_t *e)
{
	enter_ui_page(global_cxt.ui_cxt.main_menu);
}

void profile_view_activate_profile_cb(lv_event_t *e)
{
	em_ui_page *page = (em_ui_page*)lv_event_get_user_data(e);
	
	if (!page)
		return;
	
	em_profile_view_str *str = (em_profile_view_str*)page->data_struct;
	
	if (str->profile)
	{
		set_active_profile(str->profile);
		profile_view_refresh_play_button(page);
	}
	else
	{
		ESP_LOGE("profile_view_activate_profile_cb", "str->profile is NULL");
	}
}

int create_profile_view_ui(em_ui_page *page)
{
	//printf("create_profile_view_ui...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	if (page->ui_created)
		return NO_ERROR;
	
	em_profile_view_str *str = (em_profile_view_str*)page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
		
	if (!str->profile)
		return ERR_BAD_ARGS;
	
	page->screen = lv_obj_create(NULL);
	
	//printf("Creating top panel with label %s\n", str->profile->name ? str->profile->name : "(null)");
	create_top_panel_rw_title_and_left_button(page, str->profile->name ? str->profile->name : "Profile", profile_view_enter_main_menu_cb);
	
	create_standard_container(&str->transformer_list, page->screen);
    
    em_transformer_widget_ptr_linked_list *current = str->tws;
    
    int i = 0;
    while (current)
    {
		create_transformer_widget_ui(current->data, str->transformer_list);
		current = current->next;
		i++;
	}
	
    str->play_button = lv_btn_create(page->screen);
    lv_obj_set_size(str->play_button, PROFILE_VIEW_BUTTON_WIDTH / 3, PROFILE_VIEW_BUTTON_HEIGHT);
	lv_obj_align(str->play_button, LV_ALIGN_BOTTOM_MID, -PROFILE_VIEW_TRANSFORMER_LIST_WIDTH / 3, -50);
    
	str->play_button_label = lv_label_create(str->play_button);
	lv_label_set_text(str->play_button_label, LV_SYMBOL_PLAY);
	lv_obj_center(str->play_button_label);
	
	lv_obj_add_event_cb(str->play_button, profile_view_activate_profile_cb, LV_EVENT_CLICKED, page);
	
    str->plus_button = lv_btn_create(page->screen);
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
	
	lv_obj_add_event_cb(str->save_button, save_button_cb, LV_EVENT_CLICKED, page);
	lv_obj_add_event_cb(page->top_panel->title, profile_view_edit_name, LV_EVENT_CLICKED, page);
	lv_obj_add_event_cb(page->top_panel->title, profile_view_revert_name, LV_EVENT_DEFOCUSED, page);
	
	if (!str->profile->unsaved_changes)
		lv_obj_add_flag(str->save_button, LV_OBJ_FLAG_HIDDEN);
	
	page->ui_created = 1;
	
	//printf("success\n");
	return NO_ERROR;
}

int enter_profile_view(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *str = (em_profile_view_str*)page->data_struct;
	
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
	global_cxt.ui_cxt.main_menu->parent = page;
	
	profile_view_refresh_play_button(page);
	profile_view_refresh_save_button(page);
	
	return NO_ERROR;
}

int enter_profile_view_forward(em_ui_page *page)
{
	//printf("Entering profile view...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *str = page->data_struct;
	
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

int enter_profile_view_back(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *str = page->data_struct;
	
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	if (str)
		global_cxt.working_profile = str->profile;
	
	global_cxt.ui_cxt.transformer_selector.parent = page;
	global_cxt.ui_cxt.main_menu->parent = page;
	
	profile_view_refresh_play_button(page);
	profile_view_refresh_save_button(page);
	
	return NO_ERROR;
}

int profile_view_reorder_tw_list(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	em_transformer_widget_ptr_linked_list *current;
	em_transformer_widget_ptr_linked_list **current_ptr;
	em_transformer_widget_ptr_linked_list *list_array[str->n_transformer_widgets];
	
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

int profile_view_print_tw_list(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	em_transformer_widget_ptr_linked_list *current = str->tws;
	
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

int profile_view_append_transformer(em_ui_page *page, em_transformer *trans)
{
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	//printf("profile_view_append_transformer... n_transformer_widgets = %d\n", str->n_transformer_widgets);
	
	em_transformer_widget *tw = malloc(sizeof(em_transformer_widget));
	
	if (!tw)
		return ERR_ALLOC_FAIL;
	
	init_transformer_widget(tw, page, trans, str->n_transformer_widgets++);
	create_transformer_widget_ui(tw, str->transformer_list);
	
	str->tws = em_transformer_widget_ptr_linked_list_append(str->tws, tw);
	
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

int profile_view_remove_tw_from_list(em_ui_page *page, em_transformer_widget *tw)
{
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	em_transformer_widget_ptr_linked_list *current = str->tws;
	em_transformer_widget_ptr_linked_list *prev = NULL;
	
	while (current)
	{
		if (current->data == tw)
		{
			if (prev)
				prev->next = current->next;
			else
				str->tws = current->next;
			
			free(current);
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

int profile_view_recalculate_indices(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	em_transformer_widget_ptr_linked_list *current = str->tws;
	em_transformer_widget_ptr_linked_list *other;
	
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


int free_profile_view(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *str = page->data_struct;
	
	if (str)
			destructor_free_em_transformer_widget_ptr_linked_list(str->tws, free_transformer_widget);
	
	if (page->screen)
		lv_obj_del(page->screen);
	
	free(page);
	
	return NO_ERROR;
}

int profile_view_refresh_play_button(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *str = page->data_struct;
	
	if (str)
	{
		if (str->profile)
		{
			if (str->save_button)
			{
				if (str->profile->active)
				{
					lv_obj_add_flag(str->play_button, LV_OBJ_FLAG_HIDDEN);
				}
				else
				{
					lv_obj_clear_flag(str->play_button, LV_OBJ_FLAG_HIDDEN);
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


int profile_view_refresh_save_button(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *str = page->data_struct;
	
	if (str)
	{
		if (str->profile)
		{
			if (str->save_button)
			{
				if (str->profile->unsaved_changes)
				{
					lv_obj_clear_flag(str->save_button, LV_OBJ_FLAG_HIDDEN);
				}
				else
				{
					lv_obj_add_flag(str->save_button, LV_OBJ_FLAG_HIDDEN);
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

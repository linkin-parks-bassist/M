
#include "m_int.h"

static const char *TAG = "m_int_menu.c";

IMPLEMENT_LINKED_PTR_LIST(m_int_menu_item);

int init_menu_item(m_int_menu_item *item)
{
	if (!item)
		return ERR_NULL_PTR;
	
	item->type = 0;
	
	item->text = NULL;
	item->desc = NULL;
	
	item->action_cb = NULL;
	item->click_cb  = NULL;
	item->cb_arg    = NULL;
	
	item->linked_page = NULL;
	item->linked_page_indirect = NULL;
	
	item->lp_configure_arg = NULL;
	
	item->obj   = NULL;
	item->label = NULL;
	item->extra = NULL;
	
	item->data   = NULL;
	item->parent = NULL;
	
	item->long_pressed = 0;
	
	return NO_ERROR;
}

void menu_page_link_clicked_cb(lv_event_t *e)
{
	m_int_menu_item *item = (m_int_menu_item*)lv_event_get_user_data(e);
	
	//printf("menu_page_link_clicked_cb\n");
	
	if (!item)
		return;
	
	if (!item->linked_page && !item->linked_page_indirect)
		return;
	
	if (item->linked_page_indirect)
		enter_ui_page_indirect(item->linked_page_indirect);
	else if (item->linked_page)
		enter_ui_page(item->linked_page);
}

int configure_menu_item(m_int_menu_item *item)
{
	if (!item)
		return ERR_NULL_PTR;
	
	switch (item->type)
	{			
		case MENU_ITEM_PAGE_LINK:
			if (item->linked_page && !item->linked_page->configured)
				configure_ui_page(item->linked_page, item->lp_configure_arg);
			break;
	
		case MENU_ITEM_PROFILE_LISTING:
		case MENU_ITEM_SEQUENCE_LISTING:
		case MENU_ITEM_PAGE_LINK_INDIRECT:
			if (item->linked_page_indirect && *item->linked_page_indirect && !(*item->linked_page_indirect)->configured)
				configure_ui_page(*item->linked_page_indirect, item->lp_configure_arg);
			break;
		
		case MENU_ITEM_CALLBACK_BUTTON:
			if (item->linked_page_indirect && *item->linked_page_indirect && !(*item->linked_page_indirect)->configured)
				configure_ui_page(*item->linked_page_indirect, item->lp_configure_arg);
			break;
		
		case MENU_ITEM_PARAMETER_WIDGET:
		case MENU_ITEM_PAD:
			break;
			
		case MENU_ITEM_DANGER_BUTTON:
			break;
		
		default:
			return ERR_BAD_ARGS;
	}
	
	return NO_ERROR;
}


int delete_menu_item_ui(m_int_menu_item *item)
{
	if (!item)
		return ERR_NULL_PTR;
	
	if (item->timer)
	{
		lv_timer_del(item->timer);
	}
	
	lv_anim_del(item, NULL);
	
	lv_obj_del_async(item->obj);
	
	return NO_ERROR;
}

int free_menu_item(m_int_menu_item *item)
{
	if (item->text)
		m_free(item->text);
	if (item->desc)
		m_free(item->desc);
	
	m_free(item);
	
	return NO_ERROR;
}

int refresh_menu_item(m_int_menu_item *item)
{
	if (!item)
		return ERR_NULL_PTR;
	
	switch (item->type)
	{
		case MENU_ITEM_PROFILE_LISTING:
			//profile_listing_menu_item_refresh_active(item);
			break;
		
		default:
			break;
	}
	
	return NO_ERROR;
}

void parameter_widget_change_cb_settings_wrapper(lv_event_t *e)
{
	m_int_menu_item *item = lv_event_get_user_data(e);
	
	if (!item)
		return;
	
	xSemaphoreTake(settings_mutex, portMAX_DELAY);
	parameter_widget_change_cb_inner(item->data);
	global_cxt.settings.changed = 1;
	xSemaphoreGive(settings_mutex);
}

void danger_button_value_changed_cb(lv_event_t *e)
{
	m_int_menu_item *item = lv_event_get_user_data(e);
	
	if (!item)
		return;
	
	if (!item->extra)
		return;
	
	if (!item->extra[0])
		return;
	
	const char *button_text = lv_msgbox_get_active_btn_text(item->extra[0]);
	
	if (strncmp(DANGER_BUTTON_CONFIRM_TEXT, button_text, strlen(DANGER_BUTTON_CONFIRM_TEXT) + 1) == 0)
	{
		if (item->action_cb)
			item->action_cb(item->cb_arg);
	}
	
	lv_msgbox_close(item->extra[0]);
}

void danger_button_activate_popup_cb(lv_event_t *e)
{
	m_int_menu_item *item = lv_event_get_user_data(e);
	
	if (!item)
		return;
	
	if (!item->parent)
		return;
	
	if (!item->extra)
	{
		item->extra = m_alloc(sizeof(lv_obj_t*));
		if (!item->extra)
			return;
	}
	
	static const char *btns[] = {DANGER_BUTTON_CONFIRM_TEXT, DANGER_BUTTON_CANCEL_TEXT, NULL};
	
	item->extra[0] = lv_msgbox_create(item->parent->screen, item->text, "Are you sure?", btns, 1);
	lv_obj_add_event_cb(item->extra[0], danger_button_value_changed_cb, LV_EVENT_VALUE_CHANGED, item);
	lv_obj_center(item->extra[0]);
}

m_int_menu_item *create_profile_listing_menu_item(char *text, m_profile *profile, m_ui_page *parent)
{
	m_int_menu_item *item = m_alloc(sizeof(m_int_menu_item));
	
	if (!item || !profile)
		return NULL;
	
	init_menu_item(item);
	
	item->type = MENU_ITEM_PROFILE_LISTING;
	if (text)
		item->text = m_strndup(text, MENU_ITEM_TEXT_MAX_LEN);
	else
		item->text = "Profile";
	
	item->linked_page_indirect = &profile->view_page;
	item->data = profile;
	
	item->parent = parent;
	
	return item;
}

int profile_listing_menu_item_refresh_active(m_int_menu_item *item)
{
	printf("profile_listing_menu_item_refresh_active\n");
	if (!item)
		return ERR_NULL_PTR;
	
	if (!item->extra)
		return NO_ERROR;
		
	if (!item->extra[1])
		return NO_ERROR;
	
	if (item->data && ((m_profile*)item->data)->active)
	{
		printf("profile is active. going about it\n");
		lv_label_set_text(item->extra[1], LV_SYMBOL_PLAY);
		lv_obj_clear_flag(item->extra[0], LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(item->extra[0], LV_OBJ_FLAG_CLICKABLE);
	}
	else
	{
		printf("profile is not active. hiding play\n");
		lv_label_set_text(item->extra[1], LV_SYMBOL_TRASH);
		lv_obj_add_flag(item->extra[0], LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(item->extra[0], LV_OBJ_FLAG_CLICKABLE);
	}
	
	printf("profile_listing_menu_item_refresh_active done\n");
	return NO_ERROR;
}

int profile_listing_menu_item_change_name(m_int_menu_item *item, char *name)
{
	if (!item)
		return ERR_NULL_PTR;
	
	if (!item->extra)
		return NO_ERROR;
	
	item->text = strndup(name, 32);
	
	lv_label_set_text(item->label, item->text);
	
	return NO_ERROR;
}

void profile_listing_delete_button_cb(lv_event_t *e)
{
	m_int_menu_item *item = lv_event_get_user_data(e);
	
	if (!item)
		return;
	
	m_profile *profile = (m_profile*)item->data;
	
	if (!profile)
		return;
	
	if (!profile->active)
	{
		cxt_remove_profile(&global_cxt, profile);
		
		menu_page_remove_item(item->parent, item);
	}
}

void disappear_profile_listing_delete_button(lv_timer_t *timer)
{
	m_int_menu_item *item = timer->user_data;
	
	lv_obj_add_flag(item->extra[0], LV_OBJ_FLAG_HIDDEN);
	
	item->timer = NULL;
}

void menu_item_profile_listing_released_cb(lv_event_t *e)
{
	m_int_menu_item *item = (m_int_menu_item*)lv_event_get_user_data(e);
	
	if (!item)
		return;
	
	m_profile *profile = item->data;
	
	if (!item->long_pressed)
	{
		if (profile && profile->view_page)
		{
			profile->view_page->parent = &global_cxt.pages.main_menu;
			
			enter_ui_page(profile->view_page);
		}
	}
	else
	{
		if (profile && !profile->active)
		{
			item->timer = lv_timer_create(disappear_profile_listing_delete_button, STANDARD_DEL_BTN_REMAIN_MS, item);
			lv_timer_set_repeat_count(item->timer, 1);
		}
	}
	
	item->long_pressed = 0;
}

void menu_item_profile_listing_long_pressed_cb(lv_event_t *e)
{
	m_int_menu_item *item = (m_int_menu_item*)lv_event_get_user_data(e);
	
	if (!item)
		return;
	
	item->long_pressed = 1;
	
	m_profile *profile = item->data;
	
	if (profile && !profile->active)
	{
		lv_obj_clear_flag(item->extra[0], LV_OBJ_FLAG_HIDDEN);
	}
	else
	{
		lv_obj_clear_flag(item->extra[0], LV_OBJ_FLAG_HIDDEN);
	}
}

int create_menu_item_ui(m_int_menu_item *item, lv_obj_t *parent)
{
	if (!item)
		return ERR_NULL_PTR;
	
	switch (item->type)
	{
		case MENU_ITEM_PAGE_LINK:
		case MENU_ITEM_PAGE_LINK_INDIRECT:
			create_standard_button_click(&item->obj, &item->label, parent, item->text, menu_page_link_clicked_cb, item);
			break;
		
		case MENU_ITEM_CALLBACK_BUTTON:
			create_standard_button_click(&item->obj, &item->label, parent, item->text, item->click_cb, item->cb_arg);
			break;
		
		case MENU_ITEM_DANGER_BUTTON:
			create_standard_button_click(&item->obj, &item->label, parent, item->text, danger_button_activate_popup_cb, item);
			break;
		
		case MENU_ITEM_SEQUENCE_LISTING:
			create_standard_button_long_press_release(&item->obj, &item->label, parent, item->text,
				menu_item_sequence_listing_long_pressed_cb, item,
				menu_item_sequence_listing_released_cb, item);
			
			item->extra = m_alloc(sizeof(lv_obj_t*) * 2);
			
			if (!item->extra)
				return ERR_ALLOC_FAIL;
				
			item->extra[0] = lv_btn_create(item->obj);
			
			lv_obj_align(item->extra[0], LV_ALIGN_RIGHT_MID, 10, 0);
			lv_obj_set_size(item->extra[0], 0.75 * STANDARD_BUTTON_HEIGHT, 0.75 * STANDARD_BUTTON_HEIGHT);
			lv_obj_add_event_cb(item->extra[0], sequence_listing_delete_button_cb, LV_EVENT_CLICKED, item);
			lv_obj_add_flag(item->extra[0], LV_OBJ_FLAG_HIDDEN);
			
			item->extra[1] = lv_label_create(item->extra[0]);
			lv_label_set_text(item->extra[1], LV_SYMBOL_TRASH);
			
			lv_obj_center(item->extra[1]);
			break;
		
		case MENU_ITEM_PROFILE_LISTING:
			create_standard_button_long_press_release(&item->obj, &item->label, parent, item->text,
				menu_item_profile_listing_long_pressed_cb, item,
				menu_item_profile_listing_released_cb, item);
			
			item->extra = m_alloc(sizeof(lv_obj_t*) * 2);
			
			if (!item->extra)
				return ERR_ALLOC_FAIL;
				
			item->extra[0] = lv_btn_create(item->obj);
			
			lv_obj_align(item->extra[0], LV_ALIGN_RIGHT_MID, 10, 0);
			lv_obj_set_size(item->extra[0], 0.75 * STANDARD_BUTTON_HEIGHT, 0.75 * STANDARD_BUTTON_HEIGHT);
			lv_obj_add_event_cb(item->extra[0], profile_listing_delete_button_cb, LV_EVENT_CLICKED, item);
			lv_obj_add_flag(item->extra[0], LV_OBJ_FLAG_HIDDEN);
			
			item->extra[1] = lv_label_create(item->extra[0]);
			lv_label_set_text(item->extra[1], LV_SYMBOL_TRASH);
			
			lv_obj_center(item->extra[1]);
			break;
		
		case MENU_ITEM_PARAMETER_WIDGET:
			parameter_widget_create_ui_no_callback(item->data, parent);
			lv_obj_add_event_cb(((m_parameter_widget*)item->data)->obj, parameter_widget_change_cb_settings_wrapper, LV_EVENT_VALUE_CHANGED, item);
			break;
		
		case MENU_ITEM_PAD:
			item->obj = lv_obj_create(parent);
			lv_obj_remove_style_all(item->obj);
			lv_obj_set_size(item->obj, 1, (int)item->data);
		
		default:
			return ERR_BAD_ARGS;
	}
	
	return NO_ERROR;
}

m_int_menu_item *create_pad_menu_item(int pad_height)
{
	m_int_menu_item *item = m_alloc(sizeof(m_int_menu_item));
	
	if (!item)
		return NULL;
	
	init_menu_item(item);
	
	item->type = MENU_ITEM_PAD;
	item->data = (void*)pad_height;
	
	return item;
}

m_int_menu_item *create_page_link_menu_item(char *text, m_ui_page *linked_page, m_ui_page *parent)
{
	m_int_menu_item *item = m_alloc(sizeof(m_int_menu_item));
	
	if (!item)
		return NULL;
	
	printf("create_page_link_menu_item. parent = %p\n", parent);
	
	init_menu_item(item);
	
	item->type = MENU_ITEM_PAGE_LINK;
	item->text = m_strndup(text, MENU_ITEM_TEXT_MAX_LEN);
	
	item->linked_page = linked_page;
	item->parent = parent;
	
	return item;
}

m_int_menu_item *create_page_link_indirect_menu_item(char *text, m_ui_page **linked_page, m_ui_page *parent)
{
	m_int_menu_item *item = m_alloc(sizeof(m_int_menu_item));
	
	if (!item)
		return NULL;
	
	init_menu_item(item);
	
	item->type = MENU_ITEM_PAGE_LINK_INDIRECT;
	item->text = m_strndup(text, MENU_ITEM_TEXT_MAX_LEN);
	item->linked_page_indirect = linked_page;
	item->parent = parent;
	
	return item;
}

m_int_menu_item *create_parameter_widget_menu_item(m_parameter *param, m_ui_page *parent)
{
	if (!param)
		return NULL;
	
	m_int_menu_item *item = m_alloc(sizeof(m_int_menu_item));
	
	if (!item)
		return NULL;
	
	init_menu_item(item);
		
	item->type = MENU_ITEM_PARAMETER_WIDGET;
	
	m_parameter_widget *pw = m_alloc(sizeof(m_parameter_widget));
	
	nullify_parameter_widget(pw);
	
	if (!pw)
	{
		free_menu_item(item);
		return NULL;
	}
		
	item->data = pw;
	
	configure_parameter_widget(item->data, param, NULL, parent);
	
	return item;
}

m_int_menu_item *create_danger_button_menu_item(void (*action_cb)(void* arg), void *arg, const char *text, m_ui_page *parent)
{
	if (!action_cb)
		return NULL;
	
	m_int_menu_item *item = m_alloc(sizeof(m_int_menu_item));
	
	if (!item)
		return NULL;
	
	init_menu_item(item);
		
	item->type = MENU_ITEM_DANGER_BUTTON;
	
	item->text = m_strndup(text, 128);
	item->action_cb = action_cb;
	item->cb_arg = arg;
	item->parent = parent;
	
	return item;
}

int init_menu_page_str(m_int_menu_page_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	str->type = 0;
	
	str->items 	   = NULL;
	str->next_page = NULL;
	str->data 	   = NULL;
	
	return NO_ERROR;
}

int init_menu_page(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	init_ui_page(page);
	
	m_int_menu_page_str *str = m_alloc(sizeof(m_int_menu_page_str));
	
	page->data_struct = str;
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	page->create_ui	 = create_menu_page_ui;
	page->configure  = configure_menu_page;
	page->free_ui	 = free_menu_page_ui;
	page->enter_page = enter_menu_page;
	
	return init_menu_page_str(str);
}

int configure_menu_page(m_ui_page *page, void *data)
{
	printf("configure_menu_page\n");
	if (!page)
		return ERR_NULL_PTR;
	
	if (page->configured)
		return NO_ERROR;
	
	int ret_val = NO_ERROR;
	m_int_menu_page_str *str = (m_int_menu_page_str*)page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	page->panel = new_panel();
	page->panel->text = str->name;
	page->container_type = CONTAINER_TYPE_STD_BTN_LIST;
	
	ui_page_add_back_button(page);
	
	page->parent = data;
	m_int_menu_item_pll *current_item = str->items;
	
	while (current_item)
	{
		configure_menu_item(current_item->data);
		current_item = current_item->next;
	}
	
	if (str->next_page)
		ret_val = configure_menu_page(str->next_page, page);
	
	page->configured = (ret_val == NO_ERROR);
	
	printf("configure_menu_page done\n");
	return ret_val;
}

int create_menu_page_ui(m_ui_page *page)
{
	printf("create_menu_page_ui\n");
	if (!page)
		return ERR_NULL_PTR;
	
	if (page->ui_created)
	{
		return NO_ERROR;
	}
	
	ui_page_create_base_ui(page);
	
	m_int_menu_page_str *str = (m_int_menu_page_str*)page->data_struct;
	
	if (!str)
	{
		return ERR_BAD_ARGS;
	}
	
	m_int_menu_item_pll *current = str->items;
	
	int i = 0;
	while (current)
	{
		printf("Create menu item %d ui\n", i);
		create_menu_item_ui(current->data, page->container);
		current = current->next;
		i++;
	}
	
	if (str->next_page)
		create_menu_page_ui(str->next_page);
	
	page->ui_created = 1;
	
	printf("create_menu_page_ui done\n");
	return NO_ERROR;
}


int enter_menu_page(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	refresh_menu_page(page);
	
	lv_scr_load(page->screen);
	
	m_int_menu_page_str *str = (m_int_menu_page_str*)page->data_struct;
	
	if (str)
	{
		m_int_menu_item_pll *current = str->items;
		
		printf("Menu page menu items:\n");
		
		while (current)
		{
			if (current->data)
			{
				printf("Type %d\n", current->data->type);
				if (current->data->type == MENU_ITEM_PARAMETER_WIDGET)
				{
					printf("Requesting value for menu page parameter widget...\n");
					//param_widget_request_value(current->data->data);
				}
			}
			
			current = current->next;
		}
	}
	
	return NO_ERROR;
}

int refresh_menu_page(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_menu_page_str *str = (m_int_menu_page_str*)page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	m_int_menu_item_pll *current = str->items;
	
	while (current)
	{
		refresh_menu_item(current->data);
		current = current->next;
	}
	
	return NO_ERROR;
}

int free_menu_page_ui(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	
	
	return ERR_UNIMPLEMENTED;
}

int menu_page_add_item(m_int_menu_page_str *str, m_int_menu_item *item)
{
	if (!str || !item)
		return ERR_NULL_PTR;
	
	//printf("menu_page_add_item(%p, %p). str->items = %p\n", str, item, str->items);
	
	m_int_menu_item_pll *nl = m_int_menu_item_pll_append(str->items, item);
	
	if (!nl)
		return ERR_ALLOC_FAIL;
	
	str->items = nl;
	
	return NO_ERROR;
}

void enter_main_menu_cb(lv_event_t *e)
{
	enter_ui_page(&global_cxt.pages.main_menu);
}

int init_main_menu(m_ui_page *page)
{
	init_ui_page(page);
	
	page->create_ui = create_main_menu_ui;
	page->configure = configure_main_menu;
	page->enter_page = enter_main_menu;
	
	page->data_struct = NULL;
	
	return NO_ERROR;
}

int configure_main_menu(m_ui_page *page, void *data)
{
	if (!page)
		return ERR_NULL_PTR;
	
	page->parent = data;
	
	m_main_menu_str *str = m_alloc(sizeof(m_main_menu_str));
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	page->data_struct = str;
	
	str->gains_container = NULL;
	
	page->panel = new_panel();
	page->panel->text = "Main Menu";
	page->container_type = CONTAINER_TYPE_STD_BTN_LIST;
	
	ui_page_add_back_button(page);
	
	nullify_parameter_widget(&str->input_gain);
	nullify_parameter_widget(&str->output_gain);
	
	configure_parameter_widget(&str->input_gain, &global_cxt.settings.input_gain, NULL, page);
	configure_parameter_widget(&str->output_gain, &global_cxt.settings.output_gain, NULL, page);
	
	init_button(&str->profiles_button);
	init_button(&str->sequences_button);
	init_danger_button(&str->erase_sd_card_button, erase_sd_card_void_cb, NULL, page);
	
	m_button_set_label(&str->profiles_button, "Profiles");
	m_button_disable_alignment(&str->profiles_button);
	m_button_set_label(&str->sequences_button, "Sequences");
	m_button_disable_alignment(&str->sequences_button);
	m_button_set_label(&str->erase_sd_card_button.button, "Erase SD card");
	m_button_disable_alignment(&str->erase_sd_card_button.button);
	
	button_set_clicked_cb(&str->profiles_button, enter_ui_page_cb, &global_cxt.pages.main_sequence_view);
	button_set_clicked_cb(&str->sequences_button, enter_ui_page_cb, &global_cxt.pages.sequence_list);
	
	/*
	m_int_menu_item *item = create_pad_menu_item(20);
	menu_page_add_item(str, item);
	
	item = create_parameter_widget_menu_item(&global_cxt.settings.input_gain, page);
	menu_page_add_item(str, item);
	
	item = create_parameter_widget_menu_item(&global_cxt.settings.output_gain, page);
	menu_page_add_item(str, item);
	
	m_ui_page *profile_list = &global_cxt.pages.main_sequence_view;
	
	profile_list->parent = page;
	
	item = create_page_link_menu_item("Profiles", profile_list, page);
	
	menu_page_add_item(str, item);
	
	m_ui_page *sequence_list = &global_cxt.pages.sequence_list;
	
	sequence_list->parent = page;
	
	item = create_page_link_menu_item("Sequences", sequence_list, page);
	
	menu_page_add_item(str, item);
	
	item = create_danger_button_menu_item(erase_sd_card_void_cb, NULL, "Erase SD card", page);
	
	menu_page_add_item(str, item);*/
	
	page->configured = 1;
	
	return NO_ERROR;
}

int create_main_menu_ui(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	if (page->ui_created)
	{
		return NO_ERROR;
	}
	
	m_main_menu_str *str = (m_main_menu_str*)page->data_struct;
	
	if (!str)
	{
		return ERR_BAD_ARGS;
	}
	
	ui_page_create_base_ui(page);
	
	str->top_pad = lv_obj_create(page->container);
	
	lv_obj_remove_style_all(str->top_pad);
	lv_obj_set_size(str->top_pad, LV_PCT(100), 20);
	
	/*
	lv_obj_set_layout(page->container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(page->container, LV_FLEX_FLOW_ROW_WRAP);
	lv_obj_set_flex_align(page->container,
		LV_FLEX_ALIGN_SPACE_EVENLY,
		LV_FLEX_ALIGN_CENTER,
		LV_FLEX_ALIGN_START);
	*/
	str->gains_container = lv_obj_create(page->container);
	
	lv_obj_remove_style_all(str->gains_container);
	lv_obj_set_layout(str->gains_container, LV_LAYOUT_FLEX);
	lv_obj_set_flex_flow (str->gains_container, LV_FLEX_FLOW_ROW_WRAP);
	lv_obj_set_flex_align(str->gains_container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_SPACE_EVENLY);
	
	parameter_widget_create_ui( &str->input_gain, str->gains_container);
	parameter_widget_create_ui(&str->output_gain, str->gains_container);
	
	lv_obj_set_size(str->gains_container, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
	
	str->top_pad = lv_obj_create(page->container);
	
	lv_obj_remove_style_all(str->top_pad);
	lv_obj_set_size(str->top_pad, LV_PCT(100), 20);
	
	create_button_ui(&str->profiles_button, page->container);
	create_button_ui(&str->sequences_button, page->container);
	m_danger_button_create_ui(&str->erase_sd_card_button, page->container);
	
	page->ui_created = 1;
	
	return NO_ERROR;
}

int enter_main_menu(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_scr_load(page->screen);
	
	return NO_ERROR;
}

int enter_main_menu_forward(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	return NO_ERROR;
}

int enter_main_menu_back(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	return NO_ERROR;
}

int menu_page_remove_item(m_ui_page *page, m_int_menu_item *item)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_menu_page_str *str = (m_int_menu_page_str*)page->data_struct;

	if (!str)
		return ERR_BAD_ARGS;
	
	m_int_menu_item_pll *current_item = str->items;
	m_int_menu_item_pll *prev_item = NULL;
	
	while (current_item)
	{
		if (current_item->data == item)
		{
			delete_menu_item_ui(current_item->data);
			free_menu_item(current_item->data);
			
			if (prev_item)
				prev_item->next = current_item->next;
			else
				str->items = current_item->next;
			
			m_free(current_item);
			return NO_ERROR;
		}
		
		prev_item = current_item;
		current_item = current_item->next;
	}
	
	return ERR_BAD_ARGS;
}

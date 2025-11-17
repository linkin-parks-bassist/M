#include "m_int.h"

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
	
	if (profile)
		m_profile_add_menu_listing(profile, item);
	
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

int init_profile_list(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	//printf("init_profile_list\n");
	init_menu_page(page);
	
	page->configure = configure_profile_list;
	
	//printf("init_profile_list done\n");
	return NO_ERROR;
}

void profile_list_add_cb(lv_event_t *e)
{
	m_ui_page *page = lv_event_get_user_data(e);
	
	if (!page)
		return;
	
	m_int_menu_page_str *str = page->data_struct;
	
	if (!str)
		return;
	
	m_profile *new_profile = create_new_profile_with_teensy();
	
	if (new_profile->view_page)
		enter_ui_page(new_profile->view_page);
	
	m_int_menu_item *new_listing = create_profile_listing_menu_item(new_profile->name, new_profile, page);
	
	if (!new_listing)
	{
		//ugh
		return;
	}
	
	menu_page_add_item(str, new_listing);
	create_menu_item_ui(new_listing, page->container);
}

int configure_profile_list(m_ui_page *page, void *data)
{
	printf("Configure profile list\n");
	if (!page)
		return ERR_NULL_PTR;
	
	if (page->configured)
		return NO_ERROR;
	
	page->parent = (m_ui_page*)data;
	
	m_int_menu_page_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	str->name = "Profiles";
	
	page->panel = new_panel();
	page->panel->text = str->name;
	page->container_type = CONTAINER_TYPE_STD_BTN_LIST;
	
	ui_page_add_back_button(page);
	
	ui_page_add_bottom_button(page, LV_SYMBOL_PLUS, profile_list_add_cb);
	
	profile_ll *current = global_cxt.profiles;
	printf("current = global_cxt.profiles = %p\n", current);
	m_int_menu_item_pll *nl;
	
	int i = 0;
	while (current)
	{
		printf("current = %p, current->data = %p\n",
			current, current->data);
		if (current->data)
		{
			printf("Add list item for profile %d, %p = %s\n", i, current->data, current->data->name);
			printf("Profile view page pointer: %p, dbl ptr: %p\n", current->data->view_page, &current->data->view_page);
			menu_page_add_item(str, create_profile_listing_menu_item(current->data->name, current->data, page));
		}
		
		current = current->next;
		i++;
	}
	
	page->configured = 1;
	
	return NO_ERROR;
}

int free_profile_list_ui(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	
	
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
			profile->view_page->parent = global_cxt.ui_cxt.main_menu;
			
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

int profile_list_add_profile(m_ui_page *page, m_profile *profile)
{
	printf("profile_list_add_profile\n");
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_menu_page_str *str = (m_int_menu_page_str*)page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	m_int_menu_item *item = create_profile_listing_menu_item(profile->name, profile, page);
	
	if (!item)
		return ERR_ALLOC_FAIL;
	
	m_profile_add_menu_listing(profile, item);
	
	menu_page_add_item(str, item);
	
	if (page->ui_created)
	{
		create_menu_item_ui(item, page->container);
	}
	
	printf("profile_list_add_profile done\n");
	return NO_ERROR;
}

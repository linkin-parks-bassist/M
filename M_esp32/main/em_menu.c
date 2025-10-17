
#include "em.h"

static const char *TAG = "em_menu.c";

IMPLEMENT_LINKED_PTR_LIST(em_menu_item);

int init_menu_item(em_menu_item *item)
{
	if (!item)
		return ERR_NULL_PTR;
	
	item->type = 0;
	
	item->text = NULL;
	item->desc = NULL;
	
	item->click_cb = NULL;
	item->cb_arg = NULL;
	
	item->linked_page = NULL;
	item->linked_page_indirect = NULL;
	
	item->lp_configure_arg = NULL;
	
	item->obj = NULL;
	item->label = NULL;
	item->extra = NULL;
	
	item->data = NULL;
	item->parent = NULL;
	
	item->long_pressed = 0;
	
	return NO_ERROR;
}

void menu_page_link_clicked_cb(lv_event_t *e)
{
	em_menu_item *item = (em_menu_item*)lv_event_get_user_data(e);
	
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

int configure_menu_item(em_menu_item *item)
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
		case MENU_ITEM_PAGE_LINK_INDIRECT:
			if (item->linked_page_indirect && *item->linked_page_indirect && !(*item->linked_page_indirect)->configured)
				configure_ui_page(*item->linked_page_indirect, item->lp_configure_arg);
			break;
		
		case MENU_ITEM_CALLBACK_BUTTON:
			if (item->linked_page_indirect && *item->linked_page_indirect && !(*item->linked_page_indirect)->configured)
				configure_ui_page(*item->linked_page_indirect, item->lp_configure_arg);
			break;
		
		default:
			return ERR_BAD_ARGS;
	}
	
	return NO_ERROR;
}


int delete_menu_item_ui(em_menu_item *item)
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

int free_menu_item(em_menu_item *item)
{
	if (item->text)
		free(item->text);
	if (item->desc)
		free(item->desc);
	
	free(item);
	
	return NO_ERROR;
}

void profile_listing_delete_button_cb(lv_event_t *e)
{
	em_menu_item *item = lv_event_get_user_data(e);
	
	if (!item)
		return;
	
	em_profile *profile = (em_profile*)item->data;
	
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
	em_menu_item *item = timer->user_data;
	
	lv_obj_add_flag(item->extra[0], LV_OBJ_FLAG_HIDDEN);
	
	item->timer = NULL;
}

void menu_item_profile_listing_released_cb(lv_event_t *e)
{
	em_menu_item *item = (em_menu_item*)lv_event_get_user_data(e);
	
	if (!item)
		return;
	
	if (!item->long_pressed)
	{
		enter_ui_page_indirect(item->linked_page_indirect);
	}
	else
	{
		item->timer = lv_timer_create(disappear_profile_listing_delete_button, STANDARD_DEL_BTN_REMAIN_MS, item);
		lv_timer_set_repeat_count(item->timer, 1);
	}
	
	item->long_pressed = 0;
}

void menu_item_profile_listing_long_pressed_cb(lv_event_t *e)
{
	em_menu_item *item = (em_menu_item*)lv_event_get_user_data(e);
	
	if (!item)
		return;
	
	item->long_pressed = 1;
	
	em_profile *profile = item->data;
	
	if (profile)
	{
		if (!profile->active)
			lv_obj_clear_flag(item->extra[0], LV_OBJ_FLAG_HIDDEN);
	}
	else
	{
		lv_obj_clear_flag(item->extra[0], LV_OBJ_FLAG_HIDDEN);
	}
}

int create_menu_item_ui(em_menu_item *item, lv_obj_t *parent)
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
		
		case MENU_ITEM_PROFILE_LISTING:
			create_standard_button_long_press_release(&item->obj, &item->label, parent, item->text,
				menu_item_profile_listing_long_pressed_cb, item,
				menu_item_profile_listing_released_cb, item);
			item->extra = malloc(sizeof(lv_obj_t*) * 2);
			
			if (!item->extra)
				return ERR_ALLOC_FAIL;
				
			item->extra[0] = lv_btn_create(item->obj);
			
			lv_obj_align(item->extra[0], LV_ALIGN_RIGHT_MID, 10, 0);
			lv_obj_set_size(item->extra[0], 0.75 * TRANSFORMER_WIDGET_HEIGHT, 0.75 * TRANSFORMER_WIDGET_HEIGHT);
			lv_obj_add_event_cb(item->extra[0], profile_listing_delete_button_cb, LV_EVENT_CLICKED, item);
			lv_obj_add_flag(item->extra[0], LV_OBJ_FLAG_HIDDEN);
			
			item->extra[1] = lv_label_create(item->extra[0]);
			lv_label_set_text(item->extra[1], LV_SYMBOL_TRASH);
			lv_obj_center(item->extra[1]);
	
		
		default:
			return ERR_BAD_ARGS;
	}
	
	return NO_ERROR;
}

em_menu_item *create_page_link_menu_item(char *text, em_ui_page *linked_page, em_ui_page *parent)
{
	em_menu_item *item = malloc(sizeof(em_menu_item));
	
	if (!item)
		return NULL;
	
	init_menu_item(item);
	
	item->type = MENU_ITEM_PAGE_LINK;
	item->text = strndup(text, MENU_ITEM_TEXT_MAX_LEN);
	
	item->linked_page = linked_page;
	item->parent = parent;
	
	return item;
}

em_menu_item *create_page_link_indirect_menu_item(char *text, em_ui_page **linked_page, em_ui_page *parent)
{
	em_menu_item *item = malloc(sizeof(em_menu_item));
	
	if (!item)
		return NULL;
	
	init_menu_item(item);
	
	item->type = MENU_ITEM_PAGE_LINK_INDIRECT;
	item->text = strndup(text, MENU_ITEM_TEXT_MAX_LEN);
	item->linked_page_indirect = linked_page;
	item->parent = parent;
	
	return item;
}

em_menu_item *create_profile_listing_menu_item(char *text, em_profile *profile, em_ui_page *parent)
{
	em_menu_item *item = malloc(sizeof(em_menu_item));
	
	if (!item || !profile)
		return NULL;
	
	init_menu_item(item);
	
	item->type = MENU_ITEM_PROFILE_LISTING;
	item->text = strndup(text, MENU_ITEM_TEXT_MAX_LEN);
	item->linked_page_indirect = &profile->view_page;
	item->data = profile;
	item->parent = parent;
	
	return item;
}

int profile_listing_menu_item_refresh_active(em_menu_item *item, int active)
{
	if (!item)
		return ERR_NULL_PTR;
	
	if (!item->extra)
		return NO_ERROR;
		
	if (!item->extra[1])
		return NO_ERROR;
	
	if (active)
	{
		lv_label_set_text(item->extra[1], LV_SYMBOL_PLUS);
		lv_obj_clear_flag(item->extra[0], LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(item->extra[0], LV_OBJ_FLAG_CLICKABLE);
	}
	else
	{
		lv_label_set_text(item->extra[1], LV_SYMBOL_TRASH);
		lv_obj_add_flag(item->extra[0], LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(item->extra[0], LV_OBJ_FLAG_CLICKABLE);
	}
	
	return NO_ERROR;
}

int init_menu_page_str(em_menu_page_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	str->items = NULL;
	str->next_page = NULL;
	str->container = NULL;
	
	return NO_ERROR;
}

int init_menu_page(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	init_ui_page(page);
	
	em_menu_page_str *str = malloc(sizeof(em_menu_page_str));
	
	page->data_struct = str;
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	page->create_ui = create_menu_page_ui;
	page->configure = configure_menu_page;
	page->free_ui = free_menu_page_ui;
	
	return init_menu_page_str(str);
}

int configure_menu_page(em_ui_page *page, void *data)
{
	//printf("configure_menu_page\n");
	if (!page)
		return ERR_NULL_PTR;
	
	if (page->configured)
		return NO_ERROR;
	
	int ret_val = NO_ERROR;
	em_menu_page_str *str = (em_menu_page_str*)page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	str->name = "Main Menu";
	
	page->parent = data;
	menu_item_ll *current_item = str->items;
	
	while (current_item)
	{
		configure_menu_item(current_item->data);
		current_item = current_item->next;
	}
	
	if (str->next_page)
		ret_val = configure_menu_page(str->next_page, page);
	
	page->configured = (ret_val == NO_ERROR);
	
	//printf("configure_menu_page done\n");
	return ret_val;
}

int create_menu_page_ui(em_ui_page *page)
{
	//printf("create_menu_page_ui, page = %p\n", page);
	if (!page)
		return ERR_NULL_PTR;
	
	if (page->ui_created)
	{
		//printf("UI already created\n");
		return NO_ERROR;
	}
	
	em_menu_page_str *str = (em_menu_page_str*)page->data_struct;
	
	if (!str)
	{
		//printf("No struct !\n");
		return ERR_BAD_ARGS;
	}
	
	page->screen = lv_obj_create(NULL);
	
	//printf("page = %p. page->str = %p. page->str->name = %p = %s\n",
	//	page, page->data_struct, str->name, str->name);
	
	create_top_panel_with_back_button(page, str->name, NULL);
	
	create_standard_button_list(&str->container, page->screen);
	
	menu_item_ll *current = str->items;
	
	while (current)
	{
		create_menu_item_ui(current->data, str->container);
		current = current->next;
	}
	
	if (str->next_page)
		create_menu_page_ui(str->next_page);
	
	page->ui_created = 1;
	
	//printf("create_menu_page_ui done\n");
	return NO_ERROR;
}

int free_menu_page_ui(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	
	
	return ERR_UNIMPLEMENTED;
}

int menu_page_add_item(em_menu_page_str *str, em_menu_item *item)
{
	if (!str || !item)
		return ERR_NULL_PTR;
	
	//printf("menu_page_add_item(%p, %p). str->items = %p\n", str, item, str->items);
	
	menu_item_ll *nl = em_menu_item_ptr_linked_list_append(str->items, item);
	
	if (!nl)
		return ERR_ALLOC_FAIL;
	
	str->items = nl;
	
	return NO_ERROR;
}

void enter_main_menu_cb(lv_event_t *e)
{
	enter_ui_page(global_cxt.ui_cxt.main_menu);
}

int init_main_menu(em_ui_page *page)
{
	//printf("init_main_menu...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	//printf("init_menu_page(main_menu)\n");
	init_menu_page(page);
	
	em_menu_page_str *str = (em_menu_page_str*)page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	em_ui_page *profile_list = malloc(sizeof(em_ui_page));
	
	if (!profile_list)
		return ERR_NULL_PTR;
	
	init_profile_list(profile_list);
	
	em_menu_item *item = create_page_link_menu_item("Profiles", profile_list, page);
	
	//printf("Created profile list menu item, %p\n", item);
	
	menu_page_add_item(str, item);
	
	return NO_ERROR;
}

int enter_main_menu(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_scr_load(page->screen);
	
	return NO_ERROR;
}

int enter_main_menu_forward(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	return NO_ERROR;
}

int enter_main_menu_back(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	return NO_ERROR;
}

int init_profile_list(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	//printf("init_profile_list\n");
	init_menu_page(page);
	
	page->configure = configure_profile_list;
	
	//printf("init_profile_list done\n");
	return NO_ERROR;
}

int configure_profile_list(em_ui_page *page, void *data)
{
	//printf("Configure profile list\n");
	if (!page)
		return ERR_NULL_PTR;
	
	if (page->configured)
		return NO_ERROR;
	
	page->parent = (em_ui_page*)data;
	
	em_menu_page_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	str->name = "Profiles";
	
	profile_ll *current = global_cxt.profiles;
	//printf("current = global_cxt.profiles = %p\n", current);
	menu_item_ll *nl;
	
	int i = 0;
	while (current)
	{
		//printf("current = %p, current->data = %p\n",
		//	current, current->data);
		if (current->data)
		{
			//printf("Add list item for profile %d, %p = %s\n", i, current->data, current->data->name);
			//printf("Profile view page pointer: %p, dbl ptr: %p\n", current->data->view_page, &current->data->view_page);
			menu_page_add_item(str, create_profile_listing_menu_item(current->data->name, current->data, page));
		}
		
		current = current->next;
		i++;
	}
	
	page->configured = 1;
	//printf("Configure profile list done\n");
	
	return NO_ERROR;
}

int free_profile_list_ui(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	
	
	return NO_ERROR;
}

int enter_profile_list(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	
	
	return NO_ERROR;
}

int refresh_profile_list(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	
	
	return NO_ERROR;
}


int menu_page_remove_item(em_ui_page *page, em_menu_item *item)
{
	if (!page)
		return ERR_NULL_PTR;
	
	em_menu_page_str *str = (em_menu_page_str*)page->data_struct;

	if (!str)
		return ERR_BAD_ARGS;
	
	menu_item_ll *current_item = str->items;
	menu_item_ll *prev_item = NULL;
	
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
			
			free(current_item);
			return NO_ERROR;
		}
		
		prev_item = current_item;
		current_item = current_item->next;
	}
	
	return ERR_BAD_ARGS;
}

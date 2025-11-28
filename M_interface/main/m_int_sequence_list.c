#include "m_int.h"

m_int_menu_item *create_sequence_listing_menu_item(char *text, m_int_sequence *sequence, m_ui_page *parent)
{
	m_int_menu_item *item = m_alloc(sizeof(m_int_menu_item));
	
	if (!item || !sequence)
		return NULL;
	
	init_menu_item(item);
	
	item->type = MENU_ITEM_SEQUENCE_LISTING;
	if (text)
		item->text = m_strndup(text, MENU_ITEM_TEXT_MAX_LEN);
	else
		item->text = "Sequence";
	
	item->linked_page_indirect = &sequence->view_page;
	item->data = sequence;
	
	
	
	if (sequence)
		m_int_sequence_add_menu_listing(sequence, item);
	
	item->parent = parent;
	
	return item;
}

int sequence_listing_menu_item_refresh_active(m_int_menu_item *item)
{
	printf("sequence_listing_menu_item_refresh_active\n");
	if (!item)
		return ERR_NULL_PTR;
	
	if (!item->extra)
		return NO_ERROR;
		
	if (!item->extra[1])
		return NO_ERROR;
	
	if (item->data && ((m_int_sequence*)item->data)->active)
	{
		printf("sequence is active. going about it\n");
		
		if (item->extra && item->extra[0] && item->extra[1])
		{
			lv_label_set_text(item->extra[1], LV_SYMBOL_PLAY);
			lv_obj_clear_flag(item->extra[0], LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(item->extra[0], LV_OBJ_FLAG_CLICKABLE);
		}
	}
	else
	{
		printf("sequence is not active. hiding play\n");
		if (item->extra && item->extra[0] && item->extra[1])
		{
			lv_label_set_text(item->extra[1], LV_SYMBOL_TRASH);
			lv_obj_add_flag(item->extra[0], LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(item->extra[0], LV_OBJ_FLAG_CLICKABLE);
		}
	}
	
	printf("sequence_listing_menu_item_refresh_active done\n");
	return NO_ERROR;
}

int sequence_listing_menu_item_change_name(m_int_menu_item *item, char *name)
{
	if (!item)
		return ERR_NULL_PTR;
	
	if (!item->extra)
		return NO_ERROR;
	
	item->text = m_strndup(name, 32);
	
	lv_label_set_text(item->label, item->text);
	
	return NO_ERROR;
}

int init_sequence_list(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	//printf("init_sequence_list\n");
	init_menu_page(page);
	
	page->configure = configure_sequence_list;
	
	//printf("init_sequence_list done\n");
	return NO_ERROR;
}

void sequence_list_add_cb(lv_event_t *e)
{
	m_ui_page *page = lv_event_get_user_data(e);
	
	if (!page)
		return;
	
	m_int_menu_page_str *str = page->data_struct;
	
	if (!str)
		return;
	
	m_int_sequence *new_sequence = m_context_add_sequence_rp(&global_cxt);
	
	if (!new_sequence)
	{
		printf("ERROR: Couldn't create new sequence\n");
		return;
	}
	
	create_sequence_view_for(new_sequence);
	
	if (new_sequence->view_page)
	{
		new_sequence->view_page->parent = page;
		enter_ui_page(new_sequence->view_page);
	}
	
	m_int_menu_item *new_listing = create_sequence_listing_menu_item(new_sequence->name, new_sequence, page);
	
	if (!new_listing)
	{
		printf("Failed to create sequence listing menu item\n");
		return;
	}
	
	menu_page_add_item(str, new_listing);
	create_menu_item_ui(new_listing, page->container);
	sequence_listing_menu_item_refresh_active(new_listing);
}

int configure_sequence_list(m_ui_page *page, void *data)
{
	printf("Configure sequence list\n");
	if (!page)
		return ERR_NULL_PTR;
	
	if (page->configured)
		return NO_ERROR;
	
	page->parent = (m_ui_page*)data;
	
	m_int_menu_page_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	str->name = "Sequences";
	
	page->panel = new_panel();
	page->panel->text = str->name;
	page->container_type = CONTAINER_TYPE_STD_BTN_LIST;
	
	ui_page_add_back_button(page);
	
	ui_page_add_bottom_button(page, LV_SYMBOL_PLUS, sequence_list_add_cb);
	
	sequence_ll *current = global_cxt.sequences;
	printf("current = global_cxt.sequences = %p\n", current);
	m_int_menu_item_pll *nl;
	
	int i = 0;
	while (current)
	{
		printf("current = %p, current->data = %p\n",
			current, current->data);
		if (current->data)
		{
			printf("Add list item for sequence %d, %p = %s\n", i, current->data, current->data->name);
			printf("Sequence view page pointer: %p, dbl ptr: %p\n", current->data->view_page, &current->data->view_page);
			menu_page_add_item(str, create_sequence_listing_menu_item(current->data->name, current->data, page));
		}
		
		current = current->next;
		i++;
	}
	
	page->configured = 1;
	
	return NO_ERROR;
}

int free_sequence_list_ui(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	
	
	return NO_ERROR;
}

void sequence_listing_delete_button_cb(lv_event_t *e)
{
	m_int_menu_item *item = lv_event_get_user_data(e);
	
	if (!item)
		return;
	
	m_int_sequence *sequence = (m_int_sequence*)item->data;
	
	if (!sequence)
		return;
	
	if (!sequence->active)
	{
		cxt_remove_sequence(&global_cxt, sequence);
		
		menu_page_remove_item(item->parent, item);
	}
}

void disappear_sequence_listing_delete_button(lv_timer_t *timer)
{
	m_int_menu_item *item = timer->user_data;
	
	lv_obj_add_flag(item->extra[0], LV_OBJ_FLAG_HIDDEN);
	
	item->timer = NULL;
}

void menu_item_sequence_listing_released_cb(lv_event_t *e)
{
	printf("menu_item_sequence_listing_released_cb\n");
	m_int_menu_item *item = (m_int_menu_item*)lv_event_get_user_data(e);
	
	if (!item)
		return;
	
	int ret_val;
	m_int_sequence *sequence = item->data;
	
	if (!sequence)
	{
		printf("Error: sequence listing has no associated sequence!\n");
	}
	
	if (!item->long_pressed)
	{
		if (!sequence->view_page)
		{
			ret_val = create_sequence_view_for(sequence);
			if (ret_val != NO_ERROR)
			{
				printf("Error creating sequence view for sequence: %s\n", m_error_code_to_string(ret_val));
				return;
			}
		}
		
		sequence->view_page->parent = item->parent;
		enter_ui_page(sequence->view_page);
	}
	else
	{
		if (sequence && !sequence->active)
		{
			item->timer = lv_timer_create(disappear_sequence_listing_delete_button, STANDARD_DEL_BTN_REMAIN_MS, item);
			lv_timer_set_repeat_count(item->timer, 1);
		}
	}
	
	item->long_pressed = 0;
}

void menu_item_sequence_listing_long_pressed_cb(lv_event_t *e)
{
	m_int_menu_item *item = (m_int_menu_item*)lv_event_get_user_data(e);
	
	if (!item)
		return;
	
	item->long_pressed = 1;
	
	m_int_sequence *sequence = item->data;
	
	if (sequence && !sequence->active)
	{
		if (item->extra && item->extra[0])
			lv_obj_clear_flag(item->extra[0], LV_OBJ_FLAG_HIDDEN);
	}
	else
	{
		if (item->extra && item->extra[0])
			lv_obj_clear_flag(item->extra[0], LV_OBJ_FLAG_HIDDEN);
	}
}

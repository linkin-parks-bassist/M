#include "m_int.h"

int create_sequence_view_for(m_int_sequence *seq)
{
	if (!seq)
		return ERR_NULL_PTR;
	
	seq->view_page = malloc(sizeof(m_ui_page));
	
	if (!seq->view_page)
		return ERR_ALLOC_FAIL;
	
	init_sequence_view(seq->view_page);
	configure_sequence_view(seq->view_page, seq);
	
	return NO_ERROR;
}

int init_sequence_view(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	init_ui_page(page);
	
	m_int_sequence_view_str *str = malloc(sizeof(m_int_sequence_view_str));
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	str->seq = NULL;
	str->buttons = NULL;
	
	str->play_button = NULL;
	str->plus_button = NULL;
	str->save_button = NULL;
	
	page->data_struct = str;
	
	page->configure = configure_sequence_view;
	page->create_ui = create_sequence_view_ui;
	
	return NO_ERROR;
}

void seq_play_button_cb(lv_event_t *e)
{
	m_ui_page *page = lv_event_get_user_data(e);
	
	if (!page)
		return;
	
	m_int_sequence_view_str *str = (m_int_sequence_view_str*)page->data_struct;
	
	if (!str)
		return;
	
	if (!str->seq)
	{
		printf("ERROR: no sequence\n");
		return;
	}
	
	m_sequence_begin(str->seq);
}

void seq_plus_button_cb(lv_event_t *e)
{
	m_ui_page *page = lv_event_get_user_data(e);
	
	if (!page)
		return;
	
	m_int_sequence_view_str *str = (m_int_sequence_view_str*)page->data_struct;
	
	if (!str)
		return;
	
	m_profile *new_profile = create_new_profile_with_teensy();
	
	if (!new_profile)
		return;
	
	seq_profile_ll *node = sequence_append_profile_rp(str->seq, new_profile);
	m_int_glide_button *button = append_new_glide_button_to_array(str->buttons, new_profile, new_profile->name);
	
	printf("node = %p, button = %p\n", node, button);
	
	if (node)
	{
		node->button = button;
	}
	else
	{
		printf("Node is NULL!\n");
	}
	
	if (button)
	{
		profile_add_gb_reference(new_profile, button);
	}
	else
	{
		printf("Button is NULL!\n");
	}
	
	create_glide_button_ui(button, page->container);
}

void seq_save_button_cb(lv_event_t *e)
{
	
}

int seq_view_gb_free_cb(m_int_glide_button *button)
{
	if (!button)
		return ERR_NULL_PTR;
	
	
	
	return NO_ERROR;
}

int seq_view_gb_delete_cb(m_int_glide_button *button)
{
	if (!button)
		return ERR_NULL_PTR;
	
	
	
	return NO_ERROR;
}

int seq_view_gb_clicked_cb(m_int_glide_button *button)
{
	printf("clicked that thang\n");
	if (!button)
		return ERR_NULL_PTR;
	
	m_profile *profile = button->data;
	
	if (!profile)
		return ERR_BAD_ARGS;
	
	if (!profile->view_page)
	{
		if (!create_profile_view_for(profile))
			return ERR_ALLOC_FAIL;
	}
	
	if (button->array)
	{
		profile->view_page->parent = button->array->parent;
	}
	
	enter_ui_page(profile->view_page);
	
	return NO_ERROR;
}

int seq_view_gb_moved_cb(m_int_glide_button *button)
{
	printf("moved that thang; pos %d to pos %d\n", button->prev_index, button->index);
	if (!button)
		return ERR_NULL_PTR;
	
	
	
	return NO_ERROR;
}

void sequence_view_set_name(lv_event_t *e)
{
	m_ui_page *page = (m_ui_page*)lv_event_get_user_data(e);
	m_int_sequence_view_str *str = (m_int_sequence_view_str*)page->data_struct;
	
	const char *new_name = lv_textarea_get_text(page->panel->title);
	
	if (str->seq->name)
		m_free(str->seq->name);
	
	str->seq->name = m_strndup(new_name, PROFILE_NAM_ENG_MAX_LEN);
	
	lv_obj_clear_state(page->panel->title, LV_STATE_FOCUSED);
	lv_obj_add_state(page->container, LV_STATE_FOCUSED);
	
	hide_keyboard();
	
	str->seq->unsaved_changes = 1;
	lv_obj_clear_flag(str->save_button->obj, LV_OBJ_FLAG_HIDDEN);
}

void sequence_view_revert_name(lv_event_t *e)
{
	m_ui_page *page = (m_ui_page*)lv_event_get_user_data(e);
	m_int_sequence_view_str *str = (m_int_sequence_view_str*)page->data_struct;
	
	lv_textarea_set_text(page->panel->title, str->seq->name);
	
	lv_obj_clear_state(page->panel->title, LV_STATE_FOCUSED);
	lv_obj_add_state(page->container, LV_STATE_FOCUSED);
	
	hide_keyboard();
}

int configure_sequence_view(m_ui_page *page, void *data)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_sequence *seq = (m_int_sequence*)data;
	
	if (!seq)
		return ERR_BAD_ARGS;
	
	m_int_sequence_view_str *str = (m_int_sequence_view_str*)page->data_struct;
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	str->seq = seq;
	
	seq->view_page = page;
	
	page->panel = new_panel();
	
	ui_page_add_back_button(page);
	
	str->buttons = new_gb_array();
	
	str->buttons->parent = page;
	
	str->buttons->free_cb 	 = seq_view_gb_free_cb;
	str->buttons->delete_cb  = seq_view_gb_delete_cb;
	str->buttons->clicked_cb = seq_view_gb_clicked_cb;
	str->buttons->moved_cb 	 = seq_view_gb_moved_cb;
	
	str->play_button = ui_page_add_bottom_button(page, LV_SYMBOL_PLAY, seq_play_button_cb);
	str->plus_button = ui_page_add_bottom_button(page, LV_SYMBOL_PLUS, seq_plus_button_cb);
	str->save_button = ui_page_add_bottom_button(page, LV_SYMBOL_SAVE, seq_save_button_cb);
	
	page->panel->text = seq->name;
	ui_page_set_title_rw(page, sequence_view_set_name, sequence_view_revert_name);
	
	seq_profile_ll *current = seq->profiles;
	m_int_glide_button *button;
	
	while (current)
	{
		if (current->data)
		{
			button = append_new_glide_button_to_array(str->buttons, current->data, current->data->name);
			current->button = button;
		}
	}
	
	page->configured = 1;
	
	return NO_ERROR;
}

int create_sequence_view_ui(m_ui_page *page)
{
	printf("create_sequence_view_ui\n");
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_sequence_view_str *str = (m_int_sequence_view_str*)page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	ui_page_create_base_ui(page);
	
	create_glide_button_array_ui(str->buttons, page->container);
	
	printf("create_sequence_view_ui done");
	return NO_ERROR;
}

int refresh_sequence_view(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	
	
	return NO_ERROR;
}

int free_sequence_view_ui(m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	
	
	return NO_ERROR;
}

int sequence_view_free_all (m_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	
	
	return NO_ERROR;
	
}

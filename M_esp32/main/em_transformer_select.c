#include "em.h"

static const char *TAG = "em_transformer_select.c";

IMPLEMENT_LINKED_PTR_LIST(em_trans_selector_button);

void enter_transformer_selector_cb(lv_event_t *e)
{
	enter_transformer_selector(&global_cxt.ui_cxt.transformer_selector);
}

int init_transformer_selector(em_ui_page *page)
{
	//printf("init_transformer_selector...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	em_transformer_selector_str *str = malloc(sizeof(em_transformer_selector_str));
	
	page->data_struct = str;
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	str->buttons 	 = NULL;
	str->button_list = NULL;
	str->page_offset = 0;
	
	em_trans_selector_button *button;
    for (int i = 0; i < N_TRANSFORMER_TYPES; i++)
    {
		button = malloc(sizeof(em_trans_selector_button));
		
		if (!button)
			return ERR_ALLOC_FAIL;
		
		init_transformer_selector_button(button, i);
		str->buttons = em_trans_selector_button_ptr_linked_list_append(str->buttons, button);
	}
	
	return NO_ERROR;
}

int configure_transformer_selector(em_ui_page *page, void *data)
{
	//printf("configure_transformer_selector...\n");
	if (!page || !data)
		return ERR_NULL_PTR;
	
	if (page->configured)
		return NO_ERROR;
	
	em_transformer_selector_str *ts = page->data_struct;
	
	if (!ts)
		return ERR_BAD_ARGS;
	
	page->configured = 1;
	
	printf("success\n");
	return NO_ERROR;
}


void add_transformer_from_menu(lv_event_t *e)
{
	em_trans_selector_button *button = lv_event_get_user_data(e);
	
	// Should never happen
	if (!button)
	{
		ESP_LOGE(TAG, "User tried to add transformer from menu, but the pointer to the page struct is NULL!\n");
		return;
	}
	
	em_ui_page *pv = NULL;
	em_transformer *trans = NULL;
	
	em_profile *profile = global_cxt.working_profile;
	
	uint16_t type = button->type;
	
	printf("User wishes to add a \"%s\"\n", button->name);
	
	if (!profile->view_page)
	{
		ESP_LOGE(TAG, "Profile does not have a view page!\n");
	}
	else
	{
		pv = profile->view_page;
	}
	
	trans = em_profile_append_transformer_type(profile, type);
	
	if (pv)
		profile_view_append_transformer(pv, trans);
	
	profile->unsaved_changes = 1;
	
	request_append_transformer(type, trans);
	
	transformer_init_ui_page(trans, pv);
	create_transformer_view_ui(trans->view_page);
	
	enter_ui_page(profile->view_page);
}

int init_transformer_selector_button(em_trans_selector_button *button, int index)
{
	//printf("Init transformer selector button. Button = %p, index = %d, profile = %p\n", button, index, profile);
	if (!button)
		return ERR_NULL_PTR;
	
	if (index < N_TRANSFORMER_TYPES)
	{
		//printf("Index is valid. Use type %d and name %s\n", transformer_table[index].type, transformer_table[index].name);
		button->type = transformer_table[index].type;
		button->name = transformer_table[index].name;
	}
	else
	{
		button->type = 0;
		button->name = "Unknown";
	}
	
	button->button = NULL;
	button->label  = NULL;
	
	return NO_ERROR;
}


int create_transformer_selector_button_ui(em_trans_selector_button *button, lv_obj_t *parent)
{
	//printf("Create transformer selector button ui\n");
	if (!button)
		return ERR_NULL_PTR;
	
	create_standard_button_click(&button->button, &button->label, parent, button->name, add_transformer_from_menu, button);

	return NO_ERROR;
}

int create_transformer_selector_ui(em_ui_page *page)
{
	printf("create_transformer_selector_ui...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	if (page->ui_created)
		return NO_ERROR;
	
	em_transformer_selector_str *ts = (em_transformer_selector_str*)page->data_struct;
	
	if (!ts)
		return ERR_BAD_ARGS;
	
	page->screen = lv_obj_create(NULL);
	
	create_top_panel_with_back_button(page, "Add Effect", NULL);
	create_standard_button_list(&ts->button_list, page->screen);
    
    em_trans_selector_button_ptr_linked_list *current = ts->buttons;
    
    while (current)
    {
		create_transformer_selector_button_ui(current->data, ts->button_list);
		current = current->next;
	}
	
	page->ui_created = 1;
	
	printf("success\n");
	return NO_ERROR;
}

int enter_transformer_selector(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_scr_load(page->screen);
	
	return NO_ERROR;
}

int enter_transformer_selector_forward(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	return NO_ERROR;
}

int enter_transformer_selector_back(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	return NO_ERROR;
}

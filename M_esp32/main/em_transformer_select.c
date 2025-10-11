#include "em.h"

static const char *TAG = "em_transformer_select.c";

IMPLEMENT_LINKED_PTR_LIST(em_trans_selector_button);

void enter_transformer_selector_cb(lv_event_t *e)
{
	enter_transformer_selector(&global_cxt.ui_cxt.transformer_selector);
}

int init_transformer_selector(em_ui_page *page)
{
	printf("init_transformer_selector...\n");
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
		
		init_transformer_selector_button(button, i, NULL);
		str->buttons = em_trans_selector_button_ptr_linked_list_append(str->buttons, button);
	}
	
	return NO_ERROR;
}

int configure_transformer_selector(em_ui_page *page, void *data)
{
	printf("configure_transformer_selector...\n");
	if (!page || !data)
		return ERR_NULL_PTR;
	
	em_profile *profile = (em_profile*)data;
	
	em_transformer_selector_str *ts = page->data_struct;
	
	if (!ts)
		return ERR_BAD_ARGS;
	
	ts->pid = profile->id;
	ts->profile = profile;
	
	em_trans_selector_button_ptr_linked_list *current = ts->buttons;
	em_trans_selector_button_ptr_linked_list *prev = NULL;
    
    while (current)
    {
		if (current->data)
		{
			current->data->profile = profile;
		}
		else if (prev)
		{
			prev->next = current->next;
			free(current);
			current = prev->next;
			continue;
		}
		else
		{
			ts->buttons = current->next;
			free(current);
			current = ts->buttons;
			continue;
		}
		prev = current;
		current = current->next;
	}
	
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
	
	uint16_t type = button->type;
	
	printf("User wishes to add a \"%s\"\n", button->name);
	
	if (!button->profile)
	{
		ESP_LOGE(TAG, "Button is not attached to a profile!\n");
		return;
	}
	
	if (!button->profile->view_page)
	{
		ESP_LOGE(TAG, "Profile does not have a view page!\n");
	}
	else
	{
		pv = button->profile->view_page;
	}
	
	trans = em_profile_append_transformer_type(button->profile, type);
	profile_view_append_transformer(pv, trans);
	printf("Created new transformer with type \"%s\", having %d parameters\n", button->name, trans->n_parameters);
	request_append_transformer(type, trans);
	
	transformer_init_ui_page(trans, pv);
	create_transformer_view_ui(trans->view_page);
	
	enter_ui_page(button->profile->view_page);
}

int init_transformer_selector_button(em_trans_selector_button *button, int index, em_profile *profile)
{
	printf("Init transformer selector button. Button = %p, index = %d, profile = %p\n", button, index, profile);
	if (!button)
		return ERR_NULL_PTR;
	
	if (index < N_TRANSFORMER_TYPES)
	{
		printf("Index is valid. Use type %d and name %s\n", transformer_table[index].type, transformer_table[index].name);
		button->type = transformer_table[index].type;
		button->name = transformer_table[index].name;
	}
	else
	{
		button->type = TRANSFORMER_BUFFER;
		button->name = "Unknown";
	}
	
	button->profile = profile;
	
	button->button = NULL;
	button->label  = NULL;
	
	return NO_ERROR;
}


int create_transformer_selector_button_ui(em_trans_selector_button *button, lv_obj_t *parent)
{
	printf("Create transformer selector button ui\n");
	if (!button)
		return ERR_NULL_PTR;
	
	button->button = lv_btn_create(parent);
    lv_obj_set_size(button->button, LV_PCT(100), LV_SIZE_CONTENT);
    
    printf("Type: %d. Name: ", button->type);
    printf("%p = %s\n", button->name, button->name ? button->name : "(NULL)");
	button->label = lv_label_create(button->button);
	
	if (button->name)
		lv_label_set_text(button->label, button->name);
	
	lv_obj_center(button->label);
	
	lv_obj_add_event_cb(button->button, add_transformer_from_menu, LV_EVENT_CLICKED, button);
	
	return NO_ERROR;
}

int create_transformer_selector_ui(em_ui_page *page)
{
	printf("create_transformer_selector_ui...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	em_transformer_selector_str *ts = (em_transformer_selector_str*)page->data_struct;
	
	if (!ts)
		return ERR_BAD_ARGS;
	
	page->screen = lv_obj_create(NULL);
	
	create_top_panel_with_back_button(page, "Add Effect", NULL);
	
	ts->button_list = lv_obj_create(page->screen);
    lv_obj_set_size(ts->button_list, 500, 800);
    lv_obj_align(ts->button_list, LV_ALIGN_TOP_MID, 0, 120);
    lv_obj_set_flex_flow(ts->button_list, LV_FLEX_FLOW_COLUMN);
    
    em_trans_selector_button_ptr_linked_list *current = ts->buttons;
    
    while (current)
    {
		create_transformer_selector_button_ui(current->data, ts->button_list);
		current = current->next;
	}
	
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

#include "em.h"

static const char *TAG = "em_profile_view.c";

int init_profile_view(em_ui_page *page)
{
	printf("init_profile_view...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *str = malloc(sizeof(em_profile_view_str));
	page->data_struct = (void*)str;
	
	str->profile 		= NULL;
	str->transformer_list 	= NULL;
	str->profile 		= NULL;
	str->tws 			= NULL;
	str->drag_state		= 0;

	
	page->configure  			= configure_profile_view;
	page->create_ui  			= create_profile_view_ui;
	page->enter_page 			= enter_profile_view;
	page->enter_page_forward 	= enter_profile_view_forward;
	page->enter_page_back 		= enter_profile_view_back;
	
	printf("success\n");
	return NO_ERROR;
}

int configure_profile_view(em_ui_page *page, void *data)
{
	printf("configure_profile_view...\n");
	if (!page || !data)
		return ERR_NULL_PTR;
	
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
	
	printf("success\n");
	return alloc_fail ? ERR_ALLOC_FAIL : NO_ERROR;
}

int create_profile_view_ui(em_ui_page *page)
{
	printf("create_profile_view_ui...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *str = (em_profile_view_str*)page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
		
	if (!str->profile)
		return ERR_BAD_ARGS;
	
	page->screen = lv_obj_create(NULL);
	
	printf("Creating top panel with label %s\n", str->profile->name ? str->profile->name : "(null)");
	create_top_panel_with_back_button(page, str->profile->name, NULL);
	
	str->transformer_list = lv_obj_create(page->screen);
    lv_obj_set_size(str->transformer_list, PROFILE_VIEW_TRANSFORMER_LIST_WIDTH, PROFILE_VIEW_TRANSFORMER_LIST_HEIGHT);
    lv_obj_center(str->transformer_list);
    
    em_transformer_widget_ptr_linked_list *current = str->tws;
    
    int i = 0;
    while (current)
    {
		create_transformer_widget_ui(current->data, str->transformer_list);
		current = current->next;
		i++;
	}
	
    str->plus_button = lv_btn_create(page->screen);
    lv_obj_set_size(str->plus_button, PROFILE_VIEW_BUTTON_WIDTH, PROFILE_VIEW_BUTTON_HEIGHT);
	lv_obj_align(str->plus_button, LV_ALIGN_BOTTOM_MID, 0, -50);
    
	str->plus_button_label = lv_label_create(str->plus_button);
	lv_label_set_text(str->plus_button_label, "+");
	lv_obj_center(str->plus_button_label);
	
	lv_obj_add_event_cb(str->plus_button, enter_transformer_selector_cb, LV_EVENT_CLICKED, page);
	
	printf("success\n");
	return NO_ERROR;
}

int enter_profile_view(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_scr_load(page->screen);
	
	((em_transformer_selector_str*)global_cxt.ui_cxt.transformer_selector.data_struct)->pid = ((em_profile_view_str*)page->data_struct)->profile->id;
	global_cxt.ui_cxt.transformer_selector.parent = page;
	
	return NO_ERROR;
}

int enter_profile_view_forward(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	((em_transformer_selector_str*)global_cxt.ui_cxt.transformer_selector.data_struct)->pid = ((em_profile_view_str*)page->data_struct)->profile->id;
	global_cxt.ui_cxt.transformer_selector.parent = page;
	
	return NO_ERROR;
}

int enter_profile_view_back(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	((em_transformer_selector_str*)global_cxt.ui_cxt.transformer_selector.data_struct)->pid = ((em_profile_view_str*)page->data_struct)->profile->id;
	global_cxt.ui_cxt.transformer_selector.parent = page;
	
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
	
	printf("Printing transformer widget linked list. n_tramsformer_widgets = %d\n", str->n_transformer_widgets);
	
	int i = 0;
	while (current)
	{
		printf("Transformer widget %d. pointer: %p.\n", i, current->data);
		printf("Transformer ptr %p, index %d, y_pos %d\n",
			current->data->trans, current->data->index, (int)current->data->pos_y);
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
	
	printf("profile_view_append_transformer... n_transformer_widgets = %d\n", str->n_transformer_widgets);
	
	em_transformer_widget *tw = malloc(sizeof(em_transformer_widget));
	
	if (!tw)
		return ERR_ALLOC_FAIL;
	
	init_transformer_widget(tw, page, trans, str->n_transformer_widgets++);
	create_transformer_widget_ui(tw, str->transformer_list);
	
	str->tws = em_transformer_widget_ptr_linked_list_append(str->tws, tw);
	
	profile_view_print_tw_list(page);
	
	return NO_ERROR;
}

int profile_view_enter_drag_state(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	if (str->drag_state)
		return NO_ERROR;
	
	str->drag_state = 1;
	
	profile_view_print_tw_list(page);
	
	return NO_ERROR;
}

int profile_view_exit_drag_state(em_ui_page *page)
{
	printf("Exit drag state...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	if (!str->drag_state)
		return NO_ERROR;
	
	str->drag_state = 0;
	
	profile_view_print_tw_list(page);
	
	return NO_ERROR;
}

int profile_view_index_y_position(int index)
{
	return PROFILE_VIEW_BUTTON_BASE_Y + index * PROFILE_VIEW_BUTTON_DISTANCE;
}

int profile_view_remove_tw(em_ui_page *page, em_transformer_widget *tw)
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
			if (current->data)
				free_transformer_widget(current->data);
			
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
	
	str->n_transformer_widgets--;
	
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

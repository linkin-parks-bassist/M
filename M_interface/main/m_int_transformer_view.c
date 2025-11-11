#include "m_int.h"

static const char *TAG = "m_int_transformer_view.c";

m_int_ui_page *create_transformer_view_for(m_int_transformer *trans)
{
	if (!trans)
		return NULL;
	
	m_int_ui_page *page = m_int_malloc(sizeof(m_int_ui_page));
	
	if (!page)
		return NULL;
	
	init_ui_page(page);
	
	int ret_val = init_transformer_view(page);
	
	if (ret_val != NO_ERROR)
	{
		free_transformer_view(page);
		return NULL;
	}
	
	ret_val = configure_transformer_view(page, trans);
	
	if (ret_val != NO_ERROR)
	{
		free_transformer_view(page);
		return NULL;
	}
	
	return page;
}

int init_transformer_view(m_int_ui_page *page)
{
	//printf("Init transformer view...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	page->panel = new_panel();
	if (!page->panel)
		return ERR_ALLOC_FAIL;
	
	m_int_transformer_view_str *str = m_int_malloc(sizeof(m_int_transformer_view_str));
	
	page->data_struct = str;
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	str->trans 			   = NULL;
	str->parameter_widgets = NULL;
	
	str->container 		   = NULL;
	
	page->configure  		 = configure_transformer_view;
	page->create_ui  		 = create_transformer_view_ui;
	page->enter_page 		 = enter_transformer_view;
	page->enter_page_forward = enter_transformer_view_forward;
	page->enter_page_back 	 = enter_transformer_view_back;
	
	for (int i = 0; i < TRANSFORMER_VIEW_MAX_GROUPS; i++)
		str->group_containers[i] = NULL;
	
	str->settings_page = malloc(sizeof(m_int_ui_page));
	
	if (!str->settings_page)
		return ERR_ALLOC_FAIL;
	
	init_transformer_settings_page(str->settings_page);
	
	return NO_ERROR;
}

void transformer_view_enter_settings_cb(lv_event_t *e)
{
	m_int_ui_page *page = lv_event_get_user_data(e);
	
	if (!page)
		return;
	
	m_int_transformer_view_str *str = (m_int_transformer_view_str*)page->data_struct;
	
	if (!str)
		return;
	
	enter_ui_page(str->settings_page);
}

int configure_transformer_view(m_int_ui_page *page, void *data)
{
	//printf("Conpfigure transformer view... page = %p, data = %p\n", page, data);
	if (!page || !data)
	{
		if (page)
			page->data_struct = NULL;
		return ERR_NULL_PTR;
	}
	
	if (page->configured)
		return NO_ERROR;
	
	ui_page_add_back_button(page);
	ui_page_add_right_panel_button(page, LV_SYMBOL_SETTINGS, transformer_view_enter_settings_cb);
	
	m_int_transformer *trans = (m_int_transformer*)data;
	m_int_transformer_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	str->trans = trans;
	
	m_int_parameter_widget *pw;
	int ret_val;
	
	parameter_ll *current = trans->parameters;
	
	while (current)
	{
		if (current->data)
		{
			pw = m_int_malloc(sizeof(m_int_parameter_widget));
		
			if (!pw)
				return ERR_ALLOC_FAIL;
			
			nullify_parameter_widget(pw);
			ret_val = configure_parameter_widget(pw, current->data, trans->profile);
			
			str->parameter_widgets = m_int_parameter_widget_ptr_linked_list_append(str->parameter_widgets, pw);
		}
		
		current = current->next;
	}
	
	configure_transformer_settings_page(str->settings_page, trans);
	
	page->configured = 1;
	
	//printf("Done.\n");
	return NO_ERROR;
}

int create_transformer_view_ui(m_int_ui_page *page)
{
	printf("Create transformer view ui...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	if (page->ui_created)
		return NO_ERROR;
	
	ui_page_create_base_ui(page);
	
	printf("page->container = %p\n", page->container);
	
	m_int_transformer_view_str *str = (m_int_transformer_view_str*)page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	if (!str->trans)
		return ERR_BAD_ARGS;
	
	page->panel->text = transformer_type_name(str->trans->type);
    
    lv_obj_set_layout(page->container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(page->container, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(page->container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_SPACE_EVENLY);
	
	int i = 0;
	int group;
	m_int_parameter_widget_ptr_linked_list *current = str->parameter_widgets;
	
	while (current)
	{
		printf("Creating parameter widget for parameter %d...\n", i);
		if (current->data)
		{
			if (current->data->param)
			{
				group = current->data->param->group;
				if (0 <= group && group < TRANSFORMER_VIEW_MAX_GROUPS)
				{
					printf("Parameter widget lives in group %d...\n", group);
					if (!str->group_containers[group])
					{
						str->group_containers[group] = lv_obj_create(page->container);
						lv_obj_remove_style_all(str->group_containers[group]);
						lv_obj_set_flex_flow (str->group_containers[group], LV_FLEX_FLOW_ROW_WRAP);
						lv_obj_set_flex_align(str->group_containers[group], LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_SPACE_EVENLY);
					}
					
					parameter_widget_create_ui(current->data, str->group_containers[group]);
					
					lv_obj_set_width(str->group_containers[group],  LV_SIZE_CONTENT);
					lv_obj_set_height(str->group_containers[group], LV_SIZE_CONTENT);
				}
				else
				{
					printf("Parameter widget is free...\n");
					parameter_widget_create_ui(current->data, page->container);
				}
			}
		}
		current = current->next;
		i++;
	}
	
	page->ui_created = 1;
	
	for (int i = 0; i < TRANSFORMER_VIEW_MAX_GROUPS; i++)
	{
		if (str->group_containers[i])
		{
			lv_obj_set_width(str->group_containers[i],  LV_SIZE_CONTENT);
			lv_obj_set_height(str->group_containers[i], LV_SIZE_CONTENT);
		}
	}
	
	create_transformer_settings_page_ui(str->settings_page);
	
	//printf("Done\n");
	return NO_ERROR;
}

int enter_transformer_view(m_int_ui_page *page)
{
	printf("Enter transformer view...\n");
	lv_scr_load(page->screen);
	
	transformer_view_request_parameter_values(page);
	printf("Done\n");
	return NO_ERROR;
}

int enter_transformer_view_forward(m_int_ui_page *page)
{
	if (!page)
	{
		//printf("Error: transformer view is NULL\n");
		return ERR_NULL_PTR;
	}
	//printf("Enter transformer view...\n");
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	transformer_view_request_parameter_values(page);
	//printf("Done\n");
	return NO_ERROR;
}

int enter_transformer_view_back(m_int_ui_page *page)
{
	//printf("Enter transformer view...\n");
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	transformer_view_request_parameter_values(page);
	//printf("Done\n");
	return NO_ERROR;
}

int clear_transformer_view()
{
	return ERR_UNIMPLEMENTED;
}

int transformer_view_request_parameter_values(m_int_ui_page *page)
{
	//printf("transformer_view_request_parameter_values...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_transformer_view_str *str = (m_int_transformer_view_str*)page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	m_int_parameter_widget_ptr_linked_list *current = str->parameter_widgets;
	
	while (current)
	{
		param_widget_request_value(current->data);
		current = current->next;
	}
	
	//printf("done transformer_view_request_parameter_values\n");
	
	return NO_ERROR;
}


int free_transformer_view_ui(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_obj_del(page->screen);
	
	return NO_ERROR;
}

int free_transformer_view(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	m_int_transformer_view_str *str = (m_int_transformer_view_str*)page->data_struct;
	
	if (str)
		destructor_free_m_int_parameter_widget_ptr_linked_list(str->parameter_widgets, free_parameter_widget);
	
	if (page->screen)
		lv_obj_del(page->screen);
	
	m_int_free(page);
	
	return NO_ERROR;
}

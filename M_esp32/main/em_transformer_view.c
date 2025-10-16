#include "em.h"

static const char *TAG = "em_transformer_view.c";

em_ui_page *make_transformer_view_for(em_transformer *trans)
{
	if (!trans)
		return NULL;
	
	em_ui_page *page = malloc(sizeof(em_ui_page));
	
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

int init_transformer_view(em_ui_page *page)
{
	printf("Init transformer view...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	em_transformer_view_str *str = malloc(sizeof(em_transformer_view_str));
	
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
	
	printf("Done\n");
	return NO_ERROR;
}

int configure_transformer_view(em_ui_page *page, void *data)
{
	printf("Configure transformer view... page = %p, data = %p\n", page, data);
	if (!page || !data)
	{
		if (page)
			page->data_struct = NULL;
		return ERR_NULL_PTR;
	}
	
	if (page->configured)
		return NO_ERROR;
	
	em_transformer *trans = (em_transformer*)data;
	em_transformer_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	str->trans = trans;
	
	em_parameter_widget *pw;
	int ret_val;
	
	for (int i = 0; i < trans->n_parameters; i++)
	{
		pw = malloc(sizeof(em_parameter_widget));
		
		if (!pw)
			return ERR_ALLOC_FAIL;
		
		nullify_em_parameter_widget(pw);
		ret_val = configure_em_parameter_widget(pw, &trans->parameters[i]);
		printf("Error code %d encountered at parameter %d.%d.%d\n", ret_val, trans->profile_id, trans->transformer_id, trans->parameters[i].id.parameter_id);
		str->parameter_widgets = em_parameter_widget_ptr_linked_list_append(str->parameter_widgets, pw);
	}
	
	page->configured = 1;
	
	printf("Done.\n");
	return NO_ERROR;
}

int create_transformer_view_ui(em_ui_page *page)
{
	printf("Create transformer view ui...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	if (page->ui_created)
		return NO_ERROR;
	
	page->screen = lv_obj_create(NULL);
	
	em_transformer_view_str *str = (em_transformer_view_str*)page->data_struct;
	
	printf("str->trans->n_parameters: %d\n", str->trans->n_parameters);
	
	if (!str)
		return ERR_BAD_ARGS;
	
	if (!str->trans)
		return ERR_BAD_ARGS;
	
	printf("Create top panel...\n");
	create_top_panel_with_back_button(page, transformer_type_name(str->trans->type), NULL);
	
	str->container = lv_obj_create(page->screen);
    
    lv_obj_set_layout(str->container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(str->container, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(str->container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_SPACE_EVENLY);
	
	lv_obj_set_size(str->container, 500, 800);
	
	lv_obj_center(str->container);
	
	if (str->trans->n_parameters <= 3)
		lv_obj_set_style_pad_bottom(str->container, 320, 0);

	int i = 0;
	int group;
	em_parameter_widget_ptr_linked_list *current = str->parameter_widgets;
	
	while (current)
	{
		if (current->data)
		{
			if (current->data->param)
			{
				group = current->data->param->group;
				if (0 <= group && group < TRANSFORMER_VIEW_MAX_GROUPS)
				{
					if (!str->group_containers[group])
					{
						str->group_containers[group] = lv_obj_create(str->container);
						lv_obj_remove_style_all(str->group_containers[group]);
						lv_obj_set_flex_flow (str->group_containers[group], LV_FLEX_FLOW_ROW_WRAP);
						lv_obj_set_flex_align(str->group_containers[group], LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_SPACE_EVENLY);
					}
					
					parameter_widget_create_ui(current->data, str->group_containers[group]);
					
					lv_obj_set_width(str->group_containers[group], LV_SIZE_CONTENT);
					lv_obj_set_height(str->group_containers[group], LV_SIZE_CONTENT);
				}
				else
				{
					parameter_widget_create_ui(current->data, str->container);
				}
			}
		}
		current = current->next;
		i++;
	}
	
	page->ui_created = 1;
	
	printf("Done\n");
	return NO_ERROR;
}

int enter_transformer_view(em_ui_page *page)
{
	printf("Enter transformer view...\n");
	lv_scr_load(page->screen);
	
	transformer_view_request_parameter_values(page);
	printf("Done\n");
	return NO_ERROR;
}

int enter_transformer_view_forward(em_ui_page *page)
{
	if (!page)
	{
		printf("Error: transformer view is NULL\n");
		return ERR_NULL_PTR;
	}
	printf("Enter transformer view...\n");
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	transformer_view_request_parameter_values(page);
	printf("Done\n");
	return NO_ERROR;
}

int enter_transformer_view_back(em_ui_page *page)
{
	printf("Enter transformer view...\n");
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	transformer_view_request_parameter_values(page);
	printf("Done\n");
	return NO_ERROR;
}

int clear_transformer_view()
{
	return ERR_UNIMPLEMENTED;
}

int transformer_view_request_parameter_values(em_ui_page *page)
{
	printf("transformer_view_request_parameter_values...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	em_transformer_view_str *str = (em_transformer_view_str*)page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	em_parameter_widget_ptr_linked_list *current = str->parameter_widgets;
	
	while (current)
	{
		param_widget_request_value(current->data);
		current = current->next;
	}
	
	printf("done transformer_view_request_parameter_values\n");
	
	return NO_ERROR;
}


int free_transformer_view_ui(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_obj_del(page->screen);
	
	return NO_ERROR;
}

int free_transformer_view(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	em_transformer_view_str *str = (em_transformer_view_str*)page->data_struct;
	
	if (str)
		destructor_free_em_parameter_widget_ptr_linked_list(str->parameter_widgets, free_parameter_widget);
	
	if (page->screen)
		lv_obj_del(page->screen);
	
	free(page);
	
	return NO_ERROR;
}

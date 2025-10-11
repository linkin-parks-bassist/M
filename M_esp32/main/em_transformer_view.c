#include "em.h"

static const char *TAG = "em_transformer_view.c";

int init_transformer_view(em_ui_page *page)
{
	printf("Init transformer view...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	em_transformer_view_str *str = malloc(sizeof(em_transformer_view_str));
	
	page->data_struct = str;
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	str->col_dsc[0] = 250;
	str->col_dsc[1] = 200;
	str->col_dsc[2] = LV_GRID_TEMPLATE_LAST;
	
	str->trans = NULL;
	str->parameter_widgets = NULL;
	
	str->grid = NULL;
	
	str->row_dsc = NULL;
	
	page->configure  		 = configure_transformer_view;
	page->create_ui  		 = create_transformer_view_ui;
	page->enter_page 		 = enter_transformer_view;
	page->enter_page_forward = enter_transformer_view_forward;
	page->enter_page_back 	 = enter_transformer_view_back;
	
	printf("Done\n");
	return NO_ERROR;
}

int configure_transformer_view(em_ui_page *page, void *data)
{
	printf("Configure transformer view...\n");
	if (!data)
	{
		page->data_struct = NULL;
		return ERR_NULL_PTR;
	}
	
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
	
	printf("Done.\n");
	return NO_ERROR;
}

int create_transformer_view_ui(em_ui_page *page)
{
	printf("Create transformer view ui...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	page->screen = lv_obj_create(NULL);
	
	em_transformer_view_str *str = (em_transformer_view_str*)page->data_struct;
	
	printf("str->trans->n_parameters: %d\n", str->trans->n_parameters);
	
	if (!str)
		return ERR_BAD_ARGS;
	
	if (!str->trans)
		return ERR_BAD_ARGS;
	
	int n_rows = (str->trans->n_parameters + 1) / 2;
	
	str->row_dsc = malloc(sizeof(lv_coord_t) * (n_rows + 1));
	
	if (!str->row_dsc)
		return ERR_ALLOC_FAIL;
	
	for (int i = 0; i < n_rows; i++)
		str->row_dsc[i] = TRANSFORMER_VIEW_GRID_CELL_VSIZE;
	
	str->row_dsc[n_rows] = LV_GRID_TEMPLATE_LAST;
	
	str->grid = lv_obj_create(page->screen);
	
	printf("Create top panel...\n");
	create_top_panel_with_back_button(page, transformer_type_name(str->trans->type), NULL);
	
	lv_obj_set_style_grid_column_dsc_array(str->grid, str->col_dsc, 0);
	lv_obj_set_style_grid_row_dsc_array(str->grid, str->row_dsc, 0);
	lv_obj_set_size(str->grid, 500, 800);
	lv_obj_center(str->grid);
	
	lv_obj_set_layout(str->grid, LV_LAYOUT_GRID);

	int i = 0;
	em_parameter_widget_ptr_linked_list *current = str->parameter_widgets;
	
	while (current)
	{
		if (current->data)
		{
			parameter_widget_create_ui(current->data, str->grid);
			lv_obj_set_grid_cell(current->data->obj, LV_GRID_ALIGN_CENTER, i % 2, 1, LV_GRID_ALIGN_CENTER, i / 2, 1);
		}
		current = current->next;
		i++;
	}
	
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
	{
		destructor_free_em_parameter_widget_ptr_linked_list(str->parameter_widgets, free_parameter_widget);
		free(str->row_dsc);
	}
	
	free(page);
	
	return NO_ERROR;
}

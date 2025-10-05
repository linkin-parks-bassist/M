#include "em.h"


IMPLEMENT_LINKED_LIST(parameter_widget);

const char *transformer_type_labels[] = {"Buffer", "Mixer", "Amplifier", "Biquadratic Filter", "Waveshaper", "Distortion", "Compression"};

const char *TAG = "Transformer view";

#define DISTORTION_LABEL_INDEX 0

transformer_view_str transformer_view;

#define H_PAD 40
#define V_PAD 40

int init_transformer_view_struct(ui_page *page)
{
	printf("Init transformer view...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	transformer_view_str *str = malloc(sizeof(transformer_view_str));
	
	page->data_struct = str;
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	str->col_dsc[0] = 200;
	str->col_dsc[1] = 200;
	str->col_dsc[2] = LV_GRID_TEMPLATE_LAST;
	
	str->trans = NULL;
	str->parameter_widgets = NULL;
	
	str->grid = NULL;
	
	str->row_dsc = NULL;
	
	printf("Done\n");
	return NO_ERROR;
}

int configure_transformer_view(ui_page *page, void *data)
{
	printf("Configure transformer view...\n");
	if (!data)
	{
		page->data_struct = NULL;
		return ERR_NULL_PTR;
	}
	
	teensy_transformer *trans = (teensy_transformer*)data;
	transformer_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	str->trans = trans;
	
	parameter_widget pw;
	int ret_val;
	
	for (int i = 0; i < trans->n_parameters; i++)
	{
		nullify_parameter_widget(&pw);
		ret_val = configure_parameter_widget(&pw, &trans->parameters[i]);
		printf("Error code %d encountered at parameter %d.%d.%d\n", ret_val, trans->profile_id, trans->transformer_id, trans->parameters[i].id.parameter_id);
		str->parameter_widgets = parameter_widget_linked_list_append(str->parameter_widgets, pw);
	}
	
	printf("Done.\n");
	return NO_ERROR;
}

int init_transformer_view_ui(ui_page *page)
{
	printf("Create transformer view ui...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	page->screen = lv_obj_create(NULL);
	
	transformer_view_str *str = (transformer_view_str*)page->data_struct;
	
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
	create_top_panel_with_back_button(page, transformer_type_labels[str->trans->type], NULL);
	
	lv_obj_set_style_grid_column_dsc_array(str->grid, str->col_dsc, 0);
	lv_obj_set_style_grid_row_dsc_array(str->grid, str->row_dsc, 0);
	lv_obj_set_size(str->grid, 500, 800);
	lv_obj_center(str->grid);
	
	lv_obj_set_layout(str->grid, LV_LAYOUT_GRID);

	int i = 0;
	parameter_widget_linked_list *current = str->parameter_widgets;
	
	while (current)
	{
		parameter_widget_create_ui(&current->data, str->grid);
		lv_obj_set_grid_cell(current->data.obj, LV_GRID_ALIGN_CENTER, i % 2, 1, LV_GRID_ALIGN_CENTER, i / 2, 1);
		current = current->next;
		i++;
	}
	
	printf("Done\n");
	return NO_ERROR;
}

int enter_transformer_view(ui_page *page)
{
	printf("Enter transformer view...\n");
	lv_scr_load(page->screen);
	
	transformer_view_request_parameter_values(page);
	printf("Done\n");
	return NO_ERROR;
}

int clear_transformer_view()
{
	return ERR_UNIMPLEMENTED;
}

int transformer_view_request_parameter_values(ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	transformer_view_str *str = (transformer_view_str*)page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	parameter_widget_linked_list *current = str->parameter_widgets;
	
	while (current)
	{
		param_widget_request_value(&current->data);
		current = current->next;
	}
	
	return NO_ERROR;
}

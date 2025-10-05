#ifndef TRANSFORMER_VIEW_H_
#define TRANSFORMER_VIEW_H_

#include "m_transformer_enum.h"
#include "em_parameter.h"

#include "em_parameter_widget.h"
#include "em_linked_list.h"

DECLARE_LINKED_LIST(parameter_widget);

#define TRANSFORMER_VIEW_GRID_CELL_HSIZE 150
#define TRANSFORMER_VIEW_GRID_CELL_VSIZE 150

typedef struct
{
	teensy_transformer *trans;
	
	lv_obj_t *grid;
	
	lv_coord_t col_dsc[3];
	lv_coord_t *row_dsc;
	
	parameter_widget_linked_list *parameter_widgets;
} transformer_view_str;

int transformer_view_configure(ui_page *page, void *trans);

int init_transformer_view_struct(ui_page *page);
int configure_transformer_view(ui_page *page, void *data);
int init_transformer_view_ui(ui_page *page);
int free_transformer_view_ui(ui_page *page);
int enter_transformer_view(ui_page *page);
int refresh_transformer_view(ui_page *page);

int transformer_view_request_parameter_values(ui_page *page);

extern transformer_view_str transformer_view;

extern const char *transformer_type_labels[];

#endif

#ifndef EM_TRANSFORMER_VIEW_H_
#define EM_TRANSFORMER_VIEW_H_

#define TRANSFORMER_VIEW_GRID_CELL_HSIZE 250
#define TRANSFORMER_VIEW_GRID_CELL_VSIZE 200

#define TRANSFORMER_VIEW_MAX_GROUPS 5

typedef struct
{
	lv_obj_t *container;
	em_parameter_widget_ptr_linked_list *parameter_widgets;
} em_tv_grouping;

typedef struct
{
	em_transformer *trans;
	
	lv_obj_t *container;
	
	lv_obj_t *group_containers[TRANSFORMER_VIEW_MAX_GROUPS];
	
	em_parameter_widget_ptr_linked_list *parameter_widgets;
} em_transformer_view_str;


em_ui_page *make_transformer_view_for(em_transformer *trans);

int transformer_view_configure(em_ui_page *page, void *trans);

int init_transformer_view(em_ui_page *page);
int configure_transformer_view(em_ui_page *page, void *data);
int create_transformer_view_ui(em_ui_page *page);
int free_transformer_view_ui(em_ui_page *page);
int free_transformer_view(em_ui_page *page);
int enter_transformer_view(em_ui_page *page);
int enter_transformer_view_forward(em_ui_page *page);
int enter_transformer_view_back(em_ui_page *page);
int refresh_transformer_view(em_ui_page *page);

int transformer_view_request_parameter_values(em_ui_page *page);

#endif

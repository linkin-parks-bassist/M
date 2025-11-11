#ifndef M_INT_TRANSFORMER_VIEW_H_
#define M_INT_TRANSFORMER_VIEW_H_

#define TRANSFORMER_VIEW_GRID_CELL_HSIZE 250
#define TRANSFORMER_VIEW_GRID_CELL_VSIZE 200

#define TRANSFORMER_VIEW_MAX_GROUPS 5

typedef struct
{
	lv_obj_t *container;
	m_int_parameter_widget_ptr_linked_list *parameter_widgets;
} m_int_tv_grouping;

typedef struct
{
	m_int_transformer *trans;
	
	lv_obj_t *container;
	
	lv_obj_t *group_containers[TRANSFORMER_VIEW_MAX_GROUPS];
	
	m_int_parameter_widget_ptr_linked_list *parameter_widgets;
	
	m_int_ui_page *settings_page;
} m_int_transformer_view_str;


m_int_ui_page *create_transformer_view_for(m_int_transformer *trans);

int transformer_view_configure(m_int_ui_page *page, void *trans);

int init_transformer_view(m_int_ui_page *page);
int configure_transformer_view(m_int_ui_page *page, void *data);
int create_transformer_view_ui(m_int_ui_page *page);
int free_transformer_view_ui(m_int_ui_page *page);
int free_transformer_view(m_int_ui_page *page);
int enter_transformer_view(m_int_ui_page *page);
int enter_transformer_view_forward(m_int_ui_page *page);
int enter_transformer_view_back(m_int_ui_page *page);
int refresh_transformer_view(m_int_ui_page *page);

int transformer_view_request_parameter_values(m_int_ui_page *page);

#endif

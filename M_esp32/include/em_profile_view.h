#ifndef EM_PROFILE_VIEW_H_
#define EM_PROFILE_VIEW_H_

#define PROFILE_VIEW_TRANSFORMER_LIST_WIDTH  500
#define PROFILE_VIEW_TRANSFORMER_LIST_HEIGHT 700

#define PROFILE_VIEW_BUTTON_WIDTH	TRANSFORMER_WIDGET_WIDTH
#define PROFILE_VIEW_BUTTON_HEIGHT	TRANSFORMER_WIDGET_HEIGHT

#define PROFILE_VIEW_BUTTON_V_PAD	20

#define PROFILE_VIEW_BUTTON_BASE_X 		((PROFILE_VIEW_TRANSFORMER_LIST_WIDTH - TRANSFORMER_WIDGET_WIDTH) / 2)
#define PROFILE_VIEW_BUTTON_BASE_Y 		PROFILE_VIEW_BUTTON_V_PAD
#define PROFILE_VIEW_BUTTON_DISTANCE 	(PROFILE_VIEW_BUTTON_HEIGHT + PROFILE_VIEW_BUTTON_V_PAD)

#define PROFILE_VIEW_TW_MIN_Y PROFILE_VIEW_BUTTON_V_PAD
#define PROFILE_VIEW_TW_MAX_Y (PROFILE_VIEW_TRANSFORMER_LIST_HEIGHT - PROFILE_VIEW_BUTTON_DISTANCE)

typedef struct em_profile_view_str
{
	em_profile *profile;
	
	lv_obj_t *transformer_list;
	lv_obj_t *plus_button;
	lv_obj_t *plus_button_label;
	
	em_transformer_widget *add_button;
	
	lv_coord_t plus_button_x;
	lv_coord_t plus_button_y;
	
	int drag_state;
	
	int n_transformer_widgets;
	em_transformer_widget_ptr_linked_list *tws;
} em_profile_view_str;

int init_profile_view(em_ui_page *page);
int configure_profile_view(em_ui_page *page, void *data);
int create_profile_view_ui(em_ui_page *page);
int free_profile_view_ui(em_ui_page *page);
int enter_profile_view(em_ui_page *page);
int enter_profile_view_forward(em_ui_page *page);
int enter_profile_view_back(em_ui_page *page);
int refresh_profile_view(em_ui_page *page);

int profile_view_remove_tw(em_ui_page *page, em_transformer_widget *tw);
int profile_view_recalculate_indices(em_ui_page *page);

int profile_view_append_transformer(em_ui_page *page, em_transformer *trans);
int profile_view_reorder_tw_list(em_ui_page *page);
int profile_view_populate_index_pos_array(em_ui_page *page);
int profile_view_enter_drag_state(em_ui_page *page);
int profile_view_exit_drag_state(em_ui_page *page);


int profile_view_index_y_position(int index);

#endif

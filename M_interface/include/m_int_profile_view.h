#ifndef M_INT_PROFILE_VIEW_H_
#define M_INT_PROFILE_VIEW_H_

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

typedef m_int_transformer_widget_ptr_linked_list transformer_widget_ll;

typedef m_int_transformer_widget_ptr_linked_list tw_ll;

typedef struct m_int_profile_view_str
{
	m_int_profile *profile;
	
	m_int_button *play;
	m_int_button *plus;
	m_int_button *save;
	
	lv_obj_t *menu_button;
	lv_obj_t *menu_button_label;
	
	m_int_transformer_widget *add_button;
	
	lv_coord_t plus_button_x;
	lv_coord_t plus_button_y;
	
	char *name_saved;
	int n_transformer_widgets;
	m_int_transformer_widget_ptr_linked_list *tws;
	
	m_int_ui_page *settings_page;
} m_int_profile_view_str;

m_int_ui_page *create_profile_view_for(m_int_profile *profile);

int init_profile_view(m_int_ui_page *page);
int configure_profile_view(m_int_ui_page *page, void *data);
int create_profile_view_ui(m_int_ui_page *page);
int free_profile_view_ui(m_int_ui_page *page);
int free_profile_view(m_int_ui_page *page);
int enter_profile_view(m_int_ui_page *page);
int enter_profile_view_forward(m_int_ui_page *page);
int enter_profile_view_back(m_int_ui_page *page);
int refresh_profile_view(m_int_ui_page *page);

int profile_view_remove_tw_from_list(m_int_ui_page *page, m_int_transformer_widget *tw);
int profile_view_recalculate_indices(m_int_ui_page *page);

int profile_view_append_transformer(m_int_ui_page *page, m_int_transformer *trans);
int profile_view_reorder_tw_list(m_int_ui_page *page);
int profile_view_populate_index_pos_array(m_int_ui_page *page);

int profile_view_index_y_position(int index);

int profile_view_refresh_play_button(m_int_ui_page *page);
int profile_view_refresh_save_button(m_int_ui_page *page);

int profile_view_change_name(m_int_ui_page *page, char *name);

#endif

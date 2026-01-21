#ifndef M_INT_PROFILE_VIEW_H_
#define M_INT_PROFILE_VIEW_H_

typedef struct m_profile_view_str
{
	m_profile *profile;
	
	m_int_button *play;
	m_int_button *plus;
	m_int_button *save;
	
	lv_obj_t *menu_button;
	lv_obj_t *menu_button_label;
	
	char *name_saved;
	
	m_ui_page *settings_page;
	
	m_active_button_array *array;
	
	m_representation rep;
} m_profile_view_str;

m_ui_page *create_profile_view_for(m_profile *profile);

int init_profile_view		(m_ui_page *page);
int configure_profile_view	(m_ui_page *page, void *data);
int create_profile_view_ui	(m_ui_page *page);
int free_profile_view_ui	(m_ui_page *page);
int free_profile_view		(m_ui_page *page);
int enter_profile_view		(m_ui_page *page);
int enter_profile_view_from	(m_ui_page *page, m_ui_page *prev);
int refresh_profile_view	(m_ui_page *page);

int profile_view_recalculate_indices(m_ui_page *page);

int profile_view_append_transformer(m_ui_page *page, m_transformer *trans);
int profile_view_reorder_tw_list(m_ui_page *page);
int profile_view_populate_index_pos_array(m_ui_page *page);

int profile_view_index_y_position(int index);

int profile_view_refresh_play_button(m_ui_page *page);
int profile_view_refresh_save_button(m_ui_page *page);

int profile_view_change_name(m_ui_page *page, char *name);

int profile_view_set_left_button_mode(m_ui_page *page, int mode);

void profile_view_rep_update(void *representer, void *representee);

#endif

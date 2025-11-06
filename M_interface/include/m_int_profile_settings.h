#ifndef M_INT_PROFILE_SETTINGS_H_
#define M_INT_PROFILE_SETTINGS_H_

typedef struct
{
	m_int_parameter_widget volume_widget;
	m_int_profile *profile;
	
	lv_obj_t *container;
		
	lv_obj_t *default_button;
	lv_obj_t *default_button_label;
	
	lv_obj_t *plus_button;
	lv_obj_t *plus_button_label;
	
	lv_obj_t *save_button;
	lv_obj_t *save_button_label;
} m_profile_settings_str;

int init_profile_settings_page(m_int_ui_page *page);

int configure_profile_settings_page(m_int_ui_page *page, void *data);
int create_profile_settings_page_ui(m_int_ui_page *page);
int free_profile_settings_page_ui(m_int_ui_page *page);
int profile_settings_page_free_all(m_int_ui_page *page);
int enter_profile_settings_page(m_int_ui_page *page);
int enter_profile_settings_page_forward(m_int_ui_page *page);
int enter_profile_settings_page_back(m_int_ui_page *page);
int refresh_profile_settings_page(m_int_ui_page *page);

#endif

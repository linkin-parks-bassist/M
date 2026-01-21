#ifndef M_INT_TRANSFORMER_SETTINGS_H_
#define M_INT_TRANSFORMER_SETTINGS_H_

typedef struct
{
	lv_obj_t *text;
	
	m_setting_widget band_mode;
	
	m_parameter_widget band_lp_cutoff;
	m_parameter_widget band_hp_cutoff;
	
	lv_obj_t *band_control_cont;
} trans_settings_page_str;

int init_transformer_settings_page	   (m_ui_page *page);
int configure_transformer_settings_page(m_ui_page *page, void *data);
int create_transformer_settings_page_ui(m_ui_page *page);
int refresh_transformer_settings_page  (m_ui_page *page);
int free_transformer_settings_page_ui  (m_ui_page *page);
int transformer_settings_page_free_all (m_ui_page *page);

#endif

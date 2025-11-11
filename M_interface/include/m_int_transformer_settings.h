#ifndef M_INT_TRANSFORMER_SETTINGS_H_
#define M_INT_TRANSFORMER_SETTINGS_H_

typedef struct
{
	lv_obj_t *text;
	
	m_int_setting_widget band_mode;
	
	m_int_parameter_widget lp_cutoff_freq;
	m_int_parameter_widget hp_cutoff_freq;
	
	lv_obj_t *band_control_cont;
} trans_settings_page_str;

int init_transformer_settings_page	   (m_int_ui_page *page);
int configure_transformer_settings_page(m_int_ui_page *page, void *data);
int create_transformer_settings_page_ui(m_int_ui_page *page);
int refresh_transformer_settings_page  (m_int_ui_page *page);
int free_transformer_settings_page_ui  (m_int_ui_page *page);
int transformer_settings_page_free_all (m_int_ui_page *page);

#endif

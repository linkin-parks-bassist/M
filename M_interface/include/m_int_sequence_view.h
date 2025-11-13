#ifndef M_INT_SEQUENCE_VIEW_H_
#define M_INT_SEQUENCE_VIEW_H_

typedef struct
{
	m_int_sequence *seq;
	
	m_int_glide_button_array *buttons;
	
	m_int_button *play_button;
	m_int_button *plus_button;
	m_int_button *save_button;
} m_int_sequence_view_str;

int init_sequence_view	   (m_ui_page *page);
int configure_sequence_view(m_ui_page *page, void *data);
int create_sequence_view_ui(m_ui_page *page);
int refresh_sequence_view  (m_ui_page *page);
int free_sequence_view_ui  (m_ui_page *page);
int sequence_view_free_all (m_ui_page *page);

int sequence_view_append_profile(m_ui_page *page, m_profile *seq);

int create_sequence_view_for(m_int_sequence *seq);

#endif

#ifndef M_INT_TRANSFORMER_SELECT_H_
#define M_INT_TRANSFORMER_SELECT_H_

typedef struct
{
	lv_obj_t *button;
	lv_obj_t *label;
	
	uint16_t type;
	char *name;
} m_int_trans_selector_button;

DECLARE_LINKED_PTR_LIST(m_int_trans_selector_button);

typedef struct
{
	lv_obj_t *button_list;
	
	m_int_trans_selector_button_pll *buttons;
	
	int page_offset;
} m_transformer_selector_str;

int init_transformer_selector_button(m_int_trans_selector_button *button, int index);

char *transformer_type_name(uint16_t type);

int init_transformer_selector(m_ui_page *page);
int configure_transformer_selector(m_ui_page *page, void *data);
int create_transformer_selector_ui(m_ui_page *page);
int free_transformer_selector_ui(m_ui_page *page);
int enter_transformer_selector(m_ui_page *page);
int refresh_transformer_selector(m_ui_page *page);

void enter_transformer_selector_cb(lv_event_t *e);

#endif


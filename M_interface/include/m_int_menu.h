#ifndef M_INT_MAIN_MENU_H_
#define M_INT_MAIN_MENU_H_

struct m_int_menu_page_str;

#define MENU_ITEM_TEXT_MAX_LEN 256

#define MENU_ITEM_PAD					0
#define MENU_ITEM_PAGE_LINK 			1
#define MENU_ITEM_PAGE_LINK_INDIRECT 	2
#define MENU_ITEM_CALLBACK_BUTTON 		3
#define MENU_ITEM_PROFILE_LISTING 		4
#define MENU_ITEM_SEQUENCE_LISTING 		5
#define MENU_ITEM_PARAMETER_WIDGET		6

typedef struct m_int_menu_item
{
	int type;
	
	char *text;
	char *desc;
	
	void (*click_cb)(lv_event_t *e);
	void *cb_arg;
	
	void *data;
	
	lv_obj_t *obj;
	lv_obj_t *label;
	lv_obj_t **extra;
	
	lv_timer_t *timer;
	
	m_int_ui_page *linked_page;
	m_int_ui_page **linked_page_indirect;
	
	m_int_ui_page *parent;
	
	int long_pressed;
	void *lp_configure_arg;
} m_int_menu_item;

DECLARE_LINKED_PTR_LIST(m_int_menu_item);

typedef struct m_int_menu_item_ptr_linked_list menu_item_ll;

int init_menu_item(m_int_menu_item *item);

typedef struct m_int_menu_page_str
{
	int type;
	
	char *name;
	
	menu_item_ll *items;
	m_int_ui_page *next_page;
	
	void *data;
	
} m_int_menu_page_str;

int init_menu_item(m_int_menu_item *item);
int create_menu_item_ui(m_int_menu_item *item, lv_obj_t *parent);
int delete_menu_item_ui(m_int_menu_item *item);
int free_menu_item(m_int_menu_item *item);
int refresh_menu_item(m_int_menu_item *item);

int init_menu_page_str(m_int_menu_page_str *str);

int init_menu_page(m_int_ui_page *page);
int configure_menu_page(m_int_ui_page *page, void *data);
int create_menu_page_ui(m_int_ui_page *page);
int free_menu_page_ui(m_int_ui_page *page);
int enter_menu_page(m_int_ui_page *page);
int refresh_menu_page(m_int_ui_page *page);

int menu_page_add_item(m_int_menu_page_str *str, m_int_menu_item *item);

int init_main_menu(m_int_ui_page *page);
int configure_main_menu(m_int_ui_page *page, void *data);

int menu_page_remove_item(m_int_ui_page *page, m_int_menu_item *item);

void enter_main_menu_cb(lv_event_t *e);

#endif

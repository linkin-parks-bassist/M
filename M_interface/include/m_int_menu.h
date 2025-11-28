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
#define MENU_ITEM_DANGER_BUTTON			7

typedef struct m_int_menu_item
{
	int type;
	
	char *text;
	char *desc;
	
	void (*action_cb)(void *arg);
	void (*click_cb)(lv_event_t *e);
	void *cb_arg;
	
	void *data;
	
	lv_obj_t *obj;
	lv_obj_t *label;
	lv_obj_t **extra;
	
	lv_timer_t *timer;
	
	m_ui_page *linked_page;
	m_ui_page **linked_page_indirect;
	
	m_ui_page *parent;
	
	int long_pressed;
	void *lp_configure_arg;
	
	m_representation rep;
} m_int_menu_item;

DECLARE_LINKED_PTR_LIST(m_int_menu_item);

int init_menu_item(m_int_menu_item *item);

typedef struct m_int_menu_page_str
{
	int type;
	
	char *name;
	
	m_int_menu_item_pll *items;
	m_ui_page *next_page;
	
	void *data;
	
} m_int_menu_page_str;

typedef struct m_main_menu_str
{
	lv_obj_t *top_pad;
	lv_obj_t *pw_pad;
	lv_obj_t *gains_container;
	m_parameter_widget input_gain;
	m_parameter_widget output_gain;
	
	m_int_button profiles_button;
	m_int_button sequences_button;
	
	m_danger_button erase_sd_card_button;
} m_main_menu_str;

int init_menu_item(m_int_menu_item *item);
int create_menu_item_ui(m_int_menu_item *item, lv_obj_t *parent);
int delete_menu_item_ui(m_int_menu_item *item);
int free_menu_item(m_int_menu_item *item);
int refresh_menu_item(m_int_menu_item *item);

int init_menu_page_str(m_int_menu_page_str *str);

int init_menu_page(m_ui_page *page);
int configure_menu_page(m_ui_page *page, void *data);
int create_menu_page_ui(m_ui_page *page);
int free_menu_page_ui(m_ui_page *page);
int enter_menu_page(m_ui_page *page);
int refresh_menu_page(m_ui_page *page);

int menu_page_add_item(m_int_menu_page_str *str, m_int_menu_item *item);

int init_main_menu(m_ui_page *page);
int configure_main_menu(m_ui_page *page, void *data);
int create_main_menu_ui(m_ui_page *page);
int enter_main_menu(m_ui_page *page);

int menu_page_remove_item(m_ui_page *page, m_int_menu_item *item);

void enter_main_menu_cb(lv_event_t *e);

m_int_menu_item *create_profile_listing_menu_item(char *text, m_profile *profile, m_ui_page *parent);

void profile_listing_delete_button_cb(lv_event_t *e);
void disappear_profile_listing_delete_button(lv_timer_t *timer);
void menu_item_profile_listing_released_cb(lv_event_t *e);
void menu_item_profile_listing_long_pressed_cb(lv_event_t *e);

int profile_listing_menu_item_refresh_active(struct m_int_menu_item *item);
int profile_listing_menu_item_change_name(struct m_int_menu_item *item, char *name);

#endif

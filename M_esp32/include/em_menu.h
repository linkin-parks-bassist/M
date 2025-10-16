#ifndef EM_MAIN_MENU_H_
#define EM_MAIN_MENU_H_

struct em_menu_page_str;

#define MENU_ITEM_TEXT_MAX_LEN 256

#define MENU_ITEM_PAGE_LINK 			0
#define MENU_ITEM_PAGE_LINK_INDIRECT 	1
#define MENU_ITEM_CALLBACK_BUTTON 		2
#define MENU_ITEM_PROFILE_LISTING 		3

typedef struct em_menu_item
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
	
	em_ui_page *linked_page;
	em_ui_page **linked_page_indirect;
	
	em_ui_page *parent;
	
	int long_pressed;
	void *lp_configure_arg;
} em_menu_item;

DECLARE_LINKED_PTR_LIST(em_menu_item);

typedef struct em_menu_item_ptr_linked_list menu_item_ll;

int init_menu_item(em_menu_item *item);

typedef struct em_menu_page_str
{
	char *name;
	
	menu_item_ll *items;
	em_ui_page *next_page;
	
	lv_obj_t *container;
} em_menu_page_str;

int init_menu_item(em_menu_item *item);
int create_menu_item_ui(em_menu_item *item, lv_obj_t *parent);
int delete_menu_item_ui(em_menu_item *item);
int free_menu_item(em_menu_item *item);

int profile_listing_menu_item_refresh_active(em_menu_item *item, int active);

int init_menu_page_str(em_menu_page_str *str);

int init_menu_page(em_ui_page *page);
int configure_menu_page(em_ui_page *page, void *data);
int create_menu_page_ui(em_ui_page *page);
int free_menu_page_ui(em_ui_page *page);
int enter_menu_page(em_ui_page *page);
int refresh_menu_page(em_ui_page *page);

int init_main_menu(em_ui_page *page);

int init_profile_list(em_ui_page *page);
int configure_profile_list(em_ui_page *page, void *data);
int create_profile_list_ui(em_ui_page *page);
int free_profile_list_ui(em_ui_page *page);
int enter_profile_list(em_ui_page *page);
int refresh_profile_list(em_ui_page *page);

int menu_page_remove_item(em_ui_page *page, em_menu_item *item);

void enter_main_menu_cb(lv_event_t *e);

#endif

#ifndef M_INT_PROFILE_LIST_H_
#define M_INT_PROFILE_LIST_H_

int init_profile_list(m_ui_page *page);
int configure_profile_list(m_ui_page *page, void *data);
int create_profile_list_ui(m_ui_page *page);
int free_profile_list_ui(m_ui_page *page);
int enter_profile_list(m_ui_page *page);
int refresh_profile_list(m_ui_page *page);

struct m_int_menu_item *create_profile_listing_menu_item(char *text, m_profile *profile, m_ui_page *parent);

void profile_listing_delete_button_cb(lv_event_t *e);
void disappear_profile_listing_delete_button(lv_timer_t *timer);
void menu_item_profile_listing_released_cb(lv_event_t *e);
void menu_item_profile_listing_long_pressed_cb(lv_event_t *e);

int profile_list_add_profile(m_ui_page *page, m_profile *profile);

int profile_listing_menu_item_refresh_active(struct m_int_menu_item *item);
int profile_listing_menu_item_change_name(struct m_int_menu_item *item, char *name);

#endif

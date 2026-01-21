#ifndef M_ESP_UI_H_
#define M_ESP_UI_H_

#include "m_linked_list.h"
#include "m_int_button.h"

#ifdef USE_5A
#define DISPLAY_VRES 1280
#define DISPLAY_HRES 720
#else
#define DISPLAY_VRES 1024
#define DISPLAY_HRES 600
#endif

#define TOP_PANEL_HEIGHT 	((int)(0.08 * DISPLAY_VRES))
#define TOP_PANEL_COLOUR 	0x313131

#define GLOBAL_MAIN_TEXT_COLOUR 	0xFFFFFF
#define GLOBAL_MAIN_FONT			&lv_font_montserrat_28

#define GLOBAL_BACKGROUND_COLOUR	0x222222

#define UI_PAGE_TRANSITION_ANIM_MS 0

#define BACK_BUTTON_VSIZE	((int)(0.06 * DISPLAY_VRES))
#define BACK_BUTTON_HSIZE	BACK_BUTTON_HSIZE

#define STANDARD_TOP_PANEL_BUTTON_WIDTH  (TOP_PANEL_HEIGHT * 0.7)
#define STANDARD_TOP_PANEL_BUTTON_HEIGHT (TOP_PANEL_HEIGHT * 0.7)

#define GLOBAL_PAD_WIDTH	((int)(0.02 * DISPLAY_VRES))

#define H_PAD ((int)(0.067 * DISPLAY_HRES))
#define V_PAD ((int)(0.04  * DISPLAY_VRES))

#define STANDARD_YPOS  		(-(int)(0.02 * DISPLAY_VRES))

#define STANDARD_CONTAINER_WIDTH  		((int)(0.83 * DISPLAY_HRES))
#define STANDARD_CONTAINER_HEIGHT 		((int)(0.72 * DISPLAY_VRES))
#define STANDARD_CONTAINER_TALL_HEIGHT 	((int)(0.81 * DISPLAY_VRES))

DECLARE_LINKED_PTR_LIST(lv_obj_t);

#define TOP_PANEL_FLAG_RW_TITLE 0b1

typedef struct
{
	int flags;
	
	lv_obj_t *panel;
	lv_obj_t *title;
	
	m_int_button *lb;
	m_int_button *rb;
	
	lv_obj_t *left_button;
	lv_obj_t *left_button_symbol;
	lv_obj_t *right_button;
	lv_obj_t *right_button_symbol;
	char *text;
	
	lv_event_cb_t rw_save_cb;
	lv_event_cb_t rw_cancel_cb;
} m_ui_page_panel;

m_ui_page_panel *new_panel();

#define MAX_BOTTOM_BUTTONS 6
#define BOTTOM_BUTTON_PADDING GLOBAL_PAD_WIDTH

#define CONTAINER_TYPE_STD 					0
#define CONTAINER_TYPE_STD_BTN_LIST 		1
#define CONTAINER_TYPE_STD_MENU				2

#define M_UI_PAGE_GENERIC			0
#define M_UI_PAGE_MAIN_MENU			1
#define M_UI_PAGE_PROFILE_SETTINGS	2
#define M_UI_PAGE_SEQ_VIEW			3

typedef struct m_ui_page
{
	int type;
	
	lv_obj_t *screen;
	
	int container_type;
	lv_obj_t *container;
	
	m_ui_page_panel *panel;
	
	int (*configure)			(struct m_ui_page *page, void *data);
	int (*create_ui)			(struct m_ui_page *page);
	int (*free_ui)				(struct m_ui_page *page);
	int (*free_all)				(struct m_ui_page *page);
	int (*enter_page)			(struct m_ui_page *page);
	int (*enter_page_from)		(struct m_ui_page *page, struct m_ui_page *prev);
	int (*refresh)				(struct m_ui_page *page);
	
	void *data_struct;
	
	int configured;
	int ui_created;
	
	struct m_ui_page *parent;
	
	m_int_button *bottom_buttons[MAX_BOTTOM_BUTTONS];
} m_ui_page;

void m_create_ui(lv_disp_t *disp);

int init_ui_page(m_ui_page *page);
int init_ui_page_dp(m_ui_page **page);

int configure_ui_page(m_ui_page *page, void *data);
int create_page_ui(m_ui_page *page);

int enter_ui_page(m_ui_page *page);

void enter_ui_page_cb(lv_event_t *e);
int  enter_ui_page_indirect(m_ui_page **_page);
void m_ui_page_return_to_parent(m_ui_page *page);

int m_ui_page_set_background_default(m_ui_page *page);

int m_ui_page_add_child(m_ui_page *page, m_ui_page *child);

int ui_page_create_base_ui(m_ui_page *page);
int ui_page_create_container(m_ui_page *page);
int ui_page_create_bottom_buttons(m_ui_page *page);

int ui_page_add_left_panel_button(m_ui_page *page, const char *label, lv_event_cb_t cb);
int ui_page_add_right_panel_button(m_ui_page *page, const char *label, lv_event_cb_t cb);

int ui_page_add_back_button(m_ui_page *page);
int ui_page_add_parent_button(m_ui_page *page);

int ui_page_set_title(m_ui_page *page, const char *text);

int ui_page_set_title_rw(m_ui_page *page, lv_event_cb_t ok_cb, lv_event_cb_t cancel_cb);

m_int_button *ui_page_add_bottom_button(m_ui_page *page, const char *label, lv_event_cb_t cb);

int create_standard_container(lv_obj_t **cont, lv_obj_t *parent);
int create_standard_container_tall(lv_obj_t **cont, lv_obj_t *parent);
int create_standard_menu_container(lv_obj_t **cont, lv_obj_t *parent);
int create_standard_menu_container_tall(lv_obj_t **cont, lv_obj_t *parent);
int create_standard_button_list(lv_obj_t **cont, lv_obj_t *parent);
int create_standard_button_list_tall(lv_obj_t **cont, lv_obj_t *parent);

int create_standard_button_click(lv_obj_t **obj, lv_obj_t **label, lv_obj_t *parent,
	char *text, lv_event_cb_t click_cb, void *click_cb_arg);
int create_standard_button_click_short(lv_obj_t **obj, lv_obj_t **label, lv_obj_t *parent,
	char *text, lv_event_cb_t click_cb, void *click_cb_arg);
int create_standard_button_long_press_release(lv_obj_t **obj, lv_obj_t **label, lv_obj_t *parent,
	char *text, lv_event_cb_t press_cb, void *press_cb_arg, lv_event_cb_t release_cb, void *release_cb_arg);

int create_panel(m_ui_page *page);
int set_panel_text(m_ui_page *page, const char *text);
int set_panel_text_rw(m_ui_page *page, const char *text);
int create_panel_rw_title(m_ui_page *page, const char *text);
int create_panel_left_button(m_ui_page *page, const char *button_text, lv_event_cb_t cb, void *cb_arg);
int create_panel_right_button(m_ui_page *page, const char *button_text, lv_event_cb_t cb, void *cb_arg);
int create_panel_rw_title_and_left_button(m_ui_page *page, const char *text, const char *left_button_text, lv_event_cb_t left_cb, void *left_cb_arg);
int create_panel_with_back_button(m_ui_page *page);
int create_panel_with_back_and_settings_buttons(m_ui_page *page, m_ui_page *settings_page);
int create_panel_with_back_button_and_right_button(m_ui_page *page, const char *right_button_text, lv_event_cb_t right_cb, void *cb_arg);
int create_panel_with_left_button(m_ui_page *page, const char *left_button_text, lv_event_cb_t left_cb, void *cb_arg);
int create_panel_with_right_button(m_ui_page *page, const char *right_button_text, lv_event_cb_t right_cb, void *cb_arg);
int create_panel_with_back_button_and_page_button(m_ui_page *page, const char *right_button_text, m_ui_page *right_button_page);
int create_panel_with_left_and_right_buttons(m_ui_page *page,
	const char *left_button_text, lv_event_cb_t left_cb, void *left_cb_arg,
	const char *right_button_text, lv_event_cb_t right_cb, void *right_cb_arg);

void spawn_keyboard(lv_obj_t *parent, lv_obj_t *text_area, void (*ok_cb)(lv_event_t*), void *ok_arg, void (*cancel_cb)(lv_event_t*), void *cancel_arg);
void spawn_numerical_keyboard(lv_obj_t *parent, lv_obj_t *text_area, void (*ok_cb)(lv_event_t*), void *ok_arg, void (*cancel_cb)(lv_event_t*), void *cancel_arg);
void hide_keyboard_cb(lv_event_t *e);
void hide_keyboard();

#define PAGE_HISTORY_LEN 64

typedef struct
{
	m_ui_page transformer_selector;
	
	lv_obj_t *backstage;
	
	m_ui_page main_menu;
	//m_ui_page profile_list;
	m_ui_page sequence_list;
	m_ui_page main_sequence_view;
	
	m_ui_page *current_page;
} m_global_pages;

int m_init_global_pages(m_global_pages *pages);

typedef lv_obj_t_pll lv_obj_ll;

void enter_parent_page_cb(lv_event_t *e);

extern lv_obj_t *keyboard;

#endif

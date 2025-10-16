#ifndef M_ESP_UI_H_
#define M_ESP_UI_H_

#define TOP_PANEL_HEIGHT 	LV_PCT(8)
#define TOP_PANEL_COLOUR 	0x313131

#define GLOBAL_MAIN_TEXT_COLOUR 	0xFFFFFF
#define GLOBAL_MAIN_FONT			&lv_font_montserrat_24

#define GLOBAL_BACKGROUND_COLOUR	0x222222

#define UI_PAGE_TRANSITION_ANIM_MS 0

#define BACK_BUTTON_HSIZE	60
#define BACK_BUTTON_VSIZE	60

#define STANDARD_TOP_PANEL_BUTTON_WIDTH  LV_PCT(85)
#define STANDARD_TOP_PANEL_BUTTON_HEIGHT LV_PCT(85)

#define GLOBAL_PAD_WIDTH	15

#define H_PAD 40
#define V_PAD 40

#define STANDARD_CONTAINER_WIDTH  LV_PCT(83)
#define STANDARD_CONTAINER_HEIGHT LV_PCT(68)

#define STANDARD_DEL_BTN_REMAIN_MS 	1000

DECLARE_LINKED_PTR_LIST(lv_obj_t);

typedef struct
{
	lv_obj_t *panel;
	lv_obj_t *title;
	lv_obj_t *back_button;
	lv_obj_t *back_button_symbol;
	lv_obj_t *menu_button;
	lv_obj_t *menu_button_symbol;
	lv_obj_t **spacers;
	char *title_text
} em_ui_page_top_panel;

typedef struct em_ui_page
{
	lv_obj_t *screen;
	
	em_ui_page_top_panel *top_panel;
	
	int (*configure)			(struct em_ui_page *page, void *data);
	int (*create_ui)			(struct em_ui_page *page);
	int (*free_ui)				(struct em_ui_page *page);
	int (*free_all)				(struct em_ui_page *page);
	int (*enter_page)			(struct em_ui_page *page);
	int (*enter_page_forward)	(struct em_ui_page *page);
	int (*enter_page_back)		(struct em_ui_page *page);
	int (*refresh)				(struct em_ui_page *page);
	
	void *data_struct;
	
	int configured;
	int ui_created;
	
	struct em_ui_page *parent;
} em_ui_page;

void make_ui(lv_disp_t *disp);

int init_ui_page(em_ui_page *page);
int init_ui_page_dp(em_ui_page **page);

int configure_ui_page(em_ui_page *page, void *data);
int create_page_ui(em_ui_page *page);

int enter_ui_page(em_ui_page *page);
int enter_ui_page_forward(em_ui_page *page);

void enter_ui_page_cb(lv_event_t *e);
int enter_ui_page_indirect(em_ui_page **_page);
void em_ui_page_return_to_parent(em_ui_page *page);

int em_ui_page_set_background_default(em_ui_page *page);

int em_ui_page_add_child(em_ui_page *page, em_ui_page *child);

int create_standard_container(lv_obj_t **cont, lv_obj_t *parent);
int create_standard_button_list(lv_obj_t **cont, lv_obj_t *parent);

int create_standard_button_click(lv_obj_t **obj, lv_obj_t **label, lv_obj_t *parent,
	char *text, lv_event_cb_t click_cb, void *click_cb_arg);
int create_standard_button_long_press_release(lv_obj_t **obj, lv_obj_t **label, lv_obj_t *parent,
	char *text, lv_event_cb_t press_cb, void *press_cb_arg, lv_event_cb_t release_cb, void *release_cb_arg);

int create_top_panel(em_ui_page *page, char *title_text);
int create_top_panel_rw_title(em_ui_page *page, char *title_text);
int create_top_panel_rw_title_and_left_button(em_ui_page *page, char *title_text, lv_event_cb_t menu_cb);
int create_top_panel_with_back_button(em_ui_page *page, const char *title_text, lv_event_cb_t back_cb);

void spawn_keyboard(lv_obj_t *parent, lv_obj_t *text_area, void (*ok_cb)(lv_event_t*), void *ok_arg, void (*cancel_cb)(lv_event_t*), void *cancel_arg);
void hide_keyboard_cb(lv_event_t *e);
void hide_keyboard();

typedef struct
{
	em_ui_page transformer_selector;
	
	lv_obj_t *keyboard;
	
	em_ui_page *main_menu;
	em_ui_page *prev_page;
} em_ui_context;

typedef lv_obj_t_ptr_linked_list lv_obj_ll;

#endif

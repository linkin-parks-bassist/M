#ifndef M_ESP_UI_H_
#define M_ESP_UI_H_

#define TOP_PANEL_HEIGHT 	82
#define TOP_PANEL_COLOUR 	0x313131

#define GLOBAL_MAIN_TEXT_COLOUR 	0xFFFFFF
#define GLOBAL_MAIN_FONT			&manrope_24 //&lv_font_montserrat_24

#define GLOBAL_BACKGROUND_COLOUR	0x222222

#define UI_PAGE_TRANSITION_ANIM_MS 0

#define BACK_BUTTON_HSIZE	60
#define BACK_BUTTON_VSIZE	60

#define STANDARD_TOP_PANEL_BUTTON_WIDTH  (TOP_PANEL_HEIGHT * 0.7)
#define STANDARD_TOP_PANEL_BUTTON_HEIGHT (TOP_PANEL_HEIGHT * 0.7)

#define GLOBAL_PAD_WIDTH	15

#define H_PAD 40
#define V_PAD 40

#define STANDARD_YPOS  		-20

#define STANDARD_CONTAINER_WIDTH  		500
#define STANDARD_CONTAINER_HEIGHT 		740
#define STANDARD_CONTAINER_TALL_HEIGHT 	830

#define STANDARD_DEL_BTN_REMAIN_MS 	1000

#define STANDARD_BUTTON_HEIGHT 70
#define STANDARD_BUTTON_SHORT_HEIGHT 45

DECLARE_LINKED_PTR_LIST(lv_obj_t);

typedef struct m_int_button
{
	lv_obj_t *obj;
	lv_obj_t *label;
	char *label_text;
	
	lv_event_cb_t clicked_cb;
	void *clicked_cb_arg;
	
	lv_event_cb_t pressing_cb;
	void *pressing_cb_arg;
	
	lv_event_cb_t long_pressed_cb;
	void *long_pressed_cb_arg;
	
	lv_event_cb_t released_cb;
	void *released_cb_arg;
	
	int long_pressed;
	int clickable;
	
	int *hider;
	
	int draggable_x;
	int draggable_y;
	
	int width;
	int height;
	
	int n_sub_buttoms;
	
	lv_align_t alignment;
	struct m_int_button **sub_buttons;
} m_int_button;

int init_button(m_int_button *button);
m_int_button *new_button(const char *label);

int create_button_ui(m_int_button *button, lv_obj_t *parent);

int button_set_clicked_cb	  (m_int_button *button, lv_event_cb_t cb, void *cb_arg);
int button_set_pressing_cb	  (m_int_button *button, lv_event_cb_t cb, void *cb_arg);
int button_set_long_pressed_cb(m_int_button *button, lv_event_cb_t cb, void *cb_arg);
int button_set_released_cb	  (m_int_button *button, lv_event_cb_t cb, void *cb_arg);

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
#define BOTTOM_BUTTON_PADDING 20

#define CONTAINER_TYPE_STD 					0
#define CONTAINER_TYPE_STD_BTN_LIST 		1
#define CONTAINER_TYPE_STD_MENU				2

typedef struct m_ui_page
{
	lv_obj_t *screen;
	
	int container_type;
	lv_obj_t *container;
	
	m_ui_page_panel *panel;
	
	int (*configure)			(struct m_ui_page *page, void *data);
	int (*create_ui)			(struct m_ui_page *page);
	int (*free_ui)				(struct m_ui_page *page);
	int (*free_all)				(struct m_ui_page *page);
	int (*enter_page)			(struct m_ui_page *page);
	int (*enter_page_forward)	(struct m_ui_page *page);
	int (*enter_page_back)		(struct m_ui_page *page);
	int (*refresh)				(struct m_ui_page *page);
	
	void *data_struct;
	
	int configured;
	int ui_created;
	
	struct m_ui_page *parent;
	
	m_int_button *bottom_buttons[MAX_BOTTOM_BUTTONS];
} m_ui_page;

void create_ui(lv_disp_t *disp);

int init_ui_page(m_ui_page *page);
int init_ui_page_dp(m_ui_page **page);

int configure_ui_page(m_ui_page *page, void *data);
int create_page_ui(m_ui_page *page);

int enter_ui_page(m_ui_page *page);

void enter_ui_page_cb(lv_event_t *e);
int enter_ui_page_indirect(m_ui_page **_page);
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

void spawn_keyboard(lv_obj_t *parent, lv_obj_t *text_area, void (*ok_cb)(lv_event_t*), void *ok_arg, void (*cancel_cb)(lv_event_t*), void *cancel_arg);
void hide_keyboard_cb(lv_event_t *e);
void hide_keyboard();

#define PAGE_HISTORY_LEN 64

typedef struct
{
	m_ui_page transformer_selector;
	
	lv_obj_t *backstage;
	
	lv_obj_t *keyboard;
	
	m_ui_page *main_menu;
	m_ui_page *prev_page;
	m_ui_page *profile_list;
	m_ui_page *sequence_list;
} m_int_ui_context;

typedef lv_obj_t_pll lv_obj_ll;

int init_ui_context(m_int_ui_context *cxt);

void enter_parent_page_cb(lv_event_t *e);

#endif

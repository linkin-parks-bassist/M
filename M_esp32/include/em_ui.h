#ifndef M_ESP_UI_H_
#define M_ESP_UI_H_

#define TOP_PANEL_HEIGHT 	80
#define TOP_PANEL_COLOUR 	0x313131

#define GLOBAL_MAIN_TEXT_COLOUR 	0xFFFFFF
#define GLOBAL_MAIN_FONT			&lv_font_montserrat_24

#define GLOBAL_BACKGROUND_COLOUR	0x222222

#define UI_PAGE_TRANSITION_ANIM_MS 0

#define BACK_BUTTON_HSIZE	60
#define BACK_BUTTON_VSIZE	60

#define GLOBAL_PAD_WIDTH	15

#define H_PAD 40
#define V_PAD 40

DECLARE_LINKED_PTR_LIST(lv_obj_t);

typedef struct
{
	lv_obj_t *panel;
	lv_obj_t *title;
	lv_obj_t *back_button;
	lv_obj_t *back_button_symbol;
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
	
	struct em_ui_page *parent;
} em_ui_page;

void make_ui(lv_disp_t *disp);

int init_ui_page(em_ui_page *page);
int init_ui_page_dp(em_ui_page **page);

int enter_ui_page(em_ui_page *page);
int enter_ui_page_forward(em_ui_page *page);

void enter_ui_page_cb(lv_event_t *e);
void em_ui_page_return_to_parent(em_ui_page *page);

int em_ui_page_set_background_default(em_ui_page *page);

int em_ui_page_add_child(em_ui_page *page, em_ui_page *child);

int create_top_panel(em_ui_page *page, char *title_text);
int create_top_panel_with_back_button(em_ui_page *page, const char *title_text, lv_event_cb_t back_cb);

typedef struct
{
	em_ui_page transformer_selector;
} em_ui_context;

#endif

#ifndef M_ESP_UI_H_
#define M_ESP_UI_H_

#define TOP_PANEL_HEIGHT 	80
#define TOP_PANEL_COLOUR 	0x313131

#define GLOBAL_MAIN_TEXT_COLOUR 	0xFFFFFF
#define GLOBAL_MAIN_FONT			&lv_font_montserrat_24

#define GLOBAL_BACKGROUND_COLOUR	0x222222

#define BACK_BUTTON_HSIZE	60
#define BACK_BUTTON_VSIZE	60

#define GLOBAL_PAD_WIDTH	15

#include "em_linked_list.h"

DECLARE_LINKED_PTR_LIST(lv_obj_t);

typedef struct
{
	lv_obj_t *panel;
	lv_obj_t *title;
	lv_obj_t *back_button;
	lv_obj_t *back_button_symbol;
	lv_obj_t **spacers;
	char *title_text
} ui_page_top_panel;

typedef struct ui_page
{
	lv_obj_t *screen;
	
	ui_page_top_panel *top_panel;
	
	int (*init)			(struct ui_page *page);
	int (*configure)	(struct ui_page *page, void *data);
	int (*create_ui)	(struct ui_page *page);
	int (*free_ui)		(struct ui_page *page);
	int (*enter_page)	(struct ui_page *page);
	int (*refresh)		(struct ui_page *page);
	
	void *data_struct;
	
	struct ui_page *parent;
} ui_page;

void make_ui(lv_disp_t *disp);

int init_ui_page(ui_page *page);

int enter_ui_page(ui_page *page);
void ui_page_return_to_parent(ui_page *page);

int ui_page_set_background_default(ui_page *page);

int ui_page_add_child(ui_page *page, ui_page *child);

int create_top_panel(ui_page *page, char *title_text);
int create_top_panel_with_back_button(ui_page *page, const char *title_text, lv_event_cb_t back_cb);

#endif

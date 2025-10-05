#ifndef PROFILE_VIEW_H_
#define PROFILE_VIEW_H_

#include "em_linked_list.h"

typedef struct
{
	lv_obj_t *widget;
	lv_obj_t *label;
	
	const char *label_text;
	
	uint16_t profile_id;
	uint16_t transformer_id;
	
	teensy_transformer *trans;
} transformer_widget;

DECLARE_LINKED_LIST(transformer_widget);

typedef struct
{
	teensy_profile *profile;
	
	lv_obj_t *button_list;
	
	transformer_widget_linked_list *transformer_widgets;
} profile_view_str;

void create_profile_view();

int init_transformer_widget(transformer_widget *tw, profile_view_str *parent, teensy_transformer *trans);

void initialise_profile_view_struct(ui_page *page);
void initialise_profile_view_ui(ui_page *page);
void free_profile_view_ui(ui_page *page);
void enter_profile_view(ui_page *page);
void refresh_profile_view_(ui_page *page);

#endif

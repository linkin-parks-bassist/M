#include "em.h"

IMPLEMENT_LINKED_PTR_LIST(lv_obj_t);

int init_ui_context(em_ui_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	init_ui_page(&cxt->transformer_selector);
	
	cxt->transformer_selector.create_ui = create_transformer_selector_ui;
	cxt->transformer_selector.enter_page = enter_transformer_selector;
	
	init_transformer_selector(&cxt->transformer_selector);
	configure_transformer_selector(&cxt->transformer_selector, &global_cxt.profiles[0]);
	cxt->transformer_selector.create_ui(&cxt->transformer_selector);
	
	global_cxt.profiles[0].view_page = malloc(sizeof(em_ui_page));
	
	init_ui_page(global_cxt.profiles[0].view_page);
	
	global_cxt.profiles[0].view_page->configure 	= configure_profile_view;
	global_cxt.profiles[0].view_page->create_ui 	= create_profile_view_ui;
	global_cxt.profiles[0].view_page->enter_page = enter_profile_view;
	global_cxt.profiles[0].view_page->refresh 	= refresh_profile_view;
	
	init_profile_view(global_cxt.profiles[0].view_page);
	configure_profile_view(global_cxt.profiles[0].view_page, &global_cxt.profiles[0]);
	create_profile_view_ui(global_cxt.profiles[0].view_page);
	
	return NO_ERROR;
}

int em_ui_page_set_background_default(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->screen)
		return ERR_BAD_ARGS;
	
	lv_obj_set_style_bg_color(page->screen, lv_color_hex(GLOBAL_BACKGROUND_COLOUR), 0);
	lv_obj_set_style_bg_opa(page->screen, LV_OPA_COVER, 0);
	
	return NO_ERROR;
}

void free_test_page_ui(em_ui_page *page)
{
	
}

void enter_test_page(em_ui_page *page)
{
	lv_scr_load(page->screen);
}

void refresh_test_page(em_ui_page *page)
{
	
}

void make_ui(lv_disp_t *disp)
{
	printf("Setting up UI...\n");
	
	init_ui_context(&global_cxt.ui_cxt);
	
	enter_profile_view(global_cxt.profiles[0].view_page);
}

static lv_style_t bg_style;

static void screen_load_cb(lv_event_t * e)
{
    lv_obj_t *scr = lv_event_get_target(e);
    lv_obj_add_style(scr, &bg_style, LV_PART_MAIN);
}

void init_global_bg(lv_disp_t *disp)
{
    lv_style_init(&bg_style);
    lv_style_set_bg_color(&bg_style, lv_color_black());
    lv_style_set_bg_opa(&bg_style, LV_OPA_COVER);

    lv_obj_add_style(lv_scr_act(), &bg_style, LV_PART_MAIN);
    
    // Attach once: every time a new screen is loaded on this display
    lv_disp_get_scr_act(disp); // make sure disp is valid
    lv_disp_set_bg_color(disp, lv_palette_darken(LV_PALETTE_GREY, 3)); // initial screen
    lv_obj_add_event_cb(lv_disp_get_scr_act(disp),
                        screen_load_cb,
                        LV_EVENT_SCREEN_LOAD_START,
                        NULL);
}

int init_ui_page(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	page->screen 			= NULL;
	page->top_panel			= NULL;
	
	page->configure			= NULL;
	page->create_ui 		= NULL;
	page->free_ui 			= NULL;
	page->enter_page 		= NULL;
	page->refresh			= NULL;
	
	page->data_struct 		= NULL;
	page->parent	 		= NULL;
	
	return NO_ERROR;
}

em_ui_page *create_ui_page()
{
	em_ui_page *res = malloc(sizeof(em_ui_page));
	
	if (!res)
		return NULL;
	
	init_ui_page(res);
	
	return res;
}

int enter_ui_page_forward(em_ui_page *page)
{
	printf("enter ui page...\n");
	
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->screen)
		return ERR_BAD_ARGS;
	
	if (page->enter_page_forward)
		page->enter_page_forward(page);
	else
		lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, false);
	
	return NO_ERROR;
}

int enter_ui_page(em_ui_page *page)
{
	printf("enter ui page...\n");
	
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->screen)
		return ERR_BAD_ARGS;
	
	if (page->enter_page_back)
		page->enter_page_back(page);
	else
		lv_scr_load(page->screen);
	
	return NO_ERROR;
}

int enter_ui_page_indirect(em_ui_page **_page)
{
	printf("enter ui page indirect...\n");
	
	if (!_page)
		return ERR_NULL_PTR;
	
	em_ui_page *page = *_page;
	
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->screen)
		return ERR_BAD_ARGS;
	
	if (page->enter_page)
		page->enter_page(page);
	else
		lv_scr_load(page->screen);
	
	return NO_ERROR;
}

int enter_ui_page_indirect_forward(em_ui_page **_page)
{
	printf("enter ui page indirect...\n");
	
	if (!_page)
		return ERR_NULL_PTR;
	
	em_ui_page *page = *_page;
	
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->screen)
		return ERR_BAD_ARGS;
	
	if (page->enter_page)
		page->enter_page(page);
	else
		lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, false);
	
	return NO_ERROR;
}

int enter_ui_page_indirect_back(em_ui_page **_page)
{
	printf("enter ui page indirect...\n");
	
	if (!_page)
		return ERR_NULL_PTR;
	
	em_ui_page *page = *_page;
	
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->screen)
		return ERR_BAD_ARGS;
	
	if (page->enter_page_back)
		page->enter_page_back(page);
	else if (page->enter_page)
		page->enter_page(page);
	else
		lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 30, 0, false);
	
	return NO_ERROR;
}

void enter_ui_page_cb(lv_event_t *e)
{
	printf("enter ui page callback triggered\n");
	em_ui_page **_page = (em_ui_page**)lv_event_get_user_data(e);
	enter_ui_page_indirect(_page);
}

void enter_ui_page_forward_cb(lv_event_t *e)
{
	printf("enter ui page callback triggered\n");
	em_ui_page **_page = (em_ui_page**)lv_event_get_user_data(e);
	enter_ui_page_indirect_forward(_page);
}

void enter_ui_page_back_cb(lv_event_t *e)
{
	printf("enter ui page callback triggered\n");
	em_ui_page **_page = (em_ui_page**)lv_event_get_user_data(e);
	enter_ui_page_indirect_back(_page);
}

void em_ui_page_return_to_parent(em_ui_page *page)
{
	if (!page)
		return;
	
	if (!page->parent)
		return;
	
	if (page->parent->enter_page)
		page->parent->enter_page(page->parent);
	else
		enter_ui_page(page->parent);
}

int create_top_panel(em_ui_page *page, char *title_text)
{
	if (!page)
		return ERR_NULL_PTR;
	
	page->top_panel = malloc(sizeof(em_ui_page_top_panel));
	
	if (!page->top_panel)
		return ERR_ALLOC_FAIL;
	
	// The panel itself
    page->top_panel->panel = lv_obj_create(page->screen);
    
    lv_obj_set_size				 (page->top_panel->panel, LV_PCT(100), TOP_PANEL_HEIGHT);
    lv_obj_set_style_bg_color	 (page->top_panel->panel, lv_color_hex(TOP_PANEL_COLOUR), 0);
    lv_obj_set_style_pad_all	 (page->top_panel->panel, 0, 0);
    lv_obj_set_style_border_width(page->top_panel->panel, 0, 0);
    lv_obj_set_style_radius		 (page->top_panel->panel, 0, 0);
    lv_obj_set_style_pad_left	 (page->top_panel->panel, 8, 0);
	lv_obj_set_style_pad_right	 (page->top_panel->panel, 8, 0);
    lv_obj_set_flex_flow		 (page->top_panel->panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align		 (page->top_panel->panel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    page->top_panel->title_text = title_text;
    
    if (title_text)
    {
		page->top_panel->title = lv_label_create(page->top_panel->panel);
		lv_label_set_text(page->top_panel->title, page->top_panel->title_text);
		
		lv_obj_set_style_text_color(page->top_panel->title, lv_color_hex(GLOBAL_MAIN_TEXT_COLOUR), 0);
		lv_obj_set_style_text_font(page->top_panel->title, GLOBAL_MAIN_FONT, 0);
		
		lv_obj_set_flex_grow(page->top_panel->title, 1);
		lv_obj_set_style_text_align(page->top_panel->title, LV_TEXT_ALIGN_CENTER, 0);
	}

    return NO_ERROR;
}

int create_top_panel_with_back_button(em_ui_page *page, const char *title_text, lv_event_cb_t back_cb)
{
	page->top_panel = malloc(sizeof(em_ui_page_top_panel));
	
	if (!page->top_panel)
		return ERR_ALLOC_FAIL;
	
	// The panel itself
    page->top_panel->panel = lv_obj_create(page->screen);
    
    lv_obj_set_size				 (page->top_panel->panel, LV_PCT(100), TOP_PANEL_HEIGHT);
    lv_obj_set_style_bg_color	 (page->top_panel->panel, lv_color_hex(TOP_PANEL_COLOUR), 0);
    lv_obj_set_style_pad_all	 (page->top_panel->panel, 0, 0);
    lv_obj_set_style_border_width(page->top_panel->panel, 0, 0);
    lv_obj_set_style_radius		 (page->top_panel->panel, 0, 0);
    lv_obj_set_style_pad_left	 (page->top_panel->panel, GLOBAL_PAD_WIDTH, 0);
	lv_obj_set_style_pad_right	 (page->top_panel->panel, GLOBAL_PAD_WIDTH, 0);
    lv_obj_set_flex_flow		 (page->top_panel->panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align		 (page->top_panel->panel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

	// Back button
    page->top_panel->back_button = lv_btn_create(page->top_panel->panel);
    lv_obj_set_size(page->top_panel->back_button, 40, 40);
    
    page->top_panel->back_button_symbol = lv_label_create(page->top_panel->back_button);
    lv_label_set_text(page->top_panel->back_button_symbol, LV_SYMBOL_LEFT);
    lv_obj_center(page->top_panel->back_button_symbol);
    
    if (back_cb)
    {
		printf("'back' callback provided; connecting...\n");
		lv_obj_add_event_cb(page->top_panel->back_button, back_cb, LV_EVENT_CLICKED, page);
	}
	else
	{
		printf("No 'back' callback provided; assigning default...\n");
		lv_obj_add_event_cb(page->top_panel->back_button, enter_ui_page_back_cb, LV_EVENT_CLICKED, &page->parent);
	}

    page->top_panel->title_text = title_text;
    
    if (title_text)
    {
		page->top_panel->title = lv_label_create(page->top_panel->panel);
		lv_label_set_text(page->top_panel->title, page->top_panel->title_text);
		
		lv_obj_set_style_text_color(page->top_panel->title, lv_color_hex(GLOBAL_MAIN_TEXT_COLOUR), 0);
		lv_obj_set_style_text_font(page->top_panel->title, GLOBAL_MAIN_FONT, 0);
		
		lv_obj_set_flex_grow(page->top_panel->title, 1);
		lv_obj_set_style_text_align(page->top_panel->title, LV_TEXT_ALIGN_CENTER, 0);
	}
	
	page->top_panel->spacers = malloc(sizeof(lv_obj_t*));
	*(page->top_panel->spacers) = lv_obj_create(page->top_panel->panel);
	
	lv_obj_set_size(*(page->top_panel->spacers), BACK_BUTTON_HSIZE, BACK_BUTTON_VSIZE);
	lv_obj_clear_flag(*(page->top_panel->spacers), LV_OBJ_FLAG_CLICKABLE);
	lv_obj_set_style_bg_opa(*(page->top_panel->spacers), LV_OPA_TRANSP, 0); 

    return NO_ERROR;
}


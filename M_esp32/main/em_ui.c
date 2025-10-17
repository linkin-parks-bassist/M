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
	configure_transformer_selector(&cxt->transformer_selector, global_cxt.active_profile);
	cxt->transformer_selector.create_ui(&cxt->transformer_selector);
	
	make_profile_view_for(global_cxt.active_profile);
	
	if (global_cxt.active_profile)
		create_profile_view_ui(global_cxt.active_profile->view_page);
	
	cxt->main_menu = malloc(sizeof(em_ui_page));
	
	init_main_menu(cxt->main_menu);
	configure_ui_page(cxt->main_menu, global_cxt.active_profile->view_page);
	create_page_ui(cxt->main_menu);
	
	cxt->prev_page = NULL;
	
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

void make_ui(lv_disp_t *disp)
{
	//printf("Setting up UI...\n");
	
	init_ui_context(&global_cxt.ui_cxt);
	em_profile_set_active(global_cxt.active_profile);
	enter_ui_page(global_cxt.active_profile->view_page);
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
	page->free_all 			= NULL;
	page->enter_page 		= NULL;
	page->refresh			= NULL;
	
	page->data_struct 		= NULL;
	page->parent	 		= NULL;
	
	page->configured = 0;
	page->ui_created = 0;
	
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

int configure_ui_page(em_ui_page *page, void *data)
{
	//printf("configure_ui_page\n");
	if (!page)
		return ERR_NULL_PTR;
	
	if (page->configured)
	{
		//printf("page already configured\n");
		return NO_ERROR;
	}
	
	if (page->configure)
	{
		//printf("Function pointer exists\n");
		page->configure(page, data);
	}
	else
	{
		//printf("No configure function pointer!\n");
		return ERR_BAD_ARGS;
	}
	
	page->configured = 1;
	
	//printf("configure_ui_page done\n");
	return NO_ERROR;
}

int create_page_ui(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	if (page->ui_created)
		return NO_ERROR;
	
	if (page->create_ui)
		page->create_ui(page);
	else
		return ERR_BAD_ARGS;
	
	page->ui_created = 1;
	
	return NO_ERROR;
}

int enter_ui_page_forward(em_ui_page *page)
{
	//printf("enter ui page... %p\n", page);
	
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->screen)
		return ERR_BAD_ARGS;
	
	if (page->enter_page_forward)
		page->enter_page_forward(page);
	else
		lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 100, 0, false);
	
	return NO_ERROR;
}

int enter_ui_page(em_ui_page *page)
{
	//printf("enter ui page...\n");
	
	if (!page)
	{
		//printf("Error! No page!\n");
		return ERR_NULL_PTR;
	}
	
	if (!page->ui_created)
	{
		if (!page->configured)
		{
			//printf("Error! Page is unconfigured\n");
			return ERR_BAD_ARGS;
		}
		
		if (!page->create_ui)
		{
			//printf("Error! Page has no UI, and no create_ui function pointer!\n");
			return ERR_BAD_ARGS;
		}
		
		//printf("Page has not created its UI yet. Creating now...\n");
		page->create_ui(page);
	}
	
	if (page->enter_page)
	{
		page->enter_page(page);
	}
	else
	{
		if (!page->screen)
		{
			//printf("Error! Page has no screen!\n");
			//return ERR_BAD_ARGS;
		}
		lv_scr_load(page->screen);
	}
	
	return NO_ERROR;
}

int enter_ui_page_back(em_ui_page *page)
{
	//printf("enter ui page...\n");
	
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->screen)
		return ERR_BAD_ARGS;
	
	if (page->enter_page_back)
		page->enter_page_back(page);
	else
		lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	return NO_ERROR;
}

int enter_ui_page_indirect(em_ui_page **_page)
{
	//printf("enter ui page indirect...\n");
	
	if (!_page)
		return ERR_NULL_PTR;
	
	enter_ui_page(*_page);
	
	return NO_ERROR;
}

int enter_ui_page_indirect_forward(em_ui_page **_page)
{
	//printf("enter ui page indirect...\n");
	
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
		lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	return NO_ERROR;
}

int enter_ui_page_indirect_back(em_ui_page **_page)
{
	//printf("enter ui page indirect...\n");
	
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
		lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, UI_PAGE_TRANSITION_ANIM_MS, 0, false);
	
	return NO_ERROR;
}

void enter_ui_page_cb(lv_event_t *e)
{
	//printf("enter ui page callback triggered\n");
	em_ui_page **_page = (em_ui_page**)lv_event_get_user_data(e);
	enter_ui_page_indirect(_page);
}

void enter_ui_page_forward_cb(lv_event_t *e)
{
	//printf("enter ui page callback triggered\n");
	em_ui_page **_page = (em_ui_page**)lv_event_get_user_data(e);
	enter_ui_page_indirect_forward(_page);
}

void enter_ui_page_back_cb(lv_event_t *e)
{
	//printf("enter ui page callback triggered\n");
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
	else
	{
		page->top_panel->title = NULL;
	}

    return NO_ERROR;
}

int create_top_panel_rw_title(em_ui_page *page, char *title_text)
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
    
    
	page->top_panel->title = lv_textarea_create(page->top_panel->panel);
	lv_textarea_set_text(page->top_panel->title, page->top_panel->title_text);
	
	lv_obj_set_style_text_color(page->top_panel->title, lv_color_hex(GLOBAL_MAIN_TEXT_COLOUR), 0);
	lv_obj_set_style_text_font(page->top_panel->title, GLOBAL_MAIN_FONT, 0);
	
	lv_obj_set_style_border_width(page->top_panel->title, 0, 0);
    lv_obj_set_style_bg_color	 (page->top_panel->title, lv_color_hex(TOP_PANEL_COLOUR), 0);
	lv_obj_set_size(page->top_panel->title, LV_SIZE_CONTENT, TOP_PANEL_HEIGHT * 0.7);
	lv_textarea_set_one_line(page->top_panel->title, true);
	lv_textarea_set_align(page->top_panel->title, LV_TEXT_ALIGN_CENTER);
	lv_obj_center(page->top_panel->title);

    return NO_ERROR;
}

int create_top_panel_rw_title_and_left_button(em_ui_page *page, char *title_text, lv_event_cb_t menu_cb)
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
    //lv_obj_set_flex_flow		 (page->top_panel->panel, LV_FLEX_FLOW_ROW);
    //lv_obj_set_flex_align		 (page->top_panel->panel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    page->top_panel->title_text = title_text;
    
    // menu button
    page->top_panel->menu_button = lv_btn_create(page->top_panel->panel);
    lv_obj_set_size(page->top_panel->menu_button, 40, 40);
    lv_obj_align_to(page->top_panel->menu_button, page->top_panel->panel, LV_ALIGN_LEFT_MID, 0, 0);
    
    page->top_panel->menu_button_symbol = lv_label_create(page->top_panel->menu_button);
    lv_label_set_text(page->top_panel->menu_button_symbol, LV_SYMBOL_SETTINGS);
    lv_obj_center(page->top_panel->menu_button_symbol);
    
	page->top_panel->title = lv_textarea_create(page->top_panel->panel);
	lv_textarea_set_text(page->top_panel->title, page->top_panel->title_text);
	
	lv_obj_set_style_text_color(page->top_panel->title, lv_color_hex(GLOBAL_MAIN_TEXT_COLOUR), 0);
	lv_obj_set_style_text_font(page->top_panel->title, GLOBAL_MAIN_FONT, 0);
	
	lv_obj_set_style_border_width(page->top_panel->title, 0, 0);
    lv_obj_set_style_bg_color	 (page->top_panel->title, lv_color_hex(TOP_PANEL_COLOUR), 0);
	lv_obj_set_size(page->top_panel->title, LV_SIZE_CONTENT, TOP_PANEL_HEIGHT * 0.7);
	lv_textarea_set_one_line(page->top_panel->title, true);
	lv_textarea_set_align(page->top_panel->title, LV_TEXT_ALIGN_CENTER);
	lv_obj_center(page->top_panel->title);
    
    if (menu_cb)
    {
		//printf("'menu' callmenu provided; connecting...\n");
		lv_obj_add_event_cb(page->top_panel->menu_button, menu_cb, LV_EVENT_CLICKED, page);
	}
	else
	{
		//printf("No 'menu' callmenu provided; assigning default...\n");
		lv_obj_add_event_cb(page->top_panel->menu_button, menu_cb, LV_EVENT_CLICKED, page);
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
		//printf("'back' callback provided; connecting...\n");
		lv_obj_add_event_cb(page->top_panel->back_button, back_cb, LV_EVENT_CLICKED, page);
	}
	else
	{
		//printf("No 'back' callback provided; assigning default...\n");
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
	else
	{
		page->top_panel->title = NULL;
	}
	
	page->top_panel->spacers = malloc(sizeof(lv_obj_t*));
	*(page->top_panel->spacers) = lv_obj_create(page->top_panel->panel);
	
	lv_obj_set_size(*(page->top_panel->spacers), BACK_BUTTON_HSIZE, BACK_BUTTON_VSIZE);
	lv_obj_clear_flag(*(page->top_panel->spacers), LV_OBJ_FLAG_CLICKABLE);
	lv_obj_set_style_bg_opa(*(page->top_panel->spacers), LV_OPA_TRANSP, 0); 

    return NO_ERROR;
}

void spawn_keyboard(lv_obj_t *parent, lv_obj_t *text_area, void (*ok_cb)(lv_event_t*), void *ok_arg, void (*cancel_cb)(lv_event_t*), void *cancel_arg)
{
	if (!global_cxt.ui_cxt.keyboard)
	{
		global_cxt.ui_cxt.keyboard = lv_keyboard_create(parent);
		lv_obj_set_size(global_cxt.ui_cxt.keyboard, LV_PCT(100), LV_PCT(33));
		lv_obj_add_flag(global_cxt.ui_cxt.keyboard, LV_OBJ_FLAG_HIDDEN);
	}
	else
	{
		lv_obj_set_parent(global_cxt.ui_cxt.keyboard, parent);
	}
	
	lv_obj_clear_flag(global_cxt.ui_cxt.keyboard, LV_OBJ_FLAG_HIDDEN);
	lv_keyboard_set_textarea(global_cxt.ui_cxt.keyboard, text_area);
	
	lv_obj_add_event_cb(global_cxt.ui_cxt.keyboard, ok_cb, 		LV_EVENT_READY, ok_arg);
	lv_obj_add_event_cb(global_cxt.ui_cxt.keyboard, cancel_cb, LV_EVENT_CANCEL, cancel_arg);
}

void hide_keyboard()
{
	if (global_cxt.ui_cxt.keyboard)
		lv_obj_add_flag(global_cxt.ui_cxt.keyboard, LV_OBJ_FLAG_HIDDEN);
}

void hide_keyboard_cb(lv_event_t *e)
{
	if (global_cxt.ui_cxt.keyboard)
		lv_obj_add_flag(global_cxt.ui_cxt.keyboard, LV_OBJ_FLAG_HIDDEN);
}

int create_standard_container(lv_obj_t **cont, lv_obj_t *parent)
{
	if (!cont || !parent)
		return ERR_NULL_PTR;
	
	*cont = lv_obj_create(parent);
	if (!*cont)
		return ERR_ALLOC_FAIL;
	
	lv_obj_set_size(*cont, STANDARD_CONTAINER_WIDTH, STANDARD_CONTAINER_HEIGHT);
	lv_obj_center(*cont);
	
	return NO_ERROR;
}

int create_standard_button_list(lv_obj_t **cont, lv_obj_t *parent)
{
	if (!cont || !parent)
		return ERR_NULL_PTR;
	
	*cont = lv_obj_create(parent);
	if (!*cont)
		return ERR_ALLOC_FAIL;
	
	lv_obj_set_size(*cont, STANDARD_CONTAINER_WIDTH, STANDARD_CONTAINER_HEIGHT);
	lv_obj_center(*cont);
	lv_obj_set_flex_flow(*cont, LV_FLEX_FLOW_COLUMN);
	
	return NO_ERROR;
}

int create_standard_button_click(lv_obj_t **obj, lv_obj_t **label, lv_obj_t *parent,
	char *text, lv_event_cb_t click_cb, void *click_cb_arg)
{
	if (!obj || !label || !parent)
		return ERR_NULL_PTR;
	
	*obj = lv_btn_create(parent);
    lv_obj_set_size(*obj, LV_PCT(100), LV_SIZE_CONTENT);
    
	*label = lv_label_create(*obj);
	
	if (text)
		lv_label_set_text(*label, text);
	
	lv_obj_center(*label);
	
	lv_obj_add_event_cb(*obj, click_cb, LV_EVENT_CLICKED, click_cb_arg);
	
	return NO_ERROR;
}

int create_standard_button_long_press_release(lv_obj_t **obj, lv_obj_t **label, lv_obj_t *parent,
	char *text, lv_event_cb_t press_cb, void *press_cb_arg, lv_event_cb_t release_cb, void *release_cb_arg)
{
	if (!obj || !label || !parent)
		return ERR_NULL_PTR;
	
	*obj = lv_btn_create(parent);
    lv_obj_set_size(*obj, LV_PCT(100), LV_SIZE_CONTENT);
    
	*label = lv_label_create(*obj);
	
	if (text)
		lv_label_set_text(*label, text);
	
	lv_obj_center(*label);
	
	lv_obj_add_event_cb(*obj, press_cb, LV_EVENT_LONG_PRESSED, press_cb_arg);
	lv_obj_add_event_cb(*obj, release_cb, LV_EVENT_RELEASED, release_cb_arg);
	
	return NO_ERROR;
}

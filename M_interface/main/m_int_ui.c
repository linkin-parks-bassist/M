#include "m_int.h"

IMPLEMENT_LINKED_PTR_LIST(lv_obj_t);

m_int_ui_page test_page;

int create_test_page_ui(m_int_ui_page *page)
{
	ui_page_create_base_ui(page);
	return NO_ERROR;
}

void init_test_page()
{
	init_ui_page(&test_page);
	test_page.configured = 1;
	
	test_page.create_ui = &create_test_page_ui;
	
	test_page.panel = new_panel();
	test_page.panel->text = "Test page";
	
	ui_page_add_bottom_button(&test_page, "Test1", NULL);
	ui_page_add_bottom_button(&test_page, "Test2", NULL);
	//ui_page_add_bottom_button(&test_page, "Test3");
	//ui_page_add_bottom_button(&test_page, "Test4");
	//ui_page_add_bottom_button(&test_page, "Test5");
	//ui_page_add_bottom_button(&test_page, "Test6");
}

int init_ui_context(m_int_ui_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	init_ui_page(&cxt->transformer_selector);
	
	cxt->transformer_selector.create_ui = create_transformer_selector_ui;
	cxt->transformer_selector.enter_page = enter_transformer_selector;
	
	init_transformer_selector(&cxt->transformer_selector);
	configure_transformer_selector(&cxt->transformer_selector, global_cxt.active_profile);
	cxt->transformer_selector.create_ui(&cxt->transformer_selector);
	
	create_profile_view_for(global_cxt.active_profile);
	
	if (global_cxt.active_profile)
		create_profile_view_ui(global_cxt.active_profile->view_page);
	
	cxt->main_menu = m_int_malloc(sizeof(m_int_ui_page));
	
	init_main_menu(cxt->main_menu);
	configure_ui_page(cxt->main_menu, global_cxt.active_profile->view_page);
	create_page_ui(cxt->main_menu);
	
	cxt->prev_page = NULL;
	
	return NO_ERROR;
}

int m_int_ui_page_set_background_default(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->screen)
		return ERR_BAD_ARGS;
	
	lv_obj_set_style_bg_color(page->screen, lv_color_hex(GLOBAL_BACKGROUND_COLOUR), 0);
	lv_obj_set_style_bg_opa(page->screen, LV_OPA_COVER, 0);
	
	return NO_ERROR;
}

void create_ui(lv_disp_t *disp)
{
	//printf("Setting up UI...\n");
	
	//lv_disp_set_antialiasing(disp, false);
	lv_theme_default_init(disp,
                      lv_palette_main(LV_PALETTE_GREY),  // primary
                      lv_palette_main(LV_PALETTE_GREEN), // secondary
                      LV_THEME_DEFAULT_DARK,
                      LV_FONT_DEFAULT);
	lv_disp_set_theme(disp, lv_theme_default_get());
	
	init_ui_context(&global_cxt.ui_cxt);
	m_int_profile_set_active(global_cxt.active_profile);
	
	init_test_page();
	
	//enter_ui_page(&test_page);
	
	enter_ui_page(global_cxt.working_profile->view_page);
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

int init_ui_page(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	page->screen 			= NULL;
	page->panel				= NULL;
	
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
	
	page->container_type = CONTAINER_TYPE_STD;
	page->container = NULL;
	
	for (int i = 0; i < MAX_BOTTOM_BUTTONS; i++)
		page->bottom_buttons[i] = NULL;
	
	return NO_ERROR;
}

m_int_ui_page *create_ui_page()
{
	m_int_ui_page *res = m_int_malloc(sizeof(m_int_ui_page));
	
	if (!res)
		return NULL;
	
	init_ui_page(res);
	
	return res;
}

int configure_ui_page(m_int_ui_page *page, void *data)
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

int create_page_ui(m_int_ui_page *page)
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

int enter_ui_page_forward(m_int_ui_page *page)
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

int enter_ui_page(m_int_ui_page *page)
{
	printf("enter ui page...\n");
	
	if (!page)
	{
		printf("Error! No page!\n");
		return ERR_NULL_PTR;
	}
	
	if (!page->ui_created)
	{
		if (!page->configured)
		{
			printf("Error! Page is unconfigured\n");
			return ERR_BAD_ARGS;
		}
		
		if (!page->create_ui)
		{
			printf("Error! Page has no UI, and no create_ui function pointer!\n");
			return ERR_BAD_ARGS;
		}
		
		printf("Page has not created its UI yet. Creating now...\n");
		page->create_ui(page);
	}
	
	if (page->refresh)
	{
		page->refresh(page);
	}
	
	if (page->enter_page)
	{
		page->enter_page(page);
	}
	else
	{
		if (!page->screen)
		{
			printf("Error! Page has no screen!\n");
			return ERR_BAD_ARGS;
		}
		lv_scr_load(page->screen);
	}
	
	return NO_ERROR;
}

int enter_ui_page_back(m_int_ui_page *page)
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

int enter_ui_page_indirect(m_int_ui_page **_page)
{
	//printf("enter ui page indirect...\n");
	
	if (!_page)
		return ERR_NULL_PTR;
	
	enter_ui_page(*_page);
	
	return NO_ERROR;
}



int enter_ui_page_indirect_forward(m_int_ui_page **_page)
{
	//printf("enter ui page indirect...\n");
	
	if (!_page)
		return ERR_NULL_PTR;
	
	m_int_ui_page *page = *_page;
	
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

int enter_ui_page_indirect_back(m_int_ui_page **_page)
{
	//printf("enter ui page indirect...\n");
	
	if (!_page)
		return ERR_NULL_PTR;
	
	m_int_ui_page *page = *_page;
	
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
	printf("enter ui page callback triggered\n");
	m_int_ui_page *page = (m_int_ui_page*)lv_event_get_user_data(e);
	printf("Given page: %p\n", page);
	if (page)
		enter_ui_page(page);
}

void enter_ui_page_forward_cb(lv_event_t *e)
{
	//printf("enter ui page callback triggered\n");
	m_int_ui_page **_page = (m_int_ui_page**)lv_event_get_user_data(e);
	enter_ui_page_indirect_forward(_page);
}

void enter_ui_page_back_cb(lv_event_t *e)
{
	printf("enter ui page callback triggered\n");
	m_int_ui_page **_page = (m_int_ui_page**)lv_event_get_user_data(e);
	
	printf("_page = %p, *_page = %p\n", _page, _page ? *_page : NULL);
	enter_ui_page_indirect_back(_page);
}

void enter_parent_page_cb(lv_event_t *e)
{
	printf("enter_parent_page_cb\n");
	m_int_ui_page *page = lv_event_get_user_data(e);
	
	if (!page)
	{
		printf("No page !\n");
		return;
	}
	
	if (!page->parent)
	{
		printf("No parent !\n");
		return;
	}
	
	enter_ui_page(page->parent);
}

void m_int_ui_page_return_to_parent(m_int_ui_page *page)
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

int init_ui_page_panel_str(m_int_ui_page_panel *panel)
{
	if (!panel)
		return ERR_NULL_PTR;
	
	panel->title 			  	= NULL;
	panel->left_button 		  	= NULL;
	panel->left_button_symbol 	= NULL;
	panel->right_button 		= NULL;
	panel->right_button_symbol 	= NULL;
	panel->text 		  		= NULL;
	
	return NO_ERROR;
}

int create_panel(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	page->panel = m_int_malloc(sizeof(m_int_ui_page_panel));
	
	if (!page->panel)
		return ERR_ALLOC_FAIL;
	
	init_ui_page_panel_str(page->panel);
	
	page->panel->panel = lv_obj_create(page->screen);
    
    lv_obj_set_size				 (page->panel->panel, LV_PCT(100), TOP_PANEL_HEIGHT);
    lv_obj_set_style_bg_color	 (page->panel->panel, lv_color_hex(TOP_PANEL_COLOUR), 0);
    lv_obj_set_style_pad_all	 (page->panel->panel, 0, 0);
    lv_obj_set_style_border_width(page->panel->panel, 0, 0);
    lv_obj_set_style_radius		 (page->panel->panel, 0, 0);
    lv_obj_set_style_pad_left	 (page->panel->panel, GLOBAL_PAD_WIDTH, 0);
	lv_obj_set_style_pad_right	 (page->panel->panel, GLOBAL_PAD_WIDTH, 0);
    //lv_obj_set_flex_flow		 (page->panel->panel, LV_FLEX_FLOW_ROW);
    //lv_obj_set_flex_align		 (page->panel->panel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	
    return NO_ERROR;
}

int set_panel_text(m_int_ui_page *page, const char *text)
{
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->panel)
		return ERR_BAD_ARGS;
	
	page->panel->text = text;
    
    if (text)
    {
		page->panel->title = lv_label_create(page->panel->panel);
		lv_label_set_text(page->panel->title, page->panel->text);
		
		lv_obj_set_style_text_color(page->panel->title, lv_color_hex(GLOBAL_MAIN_TEXT_COLOUR), 0);
		lv_obj_set_style_text_font(page->panel->title, GLOBAL_MAIN_FONT, 0);
		
		//lv_obj_set_flex_grow(page->panel->title, 1);
		lv_obj_set_style_text_align(page->panel->title, LV_TEXT_ALIGN_CENTER, 0);
		lv_obj_align_to(page->panel->title, page->panel->panel, LV_ALIGN_CENTER, 0, 0);
	}
	else
	{
		page->panel->title = NULL;
	}

    return NO_ERROR;
}

int set_panel_text_rw(m_int_ui_page *page, const char *text)
{
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->panel)
		return ERR_BAD_ARGS;
	
	page->panel->text = text;
    
	page->panel->title = lv_textarea_create(page->panel->panel);
	lv_textarea_set_text(page->panel->title, page->panel->text);
	
	lv_obj_set_style_text_color(page->panel->title, lv_color_hex(GLOBAL_MAIN_TEXT_COLOUR), 0);
	lv_obj_set_style_text_font(page->panel->title, GLOBAL_MAIN_FONT, 0);
	
	lv_obj_set_style_border_width(page->panel->title, 0, 0);
    lv_obj_set_style_bg_color	 (page->panel->title, lv_color_hex(TOP_PANEL_COLOUR), 0);
	lv_obj_set_size(page->panel->title, LV_SIZE_CONTENT, TOP_PANEL_HEIGHT * 0.7);
	lv_textarea_set_one_line(page->panel->title, true);
	lv_textarea_set_align(page->panel->title, LV_TEXT_ALIGN_CENTER);
	
	lv_obj_align_to(page->panel->title, page->panel->panel, LV_ALIGN_CENTER, 0, 0);

    return NO_ERROR;
}

int create_panel_rw_title(m_int_ui_page *page, const char *text)
{
	if (!page)
		return ERR_NULL_PTR;
	
	create_panel(page);

    set_panel_text_rw(page, text);

    return NO_ERROR;
}

int create_panel_left_button(m_int_ui_page *page, const char *button_text, lv_event_cb_t cb, void *cb_arg)
{
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->panel)
		return ERR_BAD_ARGS;
	
	page->panel->left_button = lv_btn_create(page->panel->panel);
    lv_obj_set_size(page->panel->left_button, STANDARD_TOP_PANEL_BUTTON_WIDTH, STANDARD_TOP_PANEL_BUTTON_HEIGHT);
    lv_obj_align_to(page->panel->left_button, page->panel->panel, LV_ALIGN_LEFT_MID, 0, 0);
    
    page->panel->left_button_symbol = lv_label_create(page->panel->left_button);
    lv_label_set_text(page->panel->left_button_symbol, button_text);
    lv_obj_center(page->panel->left_button_symbol);
    
    if (cb)
		lv_obj_add_event_cb(page->panel->left_button, cb, LV_EVENT_CLICKED, cb_arg);
    
    return NO_ERROR;
}

int create_panel_right_button(m_int_ui_page *page, const char *button_text, lv_event_cb_t cb, void *cb_arg)
{
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->panel)
		return ERR_BAD_ARGS;
	
	page->panel->right_button = lv_btn_create(page->panel->panel);
    lv_obj_set_size(page->panel->right_button, STANDARD_TOP_PANEL_BUTTON_WIDTH, STANDARD_TOP_PANEL_BUTTON_HEIGHT);
    lv_obj_align_to(page->panel->right_button, page->panel->panel, LV_ALIGN_RIGHT_MID, 0, 0);
    
    page->panel->right_button_symbol = lv_label_create(page->panel->right_button);
    lv_label_set_text(page->panel->right_button_symbol, button_text);
    lv_obj_center(page->panel->right_button_symbol);
    
    if (cb)
		lv_obj_add_event_cb(page->panel->right_button, cb, LV_EVENT_CLICKED, cb_arg);
    
    return NO_ERROR;
}

int create_panel_rw_title_and_left_button(m_int_ui_page *page, const char *text, const char *left_button_text, lv_event_cb_t left_cb, void *left_cb_arg)
{
	if (!page)
		return ERR_NULL_PTR;
	
	create_panel(page);

    create_panel_left_button(page, left_button_text, left_cb, left_cb_arg);
    
    set_panel_text_rw(page, text);

    return NO_ERROR;
}

int create_panel_with_back_button(m_int_ui_page *page)
{
	return create_panel_with_left_button(page, LV_SYMBOL_LEFT, enter_parent_page_cb, page);
}

int create_panel_with_back_and_settings_buttons(m_int_ui_page *page, m_int_ui_page *settings_page)
{
	return create_panel_with_back_button_and_page_button(page, LV_SYMBOL_SETTINGS, settings_page);
}

int create_panel_with_back_button_and_right_button(m_int_ui_page *page, const char *right_button_text, lv_event_cb_t right_cb, void *cb_arg)
{
	return create_panel_with_left_and_right_buttons(page, LV_SYMBOL_LEFT, enter_parent_page_cb, page, right_button_text, right_cb, cb_arg);
}

int create_panel_with_left_button(m_int_ui_page *page, const char *left_button_text, lv_event_cb_t left_cb, void *cb_arg)
{
	if (!page)
		return ERR_NULL_PTR;
	
	create_panel(page);
	
	create_panel_left_button(page, left_button_text, left_cb, cb_arg);

    return NO_ERROR;
}

int create_panel_with_right_button(m_int_ui_page *page, const char *right_button_text, lv_event_cb_t right_cb, void *cb_arg)
{
	if (!page)
		return ERR_NULL_PTR;
	
	create_panel_with_back_button(page);
    
    create_panel_right_button(page, right_button_text, right_cb, cb_arg);

    return NO_ERROR;
}

int create_panel_with_back_button_and_page_button(m_int_ui_page *page, const char *right_button_text, m_int_ui_page *right_button_page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	create_panel_with_back_button(page);
    
    create_panel_right_button(page, right_button_text, enter_ui_page_cb, right_button_page);

    return NO_ERROR;
}

int create_panel_with_left_and_right_buttons(m_int_ui_page *page,
	const char *left_button_text, lv_event_cb_t left_cb, void *left_cb_arg,
	const char *right_button_text, lv_event_cb_t right_cb, void *right_cb_arg)
{
	if (!page)
		return ERR_NULL_PTR;
	
	create_panel(page);
	
	create_panel_left_button(page, left_button_text, left_cb, left_cb_arg);
    
    create_panel_right_button(page, right_button_text, right_cb, right_cb_arg);

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
	lv_obj_align_to(*cont, parent, LV_ALIGN_CENTER, 0, STANDARD_YPOS);
	
	lv_obj_clear_flag(*cont, LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);
	lv_obj_set_style_anim_time(*cont, 0, 0);
	
	return NO_ERROR;
}

int create_standard_container_tall(lv_obj_t **cont, lv_obj_t *parent)
{
	if (!cont || !parent)
		return ERR_NULL_PTR;
	
	*cont = lv_obj_create(parent);
	
	if (!*cont)
		return ERR_ALLOC_FAIL;
	
	lv_obj_set_size(*cont, STANDARD_CONTAINER_WIDTH, STANDARD_CONTAINER_TALL_HEIGHT);
	lv_obj_align_to(*cont, parent, LV_ALIGN_CENTER, 0, STANDARD_YPOS + (STANDARD_CONTAINER_TALL_HEIGHT - STANDARD_CONTAINER_HEIGHT) / 2);
	
	lv_obj_clear_flag(*cont, LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);
	lv_obj_set_style_anim_time(*cont, 0, 0);
	
	return NO_ERROR;
}

int create_standard_menu_container(lv_obj_t **cont, lv_obj_t *parent)
{
	if (!cont || !parent)
		return ERR_NULL_PTR;
	
	*cont = lv_obj_create(parent);
	if (!*cont)
		return ERR_ALLOC_FAIL;
	
	lv_obj_set_size(*cont, STANDARD_CONTAINER_WIDTH, STANDARD_CONTAINER_HEIGHT);
	lv_obj_align_to(*cont, parent, LV_ALIGN_CENTER, 0, STANDARD_YPOS);
	
	lv_obj_clear_flag(*cont, LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);
	lv_obj_set_style_anim_time(*cont, 0, 0);
	lv_obj_set_flex_align(*cont,
		LV_FLEX_ALIGN_SPACE_EVENLY,
		LV_FLEX_ALIGN_CENTER,
		LV_FLEX_ALIGN_CENTER);
	
	return NO_ERROR;
}

int create_standard_menu_container_tall(lv_obj_t **cont, lv_obj_t *parent)
{
	if (!cont || !parent)
		return ERR_NULL_PTR;
	
	*cont = lv_obj_create(parent);
	
	if (!*cont)
		return ERR_ALLOC_FAIL;
	
	lv_obj_set_size(*cont, STANDARD_CONTAINER_WIDTH, STANDARD_CONTAINER_TALL_HEIGHT);
	lv_obj_align_to(*cont, parent, LV_ALIGN_CENTER, 0, STANDARD_YPOS + (STANDARD_CONTAINER_TALL_HEIGHT - STANDARD_CONTAINER_HEIGHT) / 2);
	
	lv_obj_clear_flag(*cont, LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);
	lv_obj_set_style_anim_time(*cont, 0, 0);
	
	lv_obj_set_flex_flow(*cont, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(*cont,
		LV_FLEX_ALIGN_SPACE_EVENLY,
		LV_FLEX_ALIGN_CENTER,
		LV_FLEX_ALIGN_CENTER);

	
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
	lv_obj_align_to(*cont, parent, LV_ALIGN_CENTER, 0, STANDARD_YPOS);
	lv_obj_set_flex_flow(*cont, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(*cont,
        LV_FLEX_ALIGN_START,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER);
	
	return NO_ERROR;
}

int create_standard_button_list_tall(lv_obj_t **cont, lv_obj_t *parent)
{
	if (!cont || !parent)
		return ERR_NULL_PTR;
	
	*cont = lv_obj_create(parent);
	if (!*cont)
		return ERR_ALLOC_FAIL;
	
	lv_obj_set_size(*cont, STANDARD_CONTAINER_WIDTH, STANDARD_CONTAINER_TALL_HEIGHT);
	lv_obj_align_to(*cont, parent, LV_ALIGN_CENTER, 0, STANDARD_YPOS + (STANDARD_CONTAINER_TALL_HEIGHT - STANDARD_CONTAINER_HEIGHT) / 2);
	
	lv_obj_set_flex_flow(*cont, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(*cont,
        LV_FLEX_ALIGN_START,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER);
	
	return NO_ERROR;
}

int create_standard_button_click(lv_obj_t **obj, lv_obj_t **label, lv_obj_t *parent,
	char *text, lv_event_cb_t click_cb, void *click_cb_arg)
{
	if (!obj || !label || !parent)
		return ERR_NULL_PTR;
	
	*obj = lv_btn_create(parent);
    lv_obj_set_size(*obj, LV_PCT(100), STANDARD_BUTTON_HEIGHT);
    
	*label = lv_label_create(*obj);
	
	if (text)
		lv_label_set_text(*label, text);
	
	lv_obj_center(*label);
	
	lv_obj_add_event_cb(*obj, click_cb, LV_EVENT_CLICKED, click_cb_arg);
	
	return NO_ERROR;
}

int create_standard_button_click_short(lv_obj_t **obj, lv_obj_t **label, lv_obj_t *parent,
	char *text, lv_event_cb_t click_cb, void *click_cb_arg)
{
	if (!obj || !label || !parent)
		return ERR_NULL_PTR;
	
	*obj = lv_btn_create(parent);
    lv_obj_set_size(*obj, LV_PCT(100), STANDARD_BUTTON_SHORT_HEIGHT);
    
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
    lv_obj_set_size(*obj, LV_PCT(100), STANDARD_BUTTON_HEIGHT);
    
	*label = lv_label_create(*obj);
	
	if (text)
		lv_label_set_text(*label, text);
	
	lv_obj_center(*label);
	
	lv_obj_add_event_cb(*obj, press_cb, LV_EVENT_LONG_PRESSED, press_cb_arg);
	lv_obj_add_event_cb(*obj, release_cb, LV_EVENT_RELEASED, release_cb_arg);
	
	return NO_ERROR;
}

int init_button(m_int_button *button)
{
	if (!button)
		return ERR_NULL_PTR;
	
	button->obj 				= NULL;
	button->label 				= NULL;
	button->label_text 			= NULL;
	button->clicked_cb 			= NULL;
	button->clicked_cb_arg 		= NULL;
	button->pressing_cb 		= NULL;
	button->pressing_cb_arg 	= NULL;
	button->long_pressed_cb 	= NULL;
	button->long_pressed_cb_arg = NULL;
	button->released_cb 		= NULL;
	button->released_cb_arg 	= NULL;
	
	button->hider = NULL;
	button->clickable = 1;
	
	button->long_pressed = 0;
	
	button->draggable_x = 0;
	button->draggable_y = 0;
	
	button->sub_buttons = NULL;
	
	button->width  = LV_PCT(100);
	button->height = STANDARD_BUTTON_HEIGHT;
	
	return NO_ERROR;
}

m_int_button *new_button(const char *label)
{
	m_int_button *button = malloc(sizeof(m_int_button));
	
	if (!button)
		return NULL;
	
	init_button(button);
	
	button->label_text = label;
	
	return button;
}

int create_button_ui(m_int_button *button, lv_obj_t *parent)
{
	if (!button)
		return ERR_NULL_PTR;
	
	button->obj = lv_btn_create(parent);
	
	if (!button->obj)
		return ERR_ALLOC_FAIL;
	
	lv_obj_set_size(button->obj, button->width, button->height);
	
	button->label = lv_label_create(button->obj);
	
	if (!button->label)
	{
		lv_obj_del(button->obj);
		button->obj = NULL;
		return ERR_ALLOC_FAIL;
	}
	
	lv_label_set_text(button->label, button->label_text);
	lv_obj_center(button->label);
	
	if (button->clicked_cb)
		lv_obj_add_event_cb(button->obj, button->clicked_cb, LV_EVENT_CLICKED, button->clicked_cb_arg);
	
	if (button->pressing_cb)
		lv_obj_add_event_cb(button->obj, button->pressing_cb, LV_EVENT_PRESSING, button->pressing_cb_arg);
	
	if (button->long_pressed_cb)
		lv_obj_add_event_cb(button->obj, button->long_pressed_cb, LV_EVENT_LONG_PRESSED, button->long_pressed_cb_arg);
	
	if (button->released_cb)
		lv_obj_add_event_cb(button->obj, button->released_cb, LV_EVENT_RELEASED, button->released_cb_arg);
	
	return NO_ERROR;
}

int button_set_clicked_cb(m_int_button *button, lv_event_cb_t cb, void *cb_arg)
{
	if (!button)
		return ERR_NULL_PTR;
	
	button->clicked_cb = cb;
	button->clicked_cb_arg = cb_arg;
	
	return NO_ERROR;
}

int button_set_pressing_cb(m_int_button *button, lv_event_cb_t cb, void *cb_arg)
{
	if (!button)
		return ERR_NULL_PTR;
	
	button->pressing_cb = cb;
	button->pressing_cb_arg = cb_arg;
	
	return NO_ERROR;
}

int button_set_long_pressed_cb(m_int_button *button, lv_event_cb_t cb, void *cb_arg)
{
	if (!button)
		return ERR_NULL_PTR;
	
	button->long_pressed_cb = cb;
	button->long_pressed_cb_arg = cb_arg;
	
	return NO_ERROR;
}

int button_set_released_cb(m_int_button *button, lv_event_cb_t cb, void *cb_arg)
{
	if (!button)
		return ERR_NULL_PTR;
	
	button->released_cb = cb;
	button->released_cb_arg = cb_arg;
	
	return NO_ERROR;
}

int init_panel(m_int_ui_page_panel *panel)
{
	if (!panel)
		return ERR_NULL_PTR;
	
	panel->panel = NULL;
	panel->title = NULL;
	panel->text  = NULL;
	
	panel->lb = NULL;
	panel->rb = NULL;
	
	panel->left_button = NULL;
	panel->left_button_symbol = NULL;
	panel->right_button = NULL;
	panel->right_button_symbol = NULL;
	
	return NO_ERROR;
}

m_int_ui_page_panel *new_panel()
{
	m_int_ui_page_panel *panel = malloc(sizeof(m_int_ui_page_panel));
	
	if (!panel)
		return NULL;
	
	init_panel(panel);
	
	return panel;
}

static void edit_rw_text_cb(lv_event_t *e)
{
	m_int_ui_page *page = (m_int_ui_page*)lv_event_get_user_data(e);
	
	if (!page)
		return;
	
	spawn_keyboard(page->screen, page->panel->title, page->panel->rw_save_cb, page, page->panel->rw_cancel_cb, page);
	lv_obj_add_state(page->panel->title, LV_STATE_FOCUSED);
}


int ui_page_create_panel_ui(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->panel)
		return ERR_BAD_ARGS;
	
	page->panel->panel = lv_obj_create(page->screen);
    
    lv_obj_set_size				 (page->panel->panel, LV_PCT(100), TOP_PANEL_HEIGHT);
    lv_obj_set_style_bg_color	 (page->panel->panel, lv_color_hex(TOP_PANEL_COLOUR), 0);
    lv_obj_set_style_pad_all	 (page->panel->panel, 0, 0);
    lv_obj_set_style_border_width(page->panel->panel, 0, 0);
    lv_obj_set_style_radius		 (page->panel->panel, 0, 0);
    lv_obj_set_style_pad_left	 (page->panel->panel, GLOBAL_PAD_WIDTH, 0);
	lv_obj_set_style_pad_right	 (page->panel->panel, GLOBAL_PAD_WIDTH, 0);
	
	if (page->panel->lb)
	{
		create_button_ui(page->panel->lb, page->panel->panel);
		lv_obj_align_to(page->panel->lb->obj, page->panel->panel, LV_ALIGN_LEFT_MID, 0, 0);
	}
	
	char *text = page->panel->text ? page->panel->text : "";
	
	if (page->panel->flags & TOP_PANEL_FLAG_RW_TITLE)
	{
		page->panel->title = lv_textarea_create(page->panel->panel);
		lv_textarea_set_text(page->panel->title, text);
		
		lv_obj_set_style_text_color(page->panel->title, lv_color_hex(GLOBAL_MAIN_TEXT_COLOUR), 0);
		lv_obj_set_style_text_font(page->panel->title, GLOBAL_MAIN_FONT, 0);
		
		lv_obj_set_style_border_width(page->panel->title, 0, 0);
		lv_obj_set_style_bg_color	 (page->panel->title, lv_color_hex(TOP_PANEL_COLOUR), 0);
		lv_obj_set_size(page->panel->title, LV_SIZE_CONTENT, TOP_PANEL_HEIGHT * 0.7);
		lv_textarea_set_one_line(page->panel->title, true);
		lv_textarea_set_align(page->panel->title, LV_TEXT_ALIGN_CENTER);
		
		lv_obj_align_to(page->panel->title, page->panel->panel, LV_ALIGN_CENTER, 0, 0);
		
		lv_obj_add_event_cb(page->panel->title, edit_rw_text_cb, LV_EVENT_CLICKED, page);
	}
	else
	{
		page->panel->title = lv_label_create(page->panel->panel);
		lv_label_set_text(page->panel->title, text);
		
		lv_obj_set_style_text_color(page->panel->title, lv_color_hex(GLOBAL_MAIN_TEXT_COLOUR), 0);
		lv_obj_set_style_text_font(page->panel->title, GLOBAL_MAIN_FONT, 0);
		
		lv_obj_set_style_text_align(page->panel->title, LV_TEXT_ALIGN_CENTER, 0);
		lv_obj_align_to(page->panel->title, page->panel->panel, LV_ALIGN_CENTER, 0, 0);
	}
	
	if (page->panel->rb)
	{
		create_button_ui(page->panel->rb, page->panel->panel);
		lv_obj_align_to(page->panel->rb->obj, page->panel->panel, LV_ALIGN_RIGHT_MID, 0, 0);
	}
	
	return NO_ERROR;
}

int ui_page_add_back_button(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->panel)
		return ERR_BAD_ARGS;
	
	page->panel->lb = new_button(LV_SYMBOL_LEFT);
	
	if (!page->panel->lb)
		return ERR_ALLOC_FAIL;
	
	page->panel->lb->width  = STANDARD_TOP_PANEL_BUTTON_WIDTH;
	page->panel->lb->height = STANDARD_TOP_PANEL_BUTTON_HEIGHT;
	
	button_set_clicked_cb(page->panel->lb, enter_parent_page_cb, page);
	
	return NO_ERROR;
}

int ui_page_add_left_panel_button(m_int_ui_page *page, const char *label, lv_event_cb_t cb)
{
	if (!page)
		return ERR_NULL_PTR;
	
	page->panel->lb = new_button(label);
	
	if (!page->panel->lb)
		return ERR_ALLOC_FAIL;
	
	page->panel->lb->width  = STANDARD_TOP_PANEL_BUTTON_WIDTH;
	page->panel->lb->height = STANDARD_TOP_PANEL_BUTTON_HEIGHT;
	
	button_set_clicked_cb(page->panel->lb, cb, page);
	
	return NO_ERROR;
}

int ui_page_add_right_panel_button(m_int_ui_page *page, const char *label, lv_event_cb_t cb)
{
	if (!page)
		return ERR_NULL_PTR;
	
	page->panel->rb = new_button(label);
	
	if (!page->panel->rb)
		return ERR_ALLOC_FAIL;
	
	page->panel->rb->width  = STANDARD_TOP_PANEL_BUTTON_WIDTH;
	page->panel->rb->height = STANDARD_TOP_PANEL_BUTTON_HEIGHT;
	
	button_set_clicked_cb(page->panel->rb, cb, page);
	
	return NO_ERROR;
}

int ui_page_create_base_ui(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	page->screen = lv_obj_create(NULL);
	
	if (!page->screen)
		return ERR_ALLOC_FAIL;
	
	if (page->panel)
	{
		ui_page_create_panel_ui(page);
	}
	
	ui_page_create_container(page);
	
	ui_page_create_bottom_buttons(page);
	
	return NO_ERROR;
}


int ui_page_create_container(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	int tall = 1;
	
	for (int i = 0; i < MAX_BOTTOM_BUTTONS; i++)
	{
		if (page->bottom_buttons[i])
			tall = 0;
	}
	
	switch (page->container_type)
	{
		case CONTAINER_TYPE_STD:
			if (tall)
				return create_standard_container_tall(&page->container, page->screen);
			
			return create_standard_container(&page->container, page->screen);
			
		case CONTAINER_TYPE_STD_BTN_LIST:
			if (tall)
				return create_standard_button_list_tall(&page->container, page->screen);
				
			return create_standard_button_list(&page->container, page->screen);
		case CONTAINER_TYPE_STD_MENU:
			if (tall)
				return create_standard_menu_container_tall(&page->container, page->screen);
				
			return create_standard_menu_container(&page->container, page->screen);
			
		default:
			return ERR_BAD_ARGS;
	}
	
	return NO_ERROR;
}

int ui_page_create_bottom_buttons(m_int_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	int n = 0;
	
	for (int i = 0; i < MAX_BOTTOM_BUTTONS; i++)
	{
		if (page->bottom_buttons[i])
			n++;
	}
	
	if (!n)
		return NO_ERROR;
	
	int pad = (n <= 1) ? 0 : (int)((float)BOTTOM_BUTTON_PADDING / n) + BOTTOM_BUTTON_PADDING / 2;
	int width = (int)(float)(STANDARD_CONTAINER_WIDTH - (n - 1) * pad) / n;
	int height = STANDARD_BUTTON_HEIGHT;
	
	int pos;
	
	for (int i = 0; i < MAX_BOTTOM_BUTTONS; i++)
	{
		if (page->bottom_buttons[i])
		{
			create_button_ui(page->bottom_buttons[i], page->screen);
			lv_obj_set_size(page->bottom_buttons[i]->obj, width, height);
			
			pos = (i * (width + pad) + width / 2) - STANDARD_CONTAINER_WIDTH / 2;
			lv_obj_align(page->bottom_buttons[i]->obj, LV_ALIGN_BOTTOM_MID, pos, -50);
		}
	}
	
	return NO_ERROR;
}

m_int_button *ui_page_add_bottom_button(m_int_ui_page *page, const char *label, lv_event_cb_t cb)
{
	if (!page)
		return NULL;
	
	int index = -1;
	
	for (int i = 0; i < MAX_BOTTOM_BUTTONS; i++)
	{
		if (!page->bottom_buttons[i])
		{
			index = i;
			break;
		}
	}
	
	if (index == -1)
		return NULL;
	
	page->bottom_buttons[index] = new_button(label);
	
	if (cb)
		button_set_clicked_cb(page->bottom_buttons[index], cb, page);
	
	return page->bottom_buttons[index];
}

int ui_page_set_title_rw(m_int_ui_page *page, lv_event_cb_t save_cb, lv_event_cb_t cancel_cb)
{
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->panel)
		return ERR_BAD_ARGS;
	
	page->panel->flags |= TOP_PANEL_FLAG_RW_TITLE;
	
	page->panel->rw_save_cb = save_cb;
	page->panel->rw_cancel_cb = cancel_cb;
	
	return NO_ERROR;
}

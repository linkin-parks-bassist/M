#include "em.h"


IMPLEMENT_LINKED_PTR_LIST(lv_obj_t);

ui_page test_page;

teensy_transformer distortion;

void test_page_back_button_cb(lv_event_t *event)
{
	printf("back!!!\n");
}

int ui_page_set_background_default(ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	if (!page->screen)
		return ERR_BAD_ARGS;
	
	lv_obj_set_style_bg_color(page->screen, lv_color_hex(GLOBAL_BACKGROUND_COLOUR), 0);
	lv_obj_set_style_bg_opa(page->screen, LV_OPA_COVER, 0);
	
	return NO_ERROR;
}

void create_test_page_ui(ui_page *page)
{
	if (!page)
		return;
	
	page->screen = lv_obj_create(NULL);
	
	ui_page_set_background_default(page);
	
	create_top_panel_with_back_button(page, "Test page", test_page_back_button_cb);
}

void free_test_page_ui(ui_page *page)
{
	
}

void enter_test_page(ui_page *page)
{
	lv_scr_load(page->screen);
}

void refresh_test_page(ui_page *page)
{
	
}

ui_page distortion_view;

void make_ui(lv_disp_t *disp)
{
	printf("Setting up UI...\n");
	distortion.profile_id = 1;
	distortion.transformer_id = 0;
	
	distortion.type = TRANSFORMER_DISTORTION;
	
	distortion.n_parameters = 8;
	distortion.parameters = malloc(sizeof(teensy_parameter) * 8);
	
	distortion.parameters[0].type 		= M_PARAM_LEVEL;
	distortion.parameters[0].min.level 	= 0.0;
	distortion.parameters[0].max.level 	= 10.0;
	distortion.parameters[0].name 		= "Gain";
	distortion.parameters[0].id 		= (m_parameter_id){1, 0, 1};
	
	distortion.parameters[1].type 		= M_PARAM_LEVEL;
	distortion.parameters[1].min.level 	= 0.0;
	distortion.parameters[1].max.level 	= 1.0;
	distortion.parameters[1].name 		= "Wet Mix";
	distortion.parameters[1].id 		= (m_parameter_id){1, 0, 2};
	
	distortion.parameters[2].type 		= M_PARAM_LEVEL;
	distortion.parameters[2].min.level 	= 0.0;
	distortion.parameters[2].max.level 	= 1.0;
	distortion.parameters[2].name 		= "High Mix";
	distortion.parameters[2].id 		= (m_parameter_id){1, 0, 3};
	
	distortion.parameters[3].type 		= M_PARAM_LEVEL;
	distortion.parameters[3].min.level 	= 0.0;
	distortion.parameters[3].max.level 	= 1.0;
	distortion.parameters[3].name 		= "Mid Mix";
	distortion.parameters[3].id 		= (m_parameter_id){1, 0, 4};
	
	distortion.parameters[4].type 		= M_PARAM_LEVEL;
	distortion.parameters[4].min.level 	= 0.0;
	distortion.parameters[4].max.level 	= 1.0;
	distortion.parameters[4].name 		= "Bass Mix";
	distortion.parameters[4].id 		= (m_parameter_id){1, 0, 5};
	
	distortion.parameters[5].type 		= M_PARAM_LEVEL;
	distortion.parameters[5].min.level 	= 500.0;
	distortion.parameters[5].max.level 	= 5000.0;
	distortion.parameters[5].name 		= "Mid Cutoff";
	distortion.parameters[5].id 		= (m_parameter_id){1, 0, 6};
	
	distortion.parameters[6].type 		= M_PARAM_LEVEL;
	distortion.parameters[6].min.level 	= 50.0;
	distortion.parameters[6].max.level 	= 250.0;
	distortion.parameters[6].name 		= "Bass Cutoff";
	distortion.parameters[6].id 		= (m_parameter_id){1, 0, 7};
	
	distortion.parameters[7].type 		= M_PARAM_LEVEL;
	distortion.parameters[7].min.level 	= 0.0;
	distortion.parameters[7].max.level 	= 1.0;
	distortion.parameters[7].name 		= "Ratio";
	distortion.parameters[7].id 		= (m_parameter_id){1, 0, 8};
	
	init_ui_page(&distortion_view);
	
	distortion_view.init = init_transformer_view_struct;
	distortion_view.configure = configure_transformer_view;
	distortion_view.create_ui = init_transformer_view_ui;
	distortion_view.enter_page = enter_transformer_view;
	
	queue_msg_to_teensy(create_et_msg		 (ET_MESSAGE_SWITCH_PROFILE, 	 "s",  1));
	
	distortion_view.init(&distortion_view);
	distortion_view.configure(&distortion_view, (void*)&distortion);
	distortion_view.create_ui(&distortion_view);
	distortion_view.enter_page(&distortion_view);
}

static void value_changed_event_cb(lv_event_t * e)
{
	lv_obj_t *arc   = lv_event_get_target(e);
	lv_obj_t *label = lv_event_get_user_data(e);

	lv_label_set_text_fmt(label, "%d%%", lv_arc_get_value(arc));

	et_msg msg;
	msg.type = ET_MESSAGE_SET_PARAM_VALUE;
	
	et_msg_chparam_struct str;
	
	str.id.profile_id 		= 1;
	str.id.transformer_id 	= 0;
	str.id.parameter_id 	= 0;
	str.new_value.level		= 4.0 * 3.0 * lv_arc_get_value(arc) / 300.0;
	
	memcpy(&msg.data[0], &str.id.profile_id, 		2);
	memcpy(&msg.data[2], &str.id.transformer_id, 	2);
	memcpy(&msg.data[4], &str.id.parameter_id, 	2);
	memcpy(&msg.data[6], &str.new_value, 		sizeof(m_param_value));
	
	xQueueSend(et_msg_queue, (void*)&msg, 0);
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

int init_ui_page(ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	page->screen 			= NULL;
	page->top_panel			= NULL;
	
	page->init				= NULL;
	page->configure			= NULL;
	page->create_ui 		= NULL;
	page->free_ui 			= NULL;
	page->enter_page 		= NULL;
	page->refresh			= NULL;
	
	page->data_struct 		= NULL;
	
	return NO_ERROR;
}

ui_page *create_ui_page()
{
	ui_page *res = malloc(sizeof(ui_page));
	
	if (!res)
		return NULL;
	
	init_ui_page(res);
	
	return res;
}

int enter_ui_page(ui_page *page)
{
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

void enter_ui_page_cb(lv_event_t *e)
{
	ui_page *page = (ui_page*)lv_event_get_user_data(e);
	enter_ui_page(page);
}

void ui_page_return_to_parent(ui_page *page)
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

int create_top_panel(ui_page *page, char *title_text)
{
	if (!page)
		return ERR_NULL_PTR;
	
	page->top_panel = malloc(sizeof(ui_page_top_panel));
	
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

int create_top_panel_with_back_button(ui_page *page, const char *title_text, lv_event_cb_t back_cb)
{
	int ret_val = create_top_panel(page, title_text);
	
	if (ret_val != NO_ERROR)
		return ret_val;
	
	page->top_panel = malloc(sizeof(ui_page_top_panel));
	
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
		lv_obj_add_event_cb(page->top_panel->back_button, back_cb, LV_EVENT_CLICKED, page);
	else if (page->parent)
		lv_obj_add_event_cb(page->top_panel->back_button, enter_ui_page_cb, LV_EVENT_CLICKED, page->parent);

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


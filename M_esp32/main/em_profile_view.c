#include "em.h"

IMPLEMENT_LINKED_LIST(transformer_widget);

static int init_profile_view_str(profile_view_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	return NO_ERROR;
}

int init_profile_view_struct(ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	
	profile_view_str *str = malloc(sizeof(profile_view_str));
	page->data_struct = (void*)str;
	
	str->profile = NULL;
	
	str->button_list = NULL;
	
	str->profile = NULL;
	
	str->transformer_widgets = NULL;
	
	return NO_ERROR;
}

int profile_view_configure(profile_view_str *pv, teensy_profile *profile)
{
	if (!pv || profile)
		return ERR_NULL_PTR;
	
	pv->profile = profile;
	
	transformer_widget tw;
	
	for (int i = 0; i < profile->pipeline.n_transformers; i++)
	{
		init_transformer_widget(&tw, pv, &profile->pipeline.transformers[i]);
		pv->transformer_widgets = transformer_widget_linked_list_append(pv->transformer_widgets, tw);
	}
	
	return NO_ERROR;
}

void initialise_profile_view_ui(ui_page *page)
{
	if (!page)
		return;
	
	//create_top_panel_with_back_button();
}

const char *transformer_labels[] = {"???", "Buffer", "Amplifier", "Distortion", "Compressor", "Delay", "Reverb"};

int transformer_type_to_array_index(int type)
{
	switch (type)
	{
		case TRANSFORMER_BUFFER:
			return 1;
			
		case TRANSFORMER_AMPLIFIER:
			return 2;
			
		case TRANSFORMER_DISTORTION:
			return 3;
			
		case TRANSFORMER_COMPRESSOR:
			return 4;
		
		default:
			return 0;
	}
}

int init_transformer_widget(transformer_widget *tw, profile_view_str *parent, teensy_transformer *trans)
{
	if (!tw || !parent)
		return ERR_NULL_PTR;
	
	tw->trans = trans;
	
	tw->profile_id = parent->profile->id;
	tw->transformer_id = trans ? trans->transformer_id : 0;
	
	if (trans)
	{
		tw->label_text = transformer_labels[transformer_type_to_array_index(trans->type)];
	}
	
	tw->widget = NULL;
	tw->label  = NULL;
	
	return NO_ERROR;
}

#include "lvgl.h"

static lv_obj_t *main_scr;
static lv_obj_t *select_scr;
static lv_obj_t *btn_list;

static lv_obj_t *add_main_button(const char *txt)
{
    lv_obj_t *btn = lv_btn_create(btn_list);
    lv_obj_set_width(btn, lv_pct(95));
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, txt);
    lv_obj_center(label);
    return btn;
}

static void plus_event_cb(lv_event_t *e)
{
    lv_scr_load(select_scr);
}


static void option_event_cb(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    const char *choice = lv_label_get_text(lv_obj_get_child(btn, 0));

    // Add chosen option as a button on main screen
    add_main_button(choice);

    // Add a fresh "+" button again at the bottom
    lv_obj_t *plus = add_main_button("+");
    lv_obj_add_event_cb(plus, plus_event_cb, LV_EVENT_CLICKED, NULL);

    // Switch back to main screen
    lv_scr_load(main_scr);
}


// --- screen setup ---
void create_profile_view()
{
    // --- Main screen ---
    main_scr = lv_obj_create(NULL);

    btn_list = lv_obj_create(main_scr);
    lv_obj_set_size(btn_list, 500, 540);
    lv_obj_align(btn_list, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_flex_flow(btn_list, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_gap(btn_list, 0, 0);

    // First "+" button
    lv_obj_t *plus = add_main_button("+");
    lv_obj_add_event_cb(plus, plus_event_cb, LV_EVENT_CLICKED, NULL);

    // --- Select screen ---
    select_scr = lv_obj_create(NULL);
    lv_obj_t *opt_list = lv_obj_create(select_scr);
    lv_obj_set_size(opt_list, 500, 540);
    lv_obj_align(opt_list, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_flex_flow(opt_list, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_gap(opt_list, 0, 0);

    // Add some options
    const char *options[] = { "Option A", "Option B", "Option C" };
    for(int i = 0; i < 3; i++) {
        lv_obj_t *btn = lv_btn_create(opt_list);
        lv_obj_set_width(btn, lv_pct(95));
        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text(label, options[i]);
        lv_obj_center(label);
        lv_obj_add_event_cb(btn, option_event_cb, LV_EVENT_CLICKED, NULL);
    }

    // Start with main screen
    lv_scr_load(main_scr);
}

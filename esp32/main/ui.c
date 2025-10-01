#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "teensy_comms.h"
#include "lvgl.h"
#include "ui.h"

#include "transformer_view.h"

#include <math.h>

void format_float(char *buf, float val)
{
	if (!buf) return;

	// Handle negative numbers
	int is_neg = (val < 0);
	if (is_neg) val = -val;

	// Multiply and round to 2 decimal places
	int scaled = (int)roundf(val * 100.0f);
	int int_part = scaled / 100;
	int frac_part = scaled % 100;

	// Write manually to buffer
	char *p = buf;

	if (is_neg) *p++ = '-';

	// Integer part
	if (int_part == 0)
		*p++ = '0';
	else {
		// Write digits in reverse
		char tmp[10];
		int i = 0;
		while (int_part > 0) {
			tmp[i++] = '0' + (int_part % 10);
			int_part /= 10;
		}
		while (i--) *p++ = tmp[i];
	}

	*p++ = '.';

	// Fractional part (always two digits)
	*p++ = '0' + (frac_part / 10);
	*p++ = '0' + (frac_part % 10);

	*p = '\0';
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

void make_ui(lv_disp_t *disp)
{
	init_global_bg(disp);
	lv_theme_t *th = lv_theme_default_init(disp,  /*Use the DPI, size, etc from this display*/
                                        lv_palette_main(LV_PALETTE_RED),   // primary
										lv_palette_main(LV_PALETTE_RED),
                                        true,    /*Light or dark mode*/
                                        &lv_font_montserrat_14); /*Small, normal, large fonts*/

	lv_disp_set_theme(disp, th); /*Assign the theme to the display*/

	

	init_transformer_view(&transformer_view);
	
	transformer_view_distortion(&transformer_view, 1, 0);
	
	enter_transformer_view(&transformer_view);
}

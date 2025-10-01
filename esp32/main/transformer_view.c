#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "m_error_codes.h"
#include "esp_log.h"
#include "m_parameter.h"
#include "m_comms.h"
#include <string.h>
#include <math.h>
#include "lvgl.h"
#include "teensy_comms.h"
#include "ui.h"

#include "transformer_view.h"

const char *TAG = "Transformer view";

#define DISTORTION_LABEL_INDEX 0

transformer_view_str transformer_view;

int init_transformer_view(transformer_view_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	str->scr = lv_obj_create(NULL);
	
	str->grid = lv_obj_create(str->scr);
	str->transformer_type = TRANSFORMER_BUFFER;
	str->label = NULL;
	str->profile_id = 0;
	str->transformer_id = 0;
	
	str->n_param_widgets = 0;
	str->param_widgets = NULL;
	
	str->col_dsc[0] = 200;
	str->col_dsc[1] = 200;
	str->col_dsc[2] = LV_GRID_TEMPLATE_LAST;
	
	str->row_dsc = NULL;
	
	return NO_ERROR;
}

int clear_transformer_view()
{
	return ERR_UNIMPLEMENTED;
}

#define H_PAD 40
#define V_PAD 40

lv_obj_t *create_title_bar(lv_obj_t *parent, const char *title_text, lv_event_cb_t back_cb)
{
    // Panel container
    lv_obj_t *bar = lv_obj_create(parent);
    lv_obj_set_size(bar, LV_PCT(100), 60);             // full width, fixed height
    lv_obj_set_style_bg_color(bar, lv_color_hex(0x333333), 0);
    lv_obj_set_style_pad_all(bar, 5, 0);
    lv_obj_set_flex_flow(bar, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(bar, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    // Back button
    lv_obj_t *back_btn = lv_btn_create(bar);
    lv_obj_set_size(back_btn, 30, 30);
    lv_obj_t *back_lbl = lv_label_create(back_btn);
    lv_label_set_text(back_lbl, LV_SYMBOL_LEFT);
    lv_obj_center(back_lbl);
    if (back_cb) lv_obj_add_event_cb(back_btn, back_cb, LV_EVENT_CLICKED, NULL);

    // Spacer (so title is centered)
    lv_obj_t *spacer = lv_obj_create(bar);
    lv_obj_set_size(spacer, 5, 1);
    lv_obj_set_style_bg_opa(spacer, LV_OPA_TRANSP, 0);

    // Title label
    lv_obj_t *title = lv_label_create(bar);
    lv_label_set_text(title, title_text);
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_14, 0);

    return bar;
}

int enter_transformer_view(transformer_view_str *str)
{
	if (!str)
		return ERR_NULL_PTR;
	
	if (str->grid)
		lv_obj_del(str->grid);
	
	lv_obj_clean(str->scr);
	
	lv_obj_remove_style_all(str->scr);
	lv_obj_set_size(str->scr, 600, 1024);
	
	str->grid = lv_obj_create(str->scr);
	lv_obj_set_style_border_width(str->grid, 0, 0);
	
	create_title_bar(str->scr, "Distortion", NULL);
	
	int n_rows = (str->n_param_widgets + 1) / 2;
	
	if (str->row_dsc)
		free(str->row_dsc);
	
	str->row_dsc = malloc(sizeof(lv_coord_t) * (n_rows + 1));
	
	for (int i = 0; i < n_rows; i++)
		str->row_dsc[i] = 200;
	
	str->row_dsc[n_rows] = LV_GRID_TEMPLATE_LAST;

	lv_obj_set_style_grid_column_dsc_array(str->grid, str->col_dsc, 0);
	lv_obj_set_style_grid_row_dsc_array(str->grid, str->row_dsc, 0);
	lv_obj_set_size(str->grid, 2 * 200 + H_PAD, n_rows * 200 + V_PAD);
	lv_obj_center(str->grid);
	
	lv_obj_set_layout(str->grid, LV_LAYOUT_GRID);

	for (int i = 0; i < str->n_param_widgets; i++)
	{
		init_virtual_pot_ui(&str->param_widgets[i], str->grid);
		
		lv_obj_set_grid_cell(str->param_widgets[i].obj, LV_GRID_ALIGN_CENTER, i % 2, 1, LV_GRID_ALIGN_CENTER, i / 2, 1);
	}
	
	lv_scr_load(str->scr);
	
	return NO_ERROR;
}

#define DISTORTION_N_POTS 3

const char *distortion_labels[] = {"Distortion", "Wet Mix", "Presence"};

int transformer_view_distortion(transformer_view_str *str, uint16_t profile_id, uint16_t transformer_id)
{
	if (!str)
		return ERR_NULL_PTR;
	
	str->label = distortion_labels[0];
	
	str->profile_id 	= profile_id;
	str->transformer_id = transformer_id;
	
	if (!str->param_widgets)
	{
		str->param_widgets = malloc(sizeof(parameter_widget) * DISTORTION_N_POTS);
		str->param_widget_array_size = DISTORTION_N_POTS;
	}
	else if (str->param_widget_array_size < DISTORTION_N_POTS)
	{
		for (int i = 0; i < str->n_param_widgets; i++)
		{
			lv_obj_del(str->param_widgets[i].obj);
			lv_obj_del(str->param_widgets[i].val_label);
		}
		
		free(str->param_widgets);
		str->param_widgets = malloc(sizeof(parameter_widget) * DISTORTION_N_POTS);
		str->param_widget_array_size = DISTORTION_N_POTS;
	}
	
	str->n_param_widgets = DISTORTION_N_POTS;
	
	m_parameter_id id;
	id.profile_id = profile_id;
	id.transformer_id = transformer_id;
	
	// Distortion
	id.parameter_id = 0;
	init_virtual_pot_param(&str->param_widgets[0], distortion_labels[0], id, 0.0, 0.0, 5.0);
	
	// Wet mix
	id.parameter_id = 9;
	init_virtual_pot_param(&str->param_widgets[1], distortion_labels[1], id, 0.75, 0.0, 1.0);
	
	// Presence
	id.parameter_id = 8;
	init_virtual_pot_param(&str->param_widgets[2], distortion_labels[2], id, 1.0, 0.0, 7.0);
	
	for (int i = 0; i < str->n_param_widgets; i++)
		request_param_widget_value(&str->param_widgets[i]);
	
	return NO_ERROR;
}

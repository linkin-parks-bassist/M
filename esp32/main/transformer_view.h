#ifndef TRANSFORMER_VIEW_H_
#define TRANSFORMER_VIEW_H_

#include "m_transformer_enum.h"
#include "m_parameter.h"

#include "parameter_widget.h"

typedef struct
{
	int transformer_type;
	const char *label;
	
	uint16_t profile_id;
	uint16_t transformer_id;
	
	lv_obj_t *scr;
	lv_obj_t *grid;
	
	lv_coord_t col_dsc[3];
	lv_coord_t *row_dsc;
	
	int n_param_widgets;
	int param_widget_array_size;
	parameter_widget *param_widgets;
} transformer_view_str;

int transformer_view_distortion(transformer_view_str *str, uint16_t profile_id, uint16_t transformer_id);
int enter_transformer_view(transformer_view_str *str);
int init_transformer_view(transformer_view_str *str);

extern transformer_view_str transformer_view;

#endif

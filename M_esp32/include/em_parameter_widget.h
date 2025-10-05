#ifndef PARAM_WIDGET_H_
#define PARAM_WIDGET_H_

#include "em_parameter.h"

#define PARAM_WIDGET_LABEL_BUFSIZE 16

typedef enum
{
	VIRTUAL_POT
} param_widget_type;

typedef struct
{
	param_widget_type type;
	m_parameter_id id;
	
	m_param_value factor;
	
	teensy_parameter *param;
	
	char val_label_text[PARAM_WIDGET_LABEL_BUFSIZE];
	lv_obj_t *val_label;
	lv_obj_t *name_label;
	lv_obj_t *obj;
} parameter_widget;

int nullify_parameter_widget(parameter_widget *pw);
int configure_parameter_widget(parameter_widget *pw, teensy_parameter *param);

int parameter_widget_create_ui(parameter_widget *pw, lv_obj_t *parent);

int param_widget_request_value(parameter_widget *pw);

void update_virtual_pot_value_label(parameter_widget *pot);
void virtual_pot_refresh_cb(lv_event_t *event);
void virtual_pot_change_cb(lv_event_t *event);

#endif

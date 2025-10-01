#ifndef PARAM_WIDGET_H_
#define PARAM_WIDGET_H_

#include "m_parameter.h"

typedef enum
{
	VIRTUAL_POT
} param_widget_type;

typedef struct
{
	param_widget_type type;
	m_parameter_id id;
	
	m_param_value val_recieved;
	m_param_value val;
	m_param_value min;
	m_param_value max;
	
	const char *label;
	char val_label_text[16];
	lv_obj_t *val_label;
	lv_obj_t *name_label;
	lv_obj_t *obj;
} parameter_widget;

int init_virtual_pot_ui(parameter_widget *pw, lv_obj_t *parent);
int init_virtual_pot_param(parameter_widget *pw, const char *label, m_parameter_id id, m_param_level_t initial_value, m_param_level_t min, m_param_level_t max);

int request_param_widget_value(parameter_widget *pw);

void update_virtual_pot_value_label(parameter_widget *pot);

#endif

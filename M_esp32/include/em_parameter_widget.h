#ifndef EM_PARAMETER_WIDGET_H_
#define EM_PARAMETER_WIDGET_H_

#define PARAM_WIDGET_LABEL_BUFSIZE 16

typedef enum
{
	VIRTUAL_POT
} param_widget_type;

typedef struct
{
	param_widget_type type;
	em_parameter_id id;
	
	em_parameter *param;
	
	char val_label_text[PARAM_WIDGET_LABEL_BUFSIZE];
	lv_obj_t *val_label;
	lv_obj_t *name_label;
	lv_obj_t *obj;
} em_parameter_widget;

int nullify_em_parameter_widget(em_parameter_widget *pw);
int configure_em_parameter_widget(em_parameter_widget *pw, em_parameter *param);

int parameter_widget_create_ui(em_parameter_widget *pw, lv_obj_t *parent);

int param_widget_request_value(em_parameter_widget *pw);

void update_virtual_pot_value_label(em_parameter_widget *pot);

void virtual_pot_refresh_cb(lv_event_t *event);
void virtual_pot_change_cb(lv_event_t *event);

void free_parameter_widget(em_parameter_widget *pw);

DECLARE_LINKED_PTR_LIST(em_parameter_widget);

#endif

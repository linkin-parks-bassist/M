#ifndef EM_PARAMETER_WIDGET_H_
#define EM_PARAMETER_WIDGET_H_

#define PARAM_WIDGET_LABEL_BUFSIZE 16

#define PARAMETER_WIDGET_RANGE_SIZE 1000.0

#define PARAM_WIDGET_VIRTUAL_POT 0
#define PARAM_WIDGET_HSLIDER 	 1
#define PARAM_WIDGET_VSLIDER 	 2

#define OPTION_WIDGET_DROPDOWN	 1
#define OPTION_WIDGET_SWITCH 	 2

#define PARAM_WIDGET_SIZE_H 170
#define PARAM_WIDGET_SIZE_W 170

#define PARAM_WIDGET_PAD_H	10
#define PARAM_WIDGET_PAD_W	10

#define VIRTUAL_POT_SIZE_H 160
#define VIRTUAL_POT_SIZE_W 160

#define HSLIDER_SIZE_H 15
#define HSLIDER_SIZE_W 165

#define HSLIDER_H_PAD 50
#define HSLIDER_W_PAD 10

#define VSLIDER_SIZE_H 150
#define VSLIDER_SIZE_W 15

#define VSLIDER_H_PAD 40
#define VSLIDER_W_PAD 90

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
	lv_obj_t *container;
	lv_obj_t *obj;
} em_parameter_widget;

int nullify_em_parameter_widget(em_parameter_widget *pw);
int configure_em_parameter_widget(em_parameter_widget *pw, em_parameter *param);

int parameter_widget_create_ui(em_parameter_widget *pw, lv_obj_t *parent);

int param_widget_request_value(em_parameter_widget *pw);

void parameter_widget_update_value_label(em_parameter_widget *pot);

void parameter_widget_refresh_cb(lv_event_t *event);
void parameter_widget_refresh_cb(lv_event_t *event);

void free_parameter_widget(em_parameter_widget *pw);

DECLARE_LINKED_PTR_LIST(em_parameter_widget);

#endif

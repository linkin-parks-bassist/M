#ifndef M_INT_PARAMETER_WIDGET_H_
#define M_INT_PARAMETER_WIDGET_H_

#define PARAM_WIDGET_LABEL_BUFSIZE 32

#define PARAMETER_WIDGET_RANGE_SIZE 1000.0

#define PARAM_WIDGET_VIRTUAL_POT  0
#define PARAM_WIDGET_HSLIDER 	  1
#define PARAM_WIDGET_VSLIDER 	  2
#define PARAM_WIDGET_VSLIDER_TALL 3

#define PARAM_WIDGET_SIZE_H 170
#define PARAM_WIDGET_SIZE_W 170

#define VIRTUAL_POT_SIZE_H 125
#define VIRTUAL_POT_SIZE_W 125

#define VPOT_PAD_H 45
#define VPOT_PAD_W 70

#define HSLIDER_SIZE_H 15
#define HSLIDER_SIZE_W 165

#define HSLIDER_PAD_H 50
#define HSLIDER_PAD_W 10

#define VSLIDER_SIZE_H 150
#define VSLIDER_SIZE_W 15

#define VSLIDER_PAD_H 40
#define VSLIDER_PAD_W 90

#define VSLIDER_TALL_SIZE_H 300
#define VSLIDER_TALL_SIZE_W 15

#define VSLIDER_TALL_PAD_H 120
#define VSLIDER_TALL_PAD_W 80

struct m_profile;

typedef struct
{
	int type;
	m_parameter_id id;
	
	m_parameter *param;
	struct m_profile *profile;
	
	char val_label_text[PARAM_WIDGET_LABEL_BUFSIZE];
	lv_obj_t *val_label;
	lv_obj_t *name_label;
	lv_obj_t *container;
	lv_obj_t *obj;
} m_parameter_widget;

int nullify_parameter_widget(m_parameter_widget *pw);
int configure_parameter_widget(m_parameter_widget *pw, m_parameter *param, struct m_profile *profile);

int parameter_widget_create_ui(m_parameter_widget *pw, lv_obj_t *parent);
int parameter_widget_create_ui_no_callback(m_parameter_widget *pw, lv_obj_t *parent);

int param_widget_request_value(m_parameter_widget *pw);

void parameter_widget_update_value_label(m_parameter_widget *pot);

void parameter_widget_change_cb_inner(m_parameter_widget *pw);
void parameter_widget_refresh_cb(lv_event_t *event);

void free_parameter_widget(m_parameter_widget *pw);

DECLARE_LINKED_PTR_LIST(m_parameter_widget);


//
//
//
// === setting widget ===
//
//
//


#define SETTING_WIDGET_DROPDOWN	 0
#define SETTING_WIDGET_SWITCH 	 1
#define SETTING_WIDGET_FIELD 	 2

typedef struct
{
	int type;
	m_parameter_id id;
	
	m_setting *setting;
	struct m_profile *profile;
	
	lv_obj_t *container;
	lv_obj_t *obj;
	lv_obj_t *label;
	lv_obj_t *pad;
	
	const char *name;
} m_setting_widget;

int nullify_setting_widget(m_setting_widget *pw);
int configure_setting_widget(m_setting_widget *pw, m_setting *setting, struct m_profile *profile);

int setting_widget_create_ui(m_setting_widget *pw, lv_obj_t *parent);
int setting_widget_create_ui_no_callback(m_setting_widget *pw, lv_obj_t *parent);

int setting_widget_request_value(m_setting_widget *pw);

void setting_widget_update_value_label(m_setting_widget *pot);

void setting_widget_change_cb_inner(m_setting_widget *pw);
void setting_widget_refresh_cb(lv_event_t *event);

void free_setting_widget(m_setting_widget *pw);

DECLARE_LINKED_PTR_LIST(m_setting_widget);

#endif

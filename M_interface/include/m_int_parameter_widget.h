#ifndef M_INT_PARAMETER_WIDGET_H_
#define M_INT_PARAMETER_WIDGET_H_

#define PARAM_WIDGET_LABEL_BUFSIZE 32

#define PARAMETER_WIDGET_RANGE_SIZE 1000.0

#define PARAM_WIDGET_VIRTUAL_POT  0
#define PARAM_WIDGET_HSLIDER 	  1
#define PARAM_WIDGET_VSLIDER 	  2
#define PARAM_WIDGET_VSLIDER_TALL 3

#define PARAM_WIDGET_SIZE_H ((int)(0.16 * DISPLAY_VRES))
#define PARAM_WIDGET_SIZE_W PARAM_WIDGET_SIZE_H

#define VIRTUAL_POT_SIZE_H ((int)(0.13 * DISPLAY_VRES))
#define VIRTUAL_POT_SIZE_W VIRTUAL_POT_SIZE_H

#define VPOT_PAD_H ((int)((45.0  / 1024.0) * DISPLAY_VRES))
#define VPOT_PAD_W ((int)((70.0  / 600.0)  * DISPLAY_HRES))

#define HSLIDER_SIZE_H ((int)((15.0  / 1024.0) * DISPLAY_VRES))
#define HSLIDER_SIZE_W ((int)((165.0 / 600.0)  * DISPLAY_HRES))

#define HSLIDER_PAD_H  ((int)((50.0  / 1024.0) * DISPLAY_VRES))
#define HSLIDER_PAD_W  ((int)((10.0  / 600.0)  * DISPLAY_HRES))

#define VSLIDER_SIZE_H ((int)((150.0 / 1024.0) * DISPLAY_VRES))
#define VSLIDER_SIZE_W ((int)((15.0  / 600.0)  * DISPLAY_HRES))

#define VSLIDER_PAD_H  ((int)((40.0  / 1024.0) * DISPLAY_VRES))
#define VSLIDER_PAD_W  ((int)((90.0  / 600.0)  * DISPLAY_HRES))

#define VSLIDER_TALL_SIZE_H ((int)((300.0 / 1024.0) * DISPLAY_VRES))
#define VSLIDER_TALL_SIZE_W ((int)((15.0  / 600.0)  * DISPLAY_HRES))

#define VSLIDER_TALL_PAD_H  ((int)((120.0 / 1024.0) * DISPLAY_VRES))
#define VSLIDER_TALL_PAD_W  ((int)((80.0  / 600.0)  * DISPLAY_HRES))

struct m_profile;

typedef struct
{
	int type;
	m_parameter_id id;
	
	m_parameter *param;
	struct m_profile *profile;
	m_ui_page *parent;
	
	char val_label_text[PARAM_WIDGET_LABEL_BUFSIZE];
	lv_obj_t *val_label;
	lv_obj_t *name_label;
	lv_obj_t *container;
	lv_obj_t *obj;
	
	m_representation rep;
} m_parameter_widget;

int nullify_parameter_widget(m_parameter_widget *pw);
int configure_parameter_widget(m_parameter_widget *pw, m_parameter *param, struct m_profile *profile, m_ui_page *parent);

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
	m_ui_page *parent;
	
	lv_obj_t *container;
	lv_obj_t *obj;
	lv_obj_t *label;
	lv_obj_t *pad;
	
	const char *name;
	
	char *saved_field_text;
	
	m_representation rep;
} m_setting_widget;

int nullify_setting_widget(m_setting_widget *pw);
int configure_setting_widget(m_setting_widget *pw, m_setting *setting, struct m_profile *profile, m_ui_page *parent);

int setting_widget_create_ui(m_setting_widget *pw, lv_obj_t *parent);
int setting_widget_create_ui_no_callback(m_setting_widget *pw, lv_obj_t *parent);

int setting_widget_request_value(m_setting_widget *pw);

void setting_widget_update_value_label(m_setting_widget *pot);

void setting_widget_change_cb_inner(m_setting_widget *pw);
void setting_widget_refresh_cb(lv_event_t *event);

void free_setting_widget(m_setting_widget *pw);

DECLARE_LINKED_PTR_LIST(m_setting_widget);

#endif

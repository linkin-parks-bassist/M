#ifndef M_PARAMETER_H_
#define M_PARAMETER_H_

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

#define PARAM_NAME_MAX_LEN 254

#define PARAM_WIDGET_VIRTUAL_POT 0

#define OPTION_WIDGET_HSLIDER 	 0
#define OPTION_WIDGET_VSLIDER 	 1
#define OPTION_WIDGET_SWITCH 	 2

typedef struct
{
	uint16_t profile_id;
	uint16_t transformer_id;
	uint16_t parameter_id;
} em_parameter_id;

typedef em_parameter_id em_option_id;

typedef struct
{
	em_parameter_id id;
	
	float val;
	float min;
	float max;
	
	float factor;
	
	int widget_type;
	char *name;
} em_parameter;

typedef struct
{
	uint16_t value;
	char *name;
} em_option_option;

typedef struct
{
	em_option_id id;
	
	uint16_t val;
	
	int n_options;
	em_option_option **options;
	
	int widget_type;
	char *name;
} em_option;

int init_em_parameter(em_parameter *param);
int init_parameter(em_parameter *param, char *name, float level, float min, float max);

int init_em_option(em_option *option);
int init_option(em_option *option, char *name, uint16_t level);

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

#endif

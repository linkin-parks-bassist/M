#include "m_int.h"

static const char *TAG = "m_int_parameter_widget.c";

IMPLEMENT_LINKED_PTR_LIST(m_int_parameter_widget);

int format_float(char *buf, float val, int max_len)
{
	if (!buf) return 0;

	char tmp[10];
	int i = 0;
	
	// Handle negative numbers
	int is_neg = (val < 0);
	if (is_neg)
		val = -val;

	// Multiply and round to 2 decimal places
	int scaled 	  = (int)roundf(val * 100.0f);
	int int_part  = scaled / 100;
	int frac_part = scaled % 100;

	// Write manually to buffer
	int pos = 0;

	if (is_neg)
		buf[pos++] = '-';

	if (int_part == 0)
	{
		buf[pos++] = '0';
	}
	else
	{
		while (int_part > 0)
		{
			tmp[i++] = '0' + (int_part % 10);
			int_part /= 10;
		}
		
		while (i-- && pos < max_len - 1)
		{
			buf[pos++] = tmp[i];
		}
		
		if (pos == max_len - 1)
		{
			buf[pos] = 0;
			return pos;
		}
	}

	tmp[0] = (pos < 5) ? '.' : 0;
	tmp[1] = (pos < 5) ? '0' + (frac_part / 10) : 0;
	tmp[2] = (pos < 4) ? '0' + (frac_part % 10) : 0;
	tmp[3] = 0;
	
	for (i = 0; i < 4 && pos < max_len - 1 && tmp[i]; i++)
		buf[pos++] = tmp[i];

	buf[pos] = 0;
	
	return pos - 1;
}

int nullify_parameter_widget(m_int_parameter_widget *pw)
{
	if (!pw)
		return ERR_NULL_PTR;
	
	pw->param 		= NULL;
	
	pw->obj 		= NULL;
	pw->name_label  = NULL;
	pw->val_label   = NULL;
	pw->container   = NULL;
	
	pw->val_label_text[0] = 0;
	
	return NO_ERROR;
}

void format_parameter_widget_value_label(m_int_parameter_widget *pw)
{
	if (!pw || !pw->param)
		return;
	
	int i = format_float(pw->val_label_text, pw->param->val, PARAM_WIDGET_LABEL_BUFSIZE);
	
	if (pw->param->units && i < PARAM_WIDGET_LABEL_BUFSIZE)
	{
		snprintf(&pw->val_label_text[i], PARAM_WIDGET_LABEL_BUFSIZE - i, "%s", pw->param->units);
	}
}

int parameter_widget_update_value(m_int_parameter_widget *pw)
{
	if (!pw)
		return ERR_NULL_PTR;
	
	if (!pw->param || !pw->obj)
		return ERR_BAD_ARGS;
	
	uint32_t val;
	
	if (fabsf(pw->param->max - pw->param->min) < 1e-6)
	{
		val = (int)PARAMETER_WIDGET_RANGE_SIZE/2;
	}
	else
	{
		if (pw->param->scale == PARAMETER_SCALE_LOGARITHMIC)
		{
			
			val = PARAMETER_WIDGET_RANGE_SIZE * ((logf(pw->param->val) - logf(pw->param->min)) /
												 (logf(pw->param->max) - logf(pw->param->min)));
		}
		else
		{
			val = PARAMETER_WIDGET_RANGE_SIZE * ((pw->param->val - pw->param->min) /
												 (pw->param->max - pw->param->min));
		}
	}
	
	switch (pw->param->widget_type)
	{
		case PARAM_WIDGET_VSLIDER_TALL:
		case PARAM_WIDGET_VSLIDER:
		case PARAM_WIDGET_HSLIDER:
			lv_slider_set_value(pw->obj, val, LV_ANIM_ON);
			break;
			
		default:
			lv_arc_set_value(pw->obj, val);
			break;
	}
	
	return NO_ERROR;
}

void parameter_widget_update_value_label(m_int_parameter_widget *pw)
{
	if (!pw)
		return;
	
	format_parameter_widget_value_label(pw);
	
	int len = strlen(pw->val_label_text);
	
	lv_label_set_text(pw->val_label, pw->val_label_text);
}

int configure_parameter_widget(m_int_parameter_widget *pw, m_int_parameter *param, m_int_profile *profile)
{
	if (!pw || !param)
		return ERR_NULL_PTR;
	
	pw->param = param;
	pw->profile = profile;
	
	format_float(pw->val_label_text, pw->param->val, PARAM_WIDGET_LABEL_BUFSIZE);
	
	return NO_ERROR;
}

void parameter_widget_refresh_cb(lv_event_t *event)
{
	m_int_parameter_widget *pw = lv_event_get_user_data(event);
	
	if (!pw)
	{
		ESP_LOGE(TAG, "NULL virtual pw pointer");
		return;
	}
	
	parameter_widget_update_value(pw);
	
	parameter_widget_update_value_label(pw);
}

void parameter_widget_change_cb_inner(m_int_parameter_widget *pw)
{
	float val;
	
	switch (pw->param->widget_type)
	{
		case PARAM_WIDGET_VSLIDER_TALL:
		case PARAM_WIDGET_VSLIDER:
		case PARAM_WIDGET_HSLIDER:
			val = (float)lv_slider_get_value(pw->obj);
			break;
			
		default:
			val = (float)lv_arc_get_value(pw->obj);
			break;
	}
	
	val /= PARAMETER_WIDGET_RANGE_SIZE;
	
	switch (pw->param->scale)
	{
		case PARAMETER_SCALE_LOGARITHMIC:
			float lnmin = logf(pw->param->min);
			float lnmax = logf(pw->param->max);
			
			pw->param->val = expf(lnmin + val * (lnmax - lnmin));
			break;
		
		default:
			pw->param->val = pw->param->min + val * (pw->param->max - pw->param->min);
			break;
	}
	
	parameter_widget_update_value_label(pw);
	
	et_msg msg = create_et_msg(ET_MESSAGE_SET_PARAM_VALUE, "sssf", pw->param->id.profile_id, pw->param->id.transformer_id, pw->param->id.parameter_id, pw->param->val);

	queue_msg_to_teensy(msg);
	
	if (pw->profile)
	{
		pw->profile->unsaved_changes = 1;
	}
	else
	{
		global_cxt.settings.changed = 1;
	}
}

void parameter_widget_change_cb(lv_event_t *event)
{
	m_int_parameter_widget *pw = lv_event_get_user_data(event);
	
	if (!pw)
	{
		ESP_LOGE(TAG, "NULL virtual pw pointer");
		return;
	}
	
	parameter_widget_change_cb_inner(pw);
}

int parameter_widget_create_ui(m_int_parameter_widget *pw, lv_obj_t *parent)
{
	if (!pw)
		return ERR_NULL_PTR;
	
	int ret_val;
	if ((ret_val = parameter_widget_create_ui_no_callback(pw, parent)) != NO_ERROR)
		return ret_val;
	
	lv_obj_add_event_cb(pw->obj, parameter_widget_change_cb, LV_EVENT_VALUE_CHANGED, pw);
	
	return NO_ERROR;
}

int parameter_widget_create_ui_no_callback(m_int_parameter_widget *pw, lv_obj_t *parent)
{
	if (!pw || !pw->param || !parent)
		return ERR_NULL_PTR;
	
	pw->container = lv_obj_create(parent);
	lv_obj_remove_style_all(pw->container);
	
	switch (pw->param->widget_type)
	{	
		case PARAM_WIDGET_HSLIDER:
			pw->obj = lv_slider_create(pw->container);
			
			lv_obj_align(pw->obj, LV_ALIGN_CENTER, 0, 20);
			lv_obj_set_size(pw->obj, HSLIDER_SIZE_W, HSLIDER_SIZE_H);
			
			lv_obj_set_size(pw->container, HSLIDER_SIZE_W + HSLIDER_PAD_W, HSLIDER_SIZE_H + HSLIDER_PAD_H);
			
			pw->name_label = lv_label_create(pw->container);
			lv_label_set_text(pw->name_label, pw->param->name);
			lv_obj_align_to(pw->name_label, pw->obj, LV_ALIGN_OUT_TOP_LEFT, 20, -35);
			
			pw->val_label = lv_label_create(pw->container);
			lv_obj_align_to(pw->val_label, pw->obj, LV_ALIGN_OUT_TOP_RIGHT, 30, -35);
			
			lv_slider_set_range(pw->obj, 0, (int)PARAMETER_WIDGET_RANGE_SIZE);
			break;
		
		case PARAM_WIDGET_VSLIDER:
			pw->obj = lv_slider_create(pw->container);
			
			lv_obj_align(pw->obj, LV_ALIGN_CENTER, 0, VSLIDER_PAD_H / 2);
			lv_obj_set_size(pw->obj, VSLIDER_SIZE_W, VSLIDER_SIZE_H);
			
			
			lv_obj_set_size(pw->container, VSLIDER_SIZE_W + VSLIDER_PAD_W, VSLIDER_SIZE_H + VSLIDER_PAD_H);
			
			pw->name_label = lv_label_create(pw->container);
			lv_label_set_text(pw->name_label, pw->param->name);
			lv_obj_align_to(pw->name_label, pw->obj, LV_ALIGN_OUT_TOP_MID, 0, 20);
			
			pw->val_label = lv_label_create(pw->container);
			lv_obj_align_to(pw->val_label, pw->obj, LV_ALIGN_OUT_BOTTOM_LEFT, 15, 0);
			
			lv_slider_set_range(pw->obj, 0, (int)PARAMETER_WIDGET_RANGE_SIZE);
			break;
		
		case PARAM_WIDGET_VSLIDER_TALL:
			pw->obj = lv_slider_create(pw->container);
			
			lv_obj_align(pw->obj, LV_ALIGN_CENTER, 0, 30);
			lv_obj_set_size(pw->obj, VSLIDER_TALL_SIZE_W, VSLIDER_TALL_SIZE_H);
			
			lv_obj_set_size(pw->container, VSLIDER_TALL_SIZE_W + VSLIDER_TALL_PAD_W, VSLIDER_TALL_SIZE_H + VSLIDER_TALL_PAD_H);
			
			pw->name_label = lv_label_create(pw->container);
			lv_label_set_text(pw->name_label, pw->param->name);
			lv_obj_align_to(pw->name_label, pw->obj, LV_ALIGN_TOP_MID, 0, -30);
			
			pw->val_label = lv_label_create(pw->container);
			lv_obj_align_to(pw->val_label, pw->obj, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
			
			lv_slider_set_range(pw->obj, 0, (int)PARAMETER_WIDGET_RANGE_SIZE);
			break;
			
		default:
			pw->obj = lv_arc_create(pw->container);
			
			lv_obj_set_size(pw->container, VIRTUAL_POT_SIZE_W + VPOT_PAD_W, VIRTUAL_POT_SIZE_H + VPOT_PAD_H);
			
			lv_obj_align(pw->obj, LV_ALIGN_CENTER, 0, -15);
			lv_obj_set_size(pw->obj, VIRTUAL_POT_SIZE_W, VIRTUAL_POT_SIZE_H);
			
			lv_arc_set_rotation(pw->obj, 135);
			lv_arc_set_bg_angles(pw->obj, 0, 270);
			lv_arc_set_range(pw->obj, 0, (int)PARAMETER_WIDGET_RANGE_SIZE);
			
			pw->name_label = lv_label_create(pw->container);
			lv_label_set_text(pw->name_label, pw->param->name);
			lv_obj_align(pw->name_label, LV_ALIGN_BOTTOM_MID, 0, 0);
			lv_obj_set_size(pw->name_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
			
			pw->val_label = lv_label_create(pw->obj);
			lv_obj_center(pw->val_label);
			break;
	}
	
	parameter_widget_update_value(pw);
	parameter_widget_update_value_label(pw);
	
	return NO_ERROR;
}

void param_widget_receive(et_msg msg, te_msg response)
{
	m_int_parameter_widget *pw = (m_int_parameter_widget*)msg.cb_arg;
	
	if (!pw || !pw->param)
		return;
	
	if (response.type != TE_MESSAGE_PARAM_VALUE)
	{
		#ifndef M_SIMULATED
		ESP_LOGE(TAG, "Weird message (%d) send to parameter widget...\n", response.type);
		#endif
		return;
	}
	
	// Check we're getting values for the right parameter
	uint16_t profile_id, transformer_id, parameter_id;
	
	memcpy(&profile_id, 	&response.data[0], sizeof(uint16_t));
	memcpy(&transformer_id, &response.data[2], sizeof(uint16_t));
	memcpy(&parameter_id, 	&response.data[4], sizeof(uint16_t));
	
	if (profile_id 	   == pw->param->id.profile_id
	 && transformer_id == pw->param->id.transformer_id
	 && parameter_id   == pw->param->id.parameter_id)
	{
		memcpy(&pw->param->val, &response.data[6], sizeof(float));
		
		printf("Parameter %d.%d.%d value revieced: %f\n", profile_id, transformer_id, parameter_id, pw->param->val);
		parameter_widget_update_value(pw);
		parameter_widget_update_value_label(pw);
	}
	else
	{
		#ifndef M_SIMULATED
		ESP_LOGE(TAG, "Data for parameter %d.%d.%d received by parameter %d.%d.%d...",
			profile_id, transformer_id, parameter_id, 
			pw->param->id.profile_id, pw->param->id.transformer_id, pw->param->id.parameter_id); 
		#endif
	}
}

int param_widget_request_value(m_int_parameter_widget *pw)
{
	printf("param_widget_request_value...\n");
	if (!pw)
		return ERR_NULL_PTR;
	
	et_msg msg = create_et_msg(ET_MESSAGE_GET_PARAM_VALUE, "sss", pw->param->id.profile_id, pw->param->id.transformer_id, pw->param->id.parameter_id);
	msg.callback = param_widget_receive;
	msg.cb_arg = pw;

	queue_msg_to_teensy(msg);
	
	printf("param_widget_request_value done!\n");
	return NO_ERROR;
}

//
//
//
// === setting widget ===
//
//
//

void free_parameter_widget(m_int_parameter_widget *pw)
{
	if (!pw)
		return;
	
	// Currently the m_int_parameter_widget struct contains nothing that
	// it owns itself. This may change !
	m_int_free(pw);
}

int nullify_setting_widget(m_int_setting_widget *sw)
{
	if (!sw)
		return ERR_NULL_PTR;
	
	sw->setting = NULL;
	
	sw->obj = NULL;
	
	sw->type = SETTING_WIDGET_DROPDOWN;
	
	return NO_ERROR;
}

int setting_widget_update_value(m_int_setting_widget *sw)
{
	if (!sw)
		return ERR_NULL_PTR;
	
	if (!sw->setting || !sw->obj)
		return ERR_BAD_ARGS;
	
	
	return NO_ERROR;
}

void setting_widget_update_value_label(m_int_setting_widget *sw)
{
	if (!sw)
		return;
	
}

int configure_setting_widget(m_int_setting_widget *sw, m_int_setting *setting, m_int_profile *profile)
{
	if (!sw || !setting)
		return ERR_NULL_PTR;
	
	sw->setting = setting;
	sw->profile = profile;
	
	return NO_ERROR;
}

void setting_widget_refresh_cb(lv_event_t *event)
{
	m_int_setting_widget *sw = lv_event_get_user_data(event);
	
	if (!sw)
		return;
}

void setting_widget_change_cb_inner(m_int_setting_widget *sw)
{	
	et_msg msg = create_et_msg(ET_MESSAGE_SET_SETTING_VALUE, "sssf", sw->setting->id.profile_id, sw->setting->id.transformer_id, sw->setting->id.parameter_id, sw->setting->val);

	queue_msg_to_teensy(msg);
	
	if (sw->profile)
	{
		sw->profile->unsaved_changes = 1;
	}
	else
	{
		global_cxt.settings.changed = 1;
	}
}

void setting_widget_change_cb(lv_event_t *event)
{
	m_int_setting_widget *sw = lv_event_get_user_data(event);
	
	if (!sw)
	{
		ESP_LOGE(TAG, "NULL virtual sw pointer");
		return;
	}
	
	setting_widget_change_cb_inner(sw);
}

int setting_widget_create_ui(m_int_setting_widget *sw, lv_obj_t *parent)
{
	if (!sw)
		return ERR_NULL_PTR;
	
	int ret_val;
	if ((ret_val = setting_widget_create_ui_no_callback(sw, parent)) != NO_ERROR)
		return ret_val;
	
	lv_obj_add_event_cb(sw->obj, setting_widget_change_cb, LV_EVENT_VALUE_CHANGED, sw);
	
	return NO_ERROR;
}

int setting_widget_create_ui_no_callback(m_int_setting_widget *sw, lv_obj_t *parent)
{
	if (!sw || !sw->setting || !parent)
		return ERR_NULL_PTR;
	
	sw->container = lv_obj_create(parent);
	lv_obj_remove_style_all(sw->container);
	lv_obj_clear_flag(sw->container, LV_OBJ_FLAG_SCROLLABLE);
	
	
	switch (sw->setting->widget_type)
	{	
		case SETTING_WIDGET_DROPDOWN:
			printf("Creating label for setting %s\n", sw->setting->name);
			
			lv_obj_set_layout(sw->container, LV_LAYOUT_FLEX);
			lv_obj_set_flex_flow(sw->container, LV_FLEX_FLOW_ROW);
			lv_obj_set_flex_align(sw->container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
			
			sw->label = lv_label_create(sw->container);
			lv_label_set_text(sw->label, sw->setting->name);
			lv_obj_set_flex_grow(sw->label, 1);
			
			sw->pad = lv_obj_create(sw->container);
			lv_obj_remove_style_all(sw->pad);
			//lv_obj_set_flex_grow(sw->pad, 1);
			
			sw->obj = lv_dropdown_create(sw->container);
			lv_obj_set_flex_grow(sw->obj, 2);
			lv_dropdown_clear_options(sw->obj);
			
			lv_obj_set_size(sw->container, STANDARD_CONTAINER_WIDTH - 40, STANDARD_BUTTON_SHORT_HEIGHT);
			
			//lv_dropdown_set_options(sw->container, "");
			
			for (int i = 0; i < sw->setting->n_options; i++)
			{
				lv_dropdown_add_option(sw->obj, sw->setting->options[i].name, i);
			}
			
			lv_dropdown_close(sw->obj);
			
			break;
			
		case SETTING_WIDGET_SWITCH:
			break;
			
		case SETTING_WIDGET_FIELD:
			break;
	}
	
	setting_widget_update_value(sw);
	setting_widget_update_value_label(sw);
	
	return NO_ERROR;
}

void setting_widget_receive(et_msg msg, te_msg response)
{
	m_int_setting_widget *sw = (m_int_setting_widget*)msg.cb_arg;
	
	if (!sw || !sw->setting)
		return;
	
	if (response.type != TE_MESSAGE_SETTING_VALUE)
	{
		#ifndef M_SIMULATED
		ESP_LOGE(TAG, "Weird message (%d) send to setting widget...\n", response.type);
		#endif
		return;
	}
	
	// Check we're getting values for the right setting
	uint16_t profile_id, transformer_id, parameter_id;
	
	memcpy(&profile_id, 	&response.data[0], sizeof(uint16_t));
	memcpy(&transformer_id, &response.data[2], sizeof(uint16_t));
	memcpy(&parameter_id, 	&response.data[4], sizeof(uint16_t));
	
	if (profile_id 	   == sw->setting->id.profile_id
	 && transformer_id == sw->setting->id.transformer_id
	 && parameter_id   == sw->setting->id.parameter_id)
	{
		memcpy(&sw->setting->val, &response.data[6], sizeof(float));
		
		printf("Parameter %d.%d.%d value revieced: %f\n", profile_id, transformer_id, parameter_id, sw->setting->val);
		setting_widget_update_value(sw);
		setting_widget_update_value_label(sw);
	}
	else
	{
		#ifndef M_SIMULATED
		ESP_LOGE(TAG, "Data for setting %d.%d.%d received by setting %d.%d.%d...",
			profile_id, transformer_id, parameter_id, 
			sw->setting->id.profile_id, sw->setting->id.transformer_id, sw->setting->id.parameter_id); 
		#endif
	}
}

int setting_widget_request_value(m_int_setting_widget *sw)
{
	printf("setting_widget_request_value...\n");
	if (!sw)
		return ERR_NULL_PTR;
	
	et_msg msg = create_et_msg(ET_MESSAGE_GET_SETTING_VALUE, "sss", sw->setting->id.profile_id, sw->setting->id.transformer_id, sw->setting->id.parameter_id);
	msg.callback = setting_widget_receive;
	msg.cb_arg = sw;

	queue_msg_to_teensy(msg);
	
	printf("setting_widget_request_value done!\n");
	return NO_ERROR;
}

void free_setting_widget(m_int_setting_widget *sw)
{
	if (!sw)
		return;
	
	// Currently the m_int_setting_widget struct contains nothing that
	// it owns itself. This may change !
	m_int_free(sw);
}

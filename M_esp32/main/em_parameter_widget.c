#include "em.h"

static const char *TAG = "em_parameter_widget.c";

IMPLEMENT_LINKED_PTR_LIST(em_parameter_widget);

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

	buf[pos++] = 0;
	
	return pos;
}

int nullify_em_parameter_widget(em_parameter_widget *pw)
{
	if (!pw)
		return ERR_NULL_PTR;
	
	pw->param 		= NULL;
	
	pw->obj 		= NULL;
	pw->name_label  = NULL;
	pw->val_label   = NULL;
	pw->container   = NULL;
	
	return NO_ERROR;
}

void format_parameter_widget_value_label(em_parameter_widget *pw)
{
	if (!pw || !pw->param)
		return;
	
	int i = format_float(pw->val_label_text, pw->param->val, PARAM_WIDGET_LABEL_BUFSIZE);
	
	if (pw->param->units)
		strncpy(&pw->val_label_text[i ? i - 1 : 0], pw->param->units, PARAM_WIDGET_LABEL_BUFSIZE - i);
}

int parameter_widget_update_value(em_parameter_widget *pw)
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

void parameter_widget_update_value_label(em_parameter_widget *pw)
{
	if (!pw)
		return;
	
	format_parameter_widget_value_label(pw);
	
	lv_label_set_text(pw->val_label, pw->val_label_text);
}

int configure_em_parameter_widget(em_parameter_widget *pw, em_parameter *param)
{
	if (!pw || !param)
		return ERR_NULL_PTR;
	
	pw->param = param;
	
	format_float(pw->val_label_text, pw->param->val, PARAM_WIDGET_LABEL_BUFSIZE);
	
	return NO_ERROR;
}

void parameter_widget_refresh_cb(lv_event_t *event)
{
	em_parameter_widget *pw = lv_event_get_user_data(event);
	
	if (!pw)
	{
		ESP_LOGE(TAG, "NULL virtual pw pointer");
		return;
	}
	
	parameter_widget_update_value(pw);
	
	parameter_widget_update_value_label(pw);
}

void parameter_widget_change_cb(lv_event_t *event)
{
	em_parameter_widget *pw = lv_event_get_user_data(event);
	
	if (!pw)
	{
		ESP_LOGE(TAG, "NULL virtual pw pointer");
		return;
	}
	
	float val;
	
	switch (pw->param->widget_type)
	{
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
	
	et_msg msg = create_et_msg_set_param(pw->param->id.profile_id, pw->param->id.transformer_id, pw->param->id.parameter_id, pw->param->val);

	xQueueSend(et_msg_queue, (void*)&msg, 0);
}

int parameter_widget_create_ui(em_parameter_widget *pw, lv_obj_t *parent)
{
	if (!pw || !pw->param || !parent)
		return ERR_NULL_PTR;
	
	pw->container = lv_obj_create(parent);
	lv_obj_remove_style_all(pw->container);
	
	int w, h;
	//lv_obj_set_size(pw->container, PARAM_WIDGET_SIZE_W + PARAM_WIDGET_PAD_W, PARAM_WIDGET_SIZE_H + PARAM_WIDGET_PAD_H);
	
	switch (pw->param->widget_type)
	{	
		case PARAM_WIDGET_HSLIDER:
			pw->obj = lv_slider_create(pw->container);
			
			lv_obj_align(pw->obj, LV_ALIGN_CENTER, 0, 20);
			lv_obj_set_size(pw->obj, HSLIDER_SIZE_W, HSLIDER_SIZE_H);
			
			w = HSLIDER_SIZE_W + HSLIDER_W_PAD;
			h = HSLIDER_SIZE_H + HSLIDER_H_PAD;
			
			pw->name_label = lv_label_create(pw->container);
			lv_label_set_text(pw->name_label, pw->param->name);
			lv_obj_align_to(pw->name_label, pw->obj, LV_ALIGN_OUT_TOP_LEFT, 20, -35);
			
			pw->val_label = lv_label_create(pw->container);
			lv_obj_align_to(pw->val_label, pw->obj, LV_ALIGN_OUT_TOP_RIGHT, 30, -35);
			
			lv_slider_set_range(pw->obj, 0, (int)PARAMETER_WIDGET_RANGE_SIZE);
			break;
		
		case PARAM_WIDGET_VSLIDER:
			pw->obj = lv_slider_create(pw->container);
			
			lv_obj_align(pw->obj, LV_ALIGN_CENTER, 0, 20);
			lv_obj_set_size(pw->obj, VSLIDER_SIZE_W, VSLIDER_SIZE_H);
			
			w = VSLIDER_SIZE_W + VSLIDER_W_PAD;
			h = VSLIDER_SIZE_H + VSLIDER_H_PAD;
			
			pw->name_label = lv_label_create(pw->container);
			lv_label_set_text(pw->name_label, pw->param->name);
			lv_obj_set_style_transform_angle(pw->name_label, 0, 0);
			lv_obj_align_to(pw->name_label, pw->obj, LV_ALIGN_OUT_TOP_MID, 0, 20);
			
			pw->val_label = lv_label_create(pw->container);
			lv_obj_align_to(pw->val_label, pw->obj, LV_ALIGN_OUT_BOTTOM_LEFT, 15, 0);
			
			lv_slider_set_range(pw->obj, 0, (int)PARAMETER_WIDGET_RANGE_SIZE);
			break;
			
		default:
			pw->obj = lv_arc_create(pw->container);
			
			lv_obj_center(pw->obj);
			lv_obj_set_size(pw->obj, VIRTUAL_POT_SIZE_W, VIRTUAL_POT_SIZE_H);
			
			w = VIRTUAL_POT_SIZE_W;
			h = VIRTUAL_POT_SIZE_H;
			
			lv_arc_set_rotation(pw->obj, 135);
			lv_arc_set_bg_angles(pw->obj, 0, 270);
			lv_arc_set_range(pw->obj, 0, (int)PARAMETER_WIDGET_RANGE_SIZE);
			
			pw->name_label = lv_label_create(pw->obj);
			lv_label_set_text(pw->name_label, pw->param->name);
			lv_obj_align(pw->name_label, LV_ALIGN_BOTTOM_MID, 0, 0);
			
			pw->val_label = lv_label_create(pw->obj);
			lv_obj_center(pw->val_label);
			break;
	}
	
	lv_obj_set_size(pw->container, w + PARAM_WIDGET_PAD_W, h + PARAM_WIDGET_PAD_H);
	
	parameter_widget_update_value(pw);
	parameter_widget_update_value_label(pw);
	
	lv_obj_add_event_cb(pw->obj, parameter_widget_change_cb, LV_EVENT_VALUE_CHANGED, pw);
	lv_obj_add_event_cb(pw->obj, parameter_widget_refresh_cb, LV_EVENT_REFRESH, pw);
	
	return NO_ERROR;
}

void param_widget_receive(et_msg msg, te_msg response)
{
	em_parameter_widget *pw = (em_parameter_widget*)msg.cb_arg;
	
	printf("Recieve callback\n");
	if (!pw || !pw->param)
		return;
	
	if (response.type != TE_MESSAGE_PARAM_VALUE)
	{
		ESP_LOGE(TAG, "Weird message (%d) send to parameter widget...\n", response.type);
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
		ESP_LOGE(TAG, "Data for parameter %d.%d.%d recieved by parameter %d.%d.%d...\n",
			profile_id, transformer_id, parameter_id, 
			pw->param->id.profile_id, pw->param->id.transformer_id, pw->param->id.parameter_id); 
	}
}

int param_widget_request_value(em_parameter_widget *pw)
{
	printf("param_widget_request_value...\n");
	if (!pw)
		return ERR_NULL_PTR;
	
	et_msg msg = create_et_msg_get_param_value(pw->param->id.profile_id, pw->param->id.transformer_id, pw->param->id.parameter_id);
	msg.callback = param_widget_receive;
	msg.cb_arg = pw;

	if (xQueueSend(et_msg_queue, (void*)&msg, 0) != pdPASS)
		return ERR_QUEUE_FULL;
	
	printf("param_widget_request_value done!\n");
	return NO_ERROR;
}

void free_parameter_widget(em_parameter_widget *pw)
{
	if (!pw)
		return;
	
	// Currently the em_parameter_widget struct contains nothing that
	// it owns itself. This may change !
	free(pw);
}

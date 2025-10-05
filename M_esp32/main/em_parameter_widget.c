#include "em.h"


static const char *TAG = "Parameter Widget";

void format_float(char *buf, float val, int max_len)
{
	if (!buf) return;

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
			return;
		}
	}

	tmp[0] = '.';
	tmp[1] = '0' + (frac_part / 10);
	tmp[2] = '0' + (frac_part % 10);
	tmp[3] = 0;
	
	for (i = 0; i < 4 && pos < max_len - 1; i++)
		buf[pos++] = tmp[i];

	buf[pos] = 0;
}

int nullify_parameter_widget(parameter_widget *pw)
{
	if (!pw)
		return ERR_NULL_PTR;
	
	pw->param 		= NULL;
	
	pw->obj 		= NULL;
	pw->name_label  = NULL;
	pw->val_label   = NULL;
	
	return NO_ERROR;
}

int configure_parameter_widget(parameter_widget *pw, teensy_parameter *param)
{
	if (!pw || !param)
		return ERR_NULL_PTR;
	
	pw->param = param;
	
	/* Almost always, I send through the value normalstyle. But sometimes
	 * I want to have a value on the UI side that is more reasonable. Like for
	 * the compressor where values are measured in seconds but one wants attack,
	 * for instance, in the ms range. So I allow for, on the UI side, showing it
	 * as some number, but multiplying by a scaling factor before sending it off */
	switch (param->type)
	{
		case M_PARAM_OPTION:
			pw->factor.option = 1;
			break;
			
		case M_PARAM_SWITCH:
			pw->factor.active = 1;
			break;
			
		default:
		case M_PARAM_LEVEL:
			pw->factor.level = 1.0f;
			break;
	}
	
	format_float(pw->val_label_text, pw->param->val.level, PARAM_WIDGET_LABEL_BUFSIZE);
	
	return NO_ERROR;
}

void update_virtual_pot_value_label(parameter_widget *pot)
{
	if (!pot)
		return;
	
	format_float(pot->val_label_text, pot->param->val.level, PARAM_WIDGET_LABEL_BUFSIZE);
	lv_label_set_text(pot->val_label, pot->val_label_text);
}

void virtual_pot_refresh_cb(lv_event_t *event)
{
	parameter_widget *pot = lv_event_get_user_data(event);
	
	if (!pot)
	{
		ESP_LOGE(TAG, "NULL virtual pot pointer");
		return;
	}
	
	lv_arc_set_value(pot->obj, ((pot->param->val.level - pot->param->min.level) * 100 ) / (pot->param->max.level - pot->param->min.level));
	
	update_virtual_pot_value_label(pot);
}

void virtual_pot_change_cb(lv_event_t *event)
{
	parameter_widget *pot = lv_event_get_user_data(event);
	
	if (!pot)
	{
		ESP_LOGE(TAG, "NULL virtual pot pointer");
		return;
	}
	
	pot->param->val.level = pot->param->min.level + ((pot->param->max.level - pot->param->min.level) * 0.01 * lv_arc_get_value(pot->obj));
	
	update_virtual_pot_value_label(pot);
	
	et_msg msg = create_et_msg_set_param(pot->param->id, (m_param_value){.level = pot->param->val.level * pot->factor.level});

	xQueueSend(et_msg_queue, (void*)&msg, 0);
}

int parameter_widget_create_ui(parameter_widget *pw, lv_obj_t *parent)
{
	if (!pw || !pw->param || !parent)
		return ERR_NULL_PTR;
	
	switch (pw->param->type)
	{
		case M_PARAM_LEVEL:
			pw->obj = lv_arc_create(parent);
			
			lv_obj_set_size(pw->obj, 150, 150);
			lv_arc_set_rotation(pw->obj, 135);
			lv_arc_set_bg_angles(pw->obj, 0, 270);
			lv_arc_set_value(pw->obj,
				((pw->param->val.level - pw->param->min.level) * 100 )
			   / (pw->param->max.level - pw->param->min.level));
			
			pw->name_label = lv_label_create(pw->obj);
			lv_label_set_text(pw->name_label, pw->param->name);
			lv_obj_align(pw->name_label, LV_ALIGN_BOTTOM_MID, 0, 0);
			
			pw->val_label = lv_label_create(pw->obj);
			format_float(pw->val_label_text, pw->param->val.level, PARAM_WIDGET_LABEL_BUFSIZE);
			lv_label_set_text(pw->val_label, pw->val_label_text);
			lv_obj_center(pw->val_label);
			
			lv_obj_add_event_cb(pw->obj, virtual_pot_change_cb, LV_EVENT_VALUE_CHANGED, pw);
			lv_obj_add_event_cb(pw->obj, virtual_pot_refresh_cb, LV_EVENT_REFRESH, pw);
			break;
			
		case M_PARAM_OPTION:
			return ERR_UNIMPLEMENTED;
			break;
		
		case M_PARAM_SWITCH:
			return ERR_UNIMPLEMENTED;
			break;
		
		default:
			return ERR_UNIMPLEMENTED;
			break;
	}
	
	return NO_ERROR;
}

void param_widget_receive(et_msg msg, te_msg response)
{
	parameter_widget *pw = (parameter_widget*)msg.cb_arg;
	
	printf("Recieve callback\n");
	if (!pw || !pw->param)
		return;
	
	if (response.type != TE_MESSAGE_PARAM_VALUE)
	{
		ESP_LOGE(TAG, "Weird message (type %d) send to parameter widget...\n", response.type);
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
		memcpy(&pw->param->val, &response.data[6], sizeof(m_param_value));
		
		printf("Parameter %d.%d.%d value revieced: %f\n", profile_id, transformer_id, parameter_id, pw->param->val.level);
		lv_arc_set_value(pw->obj, ((pw->param->val.level - pw->param->min.level) * 100 ) / (pw->param->max.level - pw->param->min.level));
		update_virtual_pot_value_label(pw);
	}
	else
	{
		ESP_LOGE(TAG, "Data for parameter %d.%d.%d recieved by parameter %d.%d.%d...\n",
			profile_id, transformer_id, parameter_id, 
			pw->param->id.profile_id, pw->param->id.transformer_id, pw->param->id.parameter_id); 
	}
}

int param_widget_request_value(parameter_widget *pw)
{
	if (!pw)
		return ERR_NULL_PTR;
	
	et_msg msg = create_et_msg_get_param_value(pw->param->id);
	msg.callback = param_widget_receive;
	msg.cb_arg = pw;

	if (xQueueSend(et_msg_queue, (void*)&msg, 0) != pdPASS)
		return ERR_QUEUE_FULL;
	
	return NO_ERROR;
}

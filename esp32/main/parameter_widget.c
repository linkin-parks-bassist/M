#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "teensy_comms.h"
#include "m_error_codes.h"
#include "esp_log.h"
#include "m_comms.h"
#include <string.h>
#include <math.h>
#include "m_id.h"
#include "lvgl.h"
#include "ui.h"
#include "m_parameter.h"
#include "parameter_widget.h"

static const char *TAG = "Parameter Widget";

void update_virtual_pot_value_label(parameter_widget *pot)
{
	if (!pot)
		return;
	
	format_float(pot->val_label_text, pot->val.level);
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
	
	lv_arc_set_value(pot->obj, ((pot->val.level - pot->min.level) * 100 ) / (pot->max.level - pot->min.level));
	
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
	
	pot->val.level = pot->min.level + ((pot->max.level - pot->min.level) * 0.01 * lv_arc_get_value(pot->obj));
	
	update_virtual_pot_value_label(pot);
	
	et_msg msg = create_et_msg_chparam(pot->id, pot->val);
	msg.extra = pot;

	xQueueSend(et_msg_queue, (void*)&msg, 0);
}

int init_virtual_pot_ui(parameter_widget *pw, lv_obj_t *parent)
{
	if (!pw)
		return ERR_NULL_PTR;
	
	pw->type = VIRTUAL_POT;
	
	pw->obj = lv_arc_create(parent);
		
	lv_obj_set_size(pw->obj, 150, 150);
	lv_arc_set_rotation(pw->obj, 135);
	lv_arc_set_bg_angles(pw->obj, 0, 270);
	lv_arc_set_value(pw->obj, 10);
	
	pw->name_label = lv_label_create(pw->obj);
	lv_label_set_text(pw->name_label, pw->label);
	lv_obj_align(pw->name_label, LV_ALIGN_BOTTOM_MID, 0, 0);
	
	pw->val_label = lv_label_create(pw->obj);
	format_float(pw->val_label_text, pw->val.level);
	lv_label_set_text(pw->val_label, pw->val_label_text);
	lv_obj_center(pw->val_label);
	
	lv_obj_add_event_cb(pw->obj, virtual_pot_change_cb, LV_EVENT_VALUE_CHANGED, pw);
	lv_obj_add_event_cb(pw->obj, virtual_pot_refresh_cb, LV_EVENT_REFRESH, pw);
	
	return NO_ERROR;
}

int init_virtual_pot_param(parameter_widget *pw, const char *label, m_parameter_id id, m_param_level_t initial_value, m_param_level_t min, m_param_level_t max)
{
	if (!pw)
		return ERR_NULL_PTR;
	
	pw->id = id;
	pw->val.level = initial_value;
	pw->min.level = min;
	pw->max.level = max;
	
	pw->label = label;
	
	return NO_ERROR;
}

int request_param_widget_value(parameter_widget *pw)
{
	if (!pw)
		return ERR_NULL_PTR;
	
	et_msg msg = create_et_msg_rqparam(pw->id);
	msg.extra = pw;

	if (xQueueSend(et_msg_queue, (void*)&msg, 0) != pdPASS)
		return ERR_QUEUE_FULL;
	
	return NO_ERROR;
}

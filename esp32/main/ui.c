#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "teensy_comms.h"
#include "lvgl.h"
#include "ui.h"

static void value_changed_event_cb(lv_event_t * e)
{
	lv_obj_t *arc   = lv_event_get_target(e);
	lv_obj_t *label = lv_event_get_user_data(e);

	lv_label_set_text_fmt(label, "%d%%", lv_arc_get_value(arc));

	et_msg msg;
	msg.type = ET_MESSAGE_CHPARAM;
	
	et_msg_chparam_struct str;
	
	str.profile_id 		= 1;
	str.transformer_id 	= 0;
	str.parameter_id 	= 0;
	str.new_value 		= 4.0 * 3.0 * lv_arc_get_value(arc) / 300.0;
	
	/*msg.data[0] = 0;
	msg.data[1] = 0;
	msg.data[2] = 0;
	msg.data[3] = 1;
	msg.data[4] = 0;
	msg.data[5] = 0;
	msg.data[6] = 0;
	msg.data[7] = 0;
	msg.data[8] = 0;
	msg.data[9] = 0;
	msg.data[10] = 0;
	msg.data[11] = 0;
	msg.data[12] = (uint8_t)(((uint32_t)str.new_value) >> 24);
	msg.data[13] = (uint8_t)(((uint32_t)str.new_value) >> 16);
	msg.data[14] = (uint8_t)(((uint32_t)str.new_value) >> 8);
	msg.data[15] = (uint8_t)(((uint32_t)str.new_value));*/
	
	memcpy(&msg.data[0], &str.profile_id, 		2);
	memcpy(&msg.data[2], &str.transformer_id, 	2);
	memcpy(&msg.data[4], &str.parameter_id, 	2);
	memcpy(&msg.data[6], &str.new_value, 		4);
	
	xQueueSend(et_msg_queue, (void*)&msg, 0);
	
	/*Rotate the label to the current position of the arc*/
	//lv_arc_rotate_obj_to_angle(arc, label, 25);
}

void make_ui()
{
	lv_obj_t *scr = lv_scr_act();

	lv_obj_t *arc = lv_arc_create(scr);
	lv_obj_set_size(arc, 150, 150);
	lv_arc_set_rotation(arc, 135);
	lv_arc_set_bg_angles(arc, 0, 270);
	lv_arc_set_value(arc, 10);
	lv_obj_center(arc);

	// LABEL: child of arc, static position
	lv_obj_t *label = lv_label_create(arc);
	lv_label_set_text(label, "test");
	lv_obj_center(label);  // Center within arc, no rotation
	
	lv_obj_add_event_cb(arc, value_changed_event_cb, LV_EVENT_VALUE_CHANGED, label);
	lv_event_send(arc, LV_EVENT_VALUE_CHANGED, NULL);
}

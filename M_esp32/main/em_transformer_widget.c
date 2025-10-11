#include "em.h"

static const char *TAG = "em_transformer_widget.c";

IMPLEMENT_LINKED_PTR_LIST(em_transformer_widget);

int init_transformer_widget(em_transformer_widget *tw, em_ui_page *parent, em_transformer *trans, int index)
{
	if (!tw || !parent)
		return ERR_NULL_PTR;
	
	tw->trans = trans;
	
	if (trans)
	{
		tw->label_text = transformer_type_name(trans->type);
	}
	else
	{
		tw->label_text = "+";
	}
	
	tw->obj	  		= NULL;
	tw->label 		= NULL;
	tw->del_button 	= NULL;
	
	tw->del_button_label 		= NULL;
	tw->del_button_remain_timer = NULL;
	
	tw->parent 	 = parent;
	tw->index  	 = index;
	
	tw->long_pressed = 0;
	
	return NO_ERROR;
}

void transformer_widget_scale_cb(void *data, int32_t value)
{
	em_transformer_widget *tw = (em_transformer_widget*)data;
	
	int32_t new_height = ((float)value / 1000.0) * TRANSFORMER_WIDGET_HEIGHT;
	int32_t new_width  = ((float)value / 1000.0) * TRANSFORMER_WIDGET_WIDTH;
	
	lv_obj_set_height(tw->obj, new_height);
	lv_obj_set_width (tw->obj, new_width);
	
	tw->pos_y = tw->pos_y - (new_height - lv_obj_get_height(tw->obj));
	lv_obj_align(tw->obj, LV_ALIGN_TOP_MID, 0, tw->pos_y);
	
	printf("transformer_widget_scale_cb. new_width = %d, new_height = %d, tw->pos_y = %d\n", (int)new_width, (int)new_height, tw->pos_y);
}

void transformer_widget_glide_cb(void *data, int32_t value)
{
	em_transformer_widget *tw = (em_transformer_widget*)data;
	
	printf("transformer_widget_glide_cb; %p : %d -> %d\n", tw, lv_obj_get_y(tw->obj), (int)value);
	lv_obj_set_y(tw->obj, value);
	tw->pos_y = value;
}

void transformer_widget_del_button_fade_cb(void *data, int32_t value)
{
	em_transformer_widget *tw = (em_transformer_widget*)data;
	
	lv_obj_set_style_opa(tw->del_button, value, 0);
}

void transformer_widget_del_button_faded_out_cb(lv_anim_t *anim)
{
	em_transformer_widget *tw = (em_transformer_widget*)anim->user_data;
	
	lv_obj_add_flag(tw->del_button, LV_OBJ_FLAG_HIDDEN);
}

void transformer_widget_delete_anim_cb(void *data, int32_t value)
{
	em_transformer_widget *tw = (em_transformer_widget*)data;
	
	lv_obj_set_style_opa(tw->obj, 255 * ((float)value / 100.0), 0);
}

void transformer_widget_trigger_scale_anim(em_transformer_widget *tw, int direction)
{
	if (!tw)
		return;
	
	int initial = direction ? 1000 : 1000 * TRANSFORMER_WIDGET_LP_SCALE;
	int final   = direction ? 1000 * TRANSFORMER_WIDGET_LP_SCALE : 1000;
	

	lv_anim_init			(&tw->scale_anim);
	lv_anim_set_var			(&tw->scale_anim, tw);
	lv_anim_set_exec_cb		(&tw->scale_anim, transformer_widget_scale_cb);
	lv_anim_set_time		(&tw->scale_anim, TRANSFORMER_WIDGET_SCALE_ANIM_MS);
	lv_anim_set_values		(&tw->scale_anim, initial, final);
	lv_anim_path_ease_in_out(&tw->scale_anim);
	
	lv_anim_start(&tw->scale_anim);
}

void transformer_widget_trigger_glide_anim(em_transformer_widget *tw, int32_t new_pos_y)
{
	printf("Triggering glide of %p from %d to %d\n", tw, (int)tw->pos_y, (int)new_pos_y);
	lv_anim_init			(&tw->glide_anim);
	lv_anim_set_var			(&tw->glide_anim, tw);
	lv_anim_set_exec_cb		(&tw->glide_anim, transformer_widget_glide_cb);
	lv_anim_set_time		(&tw->glide_anim, TRANSFORMER_WIDGET_GLIDE_ANIM_MS);
	lv_anim_set_values		(&tw->glide_anim, tw->pos_y, new_pos_y);
	lv_anim_path_ease_in_out(&tw->glide_anim);
	
	lv_anim_start(&tw->glide_anim);
}

void transformer_widget_trigger_del_button_fade_in(em_transformer_widget *tw)
{
	printf("button fade in...\n");
	lv_anim_init			(&tw->del_button_fade);
	lv_anim_set_var			(&tw->del_button_fade, tw);
	lv_anim_set_exec_cb		(&tw->del_button_fade, transformer_widget_del_button_fade_cb);
	lv_anim_set_time		(&tw->del_button_fade, TRANSFORMER_WIDGET_DEL_BTN_FADE_IN_MS);
	lv_anim_set_values		(&tw->del_button_fade, 0, 255);
	
	lv_obj_clear_flag(tw->del_button, LV_OBJ_FLAG_HIDDEN);
	lv_anim_start(&tw->del_button_fade);
}

void transformer_widget_trigger_del_button_fade_out(em_transformer_widget *tw)
{
	lv_anim_init			(&tw->del_button_fade);
	lv_anim_set_var			(&tw->del_button_fade, tw);
	lv_anim_set_exec_cb		(&tw->del_button_fade, transformer_widget_del_button_fade_cb);
	lv_anim_set_ready_cb	(&tw->del_button_fade, transformer_widget_del_button_faded_out_cb);
	lv_anim_set_time		(&tw->del_button_fade, TRANSFORMER_WIDGET_DEL_BTN_FADE_OUT_MS);
	lv_anim_set_values		(&tw->del_button_fade, 255, 0);
	
	tw->del_button_fade.user_data = (void*)tw;
	
	lv_anim_start(&tw->del_button_fade);
}

void transformer_widget_delete_anim_ready_cb(lv_anim_t *anim)
{
	em_transformer_widget *tw = (em_transformer_widget*)anim->user_data;
	transformer_widget_delete(tw);
}

void transformer_widget_trigger_del_anim(em_transformer_widget *tw)
{
	lv_anim_init			(&tw->delete_anim);
	lv_anim_set_var			(&tw->delete_anim, tw);
	lv_anim_set_exec_cb		(&tw->delete_anim, transformer_widget_delete_anim_cb);
	lv_anim_set_ready_cb	(&tw->delete_anim, transformer_widget_delete_anim_ready_cb);
	lv_anim_set_time		(&tw->delete_anim, TRANSFORMER_WIDGET_DEL_ANIM_MS);
	lv_anim_set_values		(&tw->delete_anim, 100, 0);
	
	tw->delete_anim.user_data = (void*)tw;
	
	lv_anim_start(&tw->delete_anim);
}

int transformer_widget_force_index(em_transformer_widget *tw, int i)
{
	if (!tw)
		return ERR_NULL_PTR;
	
	lv_coord_t new_pos_y = profile_view_index_y_position(i);
	
	transformer_widget_trigger_glide_anim(tw, new_pos_y);
	
	tw->index = i;
	
	return NO_ERROR;
}

int transformer_widget_set_index(em_transformer_widget *tw, int i)
{
	//printf("Set transformer widget index (%p, %d)\n", tw, i);
	if (!tw)
		return ERR_NULL_PTR;
	
	if (tw->index == i)
		return NO_ERROR;
	
	lv_coord_t new_pos_y = profile_view_index_y_position(i);
	
	transformer_widget_trigger_glide_anim(tw, new_pos_y);
	
	tw->index = i;
	
	return NO_ERROR;
}

void transformer_widget_del_button_remain_timer_cb(lv_timer_t *timer)
{
	em_transformer_widget *tw = (em_transformer_widget*)timer->user_data;
	
	transformer_widget_trigger_del_button_fade_out(tw);
	tw->del_button_remain_timer = NULL;
}

void transformer_widget_long_pressed_cb(lv_event_t *e)
{
	em_transformer_widget *tw = (em_transformer_widget*)lv_event_get_user_data(e);
	
	if (!tw)
	{
		ESP_LOGE(TAG, "Transformer widget long press callback triggered but pointer to struct not passed");
		return;
	}
	
	tw->long_pressed = 1;
	printf("long press detected...\n");
	
	lv_point_t touch_point;
	lv_indev_t *indev = lv_indev_get_act();
	lv_indev_get_point(indev, &touch_point);
	
	lv_point_t local_point = touch_point;
	lv_obj_t *parent = lv_obj_get_parent(tw->obj);

	lv_area_t parent_coords;
	lv_obj_get_coords(parent, &parent_coords);
	
	local_point.y -= parent_coords.y1;
	
	tw->relative_touch_y = local_point.y - tw->pos_y;
	
    profile_view_enter_drag_state(tw->parent);
    
	transformer_widget_trigger_scale_anim(tw, TRANSFORMER_WIDGET_SCALE_EXPAND);
	
	lv_obj_move_foreground(tw->obj);
	
	transformer_widget_trigger_del_button_fade_in(tw);
	
	tw->prev_index = tw->index;
}

void transformer_widget_pressing_cb(lv_event_t *e)
{
	em_transformer_widget *tw = (em_transformer_widget*)lv_event_get_user_data(e);
	
	if (!tw)
	{
		ESP_LOGE(TAG, "Transformer widget long press callback triggered but pointer to struct not passed");
		return;
	}
	
	if (tw->long_pressed)
	{
		lv_point_t touch_point;
		lv_indev_t *indev = lv_indev_get_act();
		lv_indev_get_point(indev, &touch_point);
		
		lv_point_t local_point = touch_point;
		lv_obj_t *parent = lv_obj_get_parent(tw->obj);

		lv_area_t parent_coords;
		lv_obj_get_coords(parent, &parent_coords);
		
		local_point.y -= parent_coords.y1;

		tw->pos_y = local_point.y - tw->relative_touch_y;
		lv_obj_set_y(tw->obj, tw->pos_y);
		
		em_transformer_widget *index_array[((em_profile_view_str*)tw->parent->data_struct)->n_transformer_widgets];
		
		for (int i = 0; i < ((em_profile_view_str*)tw->parent->data_struct)->n_transformer_widgets; i++)
			index_array[i] = NULL;
		
		em_transformer_widget_ptr_linked_list *current = ((em_profile_view_str*)tw->parent->data_struct)->tws;
		em_transformer_widget_ptr_linked_list *other;
		
		int j = 0;
		while (current)
		{
			int i = 0;
			other = ((em_profile_view_str*)tw->parent->data_struct)->tws;
			
			while (other)
			{
				if (current != other && other->data->pos_y < current->data->pos_y)
					i++;
				
				other = other->next;
			}
			
			if (current->data != tw)
				transformer_widget_set_index(current->data, i);
			else
				current->data->index = i;
			
			printf("Transformer %d has index %d\n", j, i);
			
			current = current->next;
			j++;
		}
	}
}


void transformer_widget_release_cb(lv_event_t *e)
{
	em_transformer_widget *tw = (em_transformer_widget*)lv_event_get_user_data(e);
	
	if (!tw)
	{
		ESP_LOGE(TAG, "Transformer widget release callback triggered but pointer to struct not passed");
		return;
	}
	
	printf("long_pressed = %d\n", tw->long_pressed);
	if (tw->long_pressed)
	{
		tw->long_pressed = 0;
		
		transformer_widget_trigger_scale_anim(tw, TRANSFORMER_WIDGET_SCALE_CONTRACT);
		profile_view_exit_drag_state(tw->parent);
		
		transformer_widget_force_index(tw, tw->index);
		
		if (tw->index != tw->prev_index)
		{
			printf("Send message to move transformer %d to position %d\n", tw->trans->transformer_id, tw->index);
			queue_msg_to_teensy(create_et_msg(ET_MESSAGE_MOVE_TRANSFORMER, "sss", tw->trans->transformer_id, tw->index));
			tw->prev_index = tw->index;
		}
		
		tw->del_button_remain_timer = lv_timer_create(transformer_widget_del_button_remain_timer_cb, TRANSFORMER_WIDGET_DEL_BTN_REMAIN_MS, tw);
		lv_timer_set_repeat_count(tw->del_button_remain_timer, 1);
		
		lv_timer_resume(tw->del_button_remain_timer);
	}
	else
	{
		if (tw->trans)
		{
			if (tw->trans->view_page)
			{
				enter_ui_page_forward(tw->trans->view_page);
			}
		}
	}
}

void tw_del_button_cb(lv_event_t *e)
{
	printf("tw_del_button_cb\n");
	em_transformer_widget *tw = (em_transformer_widget*)lv_event_get_user_data(e);
	
	transformer_widget_trigger_del_anim(tw);
	
	lv_obj_clear_flag(tw->obj, LV_OBJ_FLAG_CLICKABLE);
	
	if (tw->trans)
	{
		cxt_remove_transformer(&global_cxt, tw->trans->profile_id, tw->trans->transformer_id);
	}
	printf("tw_del_button_cb done\n");
}

int create_transformer_widget_ui(em_transformer_widget *tw, lv_obj_t *parent)
{
	printf("create_transformer_widget_ui...\n");
	if (!tw)
		return ERR_NULL_PTR;
	
	tw->obj = lv_btn_create(parent);
	
	printf("tw->obj = %p\n", tw->obj);
    lv_obj_set_size(tw->obj, TRANSFORMER_WIDGET_WIDTH, TRANSFORMER_WIDGET_HEIGHT);
    
	tw->pos_y = profile_view_index_y_position(tw->index);
	
	lv_obj_align(tw->obj, LV_ALIGN_TOP_MID, 0, tw->pos_y);
	
	tw->label = lv_label_create(tw->obj);
	lv_label_set_text(tw->label, tw->label_text);
	printf("label: %s\n", tw->label_text);
	lv_obj_center(tw->label);
	
	if (tw->trans)
	{
		lv_obj_add_event_cb(tw->obj, transformer_widget_release_cb, LV_EVENT_RELEASED, tw);
		lv_obj_add_event_cb(tw->obj, transformer_widget_long_pressed_cb, LV_EVENT_LONG_PRESSED, tw);
		lv_obj_add_event_cb(tw->obj, transformer_widget_pressing_cb, LV_EVENT_PRESSING, tw);
	}
	else
	{
		lv_obj_add_event_cb(tw->obj, enter_transformer_selector_cb, LV_EVENT_CLICKED, tw->parent);
	}
	
	tw->del_button = lv_btn_create(tw->obj);
	lv_obj_align(tw->del_button, LV_ALIGN_RIGHT_MID, 10, 0);
	lv_obj_set_size(tw->del_button, 0.75 * TRANSFORMER_WIDGET_HEIGHT, 0.75 * TRANSFORMER_WIDGET_HEIGHT);
	lv_obj_add_event_cb(tw->del_button, tw_del_button_cb, LV_EVENT_CLICKED, tw);
	lv_obj_add_flag(tw->del_button, LV_OBJ_FLAG_HIDDEN);
	
	tw->del_button_label = lv_label_create(tw->del_button);
	lv_label_set_text(tw->del_button_label, "X");
	lv_obj_center(tw->del_button_label);
	
	printf("success\n");
	return NO_ERROR;
}

void transformer_widget_delete(em_transformer_widget *tw)
{
	if (!tw)
		return;
	
	lv_anim_del(tw, NULL);
	
	if (tw->del_button_remain_timer)
	{
		lv_timer_del(tw->del_button_remain_timer);
		tw->del_button_remain_timer = NULL;
	}
	
	lv_obj_del_async(tw->obj);
	
	profile_view_remove_tw(tw->parent, tw);
}


void free_transformer_widget(em_transformer_widget *tw)
{
	if (!tw)
		return;
	
	free(tw);
}

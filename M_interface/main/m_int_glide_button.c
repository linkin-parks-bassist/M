#include "m_int.h"

IMPLEMENT_LINKED_PTR_LIST(m_int_glide_button);

static const char *TAG = "m_int_glide_button.c";

int init_glide_button(m_int_glide_button *gb)
{
	if (!gb)
		return ERR_NULL_PTR;
	
	gb->obj	  		= NULL;
	gb->label 		= NULL;
	gb->del_button 	= NULL;
	
	gb->del_button_label 		= NULL;
	gb->del_button_remain_timer = NULL;
	
	gb->index  	   = 0;
	gb->prev_index = 0;
	
	gb->long_pressed = 0;
	
	return NO_ERROR;
}

void glide_button_scale_cb(void *data, int32_t value)
{
	m_int_glide_button *gb = (m_int_glide_button*)data;
	
	int32_t new_height = ((float)value / 1000.0) * GLIDE_BUTTON_HEIGHT;
	int32_t new_width  = ((float)value / 1000.0) * GLIDE_BUTTON_WIDTH;
	
	lv_obj_set_height(gb->obj, new_height);
	lv_obj_set_width (gb->obj, new_width);
	
	gb->pos_y = gb->pos_y - (new_height - lv_obj_get_height(gb->obj));
	lv_obj_align(gb->obj, LV_ALIGN_TOP_MID, 0, gb->pos_y);
}

void glide_button_glide_cb(void *data, int32_t value)
{
	m_int_glide_button *gb = (m_int_glide_button*)data;
	
	lv_obj_set_y(gb->obj, value);
	gb->pos_y = value;
}

void glide_button_del_button_fade_cb(void *data, int32_t value)
{
	m_int_glide_button *gb = (m_int_glide_button*)data;
	
	lv_obj_set_style_opa(gb->del_button, value, 0);
}

void glide_button_del_button_faded_out_cb(lv_anim_t *anim)
{
	m_int_glide_button *gb = (m_int_glide_button*)anim->user_data;
	
	lv_obj_add_flag(gb->del_button, LV_OBJ_FLAG_HIDDEN);
}

void free_glide_button_anim_cb(void *data, int32_t value)
{
	m_int_glide_button *gb = (m_int_glide_button*)data;
	
	lv_obj_set_style_opa(gb->obj, 255 * ((float)value / 100.0), 0);
}

void glide_button_trigger_scale_anim(m_int_glide_button *gb, int direction)
{
	if (!gb)
		return;
	
	int initial = direction ? 1000 : 1000 * GLIDE_BUTTON_LP_SCALE;
	int final   = direction ? 1000 * GLIDE_BUTTON_LP_SCALE : 1000;
	

	lv_anim_init			(&gb->scale_anim);
	lv_anim_set_var			(&gb->scale_anim, gb);
	lv_anim_set_exec_cb		(&gb->scale_anim, glide_button_scale_cb);
	lv_anim_set_time		(&gb->scale_anim, GLIDE_BUTTON_SCALE_ANIM_MS);
	lv_anim_set_values		(&gb->scale_anim, initial, final);
	lv_anim_path_ease_in_out(&gb->scale_anim);
	
	lv_anim_start(&gb->scale_anim);
}

void glide_button_trigger_glide_anim(m_int_glide_button *gb, int32_t new_pos_y)
{
	lv_anim_init			(&gb->glide_anim);
	lv_anim_set_var			(&gb->glide_anim, gb);
	lv_anim_set_exec_cb		(&gb->glide_anim, glide_button_glide_cb);
	lv_anim_set_time		(&gb->glide_anim, GLIDE_BUTTON_GLIDE_ANIM_MS);
	lv_anim_set_values		(&gb->glide_anim, gb->pos_y, new_pos_y);
	lv_anim_path_ease_in_out(&gb->glide_anim);
	
	lv_anim_start(&gb->glide_anim);
}

void glide_button_trigger_del_button_fade_in(m_int_glide_button *gb)
{
	lv_anim_init			(&gb->del_button_fade);
	lv_anim_set_var			(&gb->del_button_fade, gb);
	lv_anim_set_exec_cb		(&gb->del_button_fade, glide_button_del_button_fade_cb);
	lv_anim_set_time		(&gb->del_button_fade, GLIDE_BUTTON_DEL_BTN_FADE_IN_MS);
	lv_anim_set_values		(&gb->del_button_fade, 0, 255);
	
	lv_obj_clear_flag(gb->del_button, LV_OBJ_FLAG_HIDDEN);
	lv_anim_start(&gb->del_button_fade);
}

void glide_button_trigger_del_button_fade_out(m_int_glide_button *gb)
{
	lv_anim_init			(&gb->del_button_fade);
	lv_anim_set_var			(&gb->del_button_fade, gb);
	lv_anim_set_exec_cb		(&gb->del_button_fade, glide_button_del_button_fade_cb);
	lv_anim_set_ready_cb	(&gb->del_button_fade, glide_button_del_button_faded_out_cb);
	lv_anim_set_time		(&gb->del_button_fade, GLIDE_BUTTON_DEL_BTN_FADE_OUT_MS);
	lv_anim_set_values		(&gb->del_button_fade, 255, 0);
	
	gb->del_button_fade.user_data = (void*)gb;
	
	lv_anim_start(&gb->del_button_fade);
}

void free_glide_button_anim_ready_cb(lv_anim_t *anim)
{
	m_int_glide_button *gb = (m_int_glide_button*)anim->user_data;
	free_glide_button(gb);
}

void glide_button_trigger_del_anim(m_int_glide_button *gb)
{
	lv_anim_init			(&gb->delete_anim);
	lv_anim_set_var			(&gb->delete_anim, gb);
	lv_anim_set_exec_cb		(&gb->delete_anim, free_glide_button_anim_cb);
	lv_anim_set_ready_cb	(&gb->delete_anim, free_glide_button_anim_ready_cb);
	lv_anim_set_time		(&gb->delete_anim, GLIDE_BUTTON_DEL_ANIM_MS);
	lv_anim_set_values		(&gb->delete_anim, 100, 0);
	
	gb->delete_anim.user_data = (void*)gb;
	
	lv_anim_start(&gb->delete_anim);
}

int glide_button_force_index(m_int_glide_button *gb, int i)
{
	if (!gb)
		return ERR_NULL_PTR;
	
	if (!gb->array)
		return ERR_BAD_ARGS;
	
	lv_coord_t new_pos_y = glide_button_array_index_y_position(gb->array, i);
	
	glide_button_trigger_glide_anim(gb, new_pos_y);
	
	gb->index = i;
	
	return NO_ERROR;
}

int glide_button_set_index(m_int_glide_button *gb, int i)
{
	if (!gb)
		return ERR_NULL_PTR;
	
	if (gb->index == i)
		return NO_ERROR;
	
	if (!gb->array)
		return ERR_BAD_ARGS;
	
	lv_coord_t new_pos_y = glide_button_array_index_y_position(gb->array, i);
	
	glide_button_trigger_glide_anim(gb, new_pos_y);
	
	gb->index = i;
	
	return NO_ERROR;
}

void glide_button_del_button_remain_timer_cb(lv_timer_t *timer)
{
	m_int_glide_button *gb = (m_int_glide_button*)timer->user_data;
	
	glide_button_trigger_del_button_fade_out(gb);
	gb->del_button_remain_timer = NULL;
}

void glide_button_long_pressed_cb(lv_event_t *e)
{
	m_int_glide_button *gb = (m_int_glide_button*)lv_event_get_user_data(e);
	
	if (!gb)
	{
		ESP_LOGE(TAG, "Transformer widget long press callback triggered but pointer to struct not passed");
		return;
	}
	
	gb->long_pressed = 1;
	printf("long press detected... gb->index = %d, gb->prev_index = %d\n", gb->index, gb->prev_index);
	
	lv_point_t touch_point;
	lv_indev_t *indev = lv_indev_get_act();
	lv_indev_get_point(indev, &touch_point);
	
	lv_point_t local_point = touch_point;
	lv_obj_t *parent = lv_obj_get_parent(gb->obj);

	lv_area_t parent_coords;
	lv_obj_get_coords(parent, &parent_coords);
	
	local_point.y -= parent_coords.y1;
	
	gb->relative_touch_y = local_point.y - gb->pos_y;
    
	glide_button_trigger_scale_anim(gb, GLIDE_BUTTON_SCALE_EXPAND);
	
	lv_obj_move_foreground(gb->obj);
	
	glide_button_trigger_del_button_fade_in(gb);
	
	gb->prev_index = gb->index;
}

void glide_button_pressing_cb(lv_event_t *e)
{
	m_int_glide_button *gb = (m_int_glide_button*)lv_event_get_user_data(e);
	
	if (!gb)
	{
		ESP_LOGE(TAG, "Transformer widget long press callback triggered but pointer to struct not passed");
		return;
	}
	
	if (gb->long_pressed)
	{
		lv_point_t touch_point;
		lv_indev_t *indev = lv_indev_get_act();
		lv_indev_get_point(indev, &touch_point);
		
		lv_point_t local_point = touch_point;
		lv_obj_t *parent = lv_obj_get_parent(gb->obj);

		lv_area_t parent_coords;
		lv_obj_get_coords(parent, &parent_coords);
		
		local_point.y -= parent_coords.y1;

		gb->pos_y = local_point.y - gb->relative_touch_y;
		lv_obj_set_y(gb->obj, gb->pos_y);
		
		m_int_glide_button *index_array[gb->array->n_buttons];
		
		for (int i = 0; i < gb->array->n_buttons; i++)
			index_array[i] = NULL;
		
		m_int_glide_button_pll *current = gb->array->buttons;
		m_int_glide_button_pll *other;
		
		int j = 0;
		while (current)
		{
			int i = 0;
			other = gb->array->buttons;
			
			while (other)
			{
				if (current != other && other->data->pos_y < current->data->pos_y)
					i++;
				
				other = other->next;
			}
			
			if (current->data != gb)
				glide_button_set_index(current->data, i);
			else
				current->data->index = i;
			
			current = current->next;
			j++;
		}
	}
}


void glide_button_release_cb(lv_event_t *e)
{
	m_int_glide_button *gb = (m_int_glide_button*)lv_event_get_user_data(e);
	
	if (!gb)
	{
		return;
	}
	
	if (gb->long_pressed)
	{
		gb->long_pressed = 0;
		
		glide_button_trigger_scale_anim(gb, GLIDE_BUTTON_SCALE_CONTRACT);
		
		glide_button_force_index(gb, gb->index);
		
		if (gb->index != gb->prev_index)
		{
			if (gb->array && gb->array->moved_cb)
			{
				gb->array->moved_cb(gb);
			}
		}
		
		gb->del_button_remain_timer = lv_timer_create(glide_button_del_button_remain_timer_cb, GLIDE_BUTTON_DEL_BTN_REMAIN_MS, gb);
		lv_timer_set_repeat_count(gb->del_button_remain_timer, 1);
		
		lv_timer_resume(gb->del_button_remain_timer);
	}
	else
	{
		if (gb->array && gb->array->clicked_cb)
		{
			gb->array->clicked_cb(gb);
		}
	}
}

void gb_del_button_cb(lv_event_t *e)
{
	//printf("gb_del_button_cb\n");
	m_int_glide_button *gb = (m_int_glide_button*)lv_event_get_user_data(e);
	
	glide_button_trigger_del_anim(gb);
	
	lv_obj_clear_flag(gb->obj, LV_OBJ_FLAG_CLICKABLE);
	
	if (gb->array && gb->array->delete_cb)
	{
		gb->array->delete_cb(gb);
	}
}

int create_glide_button_ui(m_int_glide_button *gb, lv_obj_t *parent)
{
	if (!gb)
		return ERR_NULL_PTR;
	
	gb->obj = lv_btn_create(parent);
	
    lv_obj_set_size(gb->obj, GLIDE_BUTTON_WIDTH, GLIDE_BUTTON_HEIGHT);
    
	gb->pos_y = glide_button_array_index_y_position(gb->array, gb->index);
	
	lv_obj_align(gb->obj, LV_ALIGN_TOP_MID, 0, gb->pos_y);
	
	gb->label = lv_label_create(gb->obj);
	lv_label_set_text(gb->label, gb->label_text);
	lv_obj_center(gb->label);
	
	lv_obj_add_event_cb(gb->obj, glide_button_release_cb, LV_EVENT_RELEASED, gb);
	lv_obj_add_event_cb(gb->obj, glide_button_long_pressed_cb, LV_EVENT_LONG_PRESSED, gb);
	lv_obj_add_event_cb(gb->obj, glide_button_pressing_cb, LV_EVENT_PRESSING, gb);
	
	gb->del_button = lv_btn_create(gb->obj);
	lv_obj_align(gb->del_button, LV_ALIGN_RIGHT_MID, 10, 0);
	lv_obj_set_size(gb->del_button, 0.75 * GLIDE_BUTTON_HEIGHT, 0.75 * GLIDE_BUTTON_HEIGHT);
	lv_obj_add_event_cb(gb->del_button, gb_del_button_cb, LV_EVENT_CLICKED, gb);
	lv_obj_add_flag(gb->del_button, LV_OBJ_FLAG_HIDDEN);
	
	gb->del_button_label = lv_label_create(gb->del_button);
	lv_label_set_text(gb->del_button_label, LV_SYMBOL_TRASH);
	lv_obj_center(gb->del_button_label);
	
	return NO_ERROR;
}

int create_glide_button_array_ui(m_int_glide_button_array *array, lv_obj_t *parent)
{
	if (!array)
		return ERR_NULL_PTR;
	
	glide_button_array_sort(array);
	
	m_int_glide_button_pll *current = array->buttons;
	
	while (current)
	{
		create_glide_button_ui(current->data, parent);
		
		current = current->next;
	}
	
	return NO_ERROR;
}

void free_glide_button(m_int_glide_button *gb)
{
	if (!gb)
		return;
	
	if (gb->obj)
	{
		lv_anim_del(gb, NULL);
		
		if (gb->del_button_remain_timer)
		{
			lv_timer_del(gb->del_button_remain_timer);
			gb->del_button_remain_timer = NULL;
		}
		
		lv_obj_del_async(gb->obj);
		
		if (gb->array && gb->array->free_cb)
			gb->array->free_cb(gb);
	}
	
	m_free(gb);
}

int init_glide_button_array(m_int_glide_button_array *array)
{
	if (!array)
		return ERR_NULL_PTR;
	
	array->n_buttons = 0;
	array->buttons = NULL;
	
	array->parent = NULL;
	
	array->free_cb 		= NULL;
	array->delete_cb 	= NULL;
	array->clicked_cb 	= NULL;
	array->moved_cb 	= NULL;
	
	array->data = NULL;
	
	array->base_y_pos = GLIDE_BUTTON_ARRAY_BASE_Y;
	
	return NO_ERROR;
}

m_int_glide_button_array *new_gb_array()
{
	m_int_glide_button_array *array = malloc(sizeof(m_int_glide_button_array));
	
	if (!array)
		return NULL;
	
	init_glide_button_array(array);
	
	return array;
}

m_int_glide_button *append_new_glide_button_to_array(m_int_glide_button_array *array, void *data, char *label)
{
	if (!array)
	{
		printf("Returning NULL cause array = %p\n", array);
		return NULL;
	}
	
	m_int_glide_button *button = malloc(sizeof(m_int_glide_button));
	
	if (!button)
	{
		printf("returning NULL cause button = %p\n", button);
		return NULL;
	}
	
	init_glide_button(button);
	
	button->data  = data;
	button->label_text = label;
	
	append_glide_button_to_array(button, array);
	
	printf("returning %p\n", button);
	return button;
}

int append_glide_button_to_array(m_int_glide_button *button, m_int_glide_button_array *array)
{
	if (!button || !array)
		return ERR_NULL_PTR;
	
	m_int_glide_button_pll *nl = m_int_glide_button_pll_append(array->buttons, button);
	
	if (!nl)
		return ERR_ALLOC_FAIL;
	
	array->buttons = nl;
	
	button->index = array->n_buttons;
	button->prev_index = array->n_buttons;
	button->array = array;
	array->n_buttons++;
	
	return NO_ERROR;
}

int glide_button_array_index_y_position(m_int_glide_button_array *array, int index)
{
	return array->base_y_pos + index * GLIDE_BUTTON_DISTANCE;
}

int glide_button_array_sort(m_int_glide_button_array *array)
{
	if (!array)
		return ERR_NULL_PTR;
	
	m_int_glide_button_pll *current, *prev, *prev_prev;
	int sorted;
	
	do {
		sorted = 1;
		current = array->buttons;
		prev = NULL;
		prev_prev = NULL;
		
		while (current)
		{
			if (prev && prev->data->index > current->data->index)
			{
				prev->next = current->next;
				
				if (prev_prev)
				{
					prev_prev->next = current;
				}
				else
				{
					array->buttons = current;
				}
				
				current->next = prev;
			}
			
			prev_prev = prev;
			prev = current;
			current = current->next;
		}
		
	} while (!sorted);
	
	
	return NO_ERROR;
}


int glide_button_change_label(m_int_glide_button *gb, char *text)
{
	if (!gb)
		return ERR_NULL_PTR;
	
	if (!text)
		text = "";
	
	if (gb->label_text)
		m_free(gb->label_text);
	
	gb->label_text = m_strndup(text, 32);
	if (gb->label)
		lv_label_set_text(gb->label, gb->label_text);
	
	return NO_ERROR;
}

int glide_button_display_active(m_int_glide_button *gb)
{
	if (!gb)
		return ERR_NULL_PTR;
	
	if (!gb->del_button || !gb->del_button_label)
		return ERR_BAD_ARGS;
	
	lv_label_set_text(gb->del_button_label, LV_SYMBOL_PLAY);
	lv_obj_clear_flag(gb->del_button, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(gb->del_button, LV_OBJ_FLAG_CLICKABLE);
	
	
	return NO_ERROR;
}

int glide_button_undisplay_active(m_int_glide_button *gb)
{
	if (!gb)
		return ERR_NULL_PTR;
	
	if (!gb->del_button || !gb->del_button_label)
		return ERR_BAD_ARGS;
	
	lv_label_set_text(gb->del_button_label, LV_SYMBOL_TRASH);
	lv_obj_add_flag(gb->del_button, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(gb->del_button, LV_OBJ_FLAG_CLICKABLE);
	
	return NO_ERROR;
}

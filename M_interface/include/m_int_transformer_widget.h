#ifndef M_INT_TRANSFORMER_WIDGET_H_
#define M_INT_TRANSFORMER_WIDGET_H_

#define TRANSFORMER_WIDGET_HEIGHT 	STANDARD_BUTTON_HEIGHT
#define TRANSFORMER_WIDGET_WIDTH	390

#define TRANSFORMER_WIDGET_SCALE_EXPAND 	1
#define TRANSFORMER_WIDGET_SCALE_CONTRACT 	0

#define TRANSFORMER_WIDGET_LP_SCALE 		1.05
#define TRANSFORMER_WIDGET_SCALE_ANIM_MS 	75
#define TRANSFORMER_WIDGET_GLIDE_ANIM_MS 	150

#define TRANSFORMER_WIDGET_DEL_BTN_FADE_IN_MS 	75
#define TRANSFORMER_WIDGET_DEL_BTN_FADE_OUT_MS 	300
#define TRANSFORMER_WIDGET_DEL_BTN_REMAIN_MS 	STANDARD_DEL_BTN_REMAIN_MS

#define TRANSFORMER_WIDGET_DEL_ANIM_MS 			100


typedef struct
{
	lv_obj_t *obj;
	lv_obj_t *label;
	lv_obj_t *del_button;
	lv_obj_t *del_button_label;
	
	const char *label_text;
	
	lv_anim_t scale_anim;
	lv_anim_t glide_anim;
	lv_anim_t del_button_fade;
	lv_anim_t delete_anim;
	
	lv_timer_t *del_button_remain_timer;
	
	lv_coord_t pos_y;
	
	int index;
	int prev_index;
	int add_button;
	
	uint32_t base_width;
	uint32_t base_height;
	
	int relative_touch_y;
	
	int long_pressed;
	m_int_transformer *trans;
	m_int_ui_page *parent;
} m_int_transformer_widget;

int init_transformer_widget(m_int_transformer_widget *tw, m_int_ui_page *parent, m_int_transformer *trans, int index);
int create_transformer_widget_ui(m_int_transformer_widget *tw, lv_obj_t *parent);
int delete_transformer_widget_ui(m_int_transformer_widget *tw);

int transformer_widget_untether(m_int_transformer_widget *tw);
int transformer_widget_retether(m_int_transformer_widget *tw);
int transformer_widget_set_index(m_int_transformer_widget *tw, int i);

void transformer_widget_release_cb(lv_event_t *e);
void transformer_widget_long_pressed_cb(lv_event_t *e);
void transformer_widget_pressing_cb(lv_event_t *e);

void transformer_widget_trigger_scale_anim(m_int_transformer_widget *tw, int direction);
void transformer_widget_trigger_glide_anim(m_int_transformer_widget *tw, int32_t new_pos_y);

void free_transformer_widget(m_int_transformer_widget *tw);

DECLARE_LINKED_PTR_LIST(m_int_transformer_widget);

#endif


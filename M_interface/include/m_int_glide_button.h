#ifndef M_INT_GLIDE_BUTTON_H_
#define M_INT_GLIDE_BUTTON_H_

#define GLIDE_BUTTON_HEIGHT STANDARD_BUTTON_HEIGHT
#define GLIDE_BUTTON_WIDTH  390

#define GLIDE_BUTTON_SCALE_EXPAND 	1
#define GLIDE_BUTTON_SCALE_CONTRACT 	0

#define GLIDE_BUTTON_LP_SCALE 		1.05
#define GLIDE_BUTTON_SCALE_ANIM_MS 	75
#define GLIDE_BUTTON_GLIDE_ANIM_MS 	150

#define GLIDE_BUTTON_DEL_BTN_FADE_IN_MS 	75
#define GLIDE_BUTTON_DEL_BTN_FADE_OUT_MS 	300
#define GLIDE_BUTTON_DEL_BTN_REMAIN_MS 	STANDARD_DEL_BTN_REMAIN_MS

#define GLIDE_BUTTON_DEL_ANIM_MS 			100

#define GLIDE_BUTTON_ARRAY_BASE_Y 		15

#define GLIDE_BUTTON_V_PAD	20
#define GLIDE_BUTTON_DISTANCE (GLIDE_BUTTON_HEIGHT + GLIDE_BUTTON_V_PAD)

struct m_int_glide_button_array;

typedef struct m_int_glide_button
{
	void *data;
	
	lv_obj_t *obj;
	lv_obj_t *label;
	lv_obj_t *del_button;
	lv_obj_t *del_button_label;
	
	char *label_text;
	
	lv_anim_t scale_anim;
	lv_anim_t glide_anim;
	lv_anim_t del_button_fade;
	lv_anim_t delete_anim;
	
	lv_timer_t *del_button_remain_timer;
	
	lv_coord_t pos_y;
	
	int index;
	int prev_index;
	
	uint32_t base_width;
	uint32_t base_height;
	
	int relative_touch_y;
	
	int long_pressed;
	
	struct m_int_glide_button_array *array;
} m_int_glide_button;

DECLARE_LINKED_PTR_LIST(m_int_glide_button);

typedef struct m_int_glide_button_array
{
	int n_buttons;
	m_int_glide_button_pll *buttons;
	
	m_ui_page *parent;
	
	int base_y_pos;
	
	void *data;
	
	int (*free_cb)(struct m_int_glide_button *button);
	int (*delete_cb)(struct m_int_glide_button *button);
	int (*clicked_cb)(struct m_int_glide_button *button);
	int (*moved_cb)(struct m_int_glide_button *button);
} m_int_glide_button_array;

void free_glide_button(m_int_glide_button *gb);

int glide_button_array_index_y_position(m_int_glide_button_array *array, int index);

m_int_glide_button_array *new_gb_array();

int append_glide_button_to_array(m_int_glide_button *button, m_int_glide_button_array *array);
m_int_glide_button *append_new_glide_button_to_array(m_int_glide_button_array *array, void *data, char *label);

int create_glide_button_ui(m_int_glide_button *gb, lv_obj_t *parent);
int create_glide_button_array_ui(m_int_glide_button_array *array, lv_obj_t *parent);

int glide_button_array_sort(m_int_glide_button_array *array);

int glide_button_change_label(m_int_glide_button *gb, char *text);

int glide_button_display_active(m_int_glide_button *gb);
int glide_button_undisplay_active(m_int_glide_button *gb);

#endif

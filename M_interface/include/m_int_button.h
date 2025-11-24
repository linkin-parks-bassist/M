#ifndef M_INT_M_BUTTON_H_
#define M_INT_M_BUTTON_H_

#define STANDARD_DEL_BTN_REMAIN_MS 	1000

#define STANDARD_BUTTON_HEIGHT 70
#define STANDARD_BUTTON_SHORT_HEIGHT 45

#define M_BUTTON_HEIGHT STANDARD_BUTTON_HEIGHT
#define M_BUTTON_WIDTH  (STANDARD_CONTAINER_WIDTH - (3 * GLOBAL_PAD_WIDTH))

#define M_BUTTON_SCALE_EXPAND 	1
#define M_BUTTON_SCALE_CONTRACT 	0

#define M_BUTTON_LP_SCALE 		1.05
#define M_BUTTON_SCALE_ANIM_MS 	75
#define M_BUTTON_GLIDE_ANIM_MS 	150

#define M_BUTTON_DEL_BTN_FADE_IN_MS 	75
#define M_BUTTON_DEL_BTN_FADE_OUT_MS 	300
#define M_BUTTON_DEL_BTN_REMAIN_MS 	STANDARD_DEL_BTN_REMAIN_MS

#define M_BUTTON_DEL_ANIM_MS 			100

#define M_BUTTON_ARRAY_BASE_Y 		15

#define M_BUTTON_V_PAD	20
#define M_BUTTON_DISTANCE (M_BUTTON_HEIGHT + M_BUTTON_V_PAD)

#define M_BUTTON_MAX_SUB_BUTTONS 2

#define M_BUTTON_DISABLED_OPACITY 128

#define M_BUTTON_FLAG_HIDDEN 		0b001
#define M_BUTTON_FLAG_DISABLED	 	0b010
#define M_BUTTON_FLAG_UNCLICKABLE 	0b100

typedef struct m_int_button
{
	int flags;
	
	lv_obj_t *obj;
	lv_obj_t *label;
	char *label_text;
	
	lv_event_cb_t clicked_cb;
	void *clicked_cb_arg;
	
	lv_event_cb_t pressing_cb;
	void *pressing_cb_arg;
	
	lv_event_cb_t long_pressed_cb;
	void *long_pressed_cb_arg;
	
	lv_event_cb_t released_cb;
	void *released_cb_arg;
	
	int long_pressed;
	int clickable;
	
	int *hider;
	
	int draggable_x;
	int draggable_y;
	
	int width;
	int height;
	
	lv_align_t alignment;
	int align_offs_x;
	int align_offs_y;
	
	int n_sub_buttons;
	struct m_int_button *sub_buttons[M_BUTTON_MAX_SUB_BUTTONS];
} m_int_button;

int init_button(m_int_button *button);
m_int_button *new_button(const char *label);

int m_button_create_label_ui(m_int_button *button);
int create_button_ui(m_int_button *button, lv_obj_t *parent);

int button_set_clicked_cb	  (m_int_button *button, lv_event_cb_t cb, void *cb_arg);
int button_set_pressing_cb	  (m_int_button *button, lv_event_cb_t cb, void *cb_arg);
int button_set_long_pressed_cb(m_int_button *button, lv_event_cb_t cb, void *cb_arg);
int button_set_released_cb	  (m_int_button *button, lv_event_cb_t cb, void *cb_arg);

int m_button_set_label(m_int_button *button, const char *label);
int m_button_set_alignment(m_int_button *button, lv_align_t align, int offs_x, int offs_y);
int m_button_set_size(m_int_button *button, int width, int height);

int m_button_add_sub_button(m_int_button *button, m_int_button *sub_button);

int m_button_hide(m_int_button *button);
int m_button_unhide(m_int_button *button);
int m_button_set_clickable(m_int_button *button);
int m_button_set_unclickable(m_int_button *button);

int m_button_enable(m_int_button *button);
int m_button_disable(m_int_button *button);

int m_button_delete_ui(m_int_button *button);

struct m_active_button_array;

typedef struct m_active_button
{
	void *data;
	
	m_int_button button;
	m_int_button *del_button;
	
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
	
	m_representation rep;
	
	struct m_active_button_array *array;
} m_active_button;

DECLARE_LINKED_PTR_LIST(m_active_button);

int m_active_button_add_del_button(m_active_button *button);
int m_active_button_change_label(m_active_button *button, char *text);
int m_active_button_swap_del_button_for_persistent_unclickable(m_active_button *button, const char *label);
int m_active_button_reset_del_button(m_active_button *button);

int m_active_button_set_dimensions(m_active_button *button, int w, int h);

int m_active_button_create_ui(m_active_button *button, lv_obj_t *parent);

void m_active_button_free(m_active_button *button);

void m_active_button_set_representation(m_active_button *button,
	void *representer, void *representee, void (*update)(void*, void*));

struct m_ui_page;

#define M_ACTIVE_BUTTON_ARRAY_FLAG_DELETEABLE 0b0001
#define M_ACTIVE_BUTTON_ARRAY_FLAG_MOVEABLE   0b0010

typedef struct m_active_button_array
{
	int flags;
	
	int n_buttons;
	int length;
	
	int button_width;
	int button_height;
	
	m_active_button **buttons;
	
	struct m_ui_page *parent;
	
	int base_y_pos;
	
	void *data;
	
	int (*delete_cb)(struct m_active_button *button);
	int (*del_button_cb)(struct m_active_button *button);
	int (*clicked_cb)(struct m_active_button *button);
	int (*moved_cb)(struct m_active_button *button);
} m_active_button_array;

int m_active_button_array_index_y_position(m_active_button_array *array, int index);

m_active_button_array *m_active_button_array_new();

int m_active_button_array_append(m_active_button *button, m_active_button_array *array);
m_active_button *m_active_button_array_append_new(m_active_button_array *array, void *data, char *label);
int m_active_button_array_remove(m_active_button_array *array, int index);

int m_active_button_array_set_length(m_active_button_array *array, int n);
int m_active_button_array_set_dimensions(m_active_button_array *array, int w, int h);

int m_active_button_array_create_ui(m_active_button_array *array, lv_obj_t *parent);

#endif

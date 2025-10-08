#ifndef EM_TRANSFORMER_H_
#define EM_TRANSFORMER_H_

typedef struct
{
	uint16_t profile_id;
	uint16_t transformer_id;
	
	int type;
	int position;
	
	int n_parameters;
	int parameter_array_length;
	em_parameter *parameters;
	
	int n_options;
	int option_array_length;
	em_option *options;
	
	em_ui_page *view_page;
} em_transformer;

int init_transformer(em_transformer *trans);

int init_transformer_parameter_array(em_transformer *trans);
int init_transformer_option_array(em_transformer *trans);

int em_transformer_enlarge_parameter_array(em_transformer *trans);
int em_transformer_enlarge_option_array(em_transformer *trans);

int em_transformer_set_n_parameters(em_transformer *trans, int n);
int em_transformer_set_n_options(em_transformer *trans, int n);

int transformer_add_parameter(em_transformer *trans, em_parameter *param);
em_parameter *transformer_add_parameter_rp(em_transformer *trans);

int transformer_add_option(em_transformer *trans, em_option *option);
em_option *transformer_add_option_rp(em_transformer *trans);

int init_default_transformer_by_type(em_transformer *trans, uint16_t type, uint16_t profile_id, uint16_t transformer_id);

int transformer_init_ui_page(em_transformer *trans, em_ui_page *parent);

void add_transformer_from_menu(lv_event_t *e);

int request_append_transformer(uint16_t type, em_transformer *local);
void transformer_recieve_id(et_msg message, te_msg response);

DECLARE_LINKED_LIST(em_parameter_widget);

#define TRANSFORMER_VIEW_GRID_CELL_HSIZE 250
#define TRANSFORMER_VIEW_GRID_CELL_VSIZE 200

typedef struct
{
	em_transformer *trans;
	
	lv_obj_t *grid;
	
	lv_coord_t col_dsc[3];
	lv_coord_t *row_dsc;
	
	em_parameter_widget_linked_list *em_parameter_widgets;
} em_transformer_view_str;

int transformer_view_configure(em_ui_page *page, void *trans);

int init_transformer_view(em_ui_page *page);
int configure_transformer_view(em_ui_page *page, void *data);
int create_transformer_view_ui(em_ui_page *page);
int free_transformer_view_ui(em_ui_page *page);
int enter_transformer_view(em_ui_page *page);
int enter_transformer_view_forward(em_ui_page *page);
int enter_transformer_view_back(em_ui_page *page);
int refresh_transformer_view(em_ui_page *page);

int transformer_view_request_parameter_values(em_ui_page *page);

extern const char *transformer_type_labels[];

struct em_profile;

typedef struct
{
	lv_obj_t *button;
	lv_obj_t *label;
	
	uint16_t type;
	char *name;
	
	struct em_profile *profile;
} em_trans_selector_button;

DECLARE_LINKED_LIST(em_trans_selector_button);

typedef struct
{
	lv_obj_t *button_list;
	
	em_trans_selector_button_linked_list *buttons;
	
	int page_offset;
	uint16_t pid;
	struct em_profile *profile;
} em_transformer_selector_str;

int init_transformer_selector_button(em_trans_selector_button *button, int index, struct em_profile *profile);

char *transformer_type_name(uint16_t type);

int init_transformer_selector(em_ui_page *page);
int configure_transformer_selector(em_ui_page *page, void *data);
int create_transformer_selector_ui(em_ui_page *page);
int free_transformer_selector_ui(em_ui_page *page);
int enter_transformer_selector(em_ui_page *page);
int refresh_transformer_selector(em_ui_page *page);

#endif

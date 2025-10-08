#ifndef EM_PROFILE_H_
#define EM_PROFILE_H_

typedef struct
{
	int width, height;
	
	int n_transformers;
	int transformer_array_length;
	em_transformer *transformers;
} em_pipeline;

typedef struct
{
	char *name;
	uint16_t id;
	em_pipeline pipeline;
	
	em_ui_page *view_page;
} em_profile;

int init_em_profile(em_profile *profile);
int init_em_pipeline(em_pipeline *pipeline);

int em_profile_set_default_name_from_id(em_profile *profile);

int em_pipeline_enlarge_transformer_array(em_pipeline *pipeline);

int em_pipeline_set_n_transformers(em_pipeline *pipeline, int n);

em_transformer *em_pipeline_append_transformer_type (em_pipeline *pipeline, uint16_t type);
em_transformer *em_pipeline_insert_transformer_type (em_pipeline *pipeline, uint16_t type, int position);
em_transformer *em_pipeline_prepend_transformer_type(em_pipeline *pipeline, uint16_t type);

typedef struct
{
	lv_obj_t *obj;
	lv_obj_t *label;
	
	const char *label_text;
	
	uint16_t profile_id;
	uint16_t transformer_id;
	
	em_transformer *trans;
} em_transformer_widget;

int delete_transformer_widget_ui(em_transformer_widget *tw);

DECLARE_LINKED_LIST(em_transformer_widget);

typedef struct
{
	em_profile *profile;
	
	lv_obj_t *button_list;
	lv_obj_t *plus_button;
	lv_obj_t *plus_button_label;
	
	em_transformer_widget_linked_list *tws;
} em_profile_view_str;

int init_transformer_widget(em_transformer_widget *tw, em_profile_view_str *parent, em_transformer *trans);
int create_transformer_widget_ui(em_transformer_widget *tw, lv_obj_t *parent);

int init_profile_view(em_ui_page *page);
int configure_profile_view(em_ui_page *page, void *data);
int create_profile_view_ui(em_ui_page *page);
int free_profile_view_ui(em_ui_page *page);
int enter_profile_view(em_ui_page *page);
int enter_profile_view_forward(em_ui_page *page);
int enter_profile_view_back(em_ui_page *page);
int refresh_profile_view(em_ui_page *page);

#endif

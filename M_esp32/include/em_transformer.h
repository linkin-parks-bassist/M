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

int transformer_set_id(em_transformer *trans, uint16_t profile_id, uint16_t transformer_id);

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
void transformer_receive_id(et_msg message, te_msg response);


int clone_transformer(em_transformer *dest, em_transformer *src);
void free_transformer(em_transformer *trans);

DECLARE_LINKED_PTR_LIST(em_transformer);

typedef em_transformer_ptr_linked_list transformer_ll;

#endif

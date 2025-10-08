#include "em.h"

#define INITIAL_PARAMETER_ARRAY_LENGTH 	8
#define PARAMETER_ARRAY_CHUNK_SIZE	 	8

#define INITIAL_OPTION_ARRAY_LENGTH 	8
#define OPTION_ARRAY_CHUNK_SIZE	 		8

IMPLEMENT_LINKED_LIST(em_parameter_widget);

const char *transformer_type_labels[] = {"Buffer", "Mixer", "Amplifier", "Biquadratic Filter", "Waveshaper", "Distortion", "Compression"};

const char *TAG = "Transformer";

int init_transformer(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->profile_id 	  = 0;
	trans->transformer_id = 0;
	trans->type 		  = 0;
	
	trans->position = 0;
	
	trans->n_parameters = 0;
	trans->parameter_array_length = INITIAL_PARAMETER_ARRAY_LENGTH;
	trans->parameters = malloc(sizeof(em_parameter) * trans->parameter_array_length);
	if (!trans->parameters)
	{
		trans->parameter_array_length = 0;
		return ERR_ALLOC_FAIL;
	}
	for (int i = 0; i < trans->parameter_array_length; i++)
		init_em_parameter(&trans->parameters[i]);
	
	trans->n_options = 0;
	trans->option_array_length = INITIAL_PARAMETER_ARRAY_LENGTH;
	trans->options = malloc(sizeof(em_option) * trans->option_array_length);
	if (!trans->options)
	{
		trans->option_array_length = 0;
		return ERR_ALLOC_FAIL;
	}
	for (int i = 0; i < trans->option_array_length; i++)
		init_em_option(&trans->options[i]);
	
	trans->view_page = NULL;
	
	return NO_ERROR;
}

int init_transformer_of_type(em_transformer *trans, uint16_t type)
{
	printf("init_transformer_of_type %d...\n", type);
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->profile_id 	  = 0;
	trans->transformer_id = 0;
	trans->position 	  = 0;
	trans->type = type;
	
	trans->n_parameters 		  = 0;
	trans->parameter_array_length = 0;
	
	trans->parameters 	= NULL;
	trans->view_page 	= NULL;
	
	em_parameter *param;
	
	switch (type)
	{
		case TRANSFORMER_AMPLIFIER:
			printf("Aaaaamplifier....\n");
			param = transformer_add_parameter_rp(trans);
			init_parameter(param, "Gain", 1.0, 0.0, 2.0);
			param->id.parameter_id = 0;
			break;
		
		case TRANSFORMER_DISTORTION:
			param = transformer_add_parameter_rp(trans);
			init_parameter(param, "Gain", 1.0, 0.0, 4.0);
			param->id.parameter_id = 0;
			
			param = transformer_add_parameter_rp(trans);
			init_parameter(param, "Wet Mix", 0.7, 0.0, 1.0);
			param->id.parameter_id = 1;
			
			param = transformer_add_parameter_rp(trans);
			init_parameter(param, "High Mix", 0.7, 0.0, 1.0);
			param->id.parameter_id = 2;
			
			param = transformer_add_parameter_rp(trans);
			init_parameter(param, "Mid Mix", 0.7, 0.0, 1.0);
			param->id.parameter_id = 3;
			
			param = transformer_add_parameter_rp(trans);
			init_parameter(param, "Bass Mix", 0.7, 0.0, 1.0);
			param->id.parameter_id = 4;
			
			param = transformer_add_parameter_rp(trans);
			init_parameter(param, "Mid Cutoff", 1000.0, 1000.0, 5000.0);
			param->id.parameter_id = 5;
			
			param = transformer_add_parameter_rp(trans);
			init_parameter(param, "Bass Cutoff", 100.0, 100.0, 1000.0);
			param->id.parameter_id = 6;
			
			param = transformer_add_parameter_rp(trans);
			init_parameter(param, "Ratio", 0.1, 0.0, 0.5);
			param->id.parameter_id = 7;
			break;
		
		case TRANSFORMER_COMPRESSOR:
			param = transformer_add_parameter_rp(trans);
			init_parameter(param, "Ratio", 1.0, 0.0, 8.0);
			param->id.parameter_id = 0;
			
			param = transformer_add_parameter_rp(trans);
			init_parameter(param, "Threshold", -8.0, 0.0, -30.0);
			param->id.parameter_id = 1;
			
			param = transformer_add_parameter_rp(trans);
			init_parameter(param, "Attack", 100, 0.0, 200.0);
			param->id.parameter_id = 2;
			param->factor = 1.0/1000.0;
			
			param = transformer_add_parameter_rp(trans);
			init_parameter(param, "Release", 100.0, 0.0, 400.0);
			param->id.parameter_id = 3;
			param->factor = 1.0/1000.0;
			break;
		
		default:
			return ERR_BAD_ARGS;
	}
	
	return NO_ERROR;
}

int transformer_rectify_param_ids(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	for (int i = 0; i < trans->n_parameters; i++)
	{
		trans->parameters[i].id.profile_id = trans->profile_id;
		trans->parameters[i].id.transformer_id = trans->transformer_id;
	}
	
	return NO_ERROR;
}

int em_transformer_enlarge_parameter_array(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int try_size = PARAMETER_ARRAY_CHUNK_SIZE;
	em_parameter *new_ptr;
	
	do
	{
		new_ptr = malloc(sizeof(em_parameter) * (trans->parameter_array_length + try_size));
		
		if (!new_ptr)
			try_size /= 2;
	} while (!new_ptr && try_size);
	
	if (!new_ptr)
		return ERR_ALLOC_FAIL;
	
	if (trans->parameters)
	{
		memcpy(new_ptr, trans->parameters, sizeof(em_parameter) * trans->parameter_array_length);
		free(trans->parameters);
	}
	
	for (int i = 0; i < try_size; i++)
		init_em_parameter(&new_ptr[trans->parameter_array_length + i]);
	
	trans->parameter_array_length = trans->parameter_array_length + try_size;
	trans->parameters = new_ptr;
	
	return NO_ERROR;
}


int em_transformer_enlarge_option_array(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int try_size = OPTION_ARRAY_CHUNK_SIZE;
	em_option *new_ptr;
	
	do
	{
		new_ptr = malloc(sizeof(em_option) * (trans->option_array_length + try_size));
		
		if (!new_ptr)
			try_size /= 2;
	} while (!new_ptr && try_size);
	
	if (!new_ptr)
		return ERR_ALLOC_FAIL;
	
	if (trans->options)
	{
		memcpy(new_ptr, trans->options, sizeof(em_option) * trans->option_array_length);
		free(trans->options);
	}
	
	for (int i = 0; i < try_size; i++)
		init_em_option(&new_ptr[trans->option_array_length + i]);
	
	trans->option_array_length = trans->option_array_length + try_size;
	trans->options = new_ptr;
	
	return NO_ERROR;
}

int request_append_transformer(uint16_t type, em_transformer *local)
{
	if (!local)
		return ERR_NULL_PTR;
	
	et_msg msg = create_et_msg(ET_MESSAGE_APPEND_TRANSFORMER, "ss", local->profile_id, local->type);
	msg.callback = transformer_recieve_id;
	msg.cb_arg = local;
	
	return queue_msg_to_teensy(msg);
}

void transformer_recieve_id(et_msg message, te_msg response)
{
	em_transformer *trans = message.cb_arg;
	
	if (!trans)
		return;
	
	uint16_t pid, tid;
	
	memcpy(&pid, &response.data[0], sizeof(uint16_t));
	memcpy(&tid, &response.data[2], sizeof(uint16_t));
	
	if (pid != trans->profile_id)
	{
		ESP_LOGE(TAG, "Transformer ID for transformer in profile %d sent to transformer in %d\n", pid, trans->profile_id);
	}
	else
	{
		trans->transformer_id = tid;
	}
}

int transformer_add_parameter(em_transformer *trans, em_parameter *param)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int ret_val;
	
	if (trans->n_parameters >= trans->parameter_array_length)
	{
		ret_val = em_transformer_enlarge_parameter_array(trans);
		
		if (ret_val != NO_ERROR)
			return ret_val;
	}
	
	trans->parameters[trans->n_parameters++] = *param;
	
	return NO_ERROR;
}

em_parameter *transformer_add_parameter_rp(em_transformer *trans)
{
	if (!trans)
		return NULL;
	
	int ret_val;
	
	if (trans->n_parameters >= trans->parameter_array_length)
	{
		ret_val = em_transformer_enlarge_parameter_array(trans);
		
		if (ret_val != NO_ERROR)
			return NULL;
	}
	
	trans->n_parameters++;
	
	return &trans->parameters[trans->n_parameters - 1];
}

int em_transformer_set_n_parameters(em_transformer *trans, int n)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int tries = 0;
	
	while (trans->parameter_array_length < n && tries < 32)
	{
		em_transformer_enlarge_parameter_array(trans);
		tries++;
	}
	
	if (trans->parameter_array_length < n)
		return ERR_ALLOC_FAIL;
	
	trans->n_parameters = n;
	
	return NO_ERROR;
}


int em_transformer_set_n_options(em_transformer *trans, int n)
{
	if (!trans)
		return ERR_NULL_PTR;
	
	int tries = 0;
	
	while (trans->option_array_length < n && tries < 32)
	{
		em_transformer_enlarge_option_array(trans);
		tries++;
	}
	
	if (trans->option_array_length < n)
		return ERR_ALLOC_FAIL;
	
	trans->n_options = n;
	
	return NO_ERROR;
}

int transformer_init_ui_page(em_transformer *trans, em_ui_page *parent)
{
	printf("transformer_init_ui_page...\n");
	if (!trans)
		return ERR_NULL_PTR;
	
	trans->view_page = malloc(sizeof(em_ui_page));
	
	if (!trans->view_page)
		return ERR_NULL_PTR;
	
	init_ui_page(trans->view_page);
	init_transformer_view(trans->view_page);
	configure_transformer_view(trans->view_page, trans);
	trans->view_page->parent = parent;
	
	printf("done transformer_init_ui_page\n");
	return NO_ERROR;
}

int init_transformer_view(em_ui_page *page)
{
	printf("Init transformer view...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	em_transformer_view_str *str = malloc(sizeof(em_transformer_view_str));
	
	page->data_struct = str;
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	str->col_dsc[0] = 250;
	str->col_dsc[1] = 200;
	str->col_dsc[2] = LV_GRID_TEMPLATE_LAST;
	
	str->trans = NULL;
	str->em_parameter_widgets = NULL;
	
	str->grid = NULL;
	
	str->row_dsc = NULL;
	
	page->configure  		 = configure_transformer_view;
	page->create_ui  		 = create_transformer_view_ui;
	page->enter_page 		 = enter_transformer_view;
	page->enter_page_forward = enter_transformer_view_forward;
	page->enter_page_back 	 = enter_transformer_view_back;
	
	printf("Done\n");
	return NO_ERROR;
}

int configure_transformer_view(em_ui_page *page, void *data)
{
	printf("Configure transformer view...\n");
	if (!data)
	{
		page->data_struct = NULL;
		return ERR_NULL_PTR;
	}
	
	em_transformer *trans = (em_transformer*)data;
	em_transformer_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	str->trans = trans;
	
	em_parameter_widget pw;
	int ret_val;
	
	for (int i = 0; i < trans->n_parameters; i++)
	{
		nullify_em_parameter_widget(&pw);
		ret_val = configure_em_parameter_widget(&pw, &trans->parameters[i]);
		printf("Error code %d encountered at parameter %d.%d.%d\n", ret_val, trans->profile_id, trans->transformer_id, trans->parameters[i].id.parameter_id);
		str->em_parameter_widgets = em_parameter_widget_linked_list_append(str->em_parameter_widgets, pw);
	}
	
	printf("Done.\n");
	return NO_ERROR;
}

int create_transformer_view_ui(em_ui_page *page)
{
	printf("Create transformer view ui...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	page->screen = lv_obj_create(NULL);
	
	em_transformer_view_str *str = (em_transformer_view_str*)page->data_struct;
	
	printf("str->trans->n_parameters: %d\n", str->trans->n_parameters);
	
	if (!str)
		return ERR_BAD_ARGS;
	
	if (!str->trans)
		return ERR_BAD_ARGS;
	
	int n_rows = (str->trans->n_parameters + 1) / 2;
	
	str->row_dsc = malloc(sizeof(lv_coord_t) * (n_rows + 1));
	
	if (!str->row_dsc)
		return ERR_ALLOC_FAIL;
	
	for (int i = 0; i < n_rows; i++)
		str->row_dsc[i] = TRANSFORMER_VIEW_GRID_CELL_VSIZE;
	
	str->row_dsc[n_rows] = LV_GRID_TEMPLATE_LAST;
	
	str->grid = lv_obj_create(page->screen);
	
	printf("Create top panel...\n");
	create_top_panel_with_back_button(page, transformer_type_labels[str->trans->type], NULL);
	
	lv_obj_set_style_grid_column_dsc_array(str->grid, str->col_dsc, 0);
	lv_obj_set_style_grid_row_dsc_array(str->grid, str->row_dsc, 0);
	lv_obj_set_size(str->grid, 500, 800);
	lv_obj_center(str->grid);
	
	lv_obj_set_layout(str->grid, LV_LAYOUT_GRID);

	int i = 0;
	em_parameter_widget_linked_list *current = str->em_parameter_widgets;
	
	while (current)
	{
		parameter_widget_create_ui(&current->data, str->grid);
		lv_obj_set_grid_cell(current->data.obj, LV_GRID_ALIGN_CENTER, i % 2, 1, LV_GRID_ALIGN_CENTER, i / 2, 1);
		current = current->next;
		i++;
	}
	
	printf("Done\n");
	return NO_ERROR;
}

int enter_transformer_view(em_ui_page *page)
{
	printf("Enter transformer view...\n");
	lv_scr_load(page->screen);
	
	transformer_view_request_parameter_values(page);
	printf("Done\n");
	return NO_ERROR;
}

int enter_transformer_view_forward(em_ui_page *page)
{
	printf("Enter transformer view...\n");
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, false);
	
	transformer_view_request_parameter_values(page);
	printf("Done\n");
	return NO_ERROR;
}

int enter_transformer_view_back(em_ui_page *page)
{
	printf("Enter transformer view...\n");
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 30, 0, false);
	
	transformer_view_request_parameter_values(page);
	printf("Done\n");
	return NO_ERROR;
}

int clear_transformer_view()
{
	return ERR_UNIMPLEMENTED;
}

int transformer_view_request_parameter_values(em_ui_page *page)
{
	printf("transformer_view_request_parameter_values...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	em_transformer_view_str *str = (em_transformer_view_str*)page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	em_parameter_widget_linked_list *current = str->em_parameter_widgets;
	
	while (current)
	{
		param_widget_request_value(&current->data);
		current = current->next;
	}
	
	printf("done transformer_view_request_parameter_values\n");
	
	return NO_ERROR;
}

int init_transformer_selector(em_ui_page *page)
{
	printf("init_transformer_selector...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	em_transformer_selector_str *str = malloc(sizeof(em_transformer_selector_str));
	
	page->data_struct = str;
	
	if (!str)
		return ERR_ALLOC_FAIL;
	
	str->button_list   = NULL;
	str->buttons 	   = NULL;
	str->button_labels = NULL;
	
	return NO_ERROR;
}

int configure_transformer_selector(em_ui_page *page, void *data)
{
	printf("configure_transformer_selector...\n");
	if (!page || !data)
		return ERR_NULL_PTR;
	
	em_profile *profile = (em_profile*)data;
	
	em_transformer_selector_str *ts = page->data_struct;
	
	if (!ts)
		return ERR_ALLOC_FAIL;
	
	printf("success\n");
	return NO_ERROR;
}

#define LINEAR_TRANSFORMER_OPTIONS 3

#define AMPLIFIER_BUTTON  0
#define DISTORTION_BUTTON 1
#define COMPRESSOR_BUTTON 2

void add_transformer_from_menu(lv_event_t *e)
{
	lv_obj_t *button = lv_event_get_target(e);
	em_ui_page *page = lv_event_get_user_data(e);
	
	if (!page)
	{
		ESP_LOGE(TAG, "User tried to add transformer from menu, but the pointer to the page struct is NULL!\n");
		return;
	}
	
	em_transformer_selector_str *ts = page->data_struct;
	em_transformer *trans = NULL;
	
	uint16_t type = -1;
	
	if (button == ts->buttons[0])
	{
		printf("User wishes to add an amplifier!\n");
		type = TRANSFORMER_AMPLIFIER;
	}
	else if (button == ts->buttons[1])
	{
		printf("User wishes to add distortion!\n");
		type = TRANSFORMER_DISTORTION;
	}
	else if (button == ts->buttons[2])
	{
		printf("User wishes to add compression!\n");
		type = TRANSFORMER_COMPRESSOR;
	}
	
	if (!page->parent)
	{
		ESP_LOGE(TAG, "Transformer selection page is floating!\n");
	}
	else
	{
		em_profile_view_str *str = (em_profile_view_str*)page->parent->data_struct;
		
		em_profile *profile = str->profile;
		
		if (!profile)
		{
			ESP_LOGE(TAG, "Profile view page has no associated profile!\n");
		}
		else
		{
			trans = em_pipeline_append_transformer_type(&profile->pipeline, type);
			printf("Created new transformerwith type %d, having %d parameters\n", trans->type, trans->n_parameters);
			refresh_profile_view(page->parent);
			request_append_transformer(type, trans);
			
			transformer_init_ui_page(trans, page->parent);
			create_transformer_view_ui(trans->view_page);
		}
		
		enter_ui_page(page->parent);
	}
}

int create_transformer_selector_ui(em_ui_page *page)
{
	printf("create_transformer_selector_ui...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	em_transformer_selector_str *ts = (em_transformer_selector_str*)page->data_struct;
	
	if (!ts)
		return ERR_BAD_ARGS;
	
	page->screen = lv_obj_create(NULL);
	
	create_top_panel_with_back_button(page, "Add Effect", NULL);
	
	ts->button_list = lv_obj_create(page->screen);
    lv_obj_set_size(ts->button_list, 500, 800);
    lv_obj_align(ts->button_list, LV_ALIGN_TOP_MID, 0, 120);
    lv_obj_set_flex_flow(ts->button_list, LV_FLEX_FLOW_COLUMN);
    
    ts->buttons 	  = malloc(sizeof(lv_obj_t*) * LINEAR_TRANSFORMER_OPTIONS);
    ts->button_labels = malloc(sizeof(lv_obj_t*) * LINEAR_TRANSFORMER_OPTIONS);
    
    ts->buttons[AMPLIFIER_BUTTON] = lv_btn_create(ts->button_list);
    lv_obj_set_size(ts->buttons[AMPLIFIER_BUTTON], LV_PCT(100), LV_SIZE_CONTENT);
	ts->button_labels[AMPLIFIER_BUTTON] = lv_label_create(ts->buttons[AMPLIFIER_BUTTON]);
	lv_label_set_text(ts->button_labels[AMPLIFIER_BUTTON], "Amplifier");
	lv_obj_center(ts->button_labels[AMPLIFIER_BUTTON]);
	
	lv_obj_add_event_cb(ts->buttons[AMPLIFIER_BUTTON], add_transformer_from_menu, LV_EVENT_CLICKED, page);
    
    ts->buttons[DISTORTION_BUTTON] = lv_btn_create(ts->button_list);
    lv_obj_set_size(ts->buttons[DISTORTION_BUTTON], LV_PCT(100), LV_SIZE_CONTENT);
	ts->button_labels[DISTORTION_BUTTON] = lv_label_create(ts->buttons[DISTORTION_BUTTON]);
	lv_label_set_text(ts->button_labels[DISTORTION_BUTTON], "Distortion");
	lv_obj_center(ts->button_labels[DISTORTION_BUTTON]);
	
	lv_obj_add_event_cb(ts->buttons[DISTORTION_BUTTON], add_transformer_from_menu, LV_EVENT_CLICKED, page);
    
    ts->buttons[COMPRESSOR_BUTTON] = lv_btn_create(ts->button_list);
    lv_obj_set_size(ts->buttons[COMPRESSOR_BUTTON], LV_PCT(100), LV_SIZE_CONTENT);
	ts->button_labels[COMPRESSOR_BUTTON] = lv_label_create(ts->buttons[COMPRESSOR_BUTTON]);
	lv_label_set_text(ts->button_labels[COMPRESSOR_BUTTON], "Compressor");
	lv_obj_center(ts->button_labels[COMPRESSOR_BUTTON]);
	
	lv_obj_add_event_cb(ts->buttons[COMPRESSOR_BUTTON], add_transformer_from_menu, LV_EVENT_CLICKED, page);
	
	printf("success\n");
	return NO_ERROR;
}

int enter_transformer_selector(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_scr_load(page->screen);
	
	return NO_ERROR;
}

int enter_transformer_selector_forward(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, false);
	
	return NO_ERROR;
}

int enter_transformer_selector_back(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 30, 0, false);
	
	return NO_ERROR;
}

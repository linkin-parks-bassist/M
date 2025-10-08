#include "em.h"

IMPLEMENT_LINKED_LIST(em_transformer_widget);

static const char *TAG = "em_profile.c";

int init_em_profile(em_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	profile->id = 0;
	
	int ret_val = init_em_pipeline(&profile->pipeline);
	
	if (ret_val != NO_ERROR)
		return ret_val;
	
	return NO_ERROR;
}

int em_profile_set_default_name_from_id(em_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	// Compute the digits in the ID. 
	int id_digits;
	int id_div = profile->id;
	
	for (id_digits = 0; id_div || !id_digits; id_div = id_div / 10)
		id_digits++;
	
	profile->name = malloc(9 + id_digits);
	
	if (!profile->name)
		return ERR_ALLOC_FAIL;
	
	sprintf(profile->name, "Profile %d\n", id_digits);
	
	return NO_ERROR;
}

#define INITIAL_TRANSFORMER_ARRAY_LENGTH 8
#define TRANSFORMER_ARRAY_CHUNK_SIZE	 8

int init_em_pipeline(em_pipeline *pipeline)
{
	if (!pipeline)
		return ERR_NULL_PTR;
	
	pipeline->n_transformers = 0;
	
	pipeline->transformer_array_length = INITIAL_TRANSFORMER_ARRAY_LENGTH;
	pipeline->transformers = malloc(sizeof(em_transformer) * pipeline->transformer_array_length);
	
	if (!pipeline->transformers)
	{
		pipeline->transformer_array_length = 0;
		return ERR_ALLOC_FAIL;
	}
	
	for (int i = 0; i < pipeline->transformer_array_length; i++)
		init_transformer(&pipeline->transformers[i]);
	
	return NO_ERROR;
}

int em_pipeline_enlarge_transformer_array(em_pipeline *pipeline)
{
	if (!pipeline)
		return ERR_NULL_PTR;
	
	int try_size = TRANSFORMER_ARRAY_CHUNK_SIZE;
	em_transformer *new_ptr;
	
	do
	{
		new_ptr = malloc(sizeof(em_transformer) * (pipeline->transformer_array_length + try_size));
		
		if (!new_ptr)
			try_size /= 2;
	} while (!new_ptr && try_size);
	
	if (!new_ptr || !try_size)
		return ERR_ALLOC_FAIL;
	
	if (pipeline->transformers)
	{
		memcpy(new_ptr, pipeline->transformers, pipeline->transformer_array_length * sizeof(em_transformer));
		free(pipeline->transformers);
	}
	
	for (int i = 0; i < try_size; i++)
		init_transformer(&new_ptr[pipeline->transformer_array_length + i]);
	
	pipeline->transformer_array_length = pipeline->transformer_array_length + try_size;
	pipeline->transformers = new_ptr;
	
	return NO_ERROR;
}

em_transformer *em_profile_append_transformer_type(em_profile *profile, uint16_t type)
{
	if (!profile)
		return NULL;
	
	printf("Appending transformer of type %d. Currently there are %d transformers in the profile->pipeline. The array has size %d\n",
		type, profile->pipeline.n_transformers, profile->pipeline.transformer_array_length);
	int ret_val;
	
	if (profile->pipeline.n_transformers >= profile->pipeline.transformer_array_length)
	{
		ret_val = em_pipeline_enlarge_transformer_array(&profile->pipeline);
		
		if (ret_val != NO_ERROR)
			return NULL;
	}
	
	int position = profile->pipeline.n_transformers++;
	
	init_transformer_of_type(&profile->pipeline.transformers[position], type);
	profile->pipeline.transformers[position].position = position;
	profile->pipeline.transformers[position].profile_id = profile->id;
	
	printf("Appended transformer of type %d. Currently there are %d transformers in the profile->pipeline. The array has size %d\n", type,
		profile->pipeline.n_transformers, profile->pipeline.transformer_array_length);
	
	return &profile->pipeline.transformers[position];
}

em_transformer *em_pipeline_insert_transformer_type(em_pipeline *pipeline, uint16_t type, int position)
{
	if (!pipeline)
		return NULL;
	
	int ret_val;
	
	if (pipeline->n_transformers >= pipeline->transformer_array_length)
	{
		ret_val = em_pipeline_enlarge_transformer_array(pipeline);
		
		if (ret_val != NO_ERROR)
			return NULL;
	}
	
	for (int i = pipeline->n_transformers - 1; i >= position && i >= 0; i--)
		pipeline->transformers[i + 1] = pipeline->transformers[i];
	
	init_transformer_of_type(&pipeline->transformers[position], type);
	pipeline->transformers[position].position = position;
	
	pipeline->n_transformers++;
	
	return &pipeline->transformers[position];
}

em_transformer *em_pipeline_prepend_transformer_type(em_pipeline *pipeline, uint16_t type)
{
	return em_pipeline_insert_transformer_type(pipeline, type, 0);
}

int em_pipeline_set_n_transformers(em_pipeline *pipeline, int n)
{
	if (!pipeline)
		return ERR_NULL_PTR;
	
	int tries = 0;
	
	while (pipeline->transformer_array_length < n && tries < 32)
	{
		em_pipeline_enlarge_transformer_array(pipeline);
		tries++;
	}
	
	if (pipeline->transformer_array_length < n)
		return ERR_ALLOC_FAIL;
	
	pipeline->n_transformers = n;
	
	return NO_ERROR;
}

int init_profile_view(em_ui_page *page)
{
	printf("init_profile_view...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *str = malloc(sizeof(em_profile_view_str));
	page->data_struct = (void*)str;
	
	str->profile 		= NULL;
	str->button_list 	= NULL;
	str->profile 		= NULL;
	str->tws 			= NULL;
	
	page->configure  			= configure_profile_view;
	page->create_ui  			= create_profile_view_ui;
	page->enter_page 			= enter_profile_view;
	page->enter_page_forward 	= enter_profile_view_forward;
	page->enter_page_back 		= enter_profile_view_back;
	
	printf("success\n");
	return NO_ERROR;
}

int configure_profile_view(em_ui_page *page, void *data)
{
	printf("configure_profile_view...\n");
	if (!page || !data)
		return ERR_NULL_PTR;
	
	em_profile *profile = (em_profile*)data;
	
	em_profile_view_str *pv = page->data_struct;
	
	if (!pv)
		return ERR_ALLOC_FAIL;
	
	page->data_struct = pv;
	
	pv->profile = profile;
	
	em_transformer_widget tw;
	
	em_transformer_widget_linked_list *nl;
	
	int ret_val;
	int alloc_fail = 0;
	
	for (int i = 0; i < profile->pipeline.n_transformers; i++)
	{
		ret_val = init_transformer_widget(&tw, pv, &profile->pipeline.transformers[i]);
		
		if (ret_val != NO_ERROR)
			return ret_val;
		
		nl = em_transformer_widget_linked_list_append(pv->tws, tw);
		
		if (!nl)
		{
			free_em_transformer_widget_linked_list(pv->tws);
			pv->tws = NULL;
			return ERR_ALLOC_FAIL;
		}
		pv->tws = nl;
		
		if (!profile->pipeline.transformers[i].view_page)
		{
			ret_val = transformer_init_ui_page(&profile->pipeline.transformers[i], page);
			
			if (ret_val != NO_ERROR)
			{
				if (ret_val == ERR_ALLOC_FAIL)
				{
					alloc_fail = 1;
				}
				else
				{
					ESP_LOGE(TAG, "Erroe code %d encountered initialising transformer view page for transformer %d.%d\n", profile->id, i);
				}
			}
			else
			{
				profile->pipeline.transformers[i].view_page->create_ui(profile->pipeline.transformers[i].view_page);
			}
		}
		
	}
	
	printf("success\n");
	return alloc_fail ? ERR_ALLOC_FAIL : NO_ERROR;
}

void enter_transformer_selector_cb(lv_event_t *e)
{
	enter_transformer_selector(&global_cxt.ui_cxt.transformer_selector);
}

int create_profile_view_ui(em_ui_page *page)
{
	printf("create_profile_view_ui...\n");
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *pv = (em_profile_view_str*)page->data_struct;
	
	if (!pv)
		return ERR_BAD_ARGS;
		
	if (!pv->profile)
		return ERR_BAD_ARGS;
	
	page->screen = lv_obj_create(NULL);
	
	printf("Creating top panel with label %s\n", pv->profile->name ? pv->profile->name : "(null)");
	create_top_panel_with_back_button(page, pv->profile->name, NULL);
	
	pv->button_list = lv_obj_create(page->screen);
    lv_obj_set_size(pv->button_list, 500, 800);
    lv_obj_align(pv->button_list, LV_ALIGN_TOP_MID, 0, 120);
    lv_obj_set_flex_flow(pv->button_list, LV_FLEX_FLOW_COLUMN);
    
    em_transformer_widget_linked_list *current = pv->tws;
    
    while (current)
    {
		create_transformer_widget_ui(&current->data, pv->button_list);
		current = current->next;
	}
	
    pv->plus_button = lv_btn_create(pv->button_list);
    lv_obj_set_size(pv->plus_button, LV_PCT(100), LV_SIZE_CONTENT);
	pv->plus_button_label = lv_label_create(pv->plus_button);
	lv_label_set_text(pv->plus_button_label, "+");
	lv_obj_center(pv->plus_button_label);
	
	lv_obj_add_event_cb(pv->plus_button, enter_transformer_selector_cb, LV_EVENT_CLICKED, page);
	
	printf("success\n");
	return NO_ERROR;
}

int refresh_profile_view(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	em_profile_view_str *str = page->data_struct;
	
	if (!str)
		return ERR_BAD_ARGS;
	
	int n = str->profile->pipeline.n_transformers;
	
	em_transformer *trans;
	em_transformer *trans_array[n];
	
	// Store the transformers in a local array for convenience
	for (int i = 0; i < str->profile->pipeline.n_transformers; i++)
		trans_array[i] = &str->profile->pipeline.transformers[i];
	
	int m = 0;
	em_transformer_widget_linked_list *current, *prev, *tmp;
	
	// Count how many transformer_widgets there are
	for (current = str->tws; current; current = current->next) m++;
	
	if (m == 0)
	{
		if (n == 0)
			return NO_ERROR;
		
		em_transformer_widget tw;
		for (int i = 0; i < n; i++)
		{
			init_transformer_widget(&tw, str, trans_array[i]);
			create_transformer_widget_ui(&tw, str->button_list);
			
			tmp = em_transformer_widget_linked_list_append(str->tws, tw);
			
			if (!tmp)
				return ERR_ALLOC_FAIL;
			else
				str->tws = tmp;
			
			lv_obj_move_to_index(tw.obj, i);
		}
		
		return NO_ERROR;
	}
	
	
	em_transformer_widget_linked_list *list_array[m];
	
	// NULL-initialise the array. This is important
	for (int i = 0; i < m; i++)
		list_array[i] = NULL;
	
	int indexes[m];
	
	int i = 0;
	prev = NULL;
	
	// Store the transformer widget linked list nodes in an array,
	// deleting any which correspond to a nonexistent transformer
	
	current = str->tws;
	while (current)
	{
		list_array[i] = current;
		
		indexes[i] = -1;
		for (int j = 0; j < n; j++)
		{
			if (current->data.trans == trans_array[j])
			{
				indexes[i] = j;
			}
		}
		
		if (indexes[i] == -1)
		{
			delete_transformer_widget_ui(&current->data);
			
			if (prev)
				prev->next = current->next;
			else
				str->tws = current->next;
			
			free(current);
			current = prev->next;
			m--;
		}
		else
		{
			i++;
			current = current->next;
		}
	}

	
	int sorted;
	int itmp;
	
	// Sort the array or transformer widgets so that
	// they match the actual order of transformers
	do
	{
		sorted = 1;
		for (i = 0; i < m - 1; i++)
		{
			if (indexes[i] > indexes[i + 1])
			{
				tmp = list_array[i];
				list_array[i] = list_array[i+1];
				list_array[i+1] = tmp;
				
				itmp = indexes[i];
				indexes[i] = indexes[i+1];
				indexes[i+1] = itmp;
				
				sorted = 0;
			}
		}
	} while (!sorted);
	
	str->tws = list_array[0];
	// Re-link the linked list in the correct order
	current = str->tws;
	for (int i = 1; i < m; i++)
	{
		current->next = list_array[i];
		current = current->next;
	}
	current->next = NULL;
	
	// For any transformers without widgets, create them,
	// and add them to the linked list
	em_transformer_widget tw;
	for (int j = m; j < n; j++)
	{
		init_transformer_widget(&tw, str, trans_array[j]);
		create_transformer_widget_ui(&tw, str->button_list);
		
		tmp = em_transformer_widget_linked_list_append(str->tws, tw);
		
		if (!tmp)
			return ERR_ALLOC_FAIL;
		else
			str->tws = tmp;
	}
	
	// At this point, we have a linked list of transformer widgets
	// agreeing exactly with the array of transformers in the profile
	// Therefore, we can simply update their positions in the UI
	
	current = str->tws;
	i = 0;
	
	while (current)
	{
		lv_obj_move_to_index(current->data.obj, i);
		current = current->next;
		i++;
	}
	
	return NO_ERROR;
}

int enter_profile_view(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_scr_load(page->screen);
	
	((em_transformer_selector_str*)global_cxt.ui_cxt.transformer_selector.data_struct)->pid = ((em_profile_view_str*)page->data_struct)->profile->id;
	global_cxt.ui_cxt.transformer_selector.parent = page;
	
	return NO_ERROR;
}

int enter_profile_view_forward(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, false);
	
	((em_transformer_selector_str*)global_cxt.ui_cxt.transformer_selector.data_struct)->pid = ((em_profile_view_str*)page->data_struct)->profile->id;
	global_cxt.ui_cxt.transformer_selector.parent = page;
	
	return NO_ERROR;
}

int enter_profile_view_back(em_ui_page *page)
{
	if (!page)
		return ERR_NULL_PTR;
	
	lv_scr_load_anim(page->screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 30, 0, false);
	
	((em_transformer_selector_str*)global_cxt.ui_cxt.transformer_selector.data_struct)->pid = ((em_profile_view_str*)page->data_struct)->profile->id;
	global_cxt.ui_cxt.transformer_selector.parent = page;
	
	return NO_ERROR;
}

int init_transformer_widget(em_transformer_widget *tw, em_profile_view_str *parent, em_transformer *trans)
{
	if (!tw || !parent)
		return ERR_NULL_PTR;
	
	tw->trans = trans;
	
	tw->profile_id = parent->profile->id;
	tw->transformer_id = trans ? trans->transformer_id : 0;
	
	if (trans)
		tw->label_text = transformer_type_name(trans->type);
	
	tw->obj	  = NULL;
	tw->label = NULL;
	
	return NO_ERROR;
}


int create_transformer_widget_ui(em_transformer_widget *tw, lv_obj_t *parent)
{
	printf("create_transformer_widget_ui...\n");
	if (!tw)
		return ERR_NULL_PTR;
	
	tw->obj = lv_btn_create(parent);
	
	printf("tw->obj = %p\n", tw->obj);
    lv_obj_set_size(tw->obj, LV_PCT(100), LV_SIZE_CONTENT);
	
	tw->label = lv_label_create(tw->obj);
	lv_label_set_text(tw->label, tw->label_text);
	printf("label: %s\n", tw->label_text);
	lv_obj_center(tw->label);
	
	if (tw->trans)
	{
		lv_obj_add_event_cb(tw->obj, enter_ui_page_cb, LV_EVENT_CLICKED, &tw->trans->view_page);
	}
	
	
	printf("success\n");
	return NO_ERROR;
}

int delete_transformer_widget_ui(em_transformer_widget *tw)
{
	if (!tw)
		return ERR_NULL_PTR;
	
	lv_obj_del(tw->obj);
	lv_obj_del(tw->label);
	
	return NO_ERROR;
}

static lv_obj_t *main_scr;
static lv_obj_t *select_scr;
static lv_obj_t *btn_list;

static lv_obj_t *add_main_button(const char *txt)
{
    lv_obj_t *btn = lv_btn_create(btn_list);
    lv_obj_set_width(btn, lv_pct(95));
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, txt);
    lv_obj_center(label);
    return btn;
}

static void plus_event_cb(lv_event_t *e)
{
    lv_scr_load(select_scr);
}


static void option_event_cb(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    const char *choice = lv_label_get_text(lv_obj_get_child(btn, 0));

    // Add chosen option as a button on main screen
    add_main_button(choice);

    // Add a fresh "+" button again at the bottom
    lv_obj_t *plus = add_main_button("+");
    lv_obj_add_event_cb(plus, plus_event_cb, LV_EVENT_CLICKED, NULL);

    // Switch back to main screen
    lv_scr_load(main_scr);
}


// --- screen setup ---
void create_profile_view()
{
    // --- Main screen ---
    main_scr = lv_obj_create(NULL);

    btn_list = lv_obj_create(main_scr);
    lv_obj_set_size(btn_list, 500, 540);
    lv_obj_align(btn_list, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_flex_flow(btn_list, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_gap(btn_list, 0, 0);

    // First "+" button
    lv_obj_t *plus = add_main_button("+");
    lv_obj_add_event_cb(plus, plus_event_cb, LV_EVENT_CLICKED, NULL);

    // --- Select screen ---
    select_scr = lv_obj_create(NULL);
    lv_obj_t *opt_list = lv_obj_create(select_scr);
    lv_obj_set_size(opt_list, 500, 540);
    lv_obj_align(opt_list, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_flex_flow(opt_list, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_gap(opt_list, 0, 0);

    // Add some options
    const char *options[] = { "Option A", "Option B", "Option C" };
    for(int i = 0; i < 3; i++) {
        lv_obj_t *btn = lv_btn_create(opt_list);
        lv_obj_set_width(btn, lv_pct(95));
        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text(label, options[i]);
        lv_obj_center(label);
        lv_obj_add_event_cb(btn, option_event_cb, LV_EVENT_CLICKED, NULL);
    }

    // Start with main screen
    lv_scr_load(main_scr);
}


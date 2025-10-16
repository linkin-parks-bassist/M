#include "tm.h"

int nullify_pipeline(tm_pipeline *pipeline)
{
	if (!pipeline) return ERR_NULL_PTR;
	
	pipeline->input_node.block   = NULL;
	pipeline->output_node.block  = NULL;
	
	pipeline->nodes = NULL;
	
	pipeline->active_node_array = NULL;
	
	pipeline->n_active_nodes = 0;
	pipeline->n_transformers = 0;
	pipeline->n_active_transformers = 0;
	
	pipeline->width  = 0;
	pipeline->height = 0;
	
	for (int i = 0; i < MAX_PIPELINE_TRANSFORMERS; i++)
		pipeline->transformers[i] = NULL;
	
	pipeline->err_flags = PIPELINE_ERR_FLAG_OUTPUT_UNFED | PIPELINE_ERR_FLAG_UNCONFIGURED;
	
	return NO_ERROR;
}

int init_pipeline(tm_pipeline *pipeline, int width, int height)
{
	if (!pipeline)
		return ERR_NULL_PTR;
	
	tm_printf("Initialising pipeline...\n");
	
	// First, initialise allllll the pointers to be NULL, for safety
	pipeline->input_node.block = NULL;
	pipeline->output_node.block = NULL;
	pipeline->nodes = NULL;
	pipeline->active_node_array = NULL;
	
	for (int i = 0; i < MAX_PIPELINE_TRANSFORMERS; i++)
		pipeline->transformers[i] = NULL;
	
	// Then do the alloc's
	//tm_printf("Allocating input block...\n");
	if (!(pipeline->input_node.block = allocate_block()))
		goto free_and_err_out;
	
	tm_printf("Allocated input node block at %p\n", pipeline->input_node.block);
	
	pipeline->input_node.active  = 1;
	
	//tm_printf("Allocating output block...\n");
	if (!(pipeline->output_node.block = allocate_block()))
		goto free_and_err_out;

	tm_printf("Allocated output node block at %p\n", pipeline->output_node.block);
	
	pipeline->output_node.active = 1;
	
	//tm_printf("Allocating node array...\n");
	pipeline->nodes = (tm_pipeline_node**)malloc(width * sizeof(tm_pipeline_node*));
	
	if (!pipeline->nodes)
		goto free_and_err_out;
	
	for (int i = 0; i < width; i++)
		pipeline->nodes[i] = NULL;
	
	for (int i = 0; i < width; i++)
	{
		pipeline->nodes[i] = (tm_pipeline_node*)malloc(height * sizeof(tm_pipeline_node));
			
		if (!pipeline->nodes[i])
			goto free_and_err_out;
	}
	
	//tm_printf("Initialising array nodes...\n");
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			pipeline->nodes[i][j].active = 0;
			pipeline->nodes[i][j].updated = 0;
			pipeline->nodes[i][j].block = NULL;
		}
	}
	
	pipeline->active_node_array = (tm_pipeline_node**)malloc(height * width * sizeof(tm_pipeline_node*) + 2);
	
	if (!pipeline->active_node_array)
		goto free_and_err_out;
	
	pipeline->n_active_nodes = 2;
	
	pipeline->active_node_array[0] = &pipeline->input_node;
	pipeline->active_node_array[0] = &pipeline->output_node;
	pipeline->n_transformers = 0;
	pipeline->n_active_transformers = 0;
	
	pipeline->width  = width;
	pipeline->height = height;
	
	pipeline->err_flags = PIPELINE_ERR_FLAG_OUTPUT_UNFED | PIPELINE_ERR_FLAG_UNCONFIGURED;
	
	return NO_ERROR;
	
free_and_err_out:
	tm_printf("Pipeline initialisation failed!!\n");
	free_pipeline(pipeline);
	return ERR_ALLOC_FAIL;
}

int init_bypass_pipeline(tm_pipeline *pipeline)
{
	tm_printf("Initialising bypass pipeline...\n");
	if (!pipeline)
		return ERR_NULL_PTR;
	
	init_pipeline(pipeline, 0, 0);
	
	//pipeline_add_transformer(pipeline, alloc_buffer_transformer(INPUT_NODE_COORD, OUTPUT_NODE_COORD));
	
	pipeline->err_flags = PIPELINE_ERR_FLAG_UNCONFIGURED;
	
	return NO_ERROR;
}

int free_pipeline(tm_pipeline *pipeline)
{
	// free and nullify all non-null alloc'd pointers in the pipeline struct, inc. blocks
	return ERR_UNIMPLEMENTED;
}

int pipeline_deactivate_nodes(tm_pipeline *pipeline)
{
	if (!pipeline)
		return ERR_PIPELINE_NULL;
	
	pipeline->n_active_nodes = 0;
	
	for (int i = 0; i < pipeline->width * pipeline->height; i++)
		pipeline->active_node_array[i] = NULL;
	
	for (int i = 0; i < pipeline->width; i++)
	{
		for (int j = 0; j < pipeline->height; j++)
		{
			pipeline->nodes[i][j].active = 0;
			release_block(pipeline->nodes[i][j].block);
			pipeline->nodes[i][j].block = NULL;
		}
	}
	
	return NO_ERROR;
}

int pipeline_reconfigure(tm_pipeline *pipeline)
{
	int ret_val = 0;
	
	if (!pipeline)
		return PIPELINE_ERR_FLAG_NULL_PIPELINE;
	
	tm_printf("Configuring pipeline\n");
	
	/* I will need lots of (possibly big) arrays, but I don't want to blow up the stack.
	 * VLAs are not allowed, so I will need to malloc everything. If one malloc fails,
	 * I need to free all the previous ones. So, forward declare and NULL everything,
	 * and write a "panic, free everything non-null, and return an error" section at
	 * the end of the function (after the usual return; goto'd on malloc fail */
	vec2i 	  *current_stage_nodes 			= NULL;
	uint8_t  **node_fed 					= NULL;
	int   	  *current_stage_transformers 	= NULL;
	uint8_t   *transformer_in_current_stage = NULL;
	uint8_t   *transformer_in_prior_stage 	= NULL;
	
	pipeline_deactivate_nodes(pipeline);
	pipeline->err_flags = 0;
	
	// Add input node to array
	pipeline->n_active_nodes = 1;
	pipeline->active_node_array[0] = &pipeline->input_node;
	
	/* Forward declarations, so as to not cause problems using goto */
	
	vec2i v;
	int done = 0;
	int iterations = 0;
	int compute_order_pos = 0;
	
	int n_current_stage_nodes;
	
	int n_current_stage_transformers;
	int output_fed = 0;
	
	/* If the pipeline has non-positive width or height, there are no nodes to check.
	 * In this case, there need be at most one transformer, with at most one output,
	 * and it must by the output node; otherwise, since transformers necessarily have
	 * outputs, there will be either an output conflict, or an invalid output.
	 * 
	 * For detailed error reporting, I'll manually check whether either of these are
	 * happening.
	 * 
	 * Also, pipeline->width and pipeline->height are signed integers
	 * and I can't be bothered playing compiler whack-a-mole to change
	 * that at this point, so I have to make sure neither are negative
	 * as well.  */
	if (pipeline->width <= 0 || pipeline->height <= 0)
	{
		int output_sources = 0;
		int feeds_output;
		int bad_input;
		for (int i = 0; i < pipeline->n_transformers; i++)
		{
			bad_input  = 0;
			feeds_output = 0;
			if (!pipeline->transformers[i])
			{
				pipeline->err_flags |= PIPELINE_ERR_FLAG_NULL_TRANSFORMER;
				ret_val |= PIPELINE_ERR_FLAG_NULL_TRANSFORMER;
				continue;
			}
			
			for (unsigned int j = 0; j < pipeline->transformers[i]->n_inputs; j++)
			{
				if (pipeline->transformers[i]->inputs[j].x != INPUT_NODE_X
				 || pipeline->transformers[i]->inputs[j].y != INPUT_NODE_Y)
				{
					pipeline->err_flags |= PIPELINE_ERR_FLAG_TRANS_INPUT_BAD_COORD;
					ret_val 			|= PIPELINE_ERR_FLAG_TRANS_INPUT_BAD_COORD;
					bad_input = 1;
				}
			}
			
			for (unsigned int j = 0; j < pipeline->transformers[i]->n_outputs; j++)
			{
				if (pipeline->transformers[i]->outputs[j].x == OUTPUT_NODE_X
				 && pipeline->transformers[i]->outputs[j].y == OUTPUT_NODE_Y)
				{
					output_sources++;
					feeds_output = 1;
				}
				else
				{
					pipeline->err_flags |= PIPELINE_ERR_FLAG_TRANS_OUTPUT_BAD_COORD;
					ret_val 			|= PIPELINE_ERR_FLAG_TRANS_OUTPUT_BAD_COORD;
				}
			}
			
			if (!bad_input && feeds_output && output_sources == 1)
			{
				pipeline->n_active_transformers = 1;
				pipeline->compute_order[0] = i;
			}
		}
		
		switch (output_sources)
		{
			case 0:
				pipeline->err_flags |= PIPELINE_ERR_FLAG_OUTPUT_UNFED;
				ret_val 			|= PIPELINE_ERR_FLAG_OUTPUT_UNFED;
				break;
			
			case 1:
				break;
			
			default:
				pipeline->err_flags |= PIPELINE_ERR_FLAG_TRANS_OUTPUT_BAD_COORD;
				ret_val 			|= PIPELINE_ERR_FLAG_TRANS_OUTPUT_BAD_COORD;
				break;
		}
		
		pipeline->active_node_array[pipeline->n_active_nodes++] = &pipeline->output_node;
		return ret_val;
	}
	
	// Keep an array of nodes acting as inputs at the current propagation step
	current_stage_nodes = (vec2i*)malloc(sizeof(vec2i) * pipeline->width * pipeline->height);
	
	if (!current_stage_nodes)
		goto alloc_fail_panic;
	
	// Prepare the first stage; input flowing from the input node
	n_current_stage_nodes = 1;
	current_stage_nodes[0] = INPUT_NODE_COORD;
	
	/* Keep track of which nodes have already occurred as outputs;
	 * all of a transformers nodesmust be fed for it to be added to
	 * the current stage
	 * node has been used as an output twice, that is a node conflict.
	 * Store as coordinates for convenience */
	node_fed = (uint8_t**)malloc(pipeline->width * sizeof(uint8_t*));
	
	if (!node_fed)
		goto alloc_fail_panic;
	
	for (int x = 0; x < pipeline->width; x++)
		node_fed[x] = NULL;
	
	for (int x = 0; x < pipeline->width; x++)
	{
		node_fed[x] = (uint8_t*)malloc(pipeline->height * sizeof(uint8_t));
		
		if (!node_fed[x])
			goto alloc_fail_panic;
		
		for (int y = 0; y < pipeline->height; y++)
			node_fed[x][y] = 0;
	}
	
	/* Keep an array of transformers taking inputs in the current stage
	 * Store these as array indices (IDs) for convenience */
	current_stage_transformers = (int*)malloc(sizeof(int) * pipeline->n_transformers);
	
	if (!current_stage_transformers)
		goto alloc_fail_panic;
	
	/* Keep an array of whether or not each transformer has been
	 * added to the current stage, to prevent double-adding without
	 * having to go back and check the array */
	transformer_in_current_stage = (uint8_t*)malloc(sizeof(uint8_t) * pipeline->n_transformers);
	
	if (!transformer_in_current_stage)
		goto alloc_fail_panic;
	
	/* Keep track of which transformers have been encountered. If
	 * one appears in two stages, that is a loop! */
	transformer_in_prior_stage = (uint8_t*)malloc(sizeof(uint8_t) * pipeline->n_transformers);
	
	if (!transformer_in_prior_stage)
		goto alloc_fail_panic;
	
	for (int i = 0; i < pipeline->n_transformers; i++)
		transformer_in_prior_stage[i] = 0;
	
	
	while (!done && ++iterations < PIPELINE_RECONFIGURE_MAX_ITERATIONS)
	{
		n_current_stage_transformers = 0;
		
		for (int i = 0; i < pipeline->n_transformers; i++)
			transformer_in_current_stage[i] = 0;
		
		// First, find all transformers getting input from nodes in the current stage
		for (int j = 0; j < n_current_stage_nodes; j++)
		{
			for (int i = 0; i < pipeline->n_transformers; i++)
			{
				if (!pipeline->transformers[i])
				{
					pipeline->err_flags |= PIPELINE_ERR_FLAG_NULL_TRANSFORMER;
					ret_val 			|= PIPELINE_ERR_FLAG_NULL_TRANSFORMER;
					continue;
				}
				
				/* The transformer in question is in the current stage so long as
				 * all of its inputs are already fed, and it is not in a prior stage. */
				 
				 // If we've already added it, skip
				if (transformer_in_current_stage[i])
					continue;
				
				// If it's in a prior stage, skip
				if (transformer_in_prior_stage[i])
					continue;
				
				// Assume all inputs are valid and already fed
				transformer_in_current_stage[i] = 1;
				
				// Try to prove yourself wrong
				for (unsigned int k = 0; k < pipeline->transformers[i]->n_inputs; k++)
				{
					v = pipeline->transformers[i]->inputs[k];
					
					if (0 <= v.x && v.x < pipeline->width && 0 <= v.y && v.y < pipeline->height)
					{
						if (!node_fed[v.x][v.y])
						{
							transformer_in_current_stage[i] = 0;
							break;
						}
					}
					else
					{
						if (!(v.x == INPUT_NODE_X && v.y == INPUT_NODE_Y))
						{
							pipeline->err_flags |= PIPELINE_ERR_FLAG_TRANS_INPUT_BAD_COORD;
							ret_val 			|= PIPELINE_ERR_FLAG_TRANS_INPUT_BAD_COORD;
							
							transformer_in_current_stage[i] = 0;
							break;
						}
					}
				}
				
				// If the assumption wasn't wrong, keep it!
				if (transformer_in_current_stage[i])
					current_stage_transformers[n_current_stage_transformers++] = i;
			}
		}
		
		/* Okay, we've got a list of transformers taking inputs from the current stage.
		 * Should the pipeline be well-formed, these should be able to be computed
		 * independently, with all inputs pre-populated, and outputs flowing to
		 * later stage transformers.
		 * 
		 * Therefore, we can add their IDs to the compute order array, and
		 * log that it has been added */
		
		/* Also, forget the current stage input nodes; form the next stage consisting of
		 * all outputs of the current stage transformers, and record them as fed,
		 * reporting an error if they are already fed */
		
		n_current_stage_nodes = 0;
		
		for (int i = 0; i < n_current_stage_transformers; i++)
		{
			pipeline->compute_order[compute_order_pos++] = current_stage_transformers[i];
			transformer_in_prior_stage[current_stage_transformers[i]] = 1;
			
			for (unsigned int j = 0; j < pipeline->transformers[current_stage_transformers[i]]->n_outputs; j++)
			{
				v = pipeline->transformers[current_stage_transformers[i]]->outputs[j];
				
				if (0 <= v.x && v.x < pipeline->width && 0 <= v.y && v.y < pipeline->height)
				{
					if (node_fed[v.x][v.y])
					{
						pipeline->err_flags |= PIPELINE_ERR_FLAG_NODE_CONFLICT;
						ret_val 			|= PIPELINE_ERR_FLAG_NODE_CONFLICT;
						
						current_stage_nodes[n_current_stage_nodes++] = v;
					}
					else
					{
						pipeline_activate_node(pipeline, v);
						current_stage_nodes[n_current_stage_nodes++] = v;
						pipeline->active_node_array[pipeline->n_active_nodes++] = &pipeline->nodes[v.x][v.y];
						node_fed[v.x][v.y] = 1;
					}
				}
				else
				{
					if (v.x == OUTPUT_NODE_X && v.y == OUTPUT_NODE_Y)
					{
						if (output_fed)
						{
							pipeline->err_flags |= PIPELINE_ERR_FLAG_OUTPUT_CONFLICT;
							ret_val 			|= PIPELINE_ERR_FLAG_OUTPUT_CONFLICT;
							
							// An output conflict is an irrecoverable error. No point wasting CPU cycles continuing
							goto free_and_return;
						}
						else
						{
							output_fed = 1;
						}
					}
					else
					{
						pipeline->err_flags |= PIPELINE_ERR_FLAG_TRANS_OUTPUT_BAD_COORD;
						ret_val 			|= PIPELINE_ERR_FLAG_TRANS_OUTPUT_BAD_COORD;
					}
				}
			}
		}
		
		done = (n_current_stage_nodes == 0);
	}
	
	if (!done)
	{
		pipeline->err_flags |= PIPELINE_ERR_FLAG_RECONF_ITERS_EXCEEDED;
		ret_val 			|= PIPELINE_ERR_FLAG_RECONF_ITERS_EXCEEDED;
	}
	
	pipeline->active_node_array[pipeline->n_active_nodes++] = &pipeline->output_node;
	
	pipeline->n_active_transformers = compute_order_pos;
	
	goto free_and_return;
	
alloc_fail_panic:
	
	pipeline->err_flags |= PIPELINE_ERR_FLAG_UNCONFIGURED;
	ret_val 			|= PIPELINE_ERR_FLAG_ALLOC_FAIL;
	
free_and_return:

	if (current_stage_nodes)
		free(current_stage_nodes);
	
	if (node_fed)
	{
		for (int i = 0; i < pipeline->width; i++)
			if (node_fed[i]) free(node_fed[i]);
		
		free(node_fed);
	}
	
	if (current_stage_transformers)
		free(current_stage_transformers);
	
	if (transformer_in_current_stage)
		free(transformer_in_current_stage);
	
	if (transformer_in_prior_stage)
		free(transformer_in_prior_stage);

	return ret_val;
}

int pipeline_activate_node(tm_pipeline *pipeline, vec2i pos)
{
	if (!pipeline)
		return ERR_PIPELINE_NULL;
	
	if (pos.x < 0 || pos.y < 0 || pos.x >= pipeline->width || pos.y >= pipeline->height)
		return ERR_POSITION_ILLEGAL;
	
	int in_array;
	int index = 0;
	for (; index < pipeline->n_active_nodes; index++)
	{
		if (pipeline->active_node_array[index] == &pipeline->nodes[pos.x][pos.y])
		{
			in_array = 1;
			break;
		}
	}
	
	if (!pipeline->nodes[pos.x][pos.y].block)
	{
		if (!(pipeline->nodes[pos.x][pos.y].block = allocate_block()))
		{
			pipeline->nodes[pos.x][pos.y].active = 0;
			
			/* If a block cannot be allocated, but the node is present in
			 * the active node array, remove it, to prevent disaster */
			if (in_array)
			{
				pipeline->n_active_nodes--;
				for (int j = index; j < pipeline->n_active_nodes; j++)
					pipeline->active_node_array[j] = pipeline->active_node_array[j+1];
			}
			
			return ERR_ALLOC_FAIL;
		}
	}
	
	
	pipeline->nodes[pos.x][pos.y].active = 1;
	
	if (!in_array)
		pipeline->active_node_array[pipeline->n_active_nodes++] = &pipeline->nodes[pos.x][pos.y];
	
	return NO_ERROR;
}

void regenerate_active_node_array(tm_pipeline *pipeline)
{
	if (!pipeline)
		return;
	
	pipeline->n_active_nodes = 0;
	
	for (int x = 0; x < pipeline->width; x++)
	{
		for (int y = 0; y < pipeline->height; y++)
		{
			if (pipeline->nodes[x][y].active)
				pipeline->active_node_array[pipeline->n_active_nodes++] = &pipeline->nodes[x][y];
		}
	}
}

int pipeline_deactivate_node(tm_pipeline *pipeline, vec2i pos)
{
	if (!pipeline)
		return ERR_PIPELINE_NULL;
	
	if ((pos.x == INPUT_NODE_X && pos.y == INPUT_NODE_Y) || (pos.x == OUTPUT_NODE_X && pos.y == OUTPUT_NODE_Y))
		return ERR_NODE_PRIVATE;
	
	if (pos.x < 0 || pos.y < 0 || pos.x >= pipeline->width || pos.y >= pipeline->height)
		return ERR_POSITION_ILLEGAL;
	
	if (pipeline->nodes[pos.x][pos.y].active)
		return NO_ERROR;
	
	pipeline->nodes[pos.x][pos.y].active = 0;
	
	release_block(pipeline->nodes[pos.x][pos.y].block);
	
	int array_index = -1;
	for (int i = 0; i < pipeline->n_active_nodes; i++)
	{
		if (pipeline->active_node_array[i] == &pipeline->nodes[pos.x][pos.y])
		{
			array_index = i;
			break;
		}
	}
	
	if (array_index == -1)
		return NO_ERROR;
	
	pipeline->n_active_nodes--;
	
	for (int i = array_index; i < pipeline->n_active_nodes; i++)
		pipeline->active_node_array[i] = pipeline->active_node_array[i + 1];
	
	return NO_ERROR;
}

int reset_node_status(tm_pipeline *pipeline)
{
	if (!pipeline)
		return ERR_PIPELINE_NULL;
	
	int ret_val = NO_ERROR;
	
	for (int i = 0; i < pipeline->n_active_nodes; i++)
	{
		if (pipeline->active_node_array[i])
		{
			pipeline->active_node_array[i]->updated = 0;
			zero_out_block_float(pipeline->active_node_array[i]->block);
		}
		else
		{
			ret_val = ERR_ARRAY_MALFORMED;
		}
	}
	
	return ret_val;
}


tm_pipeline_node *pipeline_get_node(tm_pipeline *pipeline, vec2i pos)
{
	if (!pipeline)
		return NULL;
	
	if (pos.x == -1 && pos.y == 0)
		return &pipeline->input_node;
	
	if (pos.x == 0 && pos.y == -1)
		return &pipeline->output_node;
	
	if (pos.x < 0 || pos.y < 0 || pos.x >= pipeline->width || pos.y >= pipeline->height)
		return NULL;
	
	if (!pipeline->nodes[pos.x][pos.y].active)
		return NULL;
	
	return &pipeline->nodes[pos.x][pos.y];
}

int pipeline_add_transformer(tm_pipeline *pipeline, tm_transformer *trans)
{
	if (!pipeline || !trans)
		return -ERR_NULL_PTR;
	
	if (pipeline->n_transformers >= MAX_PIPELINE_TRANSFORMERS)
		return -ERR_PIPELINE_FULL;
	
	pipeline->transformers[pipeline->n_transformers++] = trans;
	
	pipeline->err_flags |= PIPELINE_ERR_FLAG_UNCONFIGURED;
	
	return pipeline->n_transformers - 1;
}

int write_node(tm_pipeline_node *node, float *data)
{
	if (!node || !data)
		return ERR_NULL_PTR;
	
	if (!node->block)
		return ERR_NULL_PTR;
	
	memcpy(node->block->data, data, sizeof(float) * AUDIO_BLOCK_SAMPLES);
	
	node->updated = 1;
	
	return NO_ERROR;
}

int compute_pipeline(tm_pipeline *pipeline, int16_t *input)
{
	if (!pipeline || !input)
		return ERR_NULL_PTR;
	
	// If the pipeline is busted, just bypass, and report
	if (pipeline->err_flags & PIPELINE_ERR_FLAG_NODE_CONFLICT
	 || pipeline->err_flags & PIPELINE_ERR_FLAG_OUTPUT_UNFED
	 || pipeline->err_flags & PIPELINE_ERR_FLAG_RECONF_ITERS_EXCEEDED
	 || pipeline->err_flags & PIPELINE_ERR_FLAG_UNCONFIGURED)
	{
		//tm_printf("pipeline is bungled; bypass\n", pipeline->output_node.block->data);
		convert_block_int_to_float(pipeline->output_node.block->data, input);
		return ERR_PIPELINE_BUSTED;
	}
	else
	{
		reset_node_status(pipeline);
		convert_block_int_to_float(pipeline->input_node.block->data, input);
		
		for (int i = 0; i < pipeline->n_active_transformers; i++)
			propagate_transformer(pipeline, pipeline->transformers[pipeline->compute_order[i]]);
	}
	
	return NO_ERROR;
}

/*
int pipeline_add_transformer_by_type(tm_pipeline *pipeline, uint16_t type)
{
	if (!pipeline)
		return -ERR_NULL_PTR;
	
	tm_transformer *trans = (tm_transformer*)malloc(sizeof(tm_transformer));
	
	if (!trans)
		return ERR_ALLOC_FAIL;
	
	int ret_val = init_transformer_default(trans, type);
	
	if (ret_val != NO_ERROR)
		return -ret_val;
	
	return pipeline_add_transformer(pipeline, trans);
}
*/

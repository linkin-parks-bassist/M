#include <Arduino.h>
#include "M.h"

int nullify_pipeline(m_pipeline *pipeline)
{
	if (!pipeline) return ERR_NULL_PTR;
	
	pipeline->input_node.block   = NULL;
	pipeline->output_node.block  = NULL;
	
	pipeline->nodes = NULL;
	
	pipeline->active_node_array = NULL;
	
	pipeline->n_active_nodes = 0;
	pipeline->n_transformers = 0;
	
	pipeline->width  = 0;
	pipeline->height = 0;
	
	for (int i = 0; i < MAX_PIPELINE_TRANSFORMERS; i++)
		pipeline->transformers[i] = NULL;
	
	return NO_ERROR;
}

int init_pipeline(m_pipeline *pipeline, int width, int height)
{
	if (!pipeline) return ERR_NULL_PTR;
	
	//m_printf("Initialising pipeline...\n");
	
	//m_printf("Allocating input block...\n");
	pipeline->input_node.block   = allocate_block();
	pipeline->input_node.active  = 1;
	
	//m_printf("Allocating output block...\n");
	pipeline->output_node.block  = allocate_block();
	pipeline->output_node.active = 1;
	
	//m_printf("Allocating node array...\n");
	pipeline->nodes = (m_pipeline_node**)malloc(width * sizeof(m_pipeline_node*));
	
	if (!pipeline->nodes)
		return ERR_ALLOC_FAIL;
	
	for (int i = 0; i < width; i++)
	{
		pipeline->nodes[i] = (m_pipeline_node*)malloc(height * sizeof(m_pipeline_node));
			
		if (!pipeline->nodes[i])
			return ERR_ALLOC_FAIL;
	}
	
	//m_printf("Initialising array nodes...\n");
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			pipeline->nodes[i][j].active = 0;
			pipeline->nodes[i][j].updated = 0;
			pipeline->nodes[i][j].block = NULL;
		}
	}
	
	pipeline->active_node_array = (m_pipeline_node**)malloc(height * width * sizeof(m_pipeline_node*));
	
	pipeline->n_active_nodes = 0;
	pipeline->n_transformers = 0;
	
	pipeline->width  = width;
	pipeline->height = height;
	
	//m_printf("Done.\n");
	
	return NO_ERROR;
}

int init_bypass_pipeline(m_pipeline *pipeline)
{
	if (!pipeline) return ERR_NULL_PTR;
	
	init_pipeline(pipeline, 0, 0);
	
	pipeline_add_transformer(pipeline, alloc_buffer_transformer(INPUT_NODE_COORD, OUTPUT_NODE_COORD));
	
	return NO_ERROR;
}

int free_pipeline(m_pipeline *pipeline)
{
	return ERR_UNIMPLEMENTED;
}

// Swap sort. I'm not expecting a large number of nodes, or frequent sorting.
// Maybe implement a better algorithm if I can be bothered.
void sort_transformer_array(m_pipeline *pipeline)
{
	if (!pipeline)
		return;
	
	m_pipeline_node *temp;
	int unsorted;
	
	int max_input_col_coords[pipeline->n_transformers];
	int itemp;
	
	for (int i = 0; i < pipeline->n_transformers; i++)
	{
		max_input_col_coords[i] = 0;
		
		for (unsigned int j = 0; j < pipeline->transformers[i]->n_inputs; j++)
		{
			if (pipeline->transformers[i]->inputs[j].x > max_input_col_coords[i])
				max_input_col_coords[i] = pipeline->transformers[i]->inputs[j].x;
		}
	}
	
	do
	{
		unsorted = 0;
		for (int i = 0; i < pipeline->n_transformers - 1; i++)
		{
			if (max_input_col_coords[i] > max_input_col_coords[i+1])
			{
				unsorted = 1;
				
				temp = pipeline->nodes[i];
				pipeline->nodes[i] = pipeline->nodes[i + 1];
				pipeline->nodes[i + 1] = temp;
				
				
				itemp = max_input_col_coords[i];
				max_input_col_coords[i] = max_input_col_coords[i + 1];
				max_input_col_coords[i + 1] = itemp;
			}
		}
	} while (unsorted);
}

int pipeline_activate_node(m_pipeline *pipeline, int x, int y)
{
	if (!pipeline)
		return ERR_PIPELINE_NULL;
	
	if (x < 0 || y < 0 || x >= pipeline->width || y >= pipeline->height)
		return ERR_POSITION_ILLEGAL;
	
	//m_printf("Activating node (%d, %d)...\n", x, y);
	
	if (!(pipeline->nodes[x][y].block = allocate_block()))
	{
		//m_printf("Block allocation failed !\n");
		pipeline->nodes[x][y].active = 0;
		return ERR_ALLOC_FAIL;
	}
	
	//m_printf("node block ptr: 0x%x, data: 0x%x\n", pipeline->nodes[x][y].block, pipeline->nodes[x][y].block->data);
	
	pipeline->nodes[x][y].active = 1;
	
	pipeline->active_node_array[pipeline->n_active_nodes++] = &pipeline->nodes[x][y];
	
	return NO_ERROR;
}

void regenerate_active_node_array(m_pipeline *pipeline)
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

int pipeline_deactivate_node(m_pipeline *pipeline, int x, int y)
{
	if (!pipeline)
		return ERR_PIPELINE_NULL;
	
	if (x < 0 || y < 0 || x >= pipeline->width || y >= pipeline->height)
		return ERR_POSITION_ILLEGAL;
	
	if (pipeline->nodes[x][y].active)
		return NO_ERROR;
	
	pipeline->nodes[x][y].active = 1;
	
	release_block(pipeline->nodes[x][y].block);
	
	int array_index = -1;
	for (int i = 0; i < pipeline->n_active_nodes; i++)
	{
		if (pipeline->active_node_array[i] == &pipeline->nodes[x][y])
		{
			array_index = i;
			break;
		}
	}
	
	if (array_index == -1)
		return ERR_ARRAY_MALFORMED;
	
	pipeline->n_active_nodes--;
	
	for (int i = array_index; i < pipeline->n_active_nodes; i++)
		pipeline->active_node_array[i] = pipeline->active_node_array[i + 1];
	
	return NO_ERROR;
}

int reset_node_status(m_pipeline *pipeline)
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


m_pipeline_node *pipeline_get_node(m_pipeline *pipeline, vec2i pos)
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

int pipeline_add_transformer(m_pipeline *pipeline, m_audio_transformer *trans)
{
	if (!pipeline || !trans)
		return ERR_NULL_PTR;
	
	if (pipeline->n_transformers >= MAX_PIPELINE_TRANSFORMERS)
		return ERR_PIPELINE_FULL;
	
	pipeline->transformers[pipeline->n_transformers++] = trans;
	
	return NO_ERROR;
}

int write_node(m_pipeline_node *node, float *data)
{
	if (!node || !data)
		return ERR_NULL_PTR;
	
	if (!node->block)
		return ERR_NULL_PTR;
	
	memcpy(node->block->data, data, sizeof(float) * AUDIO_BLOCK_SAMPLES);
	
	node->updated = 1;
	
	return NO_ERROR;
}

int compute_pipeline(m_pipeline *pipeline, int16_t *input)
{
	//m_printf("Computing pipeline 0x%x on input data 0x%x...\n", pipeline, input);
	
	if (!pipeline || !input)
	{
		//m_printf("NULL pointer error !\n");
		return ERR_NULL_PTR;
	}
	
	//m_printf("Resetting active nodes...\n");
	reset_node_status(pipeline);
	
	////m_printf("Copying input data...\n");
	convert_block_int_to_float(pipeline->input_node.block->data, input);
	
	for (int i = 0; i < pipeline->n_transformers; i++)
	{
		//m_printf("Propagate transformer %d...\n", i);
		propagate_transformer(pipeline, pipeline->transformers[i]);
		//m_printf("Done.\n");
	}
	
	//m_printf("Pipeline computation complete\n");
	return NO_ERROR;
}

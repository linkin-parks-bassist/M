#include "tm.h"

static const char *FNAME = "tm_pipe_line.c";
int init_pipe_line(tm_pipe_line *pipeline)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	pipeline->n_transformers = 0;
	pipeline->transformer_array_length = INITIAL_TRANSFORMER_ARRAY_LENGTH;
	pipeline->transformers = (tm_transformer**)malloc(sizeof(tm_transformer*) * pipeline->transformer_array_length);
	
	for (int i = 0; i < pipeline->transformer_array_length; i++)
		pipeline->transformers[i] = NULL;
	
	pipeline->next_id = 0;
	pipeline->transition_policy = TRANSITION_MONOBLOCK_COS2;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int compute_pipe_line(tm_pipe_line *pipeline, float *dest, float *src)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	src  = src  ? src  : zero_buffer;
	dest = dest ? dest : sink_buffer;
	
	float *in_buffer = src;
	float *out_buffer;
	float *buffer_1 = NULL;
	float *buffer_2 = NULL;
	float *tmp;
	
	int ret_val = NO_ERROR;
	int busted_pipeline = 0;
	int n = pipeline->n_transformers;
	
	if (n <= 0)
	{
		if (dest)
			memcpy(dest, src, sizeof(float) * AUDIO_BLOCK_SAMPLES);
		RETURN_ERR_CODE(NO_ERROR);
	}
	
	if (n == 2)
	{
		buffer_1 = allocate_buffer();
		if (!buffer_1)
		{
			ret_val = ERR_ALLOC_FAIL;
			goto panic_bypass;
		}
	}
	if (n >= 3)
	{
		buffer_1 = allocate_buffer();
		if (!buffer_1)
		{
			ret_val = ERR_ALLOC_FAIL;
			goto panic_bypass;
		}
		
		buffer_2 = allocate_buffer();
		if (!buffer_2)
		{
			release_buffer(buffer_1);
			ret_val = ERR_ALLOC_FAIL;
			goto panic_bypass;
		}
	}
	
	out_buffer = (n == 1) ? dest : buffer_1;
	
	for (int i = 0; i < pipeline->n_transformers; i++)
	{
		if (i == n - 1)
			out_buffer = dest;
		
		ret_val = ERR_NULL_PTR;
		
		if (pipeline->transformers[i])
			ret_val = run_transformer(pipeline->transformers[i], out_buffer, in_buffer);
		
		// If there is a succesful computation, swap the buffers.
		// If not, keep everything as is; the same buffer will be 
		// input for the next step, effectively bypassing the 
		// broken step
		if (ret_val == NO_ERROR)
		{
			// If this is the first sucessful computation,
			// set in_buffer = out_buffer, out_buffer = buffer_2
			tmp 		= out_buffer;
			out_buffer	= (in_buffer == src) ? buffer_2 : in_buffer;
			in_buffer 	= tmp;
		}
		else
		{
			busted_pipeline = 1;
			// If it fails on the last step, we have to copy the data directly to the output
			if (i == n - 1)
				memcpy(dest, in_buffer, sizeof(float) * AUDIO_BLOCK_SAMPLES);
		}
	}
	
	if (buffer_1)
		release_buffer(buffer_1);
	if (buffer_2)
		release_buffer(buffer_2);
	
	RETURN_ERR_CODE(busted_pipeline ? ERR_PIPELINE_BUSTED : NO_ERROR);

panic_bypass:
	
	memcpy(dest, src, sizeof(float) * AUDIO_BLOCK_SAMPLES);
	
	RETURN_ERR_CODE(ret_val);
}

#define TRANSFORMERS_MALLOC_CHUNK_SIZE 8

int pipe_line_expand_transformer_array(tm_pipe_line *pipeline)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	int try_size = PROFILES_MALLOC_CHUNK_SIZE;
	tm_transformer **new_ptr = NULL;
	
	do
	{
		new_ptr = (tm_transformer**)malloc(sizeof(tm_transformer*) * (pipeline->transformer_array_length + try_size));
		if (!new_ptr)
			try_size /= 2;
	} while (!new_ptr && try_size);
	
	if (!new_ptr)
	{
		RETURN_NEG_ERR_CODE(ERR_ALLOC_FAIL);
	}
	
	tm_disable_software_interrupts();
	
	memcpy(new_ptr, pipeline->transformers, sizeof(tm_transformer*) * (pipeline->transformer_array_length));
	free(pipeline->transformers);
	pipeline->transformers = new_ptr;
	pipeline->transformer_array_length += try_size;
	
	for (int i = pipeline->n_transformers; i < pipeline->transformer_array_length; i++)
		pipeline->transformers[i] = NULL;
	
	tm_enable_software_interrupts();
	
	RETURN_ERR_CODE(NO_ERROR);
}

int pipe_line_expand_transformer_array_to(tm_pipe_line *pipeline, int n)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	int try_size = binary_max(n - pipeline->transformer_array_length, 0);
	
	if (try_size == 0)
	{
		RETURN_ERR_CODE(NO_ERROR);
	}
	
	if (try_size < TRANSFORMERS_MALLOC_CHUNK_SIZE)
		try_size = TRANSFORMERS_MALLOC_CHUNK_SIZE;
	
	tm_transformer **new_ptr = NULL;
	
	do
	{
		new_ptr = (tm_transformer**)malloc(sizeof(tm_transformer*) * (pipeline->transformer_array_length + try_size));
		if (!new_ptr)
			try_size /= 2;
	} while (!new_ptr && try_size >= binary_max(n - pipeline->transformer_array_length, 0));
	
	if (!new_ptr)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}
	
	tm_disable_software_interrupts();
	
	memcpy(new_ptr, pipeline->transformers, sizeof(tm_transformer*) * (pipeline->transformer_array_length));
	free(pipeline->transformers);
	pipeline->transformers = new_ptr;
	pipeline->transformer_array_length += try_size;
	
	for (int i = pipeline->n_transformers; i < pipeline->transformer_array_length; i++)
		pipeline->transformers[i] = NULL;
	
	tm_enable_software_interrupts();
	
	RETURN_ERR_CODE(NO_ERROR);
}

int pipeline_update_transition_policy(tm_pipe_line *pipeline)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	int tp = 0;
	
	for (int i = 0; i < pipeline->n_transformers; i++)
	{
		if (!pipeline->transformers[i])
			continue;
		
		if (pipeline->transformers[i]->transition_policy > tp)
			tp = pipeline->transformers[i]->transition_policy;
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

int pipe_line_print_transformer_array(tm_pipe_line *pipeline)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	tm_printf("Printing transformer array. n_transformers = %d\n", pipeline->n_transformers);
	
	for (int i = 0; i < pipeline->n_transformers; i++)
		tm_printf("transformer %d: type %d, id %d\n", i, pipeline->transformers[i]->type, pipeline->transformers[i]->id);
	
	tm_printf("Done.\n");
	
	RETURN_ERR_CODE(NO_ERROR);
}

int pipe_line_append_transformer(tm_pipe_line *pipeline, tm_transformer *trans)
{
	FUNCTION_START();

	if (!pipeline || !trans)
	{
		RETURN_NEG_ERR_CODE(-ERR_NULL_PTR);
	}
	
	int ret_val = NO_ERROR;
	
	if (pipeline->n_transformers == pipeline->transformer_array_length)
	{
		ret_val = pipe_line_expand_transformer_array(pipeline);
		
		if (ret_val != NO_ERROR)
		{
			RETURN_NEG_ERR_CODE(ret_val);
		}
	}
	
	trans->id = pipeline->next_id++;
	
	tm_disable_software_interrupts();
	pipeline->transformers[pipeline->n_transformers++] = trans;
	tm_enable_software_interrupts();
	
	pipeline_update_transition_policy(pipeline);
	
	RETURN_INT(trans->id);
}


int pipe_line_remove_transformer(tm_pipe_line *pipeline, uint16_t tid)
{
	FUNCTION_START();

	tm_printf("pipe_line_remove_transformer. pipeline = %p, tid = %d\n", pipeline, tid);
	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	tm_printf("pipeline->n_transformers = %d, pipeline->transformers = %p\n", pipeline->n_transformers, pipeline->transformers);
	
	if (pipeline->transformers)
	{
		for (int j = 0; j < pipeline->n_transformers; j++)
			tm_printf("pipeline->transformers[%d] = %p,\n", pipeline->transformers[j]);
	}
	
	for (int i = 0; i < pipeline->n_transformers; i++)
	{
		tm_printf("iteration %d. pipeline->transformers[%d] = %p, pipeline->transformers[%d]->id = %d\n", i, i,
			pipeline->transformers[i], i, (pipeline->transformers[i] ? pipeline->transformers[i]->id : -420232012));
		if (pipeline->transformers[i] && pipeline->transformers[i]->id == tid)
		{
			tm_printf("this is the one! freeing it...\n");
			free_transformer(pipeline->transformers[i]);
			pipeline->transformers[i] = NULL;
			tm_printf("freed!\n");
			pipeline->n_transformers--;
			
			for (int j = i; j < pipeline->n_transformers; j++)
				pipeline->transformers[j] = pipeline->transformers[j + 1];
			
			tm_printf("Transformer array now: \n");
			
			for (int j = 0; j < pipeline->n_transformers; j++)
				tm_printf("pipeline->transformers[%d] = %p,\n", pipeline->transformers[j]);
			
			RETURN_ERR_CODE(NO_ERROR);
		}
	}
	
	RETURN_ERR_CODE(ERR_INVALID_TRANSFORMER_ID);
}

int pipe_line_insert_transformer(tm_pipe_line *pipeline, tm_transformer *trans, int pos)
{
	FUNCTION_START();

	if (!pipeline || !trans)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	int ret_val = NO_ERROR;
	
	if (pipeline->n_transformers == pipeline->transformer_array_length)
	{
		ret_val = pipe_line_expand_transformer_array(pipeline);
		
		if (ret_val != NO_ERROR)
		{
			RETURN_NEG_ERR_CODE(ret_val);
		}
	}
	
	trans->id = pipeline->next_id++;
	
	tm_disable_software_interrupts();
	for (int i = pipeline->n_transformers; i > pos && i > 0; i--)
		pipeline->transformers[i + 1] = pipeline->transformers[i];
	
	pipeline->transformers[pos] = trans;
	tm_enable_software_interrupts();
	
	RETURN_INT(trans->id);
}

int pipe_line_prepend_transformer(tm_pipe_line *pipeline, tm_transformer *trans)
{
	FUNCTION_START();

	int ret_val = pipe_line_insert_transformer(pipeline, trans, 0);

	if (ret_val < 0)
	{
		RETURN_ERR_CODE(-ret_val);
	}
	
	RETURN_INT(ret_val);
}

int pipe_line_append_transformer_type(tm_pipe_line *pipeline, uint16_t type)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	tm_transformer *trans = (tm_transformer*)malloc(sizeof(tm_transformer));
	
	if (!trans)
	{
		RETURN_NEG_ERR_CODE(ERR_ALLOC_FAIL);
	}

	int ret_val = init_transformer(trans, type);
	
	if (ret_val != NO_ERROR)
	{
		free(trans);
		RETURN_NEG_ERR_CODE(ret_val);
	}
	
	ret_val = pipe_line_append_transformer(pipeline, trans);

	if (ret_val < 0)
	{
		RETURN_ERR_CODE(-ret_val);
	}
	
	RETURN_INT(ret_val);
}

int pipe_line_insert_transformer_type(tm_pipe_line *pipeline, uint16_t type, uint16_t pos)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	tm_transformer *trans = (tm_transformer*)malloc(sizeof(tm_transformer));
	
	if (!trans)
	{
		RETURN_NEG_ERR_CODE(ERR_ALLOC_FAIL);
	}
	
	int ret_val = init_transformer(trans, type);
	
	if (ret_val != NO_ERROR)
	{
		free(trans);
		RETURN_NEG_ERR_CODE(ret_val);
	}
	
	ret_val = pipe_line_insert_transformer(pipeline, trans, pos);
	
	if (ret_val < 0)
	{
		RETURN_ERR_CODE(-ret_val);
	}
	
	RETURN_INT(ret_val);
}

int pipe_line_prepend_transformer_type(tm_pipe_line *pipeline, uint16_t type)
{
	FUNCTION_START();

	int ret_val = pipe_line_insert_transformer_type(pipeline, type, 0);
	
	if (ret_val < 0)
	{
		RETURN_ERR_CODE(-ret_val);
	}
	
	RETURN_INT(ret_val);
}

int pipe_line_get_transformer_position(tm_pipe_line *pipeline, uint16_t id)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	for (int i = 0; i < pipeline->n_transformers; i++)
	{
		if (pipeline->transformers[i]->id == id)
		{
			RETURN_INT(i);
		}
	}
	
	RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
}

int pipe_line_move_transformer(tm_pipe_line *pipeline, uint16_t id, int new_pos)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
		
	int old_pos = pipe_line_get_transformer_position(pipeline, id);
	
	if (old_pos < 0)
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	tm_printf("Moving transformer %d from position %d to position %d. The array currently:\n", id, old_pos, new_pos);
	
	pipe_line_print_transformer_array(pipeline);
	
	if (old_pos == new_pos)
	{
		RETURN_ERR_CODE(NO_ERROR);
	}
	
	if (new_pos < 0 || new_pos >= pipeline->n_transformers)
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	tm_transformer *trans = pipeline->transformers[old_pos];
	
	// Moving forward
	if (new_pos < old_pos)
	{	
		for (int i = old_pos; i > new_pos; i--)
			pipeline->transformers[i] = pipeline->transformers[i - 1];
	}
	else // Moving backwards
	{
		for (int i = old_pos; i < new_pos; i++)
			pipeline->transformers[i] = pipeline->transformers[i + 1];
	}
	
	pipeline->transformers[new_pos] = trans;
	
	tm_printf("And after the move:\n");
	pipe_line_print_transformer_array(pipeline);
	
	RETURN_ERR_CODE(NO_ERROR);
}

tm_transformer *pipe_line_get_transformer_by_id(tm_pipe_line *pipeline, uint16_t id)
{
	if (!pipeline)
	{
		RETURN_PTR(NULL);
	}
	
	if (!pipeline->transformers)
	{
		RETURN_PTR(NULL);
	}
	
	for (int i = 0; i < pipeline->n_transformers; i++)
	{
		if (pipeline->transformers[i] && pipeline->transformers[i]->id == id)
		{
			return pipeline->transformers[i];
		}
	}
	
	RETURN_PTR(NULL);
}

int pipe_line_swap_transformers(tm_pipe_line *pipeline, uint16_t id1, uint16_t id2)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	int index1 = -1;
	int index2 = -1;
	
	for (int i = 0; i < pipeline->n_transformers && (index1 == -1 || index2 == -1); i++)
	{
		// Should never happen lol
		if (!pipeline->transformers[i])
			continue;
		
		if (pipeline->transformers[i]->id == id1)
			index1 = i;
		if (pipeline->transformers[i]->id == id2)
			index2 = i;
	}
	
	if (index1 == -1 || index2 == -1)
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	tm_disable_software_interrupts();
	
	tm_transformer *tmp = pipeline->transformers[index1];
	pipeline->transformers[index1] = pipeline->transformers[index2];
	pipeline->transformers[index2] = tmp;
	
	tm_enable_software_interrupts();
	
	RETURN_ERR_CODE(NO_ERROR);
}

int pipe_line_valid(tm_pipe_line *pipeline)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_INT(0);
	}
	
	RETURN_INT(1);
}

int pipe_line_compare(tm_pipe_line *pipeline_a, tm_pipe_line *pipeline_b)
{
	FUNCTION_START();

	if (!pipeline_a || !pipeline_b)
	{
		RETURN_INT(1);
	}
	
	if (pipeline_a->n_transformers != pipeline_b->n_transformers)
	{
		RETURN_INT(1);
	}
	
	if ((!!pipeline_a->transformers) != (!!pipeline_b->transformers))
	{
		if (!pipeline_b->transformers)
		{
			RETURN_INT(1);
		}
	}
	
	if (pipeline_a->next_id != pipeline_b->next_id)
	{
		RETURN_INT(1);
	}
	
	if (pipeline_a->transformers && pipeline_b->transformers)
	{
		for (int i = 0; i < pipeline_a->n_transformers; i++)
		{
			if ((!!pipeline_a->transformers[i]) != (!!pipeline_b->transformers[i]))
			{
				RETURN_INT(1);
			}
			
			if (pipeline_a->transformers[i] && pipeline_b->transformers[i])
			{
				if (pipeline_a->transformers[i]->type != pipeline_b->transformers[i]->type)
				{
					RETURN_INT(1);
				}
				
				if (pipeline_a->transformers[i]->id != pipeline_b->transformers[i]->id)
				{
					RETURN_INT(1);
				}
				
				if (pipeline_a->transformers[i]->compute_transformer != pipeline_b->transformers[i]->compute_transformer)
				{
					RETURN_INT(1);
				}
				
				if (pipeline_a->transformers[i]->compute_transformer_nl != pipeline_b->transformers[i]->compute_transformer_nl)
				{
					RETURN_INT(1);
				}
			}
		}
	}
	
	RETURN_INT(0);
}

int gut_pipe_line(tm_pipe_line *pipeline)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (pipeline->transformers)
	{
		for (int i = 0; i < pipeline->transformer_array_length; i++)
		{
			if (pipeline->transformers[i])
			{
				free_transformer(pipeline->transformers[i]);
				pipeline->transformers[i] = NULL;
			}
		}
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

int clone_pipe_line(tm_pipe_line **dest_ptr, tm_pipe_line *src)
{
	FUNCTION_START();

	if (!dest_ptr)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (!src)
	{
		*dest_ptr = NULL;
		RETURN_ERR_CODE(NO_ERROR);
	}
	
	tm_pipe_line *dest = *dest_ptr;
	
	if (!dest)
	{
		dest = (tm_pipe_line*)malloc(sizeof(tm_pipe_line));
		
		if (!dest)
		{
			*dest_ptr = NULL;
			RETURN_ERR_CODE(ERR_ALLOC_FAIL);
		}
		
		*dest_ptr = dest;
		
		init_pipe_line(dest);
	}
	else
	{
		gut_pipe_line(dest);
	}
	
	dest->next_id = src->next_id;
	dest->transition_policy = src->transition_policy;
	
	int ret_val = NO_ERROR;
	
	if (!dest->transformers || dest->transformer_array_length < src->n_transformers)
	{
		ret_val = pipe_line_expand_transformer_array_to(dest, src->n_transformers);
		
		if (ret_val != NO_ERROR)
		{
			RETURN_ERR_CODE(ret_val);
		}
	}
	
	for (int i = 0; i < src->n_transformers; i++)
	{
		ret_val = pipe_line_clone_transformer_into_position(dest, src->transformers[i], i);
		
		if (ret_val != NO_ERROR)
		{
			RETURN_ERR_CODE(ret_val);
		}
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

int pipe_line_clone_transformer_into_position(tm_pipe_line *pipeline, tm_transformer *trans, int pos)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (pos < 0)
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	if (!trans)
	{
		pipeline->transformers[pos] = NULL;
		RETURN_ERR_CODE(NO_ERROR);
	}
	
	int ret_val;
	
	if (!pipeline->transformers || pipeline->transformer_array_length < pos + 1)
	{
		ret_val = pipe_line_expand_transformer_array_to(pipeline, pos + 1);
		if (ret_val != NO_ERROR)
		{
			RETURN_ERR_CODE(ret_val);
		}
	}
	else
	{
		if (pipeline->transformers[pos])
		{
			free_transformer(pipeline->transformers[pos]);
			pipeline->transformers[pos] = NULL;
		}
	}
	
	ret_val = clone_transformer(&pipeline->transformers[pos], trans);
	
	if (ret_val == NO_ERROR)
		pipeline->n_transformers = binary_max(pos + 1, pipeline->n_transformers);
	
	RETURN_ERR_CODE(ret_val);
}

int pipe_line_change_transformer_setting(tm_pipe_line *pipeline, uint16_t tid, uint16_t sid, int new_val)
{
	FUNCTION_START();

	RETURN_ERR_CODE(NO_ERROR);
}

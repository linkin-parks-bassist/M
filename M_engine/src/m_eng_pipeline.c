#include "m_eng.h"

static const char *FNAME = "m_eng_pipeline.c";
int init_pipeline(m_pipeline *pipeline)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	pipeline->n_transformers = 0;
	pipeline->transformer_array_length = INITIAL_TRANSFORMER_ARRAY_LENGTH;
	pipeline->transformers = (m_transformer**)malloc(sizeof(m_transformer*) * pipeline->transformer_array_length);
	
	for (int i = 0; i < pipeline->transformer_array_length; i++)
		pipeline->transformers[i] = NULL;
	
	pipeline->next_id = 0;
	pipeline->transition_policy = TRANSITION_MONOBLOCK_COS2;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int compute_pipeline(m_pipeline *pipeline, float *dest, float *src)
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

int pipeline_expand_transformer_array(m_pipeline *pipeline)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	int try_size = PROFILES_MALLOC_CHUNK_SIZE;
	m_transformer **new_ptr = NULL;
	
	do
	{
		new_ptr = (m_transformer**)malloc(sizeof(m_transformer*) * (pipeline->transformer_array_length + try_size));
		if (!new_ptr)
			try_size /= 2;
	} while (!new_ptr && try_size);
	
	if (!new_ptr)
	{
		RETURN_NEG_ERR_CODE(ERR_ALLOC_FAIL);
	}
	
	m_eng_disable_software_interrupts();
	
	memcpy(new_ptr, pipeline->transformers, sizeof(m_transformer*) * (pipeline->transformer_array_length));
	free(pipeline->transformers);
	pipeline->transformers = new_ptr;
	pipeline->transformer_array_length += try_size;
	
	for (int i = pipeline->n_transformers; i < pipeline->transformer_array_length; i++)
		pipeline->transformers[i] = NULL;
	
	m_eng_enable_software_interrupts();
	
	RETURN_ERR_CODE(NO_ERROR);
}

int pipeline_expand_transformer_array_to(m_pipeline *pipeline, int n)
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
	
	m_transformer **new_ptr = NULL;
	
	do
	{
		new_ptr = (m_transformer**)malloc(sizeof(m_transformer*) * (pipeline->transformer_array_length + try_size));
		if (!new_ptr)
			try_size /= 2;
	} while (!new_ptr && try_size >= binary_max(n - pipeline->transformer_array_length, 0));
	
	if (!new_ptr)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}
	
	m_eng_disable_software_interrupts();
	
	memcpy(new_ptr, pipeline->transformers, sizeof(m_transformer*) * (pipeline->transformer_array_length));
	free(pipeline->transformers);
	pipeline->transformers = new_ptr;
	pipeline->transformer_array_length += try_size;
	
	for (int i = pipeline->n_transformers; i < pipeline->transformer_array_length; i++)
		pipeline->transformers[i] = NULL;
	
	m_eng_enable_software_interrupts();
	
	RETURN_ERR_CODE(NO_ERROR);
}

int pipeline_update_transition_policy(m_pipeline *pipeline)
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

int pipeline_print_transformer_array(m_pipeline *pipeline)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_printf("Printing transformer array. n_transformers = %d\n", pipeline->n_transformers);
	
	for (int i = 0; i < pipeline->n_transformers; i++)
	{
		if (pipeline->transformers[i])
		{
			m_printf("transformer %d: type %d, id %d\n", i, pipeline->transformers[i]->type, pipeline->transformers[i]->id);
		}
		else
		{
			m_printf("transformer %d: NULL!!!\n", i);
		}
	}
	
	m_printf("Done.\n");
	
	RETURN_ERR_CODE(NO_ERROR);
}

int pipeline_append_transformer(m_pipeline *pipeline, m_transformer *trans)
{
	FUNCTION_START();

	if (!pipeline || !trans)
	{
		RETURN_NEG_ERR_CODE(-ERR_NULL_PTR);
	}
	
	int ret_val = NO_ERROR;
	
	if (pipeline->n_transformers == pipeline->transformer_array_length)
	{
		ret_val = pipeline_expand_transformer_array(pipeline);
		
		if (ret_val != NO_ERROR)
		{
			RETURN_NEG_ERR_CODE(ret_val);
		}
	}
	
	trans->id = pipeline->next_id++;
	
	m_eng_disable_software_interrupts();
	pipeline->transformers[pipeline->n_transformers++] = trans;
	m_eng_enable_software_interrupts();
	
	pipeline_update_transition_policy(pipeline);
	
	RETURN_INT(trans->id);
}


int pipeline_remove_transformer(m_pipeline *pipeline, uint16_t tid)
{
	FUNCTION_START();

	m_printf("pipeline_remove_transformer. pipeline = %p, tid = %d\n", pipeline, tid);
	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_printf("pipeline->n_transformers = %d, pipeline->transformers = %p\n", pipeline->n_transformers, pipeline->transformers);
	
	int j;
	
	if (pipeline->transformers)
	{
		for (j = 0; j < pipeline->n_transformers; j++)
			m_printf("pipeline->transformers[%d] = %p,\n", pipeline->transformers[j]);
	}
	
	for (int i = 0; i < pipeline->n_transformers; i++)
	{
		m_printf("iteration %d. pipeline->transformers[%d] = %p, pipeline->transformers[%d]->id = %d\n", i, i,
			pipeline->transformers[i], i, (pipeline->transformers[i] ? pipeline->transformers[i]->id : -420232012));
		if (pipeline->transformers[i] && pipeline->transformers[i]->id == tid)
		{
			m_printf("this is the one! freeing it...\n");
			free_transformer(pipeline->transformers[i]);
			pipeline->transformers[i] = NULL;
			m_printf("freed!\n");
			pipeline->n_transformers--;
			
			for (j = i; j < pipeline->n_transformers; j++)
				pipeline->transformers[j] = pipeline->transformers[j + 1];
			
			pipeline->transformers[j] = NULL;
			
			m_printf("Transformer array now: \n");
			
			for (int j = 0; j < pipeline->n_transformers; j++)
				m_printf("pipeline->transformers[%d] = %p,\n", pipeline->transformers[j]);
			
			RETURN_ERR_CODE(NO_ERROR);
		}
	}
	
	RETURN_ERR_CODE(ERR_INVALID_TRANSFORMER_ID);
}

int pipeline_insert_transformer(m_pipeline *pipeline, m_transformer *trans, int pos)
{
	FUNCTION_START();

	if (!pipeline || !trans)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	int ret_val = NO_ERROR;
	
	if (pipeline->n_transformers == pipeline->transformer_array_length)
	{
		ret_val = pipeline_expand_transformer_array(pipeline);
		
		if (ret_val != NO_ERROR)
		{
			RETURN_NEG_ERR_CODE(ret_val);
		}
	}
	
	trans->id = pipeline->next_id++;
	
	m_eng_disable_software_interrupts();
	for (int i = pipeline->n_transformers; i > pos && i > 0; i--)
		pipeline->transformers[i + 1] = pipeline->transformers[i];
	
	pipeline->transformers[pos] = trans;
	m_eng_enable_software_interrupts();
	
	RETURN_INT(trans->id);
}

int pipeline_prepend_transformer(m_pipeline *pipeline, m_transformer *trans)
{
	FUNCTION_START();

	int ret_val = pipeline_insert_transformer(pipeline, trans, 0);

	if (ret_val < 0)
	{
		RETURN_ERR_CODE(-ret_val);
	}
	
	RETURN_INT(ret_val);
}

int pipeline_append_transformer_type(m_pipeline *pipeline, uint16_t type)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_transformer *trans = (m_transformer*)malloc(sizeof(m_transformer));
	
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
	
	ret_val = pipeline_append_transformer(pipeline, trans);

	if (ret_val < 0)
	{
		RETURN_ERR_CODE(-ret_val);
	}
	
	RETURN_INT(ret_val);
}

int pipeline_insert_transformer_type(m_pipeline *pipeline, uint16_t type, uint16_t pos)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_transformer *trans = (m_transformer*)malloc(sizeof(m_transformer));
	
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
	
	ret_val = pipeline_insert_transformer(pipeline, trans, pos);
	
	if (ret_val < 0)
	{
		RETURN_ERR_CODE(-ret_val);
	}
	
	RETURN_INT(ret_val);
}

int pipeline_prepend_transformer_type(m_pipeline *pipeline, uint16_t type)
{
	FUNCTION_START();

	int ret_val = pipeline_insert_transformer_type(pipeline, type, 0);
	
	if (ret_val < 0)
	{
		RETURN_ERR_CODE(-ret_val);
	}
	
	RETURN_INT(ret_val);
}

int pipeline_get_transformer_position(m_pipeline *pipeline, uint16_t id)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
	}
	
	for (int i = 0; i < pipeline->n_transformers; i++)
	{
		if (pipeline->transformers[i] && pipeline->transformers[i]->id == id)
		{
			RETURN_INT(i);
		}
	}
	
	RETURN_NEG_ERR_CODE(ERR_NULL_PTR);
}

int pipeline_move_transformer(m_pipeline *pipeline, uint16_t id, int new_pos)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
		
	int old_pos = pipeline_get_transformer_position(pipeline, id);
	
	if (old_pos < 0)
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	m_printf("Moving transformer %d from position %d to position %d. The array currently:\n", id, old_pos, new_pos);
	
	pipeline_print_transformer_array(pipeline);
	
	if (old_pos == new_pos)
	{
		RETURN_ERR_CODE(NO_ERROR);
	}
	
	if (new_pos < 0 || new_pos >= pipeline->n_transformers)
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	m_transformer *trans = pipeline->transformers[old_pos];
	
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
	
	m_printf("And after the move:\n");
	pipeline_print_transformer_array(pipeline);
	
	RETURN_ERR_CODE(NO_ERROR);
}

m_transformer *pipeline_get_transformer_by_id(m_pipeline *pipeline, uint16_t id)
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

int pipeline_swap_transformers(m_pipeline *pipeline, uint16_t id1, uint16_t id2)
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
	
	m_eng_disable_software_interrupts();
	
	m_transformer *tmp = pipeline->transformers[index1];
	pipeline->transformers[index1] = pipeline->transformers[index2];
	pipeline->transformers[index2] = tmp;
	
	m_eng_enable_software_interrupts();
	
	RETURN_ERR_CODE(NO_ERROR);
}

int pipeline_valid(m_pipeline *pipeline)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_INT(0);
	}
	
	RETURN_INT(1);
}

int pipeline_compare(m_pipeline *pipeline_a, m_pipeline *pipeline_b)
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

int gut_pipeline(m_pipeline *pipeline)
{
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (pipeline->transformers)
	{
		printf("Freeing pipeline's transformers. Current array:\n");
		for (int i = 0; i < pipeline->transformer_array_length; i++)
		{
			printf("\tpipeline->transformers[%d] = %p\n", i, pipeline->transformers[i]);
		}
		
		for (int i = 0; i < pipeline->n_transformers; i++)
		{
			if (pipeline->transformers[i])
			{
				printf("Freeing transformer %p\n", pipeline->transformers[i]);
				free_transformer(pipeline->transformers[i]);
				pipeline->transformers[i] = NULL;
			}
		}
		
		printf("Free'd pipeline's transformers. Current array:\n");
		for (int i = 0; i < pipeline->transformer_array_length; i++)
		{
			printf("\tpipeline->transformers[%d] = %p\n", i, pipeline->transformers[i]);
		}
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

int clone_pipeline(m_pipeline **dest_ptr, m_pipeline *src)
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
	
	m_pipeline *dest = *dest_ptr;
	
	if (!dest)
	{
		dest = (m_pipeline*)malloc(sizeof(m_pipeline));
		
		if (!dest)
		{
			*dest_ptr = NULL;
			RETURN_ERR_CODE(ERR_ALLOC_FAIL);
		}
		
		*dest_ptr = dest;
		
		init_pipeline(dest);
	}
	else
	{
		gut_pipeline(dest);
	}
	
	dest->next_id = src->next_id;
	dest->transition_policy = src->transition_policy;
	
	int ret_val = NO_ERROR;
	
	if (!dest->transformers || dest->transformer_array_length < src->n_transformers)
	{
		ret_val = pipeline_expand_transformer_array_to(dest, src->n_transformers);
		
		if (ret_val != NO_ERROR)
		{
			RETURN_ERR_CODE(ret_val);
		}
	}
	
	int i = 0;
	for (; i < src->n_transformers; i++)
	{
		ret_val = pipeline_clone_transformer_into_position(dest, src->transformers[i], i);
		
		if (ret_val != NO_ERROR)
		{
			RETURN_ERR_CODE(ret_val);
		}
	}
	for (; i < dest->transformer_array_length; i++)
	{
		dest->transformers[i] = NULL;
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

int pipeline_clone_transformer_into_position(m_pipeline *pipeline, m_transformer *trans, int pos)
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
		ret_val = pipeline_expand_transformer_array_to(pipeline, pos + 1);
		if (ret_val != NO_ERROR)
		{
			RETURN_ERR_CODE(ret_val);
		}
	}
	else
	{
		if (pipeline->transformers[pos])
		{
			if (pipeline->transformers[pos] == trans)
			{
				m_printf("Trying to clone a transformer into its exact slot...\n");
				RETURN_ERR_CODE(NO_ERROR);
			}
			free_transformer(pipeline->transformers[pos]);
			pipeline->transformers[pos] = NULL;
		}
	}
	
	ret_val = clone_transformer(&pipeline->transformers[pos], trans);
	
	if (ret_val == NO_ERROR)
		pipeline->n_transformers = binary_max(pos + 1, pipeline->n_transformers);
	
	RETURN_ERR_CODE(ret_val);
}

int pipeline_change_transformer_setting(m_pipeline *pipeline, uint16_t tid, uint16_t sid, int16_t new_val)
{
	m_printf("pipeline_change_transformer_setting\n");
	FUNCTION_START();

	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_transformer *trans = pipeline_get_transformer_by_id(pipeline, tid);
	
	m_setting *setting = transformer_get_setting(trans, sid);
	
	if (setting)
	{
		setting->value = new_val;
		setting->updated = 1;
		m_printf("setting->value = %d\n", setting->value);
	}
	else
	{
		m_printf("transformer_get_setting returned NULL!\n");
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}

	RETURN_ERR_CODE(NO_ERROR);
}

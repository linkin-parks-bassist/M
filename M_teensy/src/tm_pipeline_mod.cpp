#include "tm.h"

IMPLEMENT_LINKED_LIST(tm_pipe_line_mod);

tm_pipe_line_mod create_pipe_line_mod_append_transformer(uint16_t type)
{
	tm_pipe_line_mod mod;
	
	mod.type = PIPE_LINE_MOD_APPEND_TRANSFORMER;
	mod.data = type;
	
	return mod;
}

tm_pipe_line_mod create_pipe_line_mod_move_transformer(uint16_t tid, uint16_t position)
{
	tm_pipe_line_mod mod;
	
	mod.type = PIPE_LINE_MOD_MOVE_TRANSFORMER;
	mod.tid  = tid;
	mod.data = position;
	
	return mod;
}

tm_pipe_line_mod create_pipe_line_mod_remove_transformer(uint16_t tid)
{
	tm_pipe_line_mod mod;
	
	mod.type = PIPE_LINE_MOD_REMOVE_TRANSFORMER;
	mod.tid  = tid;
	
	return mod;
}

int apply_pipe_line_mod(tm_pipe_line *pipeline, tm_pipe_line_mod mod)
{
	if (!pipeline)
		return ERR_NULL_PTR;
	
	int ret_val = NO_ERROR;
	
	switch (mod.type)
	{
		case PIPE_LINE_MOD_APPEND_TRANSFORMER:
			ret_val = pipe_line_append_transformer_type(pipeline, mod.data);
			break;
		
		case PIPE_LINE_MOD_MOVE_TRANSFORMER:
			ret_val = pipe_line_move_transformer(pipeline, mod.tid, mod.data);
			break;
		
		case PIPE_LINE_MOD_REMOVE_TRANSFORMER:
			ret_val = pipe_line_remove_transformer(pipeline, mod.tid);
			break;
		
		default:
			tm_printf("I don't know how to apply a job of type %d !\n", mod.type);
			return ERR_BAD_ARGS;
	}
	
	return ret_val;
}

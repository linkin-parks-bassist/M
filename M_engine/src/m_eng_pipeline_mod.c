#include "m_eng.h"

static const char *FNAME = "m_eng_pipeline_mod.c";
IMPLEMENT_LINKED_LIST(m_eng_pipe_line_mod);

m_eng_pipe_line_mod create_pipe_line_mod_append_transformer(uint16_t type)
{
	FUNCTION_START();

	m_eng_pipe_line_mod mod;
	
	mod.type = PIPE_LINE_MOD_APPEND_TRANSFORMER;
	mod.data = type;
	
	RETURN(mod);
}

m_eng_pipe_line_mod create_pipe_line_mod_move_transformer(uint16_t tid, uint16_t position)
{
	FUNCTION_START();

	m_eng_pipe_line_mod mod;
	
	mod.type = PIPE_LINE_MOD_MOVE_TRANSFORMER;
	mod.tid  = tid;
	mod.data = position;
	
	RETURN(mod);
}

m_eng_pipe_line_mod create_pipe_line_mod_remove_transformer(uint16_t tid)
{
	FUNCTION_START();

	m_eng_pipe_line_mod mod;
	
	mod.type = PIPE_LINE_MOD_REMOVE_TRANSFORMER;
	mod.tid  = tid;
	
	RETURN(mod);
}

m_eng_pipe_line_mod create_pipe_line_mod_change_transformer_setting(uint16_t tid, uint16_t setting_id, int16_t new_value)
{
	FUNCTION_START();

	m_eng_pipe_line_mod mod;
	
	mod.type = PIPE_LINE_MOD_CHANGE_TRANSFORMER_SETTING;
	mod.tid  = tid;
	mod.data = setting_id;
	mod.sdata = new_value;
	
	RETURN(mod);
}

int apply_pipe_line_mod(m_eng_pipe_line *pipeline, m_eng_pipe_line_mod mod)
{
	FUNCTION_START();

	m_eng_printf("apply_pipe_line_mod. pipeline = %p\n", pipeline);
	if (!pipeline)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	int ret_val = NO_ERROR;
	
	switch (mod.type)
	{
		case PIPE_LINE_MOD_APPEND_TRANSFORMER:
			m_eng_printf("pipeline mod type: append transformer\n");
			ret_val = pipe_line_append_transformer_type(pipeline, mod.data);
			m_eng_printf("apply_pipe_line_mod done. ");
			if (ret_val < 0)
			{
				m_eng_printf("appending failed with error code %s\n", m_error_code_to_string(-ret_val));
				RETURN_NEG_ERR_CODE(ret_val);
			}
			else
			{
				m_eng_printf("appended transformer id = %d\n", ret_val);
				RETURN_INT(ret_val);
			}
		
		case PIPE_LINE_MOD_MOVE_TRANSFORMER:
			m_eng_printf("pipeline mod type: move transformer\n");
			ret_val = pipe_line_move_transformer(pipeline, mod.tid, mod.data);
			break;
		
		case PIPE_LINE_MOD_REMOVE_TRANSFORMER:
			m_eng_printf("pipeline mod type: remove transformer\n");
			ret_val = pipe_line_remove_transformer(pipeline, mod.tid);
			break;
		
		case PIPE_LINE_MOD_CHANGE_TRANSFORMER_SETTING:
			pipe_line_change_transformer_setting(pipeline, mod.tid, mod.data, mod.sdata);
			break;
		
		default:
			m_eng_printf("I don't know how to apply a job of type %d !\n", mod.type);
			RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	m_eng_printf("apply_pipe_line_mod done. ret_val = %s\n", m_error_code_to_string(ret_val));
	
	RETURN_ERR_CODE(ret_val);
}

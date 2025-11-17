#include "m_eng.h"

static const char *FNAME = "m_eng_graph_mod.c";

IMPLEMENT_LINKED_LIST(m_pipeline_mod);

m_pipeline_mod create_pipeline_mod_append_transformer(uint16_t type)
{
	FUNCTION_START();

	m_pipeline_mod mod;
	
	mod.type = PIPELINE_MOD_APPEND_TRANSFORMER;
	mod.data = type;
	
	RETURN(mod);
}

m_pipeline_mod create_pipeline_mod_move_transformer(uint16_t tid, uint16_t position)
{
	FUNCTION_START();

	m_pipeline_mod mod;
	
	mod.type = PIPELINE_MOD_MOVE_TRANSFORMER;
	mod.tid  = tid;
	mod.data = position;
	
	RETURN(mod);
}

m_pipeline_mod create_pipeline_mod_remove_transformer(uint16_t tid)
{
	FUNCTION_START();

	m_pipeline_mod mod;
	
	mod.type = PIPELINE_MOD_REMOVE_TRANSFORMER;
	mod.tid  = tid;
	
	RETURN(mod);
}

m_pipeline_mod create_pipeline_mod_change_transformer_setting(uint16_t tid, uint16_t setting_id, int16_t new_value)
{
	FUNCTION_START();

	m_pipeline_mod mod;
	
	mod.type = PIPELINE_MOD_CHANGE_TRANSFORMER_SETTING;
	mod.tid  = tid;
	mod.data = setting_id;
	mod.sdata = new_value;
	
	RETURN(mod);
}

const char *pipeline_mod_type_string(int type)
{
	switch (type)
	{
		case PIPELINE_MOD_APPEND_TRANSFORMER:
			return "PIPELINE_MOD_APPEND_TRANSFORMER";
		
		case PIPELINE_MOD_MOVE_TRANSFORMER:
			return "PIPELINE_MOD_MOVE_TRANSFORMER";
		
		case PIPELINE_MOD_REMOVE_TRANSFORMER:
			return "PIPELINE_MOD_REMOVE_TRANSFORMER";
		
		case PIPELINE_MOD_CHANGE_TRANSFORMER_SETTING:
			return "PIPELINE_MOD_CHANGE_TRANSFORMER_SETTING";
		
		default:
			return "PIPELINE_MOD_UNKNOWN";
	}
}

int apply_pipeline_mod(m_pipeline *pipeline, m_pipeline_mod mod, int *err_code)
{
	FUNCTION_START();

	if (err_code)
		*err_code = NO_ERROR;
	
	if (!pipeline)
	{
		if (err_code)
			*err_code = ERR_NULL_PTR;
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	int ret_val;
	
	switch (mod.type)
	{
		case PIPELINE_MOD_APPEND_TRANSFORMER:
			ret_val = pipeline_append_transformer_type(pipeline, mod.data);
			
			if (ret_val < 0)
			{
				if (err_code)
					*err_code = ERR_NULL_PTR;
				RETURN_NEG_ERR_CODE(ret_val);
			}
			else
			{
				RETURN_INT(ret_val);
			}
		
		case PIPELINE_MOD_MOVE_TRANSFORMER:
			ret_val = pipeline_move_transformer(pipeline, mod.tid, mod.data);
			
			if (ret_val != NO_ERROR && err_code)
			{
				*err_code = ret_val;
			}
			break;
		
		case PIPELINE_MOD_REMOVE_TRANSFORMER:
			ret_val = pipeline_remove_transformer(pipeline, mod.tid);
			
			if (ret_val != NO_ERROR && err_code)
			{
				*err_code = ret_val;
			}
			break;
		
		case PIPELINE_MOD_CHANGE_TRANSFORMER_SETTING:
			ret_val = pipeline_change_transformer_setting(pipeline, mod.tid, mod.data, mod.sdata);
			
			if (ret_val != NO_ERROR && err_code)
			{
				*err_code = ret_val;
			}
			break;
		
		default:
			RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	RETURN_ERR_CODE(ret_val);
}

#include "tm.h"

int profile_id_valid(tm_context *cxt, uint16_t profile_id)
{
	if (!cxt)
		return 0;
	
	return (profile_id <= (unsigned int)cxt->n_profiles);
}

int transformer_id_valid(tm_context *cxt, uint16_t profile_id, uint16_t transformer_id)
{
	if (!profile_id_valid(cxt, profile_id))
		return 0;
	
	if (transformer_id >= (unsigned int)cxt->profiles[profile_id].pipeline.n_transformers)
		return 0;
	
	return (pipe_line_get_transformer_by_id(&cxt->profiles[profile_id].pipe_line, transformer_id) != NULL);
}

int parameter_id_valid(tm_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id)
{
	if (!transformer_id_valid(cxt, profile_id, transformer_id))
		return 0;
	
	tm_audio_transformer *trans = pipe_line_get_transformer_by_id(&cxt->profiles[profile_id].pipe_line, transformer_id);
	
	if (!trans)
		return 0;
	
	return (trans->n_parameters >= parameter_id && trans->parameters[parameter_id]);
}

int parameter_id_str_valid(tm_context *cxt, m_parameter_id pid)
{
	return parameter_id_valid(cxt, pid.profile_id, pid.transformer_id, pid.parameter_id);
}

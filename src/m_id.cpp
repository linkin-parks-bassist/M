#include "M.h"

int profile_id_valid(m_context *cxt, uint16_t profile_id)
{
	if (!cxt)
		return 0;
	
	return (profile_id <= (unsigned int)cxt->n_profiles);
}

int transformer_id_valid(m_context *cxt, uint16_t profile_id, uint16_t transformer_id)
{
	if (!profile_id_valid(cxt, profile_id))
		return 0;
	
	if (transformer_id > (unsigned int)cxt->profiles[profile_id].pipeline.n_transformers)
		return 0;
	
	if (!cxt->profiles[profile_id].pipeline.transformers[transformer_id])
		return 0;
	
	return 1;
}

int parameter_id_valid(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id)
{
	if (!transformer_id_valid(cxt, profile_id, transformer_id))
		return 0;
	
	if (parameter_id > (unsigned int)cxt->profiles[profile_id].pipeline.transformers[transformer_id]->n_parameters)
		return 0;
	
	if (!cxt->profiles[profile_id].pipeline.transformers[transformer_id]->parameters[parameter_id])
		return 0;
	
	return 1;
}

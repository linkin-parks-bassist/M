#ifndef M_ID_H_
#define M_ID_H_

int profile_id_valid	(m_context *cxt, uint16_t profile_id);
int transformer_id_valid(m_context *cxt, uint16_t profile_id, uint16_t transformer_id);
int parameter_id_valid	(m_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id);

#endif

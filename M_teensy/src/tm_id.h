#ifndef M_ID_H_
#define M_ID_H_

typedef struct
{
	uint16_t profile_id;
	uint16_t transformer_id;
} tm_transformer_id;

#ifdef M_TEENSY
int profile_id_valid	(tm_context *cxt, uint16_t profile_id);
int transformer_id_valid(tm_context *cxt, uint16_t profile_id, uint16_t transformer_id);
int parameter_id_valid	(tm_context *cxt, uint16_t profile_id, uint16_t transformer_id, uint16_t parameter_id);

int parameter_id_str_valid(tm_context *cxt, m_parameter_id id);
#endif

#endif

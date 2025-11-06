#ifndef M_INT_PIPELINE_H_
#define M_INT_PIPELINE_H_

typedef m_int_transformer_ptr_linked_list m_int_transformer_ll;
typedef m_int_transformer_ptr_linked_list transformer_ll;

typedef struct
{
	m_int_transformer_ptr_linked_list *transformers;
} m_int_pipeline;

int init_m_int_pipeline(m_int_pipeline *pipeline);

m_int_transformer *m_int_pipeline_append_transformer_type(m_int_pipeline *pipeline, uint16_t type);

int m_int_pipeline_remove_transformer(m_int_pipeline *pipeline, uint16_t id);

int m_int_pipeline_get_n_transformers(m_int_pipeline *pipeline);

int clone_pipeline(m_int_pipeline *dest, m_int_pipeline *src);
void gut_pipeline(m_int_pipeline *pipeline);

#endif

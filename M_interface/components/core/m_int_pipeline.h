#ifndef M_INT_PIPELINE_H_
#define M_INT_PIPELINE_H_

#include "m_int_transformer.h"

typedef struct
{
	m_transformer_pll *transformers;
} m_pipeline;

int init_m_pipeline(m_pipeline *pipeline);

m_transformer *m_pipeline_append_transformer_type(m_pipeline *pipeline, uint16_t type);
m_transformer *m_pipeline_append_transformer_eff(m_pipeline *pipeline, m_effect_desc *eff);

int m_pipeline_remove_transformer(m_pipeline *pipeline, uint16_t id);

int m_pipeline_get_n_transformers(m_pipeline *pipeline);

int clone_pipeline(m_pipeline *dest, m_pipeline *src);
void gut_pipeline(m_pipeline *pipeline);

m_fpga_transfer_batch m_pipeline_create_fpga_transfer_batch(m_pipeline *pipeline);

#endif

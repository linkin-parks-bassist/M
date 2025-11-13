#ifndef M_INT_PIPELINE_H_
#define M_INT_PIPELINE_H_

#include "m_pipeline.h"

int init_m_pipeline(m_pipeline *pipeline);

m_transformer *m_pipeline_append_transformer_type(m_pipeline *pipeline, uint16_t type);

int m_pipeline_remove_transformer(m_pipeline *pipeline, uint16_t id);

int m_pipeline_get_n_transformers(m_pipeline *pipeline);

int clone_pipeline(m_pipeline *dest, m_pipeline *src);
void gut_pipeline(m_pipeline *pipeline);

#endif

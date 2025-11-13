#ifndef M_ENG_PIPELINE_H_
#define M_ENG_PIPELINE_H_

#include "m_transformer.h"

#define INITIAL_TRANSFORMER_ARRAY_LENGTH 8

#include "m_pipeline.h"

int init_pipeline(m_pipeline *pipeline);
int compute_pipeline(m_pipeline *pipeline, float *dest, float *src);

int pipeline_expand_transformer_array(m_pipeline *pipeline);
int pipeline_expand_transformer_array_to(m_pipeline *pipeline, int n);
int pipeline_append_transformer(m_pipeline *pipeline, m_transformer *trans);
int pipeline_remove_transformer(m_pipeline *pipeline, uint16_t tid);
int pipeline_insert_transformer(m_pipeline *pipeline, m_transformer *trans, int pos);
int pipeline_prepend_transformer(m_pipeline *pipeline, m_transformer *trans);
int pipeline_append_transformer_type(m_pipeline *pipeline, uint16_t type);
int pipeline_insert_transformer_type(m_pipeline *pipeline, uint16_t type, uint16_t pos);
int pipeline_prepend_transformer_type(m_pipeline *pipeline, uint16_t type);
int pipeline_change_transformer_setting(m_pipeline *pipeline, uint16_t tid, uint16_t sid, int16_t new_val);

int pipeline_get_transformer_position(m_pipeline *pipeline, uint16_t id);
m_transformer *pipeline_get_transformer_by_id(m_pipeline *pipeline, uint16_t id);

int pipeline_move_transformer(m_pipeline *pipeline, uint16_t id, int positio);

int pipeline_transition_policy(m_pipeline *pipeline);

int pipeline_swap_transformers(m_pipeline *pipeline, uint16_t id1, uint16_t id2);

int pipeline_valid	 (m_pipeline *pipeline);
int pipeline_compare(m_pipeline *pipeline_a, m_pipeline *pipeline_b);
int gut_pipeline	 (m_pipeline *pipeline);
int clone_pipeline	 (m_pipeline **dest, m_pipeline *src);

int pipeline_clone_transformer_into_position(m_pipeline *pipeline, m_transformer *transformer, int pot);

#endif

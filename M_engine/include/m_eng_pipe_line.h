#ifndef M_ENG_PIPE_LINE_H_
#define M_ENG_PIPE_LINE_H_

#include "m_eng_transformer.h"

#define INITIAL_TRANSFORMER_ARRAY_LENGTH 8

typedef struct
{
	int n_transformers;
	int transformer_array_length;
	m_eng_transformer **transformers;
	
	uint16_t next_id;
	
	int transition_policy;
} m_eng_pipe_line;

int init_pipe_line(m_eng_pipe_line *pipeline);
int compute_pipe_line(m_eng_pipe_line *pipeline, float *dest, float *src);

int pipe_line_expand_transformer_array(m_eng_pipe_line *pipeline);
int pipe_line_expand_transformer_array_to(m_eng_pipe_line *pipeline, int n);
int pipe_line_append_transformer(m_eng_pipe_line *pipeline, m_eng_transformer *trans);
int pipe_line_remove_transformer(m_eng_pipe_line *pipeline, uint16_t tid);
int pipe_line_insert_transformer(m_eng_pipe_line *pipeline, m_eng_transformer *trans, int pos);
int pipe_line_prepend_transformer(m_eng_pipe_line *pipeline, m_eng_transformer *trans);
int pipe_line_append_transformer_type(m_eng_pipe_line *pipeline, uint16_t type);
int pipe_line_insert_transformer_type(m_eng_pipe_line *pipeline, uint16_t type, uint16_t pos);
int pipe_line_prepend_transformer_type(m_eng_pipe_line *pipeline, uint16_t type);
int pipe_line_change_transformer_setting(m_eng_pipe_line *pipeline, uint16_t tid, uint16_t sid, int new_val);

int pipe_line_get_transformer_position(m_eng_pipe_line *pipeline, uint16_t id);
m_eng_transformer *pipe_line_get_transformer_by_id(m_eng_pipe_line *pipeline, uint16_t id);

int pipe_line_move_transformer(m_eng_pipe_line *pipeline, uint16_t id, int positio);

int pipe_line_transition_policy(m_eng_pipe_line *pipeline);

int pipe_line_swap_transformers(m_eng_pipe_line *pipeline, uint16_t id1, uint16_t id2);

int pipe_line_valid	 (m_eng_pipe_line *pipeline);
int pipe_line_compare(m_eng_pipe_line *pipeline_a, m_eng_pipe_line *pipeline_b);
int gut_pipe_line	 (m_eng_pipe_line *pipeline);
int clone_pipe_line	 (m_eng_pipe_line **dest, m_eng_pipe_line *src);

int pipe_line_clone_transformer_into_position(m_eng_pipe_line *pipeline, m_eng_transformer *transformer, int pot);

#endif

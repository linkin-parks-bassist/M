#ifndef TM_PIPE_LINE_H_
#define TM_PIPE_LINE_H_

#include "tm_transformer.h"

#define INITIAL_TRANSFORMER_ARRAY_LENGTH 8

typedef struct
{
	int n_transformers;
	int transformer_array_length;
	tm_transformer **transformers;
	
	uint16_t next_id;
	
	int transition_policy;
} tm_pipe_line;

int init_pipe_line(tm_pipe_line *pipeline);
int compute_pipe_line(tm_pipe_line *pipeline, float *dest, float *src);

int pipe_line_expand_transformer_array(tm_pipe_line *pipeline);
int pipe_line_expand_transformer_array_to(tm_pipe_line *pipeline, int n);
int pipe_line_append_transformer(tm_pipe_line *pipeline, tm_transformer *trans);
int pipe_line_remove_transformer(tm_pipe_line *pipeline, uint16_t tid);
int pipe_line_insert_transformer(tm_pipe_line *pipeline, tm_transformer *trans, int pos);
int pipe_line_prepend_transformer(tm_pipe_line *pipeline, tm_transformer *trans);
int pipe_line_append_transformer_type(tm_pipe_line *pipeline, uint16_t type);
int pipe_line_insert_transformer_type(tm_pipe_line *pipeline, uint16_t type, uint16_t pos);
int pipe_line_prepend_transformer_type(tm_pipe_line *pipeline, uint16_t type);
int pipe_line_change_transformer_setting(tm_pipe_line *pipeline, uint16_t tid, uint16_t sid, int new_val);

int pipe_line_get_transformer_position(tm_pipe_line *pipeline, uint16_t id);
tm_transformer *pipe_line_get_transformer_by_id(tm_pipe_line *pipeline, uint16_t id);

int pipe_line_move_transformer(tm_pipe_line *pipeline, uint16_t id, int positio);

int pipe_line_transition_policy(tm_pipe_line *pipeline);

int pipe_line_swap_transformers(tm_pipe_line *pipeline, uint16_t id1, uint16_t id2);

int pipe_line_valid	 (tm_pipe_line *pipeline);
int pipe_line_compare(tm_pipe_line *pipeline_a, tm_pipe_line *pipeline_b);
int gut_pipe_line	 (tm_pipe_line *pipeline);
int clone_pipe_line	 (tm_pipe_line **dest, tm_pipe_line *src);

int pipe_line_clone_transformer_into_position(tm_pipe_line *pipeline, tm_transformer *transformer, int pot);

#endif

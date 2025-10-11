#ifndef AUDIO_FRAMEWORK_H_
#define AUDIO_FRAMEWORK_H_

#define PLACE_AT_POSITION 			0
#define PLACE_AT_END				1

#define MAX_PIPELINE_TRANSFORMERS	64

/* Pipeline error bitflags; also used for return values of reconfigure_pipeline */
#define PIPELINE_ERR_FLAG_UNCONFIGURED	 			0b000000000001
#define PIPELINE_ERR_FLAG_NULL_TRANSFORMER 			0b000000000010
#define PIPELINE_ERR_FLAG_NODE_CONFLICT	 			0b000000000100
#define PIPELINE_ERR_FLAG_OUTPUT_CONFLICT			0b000000001000
#define PIPELINE_ERR_FLAG_OUTPUT_UNFED				0b000000010000
#define PIPELINE_ERR_FLAG_TRANSFORMER_UNFED			0b000000100000
#define PIPELINE_ERR_FLAG_BLOCK_ALLOC_FAIL 			0b000001000000
#define PIPELINE_ERR_FLAG_TRANS_INPUT_BAD_COORD 	0b000010000000
#define PIPELINE_ERR_FLAG_TRANS_OUTPUT_BAD_COORD	0b000100000000
#define PIPELINE_ERR_FLAG_RECONF_ITERS_EXCEEDED		0b001000000000
#define PIPELINE_ERR_FLAG_NULL_PIPELINE	   			0b010000000000	// Only for return value
#define PIPELINE_ERR_FLAG_ALLOC_FAIL	   			0b100000000000	// Only for return value

#define PIPELINE_RECONFIGURE_MAX_ITERATIONS 512

typedef struct
{
	int active;
	int updated;
	
	vec2i pos;
	tm_audio_block_float *block;
} tm_pipeline_node;

#define INITIAL_TRANSFORMER_ARRAY_LENGTH 8

typedef struct
{
	int n_transformers;
	int transformer_array_length;
	tm_transformer **transformers;
	
	uint16_t next_id;
	
	int transition_policy;
} tm_pipe_line;

typedef struct
{
	/* Dimensions, for malloc purposes. Can be changed later, with malloc price */
	int width, height;
	int err_flags;
	
	int n_active_nodes;
	int n_transformers;
	
	tm_pipeline_node input_node, output_node;
	
	tm_pipeline_node **nodes;
	tm_pipeline_node **active_node_array;
	tm_transformer *transformers[MAX_PIPELINE_TRANSFORMERS];
	
	int n_active_transformers;
	int compute_order[MAX_PIPELINE_TRANSFORMERS];
} tm_pipeline;

extern tm_pipeline *active_pipeline;

int nullify_pipeline	(tm_pipeline *pipeline);
int init_pipeline		(tm_pipeline *pipeline, int width, int height);
int init_bypass_pipeline(tm_pipeline *pipeline);

int free_pipeline(tm_pipeline *pipeline);

int pipeline_activate_node(tm_pipeline *pipeline, vec2i);
tm_pipeline_node *pipeline_get_node(tm_pipeline *pipeline, vec2i pos);

int pipeline_add_transformer(tm_pipeline *pipeline, tm_transformer *trans);

int pipeline_add_transformer_by_type(tm_pipeline *pipeline, uint16_t type);

int write_node(tm_pipeline_node *node, float *data);

int reset_nodes(tm_pipeline *pipeline);

int propagate_transformer(tm_pipeline *pipeline, tm_transformer *trans);
int compute_pipeline(tm_pipeline *pipeline, int16_t *input);

int pipeline_reconfigure(tm_pipeline *pipeline);

int init_pipe_line(tm_pipe_line *pipeline);


// SIMPLIFICATION

int init_pipe_line(tm_pipe_line *pipeline);
int compute_pipe_line(tm_pipe_line *pipeline, float *dest, float *src);

int pipe_line_expand_transformer_array(tm_pipe_line *pipeline);
int pipe_line_append_transformer(tm_pipe_line *pipeline, tm_transformer *trans);
int pipe_line_remove_transformer(tm_pipe_line *pipeline, uint16_t tid);
int pipe_line_insert_transformer(tm_pipe_line *pipeline, tm_transformer *trans, int pos);
int pipe_line_prepend_transformer(tm_pipe_line *pipeline, tm_transformer *trans);
int pipe_line_append_transformer_type(tm_pipe_line *pipeline, uint16_t type);
int pipe_line_insert_transformer_type(tm_pipe_line *pipeline, uint16_t type, uint16_t pos);
int pipe_line_prepend_transformer_type(tm_pipe_line *pipeline, uint16_t type);

int pipe_line_get_transformer_position(tm_pipe_line *pipeline, uint16_t id);
tm_transformer *pipe_line_get_transformer_by_id(tm_pipe_line *pipeline, uint16_t id);

int pipe_line_move_transformer(tm_pipe_line *pipeline, uint16_t id, int positio);

int pipe_line_transition_policy(tm_pipe_line *pipeline);

int pipe_line_swap_transformers(tm_pipe_line *pipeline, uint16_t id1, uint16_t id2);

#endif

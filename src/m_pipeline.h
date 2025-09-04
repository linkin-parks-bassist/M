#ifndef AUDIO_FRAMEWORK_H_
#define AUDIO_FRAMEWORK_H_

#define PLACE_AT_POSITION 			0
#define PLACE_AT_END				1

#define MAX_PIPELINE_TRANSFORMERS	64

#define INPUT_NODE_COORD  (vec2i){-1, 0}
#define OUTPUT_NODE_COORD (vec2i){0, -1}

typedef struct
{
	int active;
	int updated;
	
	vec2i pos;
	m_audio_block_float *block;
} m_pipeline_node;

typedef struct
{
	int width, height;
	
	int n_active_nodes;
	int n_transformers;
	
	m_pipeline_node input_node, output_node;
	
	m_pipeline_node **nodes;
	m_pipeline_node **active_node_array;
	m_audio_transformer *transformers[MAX_PIPELINE_TRANSFORMERS];
} m_pipeline;

extern m_pipeline *active_pipeline;

int init_pipeline		(m_pipeline *pipeline, int width, int height);
int init_bypass_pipeline(m_pipeline *pipeline);

int pipeline_activate_node(m_pipeline *pipeline, int x, int y);
m_pipeline_node *pipeline_get_node(m_pipeline *pipeline, vec2i pos);

int pipeline_add_transformer(m_pipeline *pipeline, m_audio_transformer *trans);

int write_node(m_pipeline_node *node, float *data);

int reset_nodes(m_pipeline *pipeline);

int propagate_transformer(m_pipeline *pipeline, m_audio_transformer *trans);
int compute_pipeline(m_pipeline *pipeline, int16_t *input);

#endif

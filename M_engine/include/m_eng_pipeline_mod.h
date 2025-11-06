#ifndef M_ENG_PIPELINE_MOD_H_
#define M_ENG_PIPELINE_MOD_H_

#define PIPE_LINE_MOD_APPEND_TRANSFORMER 			0
#define PIPE_LINE_MOD_MOVE_TRANSFORMER				1
#define PIPE_LINE_MOD_REMOVE_TRANSFORMER			2
#define PIPE_LINE_MOD_CHANGE_TRANSFORMER_SETTING	3

typedef struct
{
	int type;
	uint16_t tid;
	uint16_t data;
} m_eng_pipe_line_mod;

int init_pipe_line_mod(m_eng_pipe_line_mod *mod);

m_eng_pipe_line_mod create_pipe_line_mod_append_transformer(uint16_t type);
m_eng_pipe_line_mod create_pipe_line_mod_move_transformer	(uint16_t tid, uint16_t position);
m_eng_pipe_line_mod create_pipe_line_mod_remove_transformer(uint16_t tid);

int apply_pipe_line_mod(m_eng_pipe_line *pipeline, m_eng_pipe_line_mod mod);

DECLARE_LINKED_LIST(m_eng_pipe_line_mod);

#endif

#ifndef M_DEBUGGING_H_
#define M_DEBUGGING_H_

void full_debug_print(m_eng_context *cxt);
void print_context_info(m_eng_context *cxt, int depth);
void print_profile_info(m_eng_profile *profile, int depth);
#ifdef GRAPH_PIPELINE
void print_pipeline_info(m_eng_pipeline *pipeline, int depth);
#endif
void print_pipe_line_info(m_eng_pipe_line *pipe_line, int depth);
void print_transformer_info(m_eng_transformer *trans, int depth);

#endif

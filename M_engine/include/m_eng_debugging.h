#ifndef M_DEBUGGING_H_
#define M_DEBUGGING_H_

void full_debug_print(m_eng_context *cxt);
void print_context_info(m_eng_context *cxt, int depth);
void print_profile_info(m_eng_profile *profile, int depth);
#ifdef GRAPH_PIPELINE
void print_pipeline_info(m_eng_graph *pipeline, int depth);
#endif
void print_pipeline_info(m_pipeline *pipeline, int depth);
void print_transformer_info(m_transformer *trans, int depth);

#endif

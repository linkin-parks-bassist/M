#ifndef M_DEBUGGING_H_
#define M_DEBUGGING_H_

void full_debug_print(tm_context *cxt);
void print_context_info(tm_context *cxt, int depth);
void print_profile_info(tm_profile *profile, int depth);
void print_pipeline_info(tm_pipeline *pipeline, int depth);
void print_pipe_line_info(tm_pipe_line *pipe_line, int depth);
void print_transformer_info(tm_transformer *trans, int depth);

#endif

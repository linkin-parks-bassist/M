#ifndef EM_PIPELINE_H_
#define EM_PIPELINE_H_

typedef em_transformer_ptr_linked_list em_transformer_ll;

typedef struct
{
	em_transformer_ptr_linked_list *transformers;
} em_pipeline;

int init_em_pipeline(em_pipeline *pipeline);

em_transformer *em_pipeline_append_transformer_type(em_pipeline *pipeline, uint16_t type);

int em_pipeline_remove_transformer(em_pipeline *pipeline, uint16_t id);

int em_pipeline_get_n_transformers(em_pipeline *pipeline);

int clone_pipeline(em_pipeline *dest, em_pipeline *src);
void gut_pipeline(em_pipeline *pipeline);

#endif

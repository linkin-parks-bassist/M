#ifndef EM_PROFILE_H_
#define EM_PROFILE_H_

typedef struct em_profile
{
	char *name;
	uint16_t id;
	em_pipeline pipeline;
	
	em_ui_page *view_page;
} em_profile;

int init_em_profile(em_profile *profile);
int init_em_pipeline(em_pipeline *pipeline);

int em_profile_set_default_name_from_id(em_profile *profile);

em_transformer *em_profile_append_transformer_type(em_profile *profile, uint16_t type);
int em_profile_remove_transformer(em_profile *profile, uint16_t id);

#endif

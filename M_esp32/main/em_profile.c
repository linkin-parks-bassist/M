#include "em.h"

static const char *TAG = "em_profile.c";

int init_em_profile(em_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	profile->id = 0;
	
	int ret_val = init_em_pipeline(&profile->pipeline);
	
	if (ret_val != NO_ERROR)
		return ret_val;
	
	return NO_ERROR;
}

int em_profile_set_default_name_from_id(em_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	// Compute the digits in the ID. 
	int id_digits;
	int id_div = profile->id;
	
	for (id_digits = 0; id_div || !id_digits; id_div = id_div / 10)
		id_digits++;
	
	profile->name = malloc(9 + id_digits);
	
	if (!profile->name)
		return ERR_ALLOC_FAIL;
	
	sprintf(profile->name, "Profile %d\n", id_digits);
	
	return NO_ERROR;
}
em_transformer *em_profile_append_transformer_type(em_profile *profile, uint16_t type)
{
	if (!profile)
		return NULL;
	
	return em_pipeline_append_transformer_type(&profile->pipeline, type);
}


int em_profile_remove_transformer(em_profile *profile, uint16_t id)
{
	printf("cxt_remove_transformer\n");
	if (!profile)
		return ERR_NULL_PTR;
	
	int ret_val = em_pipeline_remove_transformer(&profile->pipeline, id);
	
	printf("cxt_remove_transformer done. ret_val = %s\n", m_error_code_to_string(ret_val));
	return ret_val;
}

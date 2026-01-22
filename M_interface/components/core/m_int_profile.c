#include "m_int.h"

static const char *TAG = "m_profile.c";

IMPLEMENT_LINKED_PTR_LIST(m_profile);

int init_m_profile(m_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	profile->id = 0;
	
	int ret_val = init_m_pipeline(&profile->pipeline);
	
	profile->view_page = NULL;
	profile->name = NULL;
	profile->id = 0;
	
	profile->fname = NULL;
	
	profile->active = 0;
	profile->unsaved_changes = 1;
	
	profile->sequence = NULL;
	
	if (ret_val != NO_ERROR)
		return ret_val;
	
	init_parameter(&profile->volume, "Gain", 0.0, -12.0, 12.0);
	profile->volume.units = " dB";
	profile->volume.id = (m_parameter_id){.profile_id = 0, .transformer_id = 0xFFFF, .parameter_id = 0};
	
	profile->representations 		= NULL;
	
	return NO_ERROR;
}

int profile_set_id(m_profile *profile, uint16_t id)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	profile->id = id;
	profile->volume.id.profile_id = id;
	
	return NO_ERROR;
}

int m_profile_set_active(m_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	profile->active = 1;
	
	m_profile_update_representations(profile);
	
	m_profile_program_fpga(profile);
	
	return NO_ERROR;
}

int m_profile_set_inactive(m_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	profile->active = 0;
	
	m_profile_update_representations(profile);
	
	return NO_ERROR;
}

int m_profile_add_representation(m_profile *profile, m_representation *rep)
{
	if (!profile || !rep)
		return ERR_NULL_PTR;
	
	m_representation_pll *nl = m_representation_pll_append(profile->representations, rep);
	
	if (nl)
		profile->representations = nl;
	else
		return ERR_ALLOC_FAIL;
	
	printf("profile->representations = %p\n", profile->representations);
	
	return NO_ERROR;
}

int m_profile_update_representations(m_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	if (profile->representations)
		queue_representation_list_update(profile->representations);
	
	return NO_ERROR;
}

int m_profile_remove_representation(m_profile *profile, m_representation *rep)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	profile->representations = m_representation_pll_remove(profile->representations, rep);
	
	return NO_ERROR;
}

int m_profile_set_default_name_from_id(m_profile *profile)
{
	printf("m_profile_set_default_name_from_id\n");
	if (!profile)
		return ERR_NULL_PTR;
	
	printf("ID = %d\n", profile->id);
	
	// Compute the digits in the ID. 
	int id_digits;
	int id_div = profile->id;
	
	for (id_digits = 0; id_div || !id_digits; id_div = id_div / 10)
		id_digits++;
	
	if (profile->name)
		m_free(profile->name);
	
	profile->name = m_alloc(9 + id_digits);
	
	if (!profile->name)
		return ERR_ALLOC_FAIL;
	
	sprintf(profile->name, "Profile %d", profile->id);
	
	printf("Resulting name: %s\n", profile->name);
	
	return NO_ERROR;
}

m_transformer *m_profile_append_transformer_type(m_profile *profile, uint16_t type)
{
	if (!profile)
		return NULL;
	
	m_transformer *trans = m_pipeline_append_transformer_type(&profile->pipeline, type);
	
	if (!trans)
		return NULL;
	
	trans->profile = profile;
	
	return trans;
}

m_transformer *m_profile_append_transformer_eff(m_profile *profile, m_effect_desc *eff)
{
	if (!profile)
		return NULL;
	
	m_transformer *trans = m_pipeline_append_transformer_eff(&profile->pipeline, eff);
	
	if (!trans)
		return NULL;
	
	trans->profile = profile;
	
	return trans;
}


int m_profile_remove_transformer(m_profile *profile, uint16_t id)
{
	printf("cxt_remove_transformer\n");
	if (!profile)
		return ERR_NULL_PTR;
	
	int ret_val = m_pipeline_remove_transformer(&profile->pipeline, id);
	
	printf("cxt_remove_transformer done. ret_val = %s\n", m_error_code_to_string(ret_val));
	return ret_val;
}

int clone_profile(m_profile *dest, m_profile *src)
{
	if (!src || !dest)
		return ERR_NULL_PTR;
	
	printf("Cloning profile\n");
	
	printf("Clone name...\n");
	dest->name = m_strndup(src->name, PROFILE_NAME_MAX_LEN);
	clone_parameter(&dest->volume, &src->volume);
	dest->id = src->id;
	
	printf("Clone pipeline...\n");
	clone_pipeline(&dest->pipeline, &src->pipeline);
	
	printf("Done!\n");
	dest->view_page = NULL;
	
	return NO_ERROR;
}

void gut_profile(m_profile *profile)
{
	if (!profile)
		return;
	
	printf("Gut view page %p...\n", profile->view_page);
	if (profile->view_page)
		profile->view_page->free_all(profile->view_page);
	
	profile->view_page = NULL;
	
	printf("Gut name %p...\n", profile->name);
	if (profile->name)
		m_free(profile->name);
	
	profile->name = NULL;
	
	printf("Gut profile...\n");
	gut_pipeline(&profile->pipeline);
	printf("Done!\n");
}

void free_profile(m_profile *profile)
{
	if (!profile)
		return;
		
	gut_profile(profile);
	
	m_free(profile);
}

void new_profile_receive_id(m_message msg, m_response response)
{
	m_profile *profile = msg.cb_arg;
	
	if (!profile)
	{
		printf("ERROR: Profile ID recieved, but no profile associated !\n");
		return;
	}
	
	uint16_t id;
	memcpy(&id, response.data, sizeof(uint16_t));
	
	printf("New profile recieved its ID: %d\n", id);
	
	profile_set_id(profile, id);
	m_profile_set_default_name_from_id(profile);
	
	
	m_profile_update_representations(profile);
}

m_profile *create_new_profile_with_teensy()
{
	m_profile *new_profile = m_context_add_profile_rp(&global_cxt);
	
	if (!new_profile)
	{
		printf("ERROR: Couldn't create new profile\n");
		return NULL;
	}
	
	m_message msg = create_m_message_nodata(M_MESSAGE_CREATE_PROFILE);
	
	msg.callback = new_profile_receive_id;
	msg.cb_arg = new_profile;
	
	queue_msg_to_teensy(msg);
	
	create_profile_view_for(new_profile);

	return new_profile;
}

int m_profile_save(m_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	printf("m_profile_save\n");
	
	int ret_val = save_profile(profile);
	
	if (ret_val == NO_ERROR)
	{
		profile->unsaved_changes = 0;
		m_profile_update_representations(profile);
	}
	
	printf("m_profile_save done\n");
	
	return NO_ERROR;
}

int m_profile_if_active_update_fpga(m_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	if (!profile->active)
		return NO_ERROR;
	
	m_fpga_send_byte(COMMAND_RESET_PIPELINE);
	m_fpga_transfer_batch send_seq = m_pipeline_create_fpga_transfer_batch(&profile->pipeline);
	
	m_fpga_transfer_batch_send(send_seq);
	m_fpga_send_byte(COMMAND_SWAP_PIPELINES);
	
	return NO_ERROR;
}

int m_profile_program_fpga(m_profile *profile)
{
	if (!profile)
		return ERR_NULL_PTR;
	
	m_fpga_send_byte(COMMAND_RESET_PIPELINE);
	m_fpga_transfer_batch send_seq = m_pipeline_create_fpga_transfer_batch(&profile->pipeline);
	
	m_fpga_transfer_batch_send(send_seq);
	m_fpga_send_byte(COMMAND_SWAP_PIPELINES);
	
	return NO_ERROR;
}

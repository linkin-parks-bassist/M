#include "m_int.h"

IMPLEMENT_LINKED_PTR_LIST(m_int_sequence);

int init_m_int_sequence(m_int_sequence *sequence)
{
	if (!sequence)
		return ERR_NULL_PTR;
	
	sequence->name 	  = NULL;
	sequence->profiles = NULL;
	
	sequence->active = 0;
	sequence->unsaved_changes = 1;
	sequence->position = NULL;
	
	sequence->view_page = NULL;
	
	sequence->fname = NULL;
	
	sequence->listings = NULL;
	
	sequence->main_sequence = 0;
	
	sequence->representations = NULL;
	
	return NO_ERROR;
}

int sequence_append_profile(m_int_sequence *sequence, m_profile *profile)
{
	if (!sequence || !profile)
		return ERR_NULL_PTR;
	
	seq_profile_ll *new_node = malloc(sizeof(seq_profile_ll));
	
	if (!new_node)
		return ERR_ALLOC_FAIL;
	
	new_node->data = profile;
	new_node->next = NULL;
	new_node->prev = NULL;
	
	if (!sequence->profiles)
	{
		sequence->profiles = new_node;
		return NO_ERROR;
	}
	
	seq_profile_ll *current = sequence->profiles;
	
	while (current)
	{
		if (!current->next)
			break;
		current = current->next;
	}
	
	current->next = new_node;
	new_node->prev = current;
	
	profile->sequence = sequence;
	
	return NO_ERROR;
}


seq_profile_ll *sequence_append_profile_rp(m_int_sequence *sequence, m_profile *profile)
{
	if (!sequence || !profile)
		return NULL;
	
	seq_profile_ll *new_node = malloc(sizeof(seq_profile_ll));
	
	if (!new_node)
		return NULL;
	
	new_node->data = profile;
	new_node->next = NULL;
	new_node->prev = NULL;
	
	if (!sequence->profiles)
	{
		sequence->profiles = new_node;
		return new_node;
	}
	
	seq_profile_ll *current = sequence->profiles;
	
	while (current)
	{
		if (!current->next)
			break;
		current = current->next;
	}
	
	current->next = new_node;
	new_node->prev = current;
	
	return new_node;
}

int sequence_move_profile(m_int_sequence *sequence, int pos, int new_pos)
{
	if (!sequence)
		return ERR_NULL_PTR;
	
	if (pos < 0 || new_pos < 0)
		return ERR_BAD_ARGS;
	
	seq_profile_ll *target = sequence->profiles;
	seq_profile_ll *prev = NULL;
	
	for (int i = 0; i < pos; i++)
	{
		prev = target;
		if (target)
		{
			target = target->next;
		}
	}
	
	if (!target)
		return ERR_BAD_ARGS;
	
	if (prev)
	{
		prev->next = target->next;
	}
	
	if (new_pos == 0)
	{
		target->next = sequence->profiles;
		sequence->profiles = target;
		return NO_ERROR;
	}
	
	seq_profile_ll *current = sequence->profiles;
	
	for (int i = 0; i < new_pos; i++)
	{
		prev = current;
		if (current)
		{
			current = current->next;
		}
	}
	
	if (prev)
	{
		target->next = prev->next;
		prev->next = target;
		return NO_ERROR;
	}
	else
	{
		return ERR_BAD_ARGS;
	}
}

void free_sequence(m_int_sequence *sequence)
{
	
}

int m_int_sequence_add_menu_listing(m_int_sequence *sequence, m_int_menu_item *listing)
{
	if (!sequence || !listing)
		return ERR_NULL_PTR;
	
	m_int_menu_item_pll *nl = m_int_menu_item_pll_append(sequence->listings, listing);
	
	if (nl)
		sequence->listings = nl;
	else
		return ERR_ALLOC_FAIL;
	
	return NO_ERROR;
}


int m_sequence_begin(m_int_sequence *sequence)
{
	if (!sequence)
		return ERR_NULL_PTR;
	
	if (!sequence->profiles)
	{
		printf("Error: empty sequence\n");
		return ERR_BAD_ARGS;
	}
	
	if (!sequence->profiles)
	{
		printf("Sequence is empty !\n");
		return NO_ERROR;
	}
	
	global_cxt.sequence = sequence;
	sequence->active = 1;
	
	set_active_profile(sequence->profiles->data);
	
	sequence->position = sequence->profiles;
	
	m_sequence_update_representations(sequence);
	
	return NO_ERROR;
}


int m_sequence_regress(m_int_sequence *sequence)
{
	if (!sequence)
		return ERR_NULL_PTR;
	
	printf("regressing sequence\n");
	
	if (!sequence->profiles)
	{
		printf("Error: empty sequence\n");
		return ERR_BAD_ARGS;
	}
	
	if (!sequence->active || !sequence->position)
	{
		printf("Error: sequence not active\n");
		return ERR_BAD_ARGS;
	}
	
	if (!sequence->position->prev)
	{
		printf("Can't regress sequence; sequence at start already\n");
		return NO_ERROR;
	}
	
	sequence->position = sequence->position->prev;
	
	set_active_profile(sequence->position->data);
	
	return NO_ERROR;
}

int m_sequence_advance(m_int_sequence *sequence)
{
	if (!sequence)
		return ERR_NULL_PTR;
	
	printf("advancing sequence\n");
	
	if (!sequence->profiles)
	{
		printf("Error: empty sequence\n");
		return ERR_BAD_ARGS;
	}
	
	if (!sequence->active || !sequence->position)
	{
		printf("Error: sequence not active\n");
		return ERR_BAD_ARGS;
	}
	
	if (!sequence->position->next)
	{
		printf("Can't regress sequence; sequence at end already\n");
		return NO_ERROR;
	}
	
	sequence->position = sequence->position->next;
	
	set_active_profile(sequence->position->data);
	
	return NO_ERROR;
}

int m_sequence_stop(m_int_sequence *sequence)
{
	if (!sequence)
		return ERR_NULL_PTR;
	
	global_cxt.sequence = NULL;
	sequence->active = 0;
	
	set_active_profile(NULL);
	
	sequence->position = NULL;
	
	m_sequence_update_representations(sequence);
	
	return NO_ERROR;
}


int m_sequence_stop_from_profile(m_int_sequence *sequence)
{
	if (!sequence)
		return ERR_NULL_PTR;
	
	global_cxt.sequence = NULL;
	sequence->active = 0;
	
	sequence->position = NULL;
	
	m_sequence_update_representations(sequence);
	
	return NO_ERROR;
}

int m_sequence_activate_at(m_int_sequence *sequence, m_profile *profile)
{
	if (!sequence)
		return ERR_NULL_PTR;
	
	seq_profile_ll *current = sequence->profiles;
	
	while (current)
	{
		if (current->data && current->data == profile)
		{
			sequence->position = current;
			sequence->active = 1;
			
			m_sequence_update_representations(sequence);
			return NO_ERROR;
		}
	}
	
	return ERR_BAD_ARGS;
}

int m_sequence_add_representation(m_int_sequence *sequence, m_representation *rep)
{
	if (!sequence)
		return ERR_NULL_PTR;
	
	m_representation_pll *nl = m_representation_pll_append(sequence->representations, rep);
	
	if (nl)
		sequence->representations = nl;
	else
		return ERR_ALLOC_FAIL;
	
	return NO_ERROR;
}

int m_sequence_update_representations(m_int_sequence *sequence)
{
	if (!sequence)
		return ERR_NULL_PTR;
	
	if (sequence->representations)
		queue_representation_list_update(sequence->representations);
	
	return NO_ERROR;
}

#include "m_int.h"

IMPLEMENT_LINKED_PTR_LIST(m_int_sequence);

int init_m_int_sequence(m_int_sequence *seq)
{
	if (!seq)
		return ERR_NULL_PTR;
	
	seq->name 	  = NULL;
	seq->profiles = NULL;
	
	seq->active = 0;
	seq->unsaved_changes = 1;
	seq->position = NULL;
	
	seq->view_page = NULL;
	
	seq->fname = NULL;
	
	seq->listings = NULL;
	
	seq->main_sequence = 0;
	
	return NO_ERROR;
}

int sequence_append_profile(m_int_sequence *seq, m_profile *profile)
{
	if (!seq || !profile)
		return ERR_NULL_PTR;
	
	seq_profile_ll *new_node = malloc(sizeof(seq_profile_ll));
	
	if (!new_node)
		return ERR_ALLOC_FAIL;
	
	new_node->data = profile;
	new_node->next = NULL;
	new_node->prev = NULL;
	
	if (!seq->profiles)
	{
		seq->profiles = new_node;
		return NO_ERROR;
	}
	
	seq_profile_ll *current = seq->profiles;
	
	while (current)
	{
		if (!current->next)
			break;
		current = current->next;
	}
	
	current->next = new_node;
	new_node->prev = current;
	
	profile->sequence = seq;
	
	return NO_ERROR;
}


seq_profile_ll *sequence_append_profile_rp(m_int_sequence *seq, m_profile *profile)
{
	if (!seq || !profile)
		return NULL;
	
	seq_profile_ll *new_node = malloc(sizeof(seq_profile_ll));
	
	if (!new_node)
		return NULL;
	
	new_node->data = profile;
	new_node->next = NULL;
	new_node->prev = NULL;
	
	if (!seq->profiles)
	{
		seq->profiles = new_node;
		return new_node;
	}
	
	seq_profile_ll *current = seq->profiles;
	
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

int sequence_move_profile(m_int_sequence *seq, int pos, int new_pos)
{
	if (!seq)
		return ERR_NULL_PTR;
	
	if (pos < 0 || new_pos < 0)
		return ERR_BAD_ARGS;
	
	seq_profile_ll *target = seq->profiles;
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
		target->next = seq->profiles;
		seq->profiles = target;
		return NO_ERROR;
	}
	
	seq_profile_ll *current = seq->profiles;
	
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

void free_sequence(m_int_sequence *seq)
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


int m_sequence_begin(m_int_sequence *seq)
{
	if (!seq)
		return ERR_NULL_PTR;
	
	if (!seq->profiles)
	{
		printf("Error: empty sequence\n");
		return ERR_BAD_ARGS;
	}
	
	if (!seq->profiles)
	{
		printf("Sequence is empty !\n");
		return NO_ERROR;
	}
	
	global_cxt.sequence = seq;
	seq->active = 1;
	
	set_active_profile(seq->profiles->data);
	
	seq->position = seq->profiles;
	
	return NO_ERROR;
}


int m_sequence_regress(m_int_sequence *seq)
{
	if (!seq)
		return ERR_NULL_PTR;
	
	printf("regressing sequence\n");
	
	if (!seq->profiles)
	{
		printf("Error: empty sequence\n");
		return ERR_BAD_ARGS;
	}
	
	if (!seq->active || !seq->position)
	{
		printf("Error: sequence not active\n");
		return ERR_BAD_ARGS;
	}
	
	if (!seq->position->prev)
	{
		printf("Can't regress sequence; sequence at start already\n");
		return NO_ERROR;
	}
	
	seq->position = seq->position->prev;
	
	set_active_profile(seq->position->data);
	
	return NO_ERROR;
}

int m_sequence_advance(m_int_sequence *seq)
{
	if (!seq)
		return ERR_NULL_PTR;
	
	printf("advancing sequence\n");
	
	if (!seq->profiles)
	{
		printf("Error: empty sequence\n");
		return ERR_BAD_ARGS;
	}
	
	if (!seq->active || !seq->position)
	{
		printf("Error: sequence not active\n");
		return ERR_BAD_ARGS;
	}
	
	if (!seq->position->next)
	{
		printf("Can't regress sequence; sequence at end already\n");
		return NO_ERROR;
	}
	
	seq->position = seq->position->next;
	
	set_active_profile(seq->position->data);
	
	return NO_ERROR;
}

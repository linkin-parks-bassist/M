#ifndef M_INT_SEQUENCE_H_
#define M_INT_SEQUENCE_H_

typedef struct seq_profile_ll
{
	m_int_profile *data;
	struct seq_profile_ll *next;
	struct seq_profile_ll *prev;
	
	m_int_glide_button *button;
} seq_profile_ll;

typedef struct
{
	char *name;
	int active;
	
	seq_profile_ll *profiles;
	seq_profile_ll *position;
	
	m_int_ui_page *view_page;
	
	struct m_int_menu_item_ptr_linked_list *listings;
	char *fname;
	
	int unsaved_changes;
} m_int_sequence;

DECLARE_LINKED_PTR_LIST(m_int_sequence);

typedef m_int_sequence_ptr_linked_list sequence_ll;

int init_m_int_sequence(m_int_sequence *seq);

int sequence_append_profile(m_int_sequence *seq, m_int_profile *profile);
seq_profile_ll *sequence_append_profile_rp(m_int_sequence *seq, m_int_profile *profile);
int sequence_move_profile(m_int_sequence *seq, int pos, int new_pos);

int m_int_sequence_add_menu_listing(m_int_sequence *seq, struct m_int_menu_item *listing);

void free_sequence(m_int_sequence *seq);

int m_sequence_begin(m_int_sequence *seq);
int m_sequence_regress(m_int_sequence *seq);
int m_sequence_advance(m_int_sequence *seq);

#endif

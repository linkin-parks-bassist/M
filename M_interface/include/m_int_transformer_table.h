#ifndef M_INT_TRANS_TABLE_H_
#define M_INT_TRANS_TABLE_H_

typedef struct
{
	char *name;
	uint16_t type;
} m_int_trans_desc;

extern const int N_TRANSFORMER_TYPES;
extern m_int_trans_desc transformer_table[];

#endif

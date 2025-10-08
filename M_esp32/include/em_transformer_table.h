#ifndef EM_TRANS_TABLE_H_
#define EM_TRANS_TABLE_H_

typedef struct
{
	char *name;
	uint16_t type;
} em_trans_desc;

extern const int N_TRANSFORMER_TYPES;
extern em_trans_desc transformer_table[];

#endif

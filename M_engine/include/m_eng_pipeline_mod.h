#ifndef M_ENG_PIPELINE_MOD_H_
#define M_ENG_PIPELINE_MOD_H_

#define PIPELINE_MOD_APPEND_TRANSFORMER 		0
#define PIPELINE_MOD_MOVE_TRANSFORMER			1
#define PIPELINE_MOD_REMOVE_TRANSFORMER			2
#define PIPELINE_MOD_CHANGE_TRANSFORMER_SETTING	3

typedef struct m_pipeline_mod
{
	int type;
	uint16_t tid;
	uint16_t data;
	int16_t sdata;
} m_pipeline_mod;

int init_pipeline_mod(m_pipeline_mod *mod);

m_pipeline_mod create_pipeline_mod_append_transformer			(uint16_t type);
m_pipeline_mod create_pipeline_mod_move_transformer			(uint16_t tid, uint16_t position);
m_pipeline_mod create_pipeline_mod_remove_transformer			(uint16_t tid);
m_pipeline_mod create_pipeline_mod_change_transformer_setting (uint16_t tid, uint16_t setting_id, int16_t new_value);

int apply_pipeline_mod(m_pipeline *pipeline, m_pipeline_mod mod, int *err_code);

const char *pipeline_mod_type_string(int type);

DECLARE_LINKED_LIST(m_pipeline_mod);

#endif

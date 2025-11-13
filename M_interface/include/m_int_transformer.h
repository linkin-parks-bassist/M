#ifndef M_INT_TRANSFORMER_H_
#define M_INT_TRANSFORMER_H_

int init_transformer(m_transformer *trans);

int transformer_set_id(m_transformer *trans, uint16_t profile_id, uint16_t transformer_id);

m_parameter *transformer_add_parameter(m_transformer *trans);
m_setting *transformer_add_setting(m_transformer *trans);

int init_default_transformer_by_type(m_transformer *trans, uint16_t type, uint16_t profile_id, uint16_t transformer_id);

int transformer_init_ui_page(m_transformer *trans, m_ui_page *parent);

void add_transformer_from_menu(lv_event_t *e);

int request_append_transformer(uint16_t type, m_transformer *local);
void transformer_receive_id(et_msg message, te_msg response);

int clone_transformer(m_transformer *dest, m_transformer *src);
void free_transformer(m_transformer *trans);

m_parameter *transformer_get_parameter(m_transformer *trans, int n);
m_setting *transformer_get_setting(m_transformer *trans, int n);

#endif

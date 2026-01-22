#ifndef M_INT_TRANSFORMER_H_
#define M_INT_TRANSFORMER_H_

#include <lvgl.h>

struct m_profile;
struct m_ui_page;

#include "m_effect.h"
#include "m_comms.h"

typedef struct m_transformer
{
	uint16_t type;
	uint16_t id;
	
	m_parameter wet_mix;
	
	m_setting band_mode;
	m_parameter band_lp_cutoff;
	m_parameter band_hp_cutoff;
	m_parameter band_center;
	m_parameter band_width;
	
	int position;
	int block_position;
	
	m_parameter_pll *parameters;
	m_setting_pll *settings;
	
	struct m_profile *profile;
	struct m_ui_page *view_page;
	
	m_effect_desc *eff;
} m_transformer;

const char *m_transformer_name(m_transformer *trans);

DECLARE_LINKED_PTR_LIST(m_transformer);

int init_transformer(m_transformer *trans);

int transformer_set_id(m_transformer *trans, uint16_t profile_id, uint16_t transformer_id);

m_parameter *transformer_add_parameter(m_transformer *trans);
m_setting *transformer_add_setting(m_transformer *trans);

int init_default_transformer_by_type(m_transformer *trans, uint16_t type, uint16_t profile_id, uint16_t transformer_id);
int init_transformer_from_effect_desc(m_transformer *trans, m_effect_desc *eff);

int transformer_init_ui_page(m_transformer *trans, struct m_ui_page *parent);

void add_transformer_from_menu(lv_event_t *e);

int request_append_transformer(uint16_t type, m_transformer *local);
void transformer_receive_id(m_message message, m_response response);

int clone_transformer(m_transformer *dest, m_transformer *src);
void free_transformer(m_transformer *trans);

m_parameter *transformer_get_parameter(m_transformer *trans, int n);
m_setting *transformer_get_setting(m_transformer *trans, int n);

int m_fpga_transfer_batch_append_transformer(
		m_transformer *trans,
		const m_fpga_resource_report *cxt,
		m_fpga_resource_report *report,
		m_fpga_transfer_batch *batch
	);


int m_transformer_update_fpga_registers(m_transformer *trans);

#endif

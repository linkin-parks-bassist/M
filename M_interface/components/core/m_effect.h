#ifndef M_EFFECT_H_
#define M_EFFECT_H_

#include "m_linked_list.h"

#include "m_int_fpga.h"
#include "m_int_parameter.h"

#define M_DSP_BLOCK_N_REGS 2

#define M_DERIVED_QUANTITY_CONST_FLT 0
#define M_DERIVED_QUANTITY_CONST_INT 1
#define M_DERIVED_QUANTITY_REFERENCE 2
#define M_DERIVED_QUANTITY_FCALL_ADD 3
#define M_DERIVED_QUANTITY_FCALL_SUB 4
#define M_DERIVED_QUANTITY_FCALL_MUL 5
#define M_DERIVED_QUANTITY_FCALL_DIV 6
#define M_DERIVED_QUANTITY_FCALL_ABS 7
#define M_DERIVED_QUANTITY_FCALL_SQR 8
#define M_DERIVED_QUANTITY_FCALL_EXP 9
#define M_DERIVED_QUANTITY_FCALL_LOG 10
#define M_DERIVED_QUANTITY_FCALL_POW 11
#define M_DERIVED_QUANTITY_FCALL_SIN 12
#define M_DERIVED_QUANTITY_FCALL_COS 13
#define M_DERIVED_QUANTITY_FCALL_TAN 14

#define M_DERIVED_QUANTITY_TYPE_MAX_VAL M_DERIVED_QUANTITY_FCALL_TAN

typedef struct m_derived_quantity
{
	int type;
	union {
		float val_float;
		int16_t val_int;
		char *ref_name;
		struct m_derived_quantity **sub_dqs;
	} val;
} m_derived_quantity;

m_derived_quantity *new_m_derived_quantity_from_string(char *str);

int m_derived_quantity_references_param(m_derived_quantity *dq, m_parameter *param);
float m_derived_quantity_compute(m_derived_quantity *dq, m_parameter_pll *params);

#define DSP_REG_FORMAT_LITERAL 0xFFFF

typedef struct
{
	int reg;
	int format;
	
	m_derived_quantity *dq;
} m_dsp_register_val;

m_dsp_register_val *new_m_dsp_register_val(int reg, int format, m_derived_quantity *dq);
m_dsp_register_val *new_m_dsp_register_val_literal(int reg, int16_t literal_value);

typedef struct
{
	m_dsp_block_instr instr;
	m_dsp_register_val *reg_vals[M_DSP_BLOCK_N_REGS];
} m_dsp_block;

m_dsp_block *new_m_dsp_block();
m_dsp_block *new_m_dsp_block_with_instr(m_dsp_block_instr instr);
int m_dsp_block_add_register_val(m_dsp_block *blk, int i, m_dsp_register_val *p);
int m_dsp_block_uses_param(m_dsp_block *blk, m_parameter *param);

#define M_FPGA_RESOURCE_DDELAY 0

typedef struct {
	int type;
	int data;
} m_fpga_resource_req;

m_fpga_resource_req *new_fpga_resource_req(int type, int data);

typedef struct
{
	const char *name;
	
	int n_blocks;
	int block_array_len;
	m_dsp_block **blocks;
	
	int n_params;
	int param_array_len;
	m_parameter **params;
	
	int n_res_reqs;
	int res_req_array_len;
	m_fpga_resource_req **res_reqs;
} m_effect_desc;

m_effect_desc *new_m_effect_desc(const char *name);
int m_effect_desc_add_block(m_effect_desc *eff, m_dsp_block *blk);
int m_effect_desc_add_param(m_effect_desc *eff, m_parameter *param);
int m_effect_desc_add_resource_request(m_effect_desc *eff, m_fpga_resource_req *req);

int m_effect_desc_add_register_val(m_effect_desc *eff, int block_no, int reg, int format, char *expr);
int m_effect_desc_add_register_val_literal(m_effect_desc *eff, int block_no, int reg, uint16_t val);

int m_fpga_transfer_batch_append_effect_register_writes(
		m_fpga_transfer_batch *batch,
		m_effect_desc *eff, int blocks_start,
		m_parameter_pll *params
	);
int m_fpga_transfer_batch_append_effect_register_updates(
		m_fpga_transfer_batch *batch,
		m_effect_desc *eff, int blocks_start,
		m_parameter_pll *params
	);

DECLARE_LINKED_PTR_LIST(m_effect_desc);

int m_fpga_transfer_batch_append_effect(
		m_effect_desc *eff,
		const m_fpga_resource_report *cxt,
		m_fpga_resource_report *report,
		m_parameter_pll *params,
		m_fpga_transfer_batch *batch
	);

m_effect_desc *create_amplifier_eff_desc();
m_effect_desc *create_delay_eff_desc();
m_effect_desc *create_flanger_eff_desc();

#endif

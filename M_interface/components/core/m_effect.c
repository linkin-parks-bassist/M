#include <string.h>
#include <math.h>

#include "m_error_codes.h"
#include "m_alloc.h"

#include "m_int_hfunc.h"
#include "m_int_parameter.h"
#include "m_int_transformer.h"
#include "m_effect.h"

IMPLEMENT_LINKED_PTR_LIST(m_effect_desc);

m_dsp_block *new_m_dsp_block()
{
	m_dsp_block *result = (m_dsp_block*)m_alloc(sizeof(m_dsp_block));
	
	for (int i = 0; i < N_BLOCKS_REGS; i++)
		result->reg_vals[i] = NULL;
	
	return result;
}

m_dsp_block *new_m_dsp_block_with_instr(m_dsp_block_instr instr)
{
	m_dsp_block *result = (m_dsp_block*)m_alloc(sizeof(m_dsp_block));
	
	for (int i = 0; i < N_BLOCKS_REGS; i++)
		result->reg_vals[i] = NULL;
	
	result->instr = instr;
	
	return result;
}

int m_dsp_m_dsp_block_add_register_val(m_dsp_block *blk, int i, m_dsp_register_val *p)
{
	if (!blk || !p || i < 0 || i > N_BLOCKS_REGS)
		return ERR_NULL_PTR;

	p->reg = i;
	
	blk->reg_vals[i] = p;
	return NO_ERROR;
}

// Compute arity in the sense of, how many sub-dq's it uses.
// this is used to guard accesses to the array dq->sub_dqs.
// therefore, if in doubt, return 0.
// it should not return x if dq->val.sub_dq[x-1]
// is not a valid pointer to another dq
int m_derived_quantity_arity(m_derived_quantity *dq)
{
	if (!dq) return NO_ERROR;
	
	// if the type is nonsense, return 0
	if (dq->type < 0 || dq->type > M_DERIVED_QUANTITY_TYPE_MAX_VAL)
		return NO_ERROR;
	
	if (dq->type == M_DERIVED_QUANTITY_CONST_FLT || dq->type == M_DERIVED_QUANTITY_CONST_INT || dq->type == M_DERIVED_QUANTITY_REFERENCE)
		return NO_ERROR;
	
	// arity is at least 1 if we reach this point. there are more arity 1 types than arity 2, but also arity 2 will
	// be more common, bc arithmetic. and none of arity 3. therefore, check the arity 2 case, then return 1 otherwise
	if (dq->type == M_DERIVED_QUANTITY_FCALL_ADD
	 || dq->type == M_DERIVED_QUANTITY_FCALL_SUB
	 || dq->type == M_DERIVED_QUANTITY_FCALL_MUL
	 || dq->type == M_DERIVED_QUANTITY_FCALL_DIV
	 || dq->type == M_DERIVED_QUANTITY_FCALL_POW)
		return 2;
	
	return ERR_NULL_PTR;
}

#define DQ_MAX_RECURSION_DEPTH 256

static float m_derived_quantity_compute_rec(m_derived_quantity *dq, m_parameter_pll *params, int depth)
{
	if (!dq) return 0.0;
	
	if (dq->type == M_DERIVED_QUANTITY_REFERENCE)
	{
		if (!dq->val.ref_name || !params)
			return 0.0;
		
		m_parameter_pll *current;
		m_parameter *param;
		
		int cmplen = strlen(dq->val.ref_name) + 1;
		
		current = params;
		
		while (current)
		{
			param = current->data;
			if (param && param->name_internal)
			{
				if (strncmp(dq->val.ref_name, param->name_internal, cmplen) == 0)
					return param->value;
			}
			
			current = current->next;
		}
		
		return 0.0;
	}
	
	if (dq->type == M_DERIVED_QUANTITY_CONST_FLT)
	{
		return dq->val.val_float;
	}
	else if (dq->type == M_DERIVED_QUANTITY_CONST_INT)
	{
		return (float)dq->val.val_int;
	}
	
	if (depth > DQ_MAX_RECURSION_DEPTH || !dq->val.sub_dqs)
		return 0.0;
	
	float x = 0.0;
	float ret_val = 0.0;
	
	switch (dq->type)
	{
		case M_DERIVED_QUANTITY_FCALL_ADD:
			ret_val = (m_derived_quantity_compute_rec(dq->val.sub_dqs[0], params, depth + 1) + m_derived_quantity_compute_rec(dq->val.sub_dqs[1], params, depth + 1));
			break;

		case M_DERIVED_QUANTITY_FCALL_SUB:
			ret_val = m_derived_quantity_compute_rec(dq->val.sub_dqs[0], params, depth + 1) - m_derived_quantity_compute_rec(dq->val.sub_dqs[1], params, depth + 1);
			break;

		case M_DERIVED_QUANTITY_FCALL_MUL:
			ret_val = m_derived_quantity_compute_rec(dq->val.sub_dqs[0], params, depth + 1) * m_derived_quantity_compute_rec(dq->val.sub_dqs[1], params, depth + 1);
			break;

		case M_DERIVED_QUANTITY_FCALL_DIV:
			x = m_derived_quantity_compute_rec(dq->val.sub_dqs[1], params, depth + 1);
			
			if (fabsf(x) < 1e-20)
				return 0.0; // avoid division by zero by just returning 0 lol. idk. what else to do?
			
			ret_val = m_derived_quantity_compute_rec(dq->val.sub_dqs[0], params, depth + 1) / x;
			break;

		case M_DERIVED_QUANTITY_FCALL_ABS:
			ret_val = fabs(m_derived_quantity_compute_rec(dq->val.sub_dqs[0], params, depth + 1));
			break;

		case M_DERIVED_QUANTITY_FCALL_SQR: x = m_derived_quantity_compute_rec(dq->val.sub_dqs[0], params, depth + 1); ret_val = x * x;
			break;

		case M_DERIVED_QUANTITY_FCALL_EXP:
			ret_val = exp(m_derived_quantity_compute_rec(dq->val.sub_dqs[0], params, depth + 1));
			break;

		case M_DERIVED_QUANTITY_FCALL_LOG:
			ret_val = log(m_derived_quantity_compute_rec(dq->val.sub_dqs[0], params, depth + 1));
			break;

		case M_DERIVED_QUANTITY_FCALL_POW:
			ret_val = pow(m_derived_quantity_compute_rec(dq->val.sub_dqs[0], params, depth + 1),
						  m_derived_quantity_compute_rec(dq->val.sub_dqs[1], params, depth + 1));
			break;
		case M_DERIVED_QUANTITY_FCALL_SIN:
			ret_val = sin(m_derived_quantity_compute_rec(dq->val.sub_dqs[0], params, depth + 1));
			break;

		case M_DERIVED_QUANTITY_FCALL_COS:
			ret_val = cos(m_derived_quantity_compute_rec(dq->val.sub_dqs[0], params, depth + 1));
			break;

		case M_DERIVED_QUANTITY_FCALL_TAN:
			ret_val = tan(m_derived_quantity_compute_rec(dq->val.sub_dqs[0], params, depth + 1));
			break;
	}
	
	return ret_val;
}

float m_derived_quantity_compute(m_derived_quantity *dq, m_parameter_pll *params)
{
	return m_derived_quantity_compute_rec(dq, params, 0);
}

int m_derived_quantity_references_param_rec(m_derived_quantity *dq, m_parameter *param, int depth)
{
	if (!dq || !param)
		return NO_ERROR;
	
	if (!param->name_internal)
		return NO_ERROR;
	
	int arity = m_derived_quantity_arity(dq);
	
	if (arity == 0)
	{
		if (dq->type != M_DERIVED_QUANTITY_REFERENCE)
			return NO_ERROR;
	
		if (!dq->val.ref_name)
				return NO_ERROR;
			
		return (strncmp(dq->val.ref_name, param->name_internal, strlen(dq->val.ref_name) + 1) == 0);
	}
	
	if (depth > DQ_MAX_RECURSION_DEPTH)
		return NO_ERROR;
	
	for (int i = 0; i < arity; i++)
	{
		if (m_derived_quantity_references_param_rec(dq->val.sub_dqs[i], param, depth + 1))
			return ERR_NULL_PTR;
	}
	
	return NO_ERROR;
}

int m_derived_quantity_references_param(m_derived_quantity *dq, m_parameter *param)
{
	return m_derived_quantity_references_param_rec(dq, param, 0);
}

int m_dsp_block_uses_param(m_dsp_block *blk, m_parameter *param)
{
	if (!blk || !param)
		return NO_ERROR;
	
	for (int i = 0; i < M_DSP_BLOCK_N_REGS; i++)
	{
		if (blk->reg_vals[i])
		{
			if (m_derived_quantity_references_param(blk->reg_vals[i]->dq, param))
				return ERR_NULL_PTR;
		}
	}
	
	return NO_ERROR;
}

int m_fpga_transfer_batch_append_block_register_write(m_fpga_transfer_batch *batch, int block_no, m_dsp_register_val *reg_val, m_parameter_pll *params)
{
	if (!batch)
		return ERR_NULL_PTR;
	
	if (!reg_val)
		return ERR_NULL_PTR;
	
	if (!reg_val->dq)
		return ERR_BAD_ARGS;
	
	int ret_val;
	
	if ((ret_val = m_fpga_batch_append(batch, COMMAND_WRITE_BLOCK_REG)) != NO_ERROR) return ret_val;
	
	if (N_BLOCKS > 255)
	{
		if ((ret_val = m_fpga_batch_append(batch, (block_no & 0xFF00) >> 8)) != NO_ERROR) return ret_val;
	}
	
	if ((ret_val = m_fpga_batch_append(batch, block_no & 0x00FF)) != NO_ERROR) return ret_val;
	if ((ret_val = m_fpga_batch_append(batch, reg_val->reg)) 	  != NO_ERROR) return ret_val;
	
	int16_t s;
	
	if (reg_val->format == DSP_REG_FORMAT_LITERAL)
	{
		s = reg_val->dq->val.val_int;
	}
	else
	{
		float v = m_derived_quantity_compute(reg_val->dq, params);
		
		s = float_to_q_nminus1(v, reg_val->format);
	}
	
	if ((ret_val = m_fpga_batch_append(batch, (s & 0xFF00) >> 8)) != NO_ERROR) return ret_val;
	if ((ret_val = m_fpga_batch_append(batch, (s & 0x00FF))) 	  != NO_ERROR) return ret_val;
	
	return NO_ERROR;
}

int m_fpga_transfer_batch_append_block_register_writes(m_fpga_transfer_batch *batch, m_dsp_block *blk, int blk_index, m_parameter_pll *params)
{
	if (!batch || !blk)
		return ERR_NULL_PTR;
	
	int ret_val;
	
	for (int j = 0; j < N_BLOCKS_REGS; j++)
	{
		if (blk->reg_vals[j])
		{
			if ((ret_val = m_fpga_transfer_batch_append_block_register_write(batch, blk_index, blk->reg_vals[j], params)) != NO_ERROR)
				return ret_val;
		}
	}
	
	return NO_ERROR;
}

int m_dsp_block_instr_encode_resource_aware(const m_fpga_resource_report *cxt, m_fpga_resource_report *local, m_dsp_block *blk, uint32_t *out)
{
	if (!cxt || !local || !blk || !out)
		return ERR_NULL_PTR;
	
	local->blocks = 0;
	local->memory = 0;
	local->sdelay = 0;
	local->ddelay = 0;
	
	m_dsp_block_instr rectified = blk->instr;
	
	if (m_dsp_block_instr_format(blk->instr) == INSTR_FORMAT_B)
	{
		switch (blk->instr.opcode)
		{
			case BLOCK_INSTR_DELAY:
				rectified.res_addr += cxt->ddelay;
				local->ddelay = blk->instr.res_addr + 1;
				break;
			
			case BLOCK_INSTR_SAVE:
			case BLOCK_INSTR_LOAD:
				rectified.res_addr += cxt->memory;
				local->memory = blk->instr.res_addr + 1;
				break;
		}
	}
	
	*out = m_encode_dsp_block_instr(rectified);
	
	local->blocks = 1;
	
	return NO_ERROR;
}

int m_dsp_blocks_encode_resource_aware(const m_fpga_resource_report *cxt, m_fpga_resource_report *report, m_dsp_block **blocks, int n, uint32_t *out)
{
	if (!cxt || !report || !blocks || !out)
		return ERR_NULL_PTR;
	
	int ret_val;
	m_fpga_resource_report local;
	
	for (int i = 0; i < n; i++)
	{
		if (!blocks[i])
			continue;
		
		ret_val = m_dsp_block_instr_encode_resource_aware(cxt, &local, blocks[i], &out[i]);
		
		report->blocks += local.blocks;
		
		report->memory 	= (local.memory > report->memory) ? local.memory : report->memory;
		report->sdelay 	= (local.sdelay > report->sdelay) ? local.sdelay : report->sdelay;
		report->ddelay 	= (local.ddelay > report->ddelay) ? local.ddelay : report->ddelay;
	}
	
	return NO_ERROR;
}

int m_fpga_transfer_batch_append_effect_register_writes(
		m_fpga_transfer_batch *batch,
		m_effect_desc *eff, int blocks_start,
		m_parameter_pll *params
	)
{
	if (!eff || !batch)
		return ERR_NULL_PTR;
	
	if (!eff->blocks)
		return ERR_BAD_ARGS;
	
	for (int i = 0; i < eff->n_blocks; i++)
	{
		if (eff->blocks[i])
			m_fpga_transfer_batch_append_block_register_writes(batch, eff->blocks[i], blocks_start + i, params);
	}
	
	return NO_ERROR;
}

int m_fpga_transfer_batch_append_effect(
		m_effect_desc *eff,
		const m_fpga_resource_report *cxt,
		m_fpga_resource_report *report,
		m_parameter_pll *params,
		m_fpga_transfer_batch *batch
	)
{
	if (!eff || !cxt || !report || !batch)
		return ERR_NULL_PTR;
	
	if (eff->n_blocks == 0)
		return NO_ERROR;
	
	if (!eff->blocks || eff->n_blocks > N_BLOCKS)
		return ERR_BAD_ARGS;
	
	uint32_t instr_seq[eff->n_blocks];
	
	*report = m_empty_fpga_resource_report();
	
	m_dsp_blocks_encode_resource_aware(cxt, report, eff->blocks, eff->n_blocks, instr_seq);
	
	int ret_val;
	
	int block_n;
	for (int i = 0; i < eff->n_blocks; i++)
	{
		block_n = i + cxt->blocks;
		
		if ((ret_val = m_fpga_batch_append(batch, COMMAND_WRITE_BLOCK_INSTR)) != NO_ERROR) return ret_val;
		if (N_BLOCKS > 255)
		{
			if ((ret_val = m_fpga_batch_append(batch, (block_n & 0xFF00) >> 8)) != NO_ERROR) return ret_val;
		}
		if ((ret_val = m_fpga_batch_append(batch, block_n & 0x00FF)) != NO_ERROR) return ret_val;
		
		if ((ret_val = m_fpga_batch_append(batch, (instr_seq[i] & 0xFF000000) >> 24)) != NO_ERROR) return ret_val;
		if ((ret_val = m_fpga_batch_append(batch, (instr_seq[i] & 0x00FF0000) >> 16)) != NO_ERROR) return ret_val;
		if ((ret_val = m_fpga_batch_append(batch, (instr_seq[i] & 0x0000FF00) >> 8 )) != NO_ERROR) return ret_val;
		if ((ret_val = m_fpga_batch_append(batch, (instr_seq[i] & 0x000000FF) >> 0 )) != NO_ERROR) return ret_val;
	}
	
	if ((ret_val = m_fpga_transfer_batch_append_effect_register_writes(batch, eff, cxt->blocks, params)) != NO_ERROR) return ret_val;
	
	return NO_ERROR;
}

/*
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
*/

m_derived_quantity m_derived_quantity_const_float(float v)
{
	m_derived_quantity result;
	result.type = M_DERIVED_QUANTITY_CONST_FLT;
	result.val.val_float = v;
	return result;
}

m_derived_quantity m_derived_quantity_const_int(int v)
{
	m_derived_quantity result;
	result.type = M_DERIVED_QUANTITY_CONST_FLT;
	result.val.val_int = v;
	return result;
}

m_derived_quantity *new_m_derived_quantity_const_float(float v)
{
	m_derived_quantity *result = m_alloc(sizeof(m_derived_quantity));
	
	if (!result)
		return NULL;
	
	*result = m_derived_quantity_const_float(v);
	
	return result;
}


m_derived_quantity *new_m_derived_quantity_const_int(int v)
{
	m_derived_quantity *result = m_alloc(sizeof(m_derived_quantity));
	
	if (!result)
		return NULL;
	
	*result = m_derived_quantity_const_int(v);
	
	return result;
}

m_derived_quantity *new_m_derived_quantity_from_string_rec(char *str, char **next)
{
	if (!str)
		return NULL;
	
	m_derived_quantity *dq = (m_derived_quantity*)m_alloc(sizeof(m_derived_quantity));
	
	if (!dq)
		return NULL;
	
	dq->type = M_DERIVED_QUANTITY_CONST_FLT;
	dq->val.val_float = 0.0;
	
	int pos = 0;
	
	int bufpos = 0;
	int len = strlen(str);
	
	char buf[len];
	
	int state = 0;
	char c;
	
	int arithmetic = 0;
	int unary_call = 0;
	int binary_call = 0;
	int type = 0;
	
	char *sub_next = NULL;
	
	while (pos < len)
	{
		c = str[pos];
		
		switch (state)
		{
			case -1:
				m_free(dq);
				return NULL;
				
			case 0:
				if (c == ' ')
					break;
				
				if (c == '(')
				{
					pos++;
					continue;
				}
				
				if (c == 0)
				{
					state = -1;
				}
				else if (c == '+')
				{
					dq->type = M_DERIVED_QUANTITY_FCALL_ADD;
					binary_call = 1;
				}
				else if (c == '-')
				{
					dq->type = M_DERIVED_QUANTITY_FCALL_SUB;
					binary_call = 1;
				}
				else if (c == '*')
				{
					dq->type = M_DERIVED_QUANTITY_FCALL_MUL;
					binary_call = 1;
				}
				else if (c == '/')
				{
					dq->type = M_DERIVED_QUANTITY_FCALL_DIV;
					binary_call = 1;
				}
				else if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_')
				{
					state = 1;
					buf[0] = c;
					bufpos = 1;
				}
				else if ('0' <= c && c <= '9')
				{
					state = 2;
					buf[0] = c;
					bufpos = 1;
				}
				else
				{
					state = -1;
				}
				
				break;
				
			case 1:
				if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9') || c == '_')
				{
					buf[bufpos++] = c;
				}
				else if (c == ' ' || c == ')' || c == 0)
				{
					buf[bufpos++] = 0;
					
					if (strcmp(buf, "abs") == 0)
					{
						dq->type = M_DERIVED_QUANTITY_FCALL_ABS;
						unary_call = 1;
					}
					else if (strcmp(buf, "sqr") == 0)
					{
						dq->type = M_DERIVED_QUANTITY_FCALL_SQR;
						unary_call = 1;
					}
					else if (strcmp(buf, "exp") == 0)
					{
						dq->type = M_DERIVED_QUANTITY_FCALL_EXP;
						unary_call = 1;
					}
					else if (strcmp(buf, "log") == 0)
					{
						dq->type = M_DERIVED_QUANTITY_FCALL_LOG;
						unary_call = 1;
					}
					else if (strcmp(buf, "sin") == 0)
					{
						dq->type = M_DERIVED_QUANTITY_FCALL_SIN;
						unary_call = 1;
					}
					else if (strcmp(buf, "cos") == 0)
					{
						dq->type = M_DERIVED_QUANTITY_FCALL_COS;
						unary_call = 1;
					}
					else if (strcmp(buf, "tan") == 0)
					{
						dq->type = M_DERIVED_QUANTITY_FCALL_TAN;
						unary_call = 1;
					}
					else  if (strcmp(buf, "pow") == 0)
					{
						dq->type = M_DERIVED_QUANTITY_FCALL_POW;
						binary_call = 1;
					}
					else
					{
						dq->type = M_DERIVED_QUANTITY_REFERENCE;
						dq->val.ref_name = m_strndup(buf, len);
						if (next) *next = &str[pos+1];
						return dq;
					}
				}
				else
				{
					state = -1;
				}
				
				break;
			
			case 2:
				if (('0' <= c && c <= '9') || c == '.')
				{
					buf[bufpos++] = c;
				}
				else if (c == ' ' || c == ')' || c == ',' || c == 0)
				{
					buf[bufpos] = 0;
					
					dq->type = M_DERIVED_QUANTITY_CONST_FLT;
					dq->val.val_float = strtof(buf, NULL);
					
					if (next)
						*next = &str[pos+1];
					
					return dq;
				}
				else
				{
					state = -1;
				}
				
				break;
			
			default:
				state = -1;
				break;
		}
		
		if (unary_call)
		{
			dq->val.sub_dqs = (m_derived_quantity**)m_alloc(sizeof(m_derived_quantity*) * 1);
			if (!dq->val.sub_dqs) // alloc fail; delete everything and bail
			{
				m_free(dq);
				return NULL;
			}
			dq->val.sub_dqs[0] = new_m_derived_quantity_from_string_rec(&str[pos+1], next);
			
			return dq;
		}
		
		if (binary_call)
		{
			dq->val.sub_dqs = (m_derived_quantity**)m_alloc(sizeof(m_derived_quantity*) * 2);
			if (!dq->val.sub_dqs) // alloc fail; delete everything and bail
			{
				m_free(dq);
				return NULL;
			}
			dq->val.sub_dqs[0] = new_m_derived_quantity_from_string_rec(&str[pos+1], &sub_next);
			dq->val.sub_dqs[1] = new_m_derived_quantity_from_string_rec(sub_next, next);
			
			return dq;
		}
		
		pos++;
	}
	
	return dq;
}

m_derived_quantity *new_m_derived_quantity_from_string(char *str)
{
	return new_m_derived_quantity_from_string_rec(str, NULL);
}

/*
typedef struct
{
	int reg;
	int format;
	
	m_derived_quantity dq;
} m_dsp_register_val;
*/

/*
typedef struct
{
	m_dsp_block_instr instr;
	m_dsp_register_val *reg_vals[M_DSP_BLOCK_N_REGS];
} m_dsp_block;
*/

/*
typedef struct
{
	const char *name;
	
	int n_blocks;
	int block_array_len;
	m_dsp_block **blocks;
	
	int n_params;
	int param_array_len;
	m_parameter **params;
} m_effect_desc;
*/

m_effect_desc *new_m_effect_desc(const char *name)
{
	printf("Creating effect descriptor...\n");
	m_effect_desc *result = (m_effect_desc*)m_alloc(sizeof(m_effect_desc));
	
	printf("Sucessfully allocated struct\n");
	if (!result)
		return NULL;
	
	result->blocks = (m_dsp_block**)m_alloc(sizeof(m_dsp_block*) * 32);
	
	if (!result->blocks)
	{
		m_free(result);
		return NULL;
	}
	
	printf("Sucessfully allocated block array\n");
	
	result->block_array_len = 32;
	result->n_blocks = 0;
	
	for (int i = 0; i < result->block_array_len; i++)
		result->blocks[i] = NULL;
	
	result->params = (m_parameter**)m_alloc(sizeof(m_parameter*) * 32);
	
	if (!result->params)
	{
		m_free(result->blocks);
		m_free(result);
		return NULL;
	}
	
	printf("Sucesffully allocated parameter array\n");
	
	result->param_array_len = 32;
	result->n_params = 0;
	
	for (int i = 0; i < result->param_array_len; i++)
		result->params[i] = NULL;
	
	result->name = name;
	
	printf("Returning %p\n", result);
	
	return result;
}

int m_effect_desc_add_block(m_effect_desc *eff, m_dsp_block *blk)
{
	if (!eff || !blk)
		return ERR_NULL_PTR;
	
	if (eff->n_blocks < eff->block_array_len)
	{
		eff->blocks[eff->n_blocks++] = blk;
	}
	else
	{
		return ERR_UNIMPLEMENTED; // dont care at the moment
	}
	
	return NO_ERROR;
}

int m_effect_desc_add_param(m_effect_desc *eff, m_parameter *param)
{
	printf("m_effect_desc_add_param, eff = %p, param = %p\n", eff, param);
	if (!eff || !param)
		return ERR_NULL_PTR;
	
	printf("eff->n_params = %d\n", eff->n_params);
	
	if (eff->n_params < eff->param_array_len)
	{
		printf("There is room. Adding\n");
		eff->params[eff->n_params++] = param;
		printf("eff->n_params = %d\n", eff->n_params);
	}
	else
	{
		printf("Oh no!\n");
		return ERR_UNIMPLEMENTED; // dont care at the moment
	}
	
	return NO_ERROR;
}

m_dsp_register_val *new_m_dsp_register_val(int reg, int format, m_derived_quantity *dq)
{
	if (!dq)
		return NULL;
	
	m_dsp_register_val *result = (m_dsp_register_val*)m_alloc(sizeof(m_dsp_register_val));
	
	if (!result)
		return NULL;
	
	result->reg = reg;
	result->format = format;
	result->dq = dq;
	
	return result;
}

m_dsp_register_val *new_m_dsp_register_val_literal(int reg, int16_t literal_value)
{
	m_dsp_register_val *result = (m_dsp_register_val*)m_alloc(sizeof(m_dsp_register_val));
	
	result->reg = reg;
	result->format = DSP_REG_FORMAT_LITERAL;
	
	result->dq = new_m_derived_quantity_const_int(literal_value);
	
	return result;
}

int m_effect_desc_set_register(m_effect_desc *eff, int block_no, int reg, int format, char *expr)
{
	if (!eff)
		return ERR_NULL_PTR;
	
	if (block_no < 0 || block_no > eff->n_blocks || reg < 0 || reg > N_BLOCKS_REGS)
		return ERR_BAD_ARGS;
	
	m_dsp_register_val *bp = new_m_dsp_register_val(reg, format, new_m_derived_quantity_from_string(expr));
	
	return m_dsp_m_dsp_block_add_register_val(eff->blocks[block_no], reg, bp);
}

int m_effect_desc_add_add_cc(m_effect_desc *eff, int src_a, int src_b, int dest)
{
	if (!eff)
		return ERR_NULL_PTR;
	
	m_dsp_block *blk = new_m_dsp_block_with_instr(m_dsp_block_instr_type_a_str(BLOCK_INSTR_ADD, src_a, src_b, 0, dest, 0, 0, 0, 0, 0, 0));
	m_effect_desc_add_block(eff, blk);
	
	return NO_ERROR;
}

int m_effect_desc_add_mul_cc(m_effect_desc *eff, int src_a, int src_b, int dest)
{
	if (!eff)
		return ERR_NULL_PTR;
	
	m_dsp_block *blk = new_m_dsp_block_with_instr(m_dsp_block_instr_type_a_str(BLOCK_INSTR_MUL, src_a, src_b, 0, dest, 0, 0, 0, 0, 0, 0));
	m_effect_desc_add_block(eff, blk);
	
	return NO_ERROR;
}

int m_effect_desc_add_const_mul_rc(m_effect_desc *eff, int src_a, float v, int dest)
{
	if (!eff)
		return ERR_NULL_PTR;
	
	if (fabsf(v) > (float)(1 << SHIFT_WIDTH))
		return 2;
	
	float fmt = 1.0;
	int shift = 0;
	
	while (fabsf(v) > fmt)
	{
		fmt *= 2.0;
		shift++;
	}
	
	m_dsp_block *blk = new_m_dsp_block_with_instr(m_dsp_block_instr_type_a_str(BLOCK_INSTR_MUL, src_a, 0, 0, dest, 0, 1, 0, 0, shift, 0));
	m_dsp_block_add_register_val(blk, 0, new_m_dsp_register_val(0, shift, new_m_derived_quantity_const_float(v)));
	m_effect_desc_add_block(eff, blk);
	
	return NO_ERROR;
}

int m_effect_desc_add_mad_ccc(m_effect_desc *eff, int src_a, int src_b, int src_c, int dest)
{
	if (!eff)
		return ERR_NULL_PTR;
	
	m_dsp_block *blk = new_m_dsp_block_with_instr(m_dsp_block_instr_type_a_str(BLOCK_INSTR_MUL, src_a, src_b, src_c, dest, 0, 0, 0, 0, 0, 0));
	m_effect_desc_add_block(eff, blk);
	
	return NO_ERROR;
}

int m_effect_desc_add_mad_ccr(m_effect_desc *eff, int src_a, float v, int src_c, int dest)
{
	if (!eff)
		return ERR_NULL_PTR;
	
	if (fabsf(v) > (float)(1 << SHIFT_WIDTH))
		return 2;
	
	float fmt = 1.0;
	int shift = 0;
	
	while (fabsf(v) > fmt)
	{
		fmt *= 2.0;
		shift++;
	}
	
	m_dsp_block *blk = new_m_dsp_block_with_instr(m_dsp_block_instr_type_a_str(BLOCK_INSTR_MUL, src_a, 0, src_c, 0, 0, 1, 0, 0, shift, 0));
	m_dsp_block_add_register_val(blk, 0, new_m_dsp_register_val(0, shift, new_m_derived_quantity_const_float(v)));
	m_effect_desc_add_block(eff, blk);
	
	return NO_ERROR;
}

int m_effect_desc_add_macz_cc(m_effect_desc *eff, int src_a, int src_b)
{
	if (!eff)
		return ERR_NULL_PTR;
	
	m_dsp_block *blk = new_m_dsp_block_with_instr(m_dsp_block_instr_type_a_str(BLOCK_INSTR_MACZ, src_a, src_b, 0, 0, 0, 0, 0, 0, 0, 0));
	m_effect_desc_add_block(eff, blk);
	
	return NO_ERROR;
}

int m_effect_desc_add_macz_rc(m_effect_desc *eff, int src_a, float v)
{
	if (!eff)
		return ERR_NULL_PTR;
	
	if (fabsf(v) > (float)(1 << SHIFT_WIDTH))
		return 2;
	
	float fmt = 1.0;
	int shift = 0;
	
	while (fabsf(v) > fmt)
	{
		fmt *= 2.0;
		shift++;
	}
	
	m_dsp_block *blk = new_m_dsp_block_with_instr(m_dsp_block_instr_type_a_str(BLOCK_INSTR_MACZ, src_a, 0, 0, 0, 0, 1, 0, 0, 0, 0));
	m_dsp_block_add_register_val(blk, 0, new_m_dsp_register_val(0, shift, new_m_derived_quantity_const_float(v)));
	m_effect_desc_add_block(eff, blk);
	
	return NO_ERROR;
}

int m_effect_desc_add_mac_cc(m_effect_desc *eff, int src_a, int src_b)
{
	if (!eff)
		return ERR_NULL_PTR;
	
	m_dsp_block *blk = new_m_dsp_block_with_instr(m_dsp_block_instr_type_a_str(BLOCK_INSTR_MAC, src_a, src_b, 0, 0, 0, 0, 0, 0, 0, 0));
	m_effect_desc_add_block(eff, blk);
	
	return NO_ERROR;
}

int m_effect_desc_add_mac_cc_ns(m_effect_desc *eff, int src_a, int src_b)
{
	if (!eff)
		return ERR_NULL_PTR;
	
	m_dsp_block *blk = new_m_dsp_block_with_instr(m_dsp_block_instr_type_a_str(BLOCK_INSTR_MAC, src_a, src_b, 0, 0, 0, 0, 0, 0, 0, 1));
	m_effect_desc_add_block(eff, blk);
	
	return NO_ERROR;
}

int m_effect_desc_add_mac_rc(m_effect_desc *eff, int src_a, float v)
{
	if (!eff)
		return ERR_NULL_PTR;
	
	if (fabsf(v) > (float)(1 << SHIFT_WIDTH))
		return 2;
	
	float fmt = 1.0;
	int shift = 0;
	
	while (fabsf(v) > fmt)
	{
		fmt *= 2.0;
		shift++;
	}
	
	m_dsp_block *blk = new_m_dsp_block_with_instr(m_dsp_block_instr_type_a_str(BLOCK_INSTR_MAC, src_a, 0, 0, 0, 0, 1, 0, 0, shift, 0));
	m_dsp_block_add_register_val(blk, 0, new_m_dsp_register_val(0, shift, new_m_derived_quantity_const_float(v)));
	m_effect_desc_add_block(eff, blk);
	
	return NO_ERROR;
}

int m_effect_desc_add_mac_rc_ns(m_effect_desc *eff, int src_a, float v)
{
	if (!eff)
		return ERR_NULL_PTR;
	
	if (fabsf(v) > (float)(1 << SHIFT_WIDTH))
		return ERR_BAD_ARGS;
	
	float fmt = 1.0;
	int shift = 0;
	
	while (fabsf(v) > fmt)
	{
		fmt *= 2.0;
		shift++;
	}
	
	m_dsp_block *blk = new_m_dsp_block_with_instr(m_dsp_block_instr_type_a_str(BLOCK_INSTR_MAC, src_a, 0, 0, 0, 0, 1, 0, 0, shift, 1));
	m_dsp_block_add_register_val(blk, 0, new_m_dsp_register_val(0, shift, new_m_derived_quantity_const_float(v)));
	m_effect_desc_add_block(eff, blk);
	
	return NO_ERROR;
}

int m_effect_desc_add_mac_rc_ns_sh(m_effect_desc *eff, int src_a, float v, int shift)
{
	if (!eff)
		return ERR_NULL_PTR;
	
	m_dsp_block *blk = new_m_dsp_block_with_instr(m_dsp_block_instr_type_a_str(BLOCK_INSTR_MAC, src_a, 0, 0, 0, 0, 1, 0, 0, shift, 1));
	m_dsp_block_add_register_val(blk, 0, new_m_dsp_register_val(0, shift, new_m_derived_quantity_const_float(v)));
	m_effect_desc_add_block(eff, blk);
	
	return NO_ERROR;
}

int m_effect_desc_add_load(m_effect_desc *eff, int addr, int dest)
{
	if (!eff)
		return ERR_NULL_PTR;
	
	m_dsp_block *blk = new_m_dsp_block_with_instr(m_dsp_block_instr_type_b_str(BLOCK_INSTR_LOAD, 0, 0, dest, addr));
	m_effect_desc_add_block(eff, blk);
	
	return NO_ERROR;
}

int m_effect_desc_add_save(m_effect_desc *eff, int src_a, int addr)
{
	if (!eff)
		return ERR_NULL_PTR;
	
	m_dsp_block *blk = new_m_dsp_block_with_instr(m_dsp_block_instr_type_b_str(BLOCK_INSTR_SAVE, src_a, 0, 0, addr));
	m_effect_desc_add_block(eff, blk);
	
	return NO_ERROR;
}

int m_effect_desc_add_mov_acc(m_effect_desc *eff, int dest)
{
	if (!eff)
		return ERR_NULL_PTR;
	
	m_dsp_block *blk = new_m_dsp_block_with_instr(m_dsp_block_instr_type_a_str(BLOCK_INSTR_MOV_ACC, 0, 0, 0, dest, 0, 0, 0, 0, 0, 0));
	m_effect_desc_add_block(eff, blk);
	
	return NO_ERROR;
}

int m_effect_desc_add_mov_acc_sh(m_effect_desc *eff, int dest, int shift)
{
	if (!eff)
		return ERR_NULL_PTR;
	
	m_dsp_block *blk = new_m_dsp_block_with_instr(m_dsp_block_instr_type_a_str(BLOCK_INSTR_MOV_ACC, 0, 0, 0, dest, 0, 0, 0, 0, 1, 0));
	m_effect_desc_add_block(eff, blk);
	
	return NO_ERROR;
}

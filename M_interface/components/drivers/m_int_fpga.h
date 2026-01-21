#ifndef M_INT_FPGA_H_
#define M_INT_FPGA_H_

#define BLOCK_INSTR_NOP 	0
#define BLOCK_INSTR_ADD 	1
#define BLOCK_INSTR_SUB 	2
#define BLOCK_INSTR_LSH 	3
#define BLOCK_INSTR_RSH 	4
#define BLOCK_INSTR_ARSH 	5
#define BLOCK_INSTR_MUL 	6
#define BLOCK_INSTR_MAD		7
#define BLOCK_INSTR_ABS		8
#define BLOCK_INSTR_LUT		9
#define BLOCK_INSTR_ENVD 	10
#define BLOCK_INSTR_DELAY 	11
#define BLOCK_INSTR_SAVE 	12
#define BLOCK_INSTR_LOAD	13
#define BLOCK_INSTR_MOV		14
#define BLOCK_INSTR_CLAMP	15

#define BLOCK_INSTR_OP_WIDTH 5
#define BLOCK_REG_ADDR_WIDTH 4

#define BLOCK_INSTR_OP_TYPE_START 	(4 * BLOCK_REG_ADDR_WIDTH + BLOCK_INSTR_OP_WIDTH)
#define BLOCK_INSTR_PMS_START		(BLOCK_INSTR_OP_TYPE_START + 5)

#define BLOCK_INSTR(opcode, src_a, src_b, src_c, dest, a_reg, b_reg, c_reg, dest_reg, shift) \
	BLOCK_INSTR_S(opcode, src_a, src_b, src_c, dest, a_reg, b_reg, c_reg, dest_reg, shift, 1)
	
#define BLOCK_INSTR_S(opcode, src_a, src_b, src_c, dest, a_reg, b_reg, c_reg, dest_reg, shift, sat) (\
		  ((uint32_t)opcode) \
		| ((uint32_t)src_a 	<< (0 * BLOCK_REG_ADDR_WIDTH + BLOCK_INSTR_OP_WIDTH    )) \
		| ((uint32_t)src_b 	<< (1 * BLOCK_REG_ADDR_WIDTH + BLOCK_INSTR_OP_WIDTH    )) \
		| ((uint32_t)src_c 	<< (2 * BLOCK_REG_ADDR_WIDTH + BLOCK_INSTR_OP_WIDTH    )) \
		| ((uint32_t)dest  	<< (3 * BLOCK_REG_ADDR_WIDTH + BLOCK_INSTR_OP_WIDTH    )) \
		| ((uint32_t)a_reg 	<< (BLOCK_INSTR_OP_TYPE_START + 0)) \
		| ((uint32_t)b_reg 	<< (BLOCK_INSTR_OP_TYPE_START + 1)) \
		| ((uint32_t)c_reg 	<< (BLOCK_INSTR_OP_TYPE_START + 2)) \
		| ((uint32_t)dest_reg	<< (BLOCK_INSTR_OP_TYPE_START + 3)) \
		| ((uint32_t)shift << (BLOCK_INSTR_PMS_START)) \
		| ((uint32_t)sat   << (BLOCK_INSTR_OP_TYPE_START + 4)))

#define COMMAND_WRITE_BLOCK_INSTR 	0b10010000
#define COMMAND_WRITE_BLOCK_REG 	0b11100000
#define COMMAND_UPDATE_BLOCK_REG 	0b11101001
#define COMMAND_ALLOC_SRAM_DELAY 	0b00100000
#define COMMAND_SWAP_PIPELINES 		0b00000001
#define COMMAND_RESET_PIPELINE 		0b00001001
#define COMMAND_SET_INPUT_GAIN 		0b00000010
#define COMMAND_SET_OUTPUT_GAIN 	0b00000011

void m_fpga_comms_task(void *param);

int m_send_bytes_to_fpga(uint8_t *buf, int n);
int m_send_byte_to_fpga(uint8_t byte);

int m_fpga_send_byte(uint8_t byte);

int16_t float_to_q_nminus1(float x, int shift);
int16_t float_to_q15(float x);

void m_fpga_set_input_gain(float gain_db);
void m_fpga_set_output_gain(float gain_db);

#endif

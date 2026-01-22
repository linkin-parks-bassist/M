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
#define BLOCK_INSTR_MACZ	16
#define BLOCK_INSTR_MAC		17
#define BLOCK_INSTR_MOV_ACC	18

#define BLOCK_INSTR_OP_WIDTH 5
#define BLOCK_REG_ADDR_WIDTH 4

#define BLOCK_INSTR_OP_TYPE_START 	(4 * BLOCK_REG_ADDR_WIDTH + BLOCK_INSTR_OP_WIDTH)
#define BLOCK_INSTR_PMS_START		(BLOCK_INSTR_OP_TYPE_START + 5)
#define SHIFT_WIDTH 4

#define BLOCK_RES_ADDR_WIDTH	8

#define COMMAND_WRITE_BLOCK_INSTR 	0b10010000
#define COMMAND_WRITE_BLOCK_REG 	0b11100000
#define COMMAND_UPDATE_BLOCK_REG 	0b11101001
#define COMMAND_ALLOC_SRAM_DELAY 	0b00100000
#define COMMAND_SWAP_PIPELINES 		0b00000001
#define COMMAND_RESET_PIPELINE 		0b00001001
#define COMMAND_SET_INPUT_GAIN 		0b00000010
#define COMMAND_SET_OUTPUT_GAIN 	0b00000011

#define INSTR_FORMAT_A 0
#define INSTR_FORMAT_B 1

#define N_BLOCKS 255
#define N_BLOCKS_REGS 2

typedef struct
{
	int opcode;
	int src_a;
	int src_b;
	int src_c;
	int dest;
	
	int src_a_reg;
	int src_b_reg;
	int src_c_reg;
	int dest_reg;
	
	int shift;
	int sat;
	
	int res_addr;
} m_dsp_block_instr;

int m_dsp_block_instr_format(m_dsp_block_instr instr);
uint32_t m_encode_dsp_block_instr(m_dsp_block_instr instr);

m_dsp_block_instr m_dsp_block_instr_type_a_str(int opcode, int src_a, int src_b, int src_c, int dest, int a_reg, int b_reg, int c_reg, int dest_reg, int shift, int sat);
m_dsp_block_instr m_dsp_block_instr_type_b_str(int opcode, int src_a, int src_b, int dest, int res_addr);

typedef struct
{
	int len;
	uint8_t *buf;
	int buf_len;
} m_fpga_transfer_batch;

m_fpga_transfer_batch m_new_fpga_transfer_batch();

int m_send_bytes_to_fpga(uint8_t *buf, int n);
int m_send_byte_to_fpga(uint8_t byte);

int m_fpga_send_byte(uint8_t byte);

void m_fpga_set_input_gain(float gain_db);
void m_fpga_set_output_gain(float gain_db);

int m_fpga_batch_append(m_fpga_transfer_batch *seq, uint8_t byte);

int m_fpga_transfer_batch_send(m_fpga_transfer_batch batch);

typedef struct
{
	unsigned int blocks;
	unsigned int memory;
	unsigned int sdelay;
	unsigned int ddelay;
} m_fpga_resource_report;

m_fpga_resource_report m_empty_fpga_resource_report();
int m_fpga_resource_report_integrate(m_fpga_resource_report *cxt, m_fpga_resource_report *local);

void m_fpga_comms_task(void *param);

#endif

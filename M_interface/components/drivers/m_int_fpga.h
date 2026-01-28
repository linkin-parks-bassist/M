#ifndef M_INT_FPGA_H_
#define M_INT_FPGA_H_

#define BLOCK_INSTR_NOP 		0
#define BLOCK_INSTR_ADD 		1
#define BLOCK_INSTR_SUB 		2
#define BLOCK_INSTR_LSH 		3
#define BLOCK_INSTR_RSH 		4
#define BLOCK_INSTR_ARSH 		5
#define BLOCK_INSTR_MUL 		6
#define BLOCK_INSTR_MADD		7
#define BLOCK_INSTR_ABS			8
#define BLOCK_INSTR_LUT			9
#define BLOCK_INSTR_ENVD 		10
#define BLOCK_INSTR_DELAY_READ 	11
#define BLOCK_INSTR_DELAY_WRITE 12
#define BLOCK_INSTR_SAVE 		13
#define BLOCK_INSTR_LOAD		14
#define BLOCK_INSTR_MOV			15
#define BLOCK_INSTR_CLAMP		16
#define BLOCK_INSTR_MACZ		17
#define BLOCK_INSTR_MAC			18
#define BLOCK_INSTR_MOV_ACC		19
#define BLOCK_INSTR_LINTERP		20
#define BLOCK_INSTR_FRAC_DELAY	21
#define BLOCK_INSTR_LOAD_ACC	22
#define BLOCK_INSTR_SAVE_ACC	23
#define BLOCK_INSTR_ACC			24
#define BLOCK_INSTR_CLEAR_ACC	25
#define BLOCK_INSTR_MOV_UACC	26

#define NO_SHIFT 255

#define STOCK_LUTS 2

#define BLOCK_INSTR_WIDTH	32
#define BLOCK_INSTR_OP_WIDTH 5
#define BLOCK_REG_ADDR_WIDTH 4

#define BLOCK_INSTR_OP_TYPE_START 	(4 * BLOCK_REG_ADDR_WIDTH + BLOCK_INSTR_OP_WIDTH)
#define BLOCK_INSTR_PMS_START		(BLOCK_INSTR_OP_TYPE_START + 5)
#define SHIFT_WIDTH 4

#define BLOCK_RES_ADDR_WIDTH		8

#define COMMAND_WRITE_BLOCK_INSTR 	0b10010000
#define COMMAND_WRITE_BLOCK_REG 	0b11100000
#define COMMAND_UPDATE_BLOCK_REG 	0b11101000
#define COMMAND_ALLOC_SRAM_DELAY 	0b00100000
#define COMMAND_SWAP_PIPELINES 		0b00000001
#define COMMAND_RESET_PIPELINE 		0b00001001
#define COMMAND_SET_INPUT_GAIN 		0b00000010
#define COMMAND_SET_OUTPUT_GAIN 	0b00000011

#define NO_SHIFT 255

#define INSTR_FORMAT_A 0
#define INSTR_FORMAT_B 1

#define N_BLOCKS 255
#define N_BLOCKS_REGS 2

#define M_DSP_BLOCK_N_REGS 2

typedef struct
{
	int opcode;
	int src_a;
	int src_a_reg;
	int src_b;
	int src_b_reg;
	int src_c;
	int src_c_reg;
	int dest;
	
	int no_shift;
	int shift;
	int sat;
	
	int res_addr;
} m_dsp_block_instr;

int m_dsp_block_instr_format(m_dsp_block_instr instr);
uint32_t m_encode_dsp_block_instr(m_dsp_block_instr instr);

m_dsp_block_instr m_dsp_block_instr_type_a_str(int opcode, int src_a, int a_reg, int src_b, int b_reg, int src_c, int c_reg, int dest,  int shift, int sat);
m_dsp_block_instr m_dsp_block_instr_type_b_str(int opcode, int src_a, int a_reg, int src_b, int b_reg, int dest, int res_addr);

m_dsp_block_instr m_dsp_block_instr_nop();
m_dsp_block_instr m_dsp_block_instr_add(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_add_unsat(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_sub(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_sub_unsat(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_lsh(int src_a, int src_a_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_rsh(int src_a, int src_a_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_arsh(int src_a, int src_a_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_lsh4(int src_a, int src_a_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_rsh4(int src_a, int src_a_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_arsh4(int src_a, int src_a_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_lsh8(int src_a, int src_a_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_rsh8(int src_a, int src_a_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_arsh8(int src_a, int src_a_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_mul(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest, int shift);
m_dsp_block_instr m_dsp_block_instr_mul_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_mul_unsat(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_mul_unsat_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_madd(int src_a, int src_a_reg, int src_b, int src_b_reg, int src_c, int src_c_reg, int dest, int shift);
m_dsp_block_instr m_dsp_block_instr_madd_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg, int src_c, int src_c_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_madd_unsat(int src_a, int src_a_reg, int src_b, int src_b_reg, int src_c, int src_c_reg, int dest, int shift);
m_dsp_block_instr m_dsp_block_instr_madd_unsat_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg, int src_c, int src_c_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_abs(int src_a, int src_a_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_lut(int src_a, int src_a_reg, int lut, int dest);
m_dsp_block_instr m_dsp_block_instr_delay_read(int delay, int delay_reg, int buffer, int dest);
m_dsp_block_instr m_dsp_block_instr_delay_write(int src, int src_reg, int buffer);
m_dsp_block_instr m_dsp_block_instr_save(int addr, int src, int src_reg);
m_dsp_block_instr m_dsp_block_instr_load(int addr, int dest);
m_dsp_block_instr m_dsp_block_instr_mov(int src, int src_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_clamp(int src_a, int src_a_reg, int src_b, int src_b_reg, int src_c, int src_c_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_macz(int src_a, int src_a_reg, int src_b, int src_b_reg);
m_dsp_block_instr m_dsp_block_instr_macz_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg);
m_dsp_block_instr m_dsp_block_instr_mac(int src_a, int src_a_reg, int src_b, int src_b_reg);
m_dsp_block_instr m_dsp_block_instr_mac_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg);
m_dsp_block_instr m_dsp_block_instr_mov_acc(int dest);
m_dsp_block_instr m_dsp_block_instr_linterp(int src_a, int src_a_reg, int src_b, int src_b_reg, int src_c, int src_c_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_frac_delay(int buffer, int dest);
m_dsp_block_instr m_dsp_block_instr_load_acc(int addr);
m_dsp_block_instr m_dsp_block_instr_save_acc(int addr);
m_dsp_block_instr m_dsp_block_instr_acc(int src_a, int src_a_reg);
m_dsp_block_instr m_dsp_block_instr_accu(int src_a, int src_a_reg);
m_dsp_block_instr m_dsp_block_instr_clear_acc();
m_dsp_block_instr m_dsp_block_instr_mov_uacc(int dest);


typedef struct
{
	int len;
	uint8_t *buf;
	int buf_len;
} m_fpga_transfer_batch;

m_fpga_transfer_batch m_new_fpga_transfer_batch();
void m_free_fpga_transfer_batch(m_fpga_transfer_batch batch);

int m_send_bytes_to_fpga(uint8_t *buf, int n);
int m_send_byte_to_fpga(uint8_t byte);

int m_fpga_send_byte(uint8_t byte);

void m_fpga_set_input_gain(float gain_db);
void m_fpga_set_output_gain(float gain_db);

int m_fpga_batch_append(m_fpga_transfer_batch *seq, uint8_t byte);
int m_fpga_batch_append_16(m_fpga_transfer_batch *seq, uint16_t x);
int m_fpga_batch_append_32(m_fpga_transfer_batch *seq, uint32_t x);

int m_fpga_transfer_batch_send(m_fpga_transfer_batch batch);

typedef struct
{
	unsigned int blocks;
	unsigned int memory;
	unsigned int sdelay;
	unsigned int ddelay;
	unsigned int luts;
} m_fpga_resource_report;

m_fpga_resource_report m_empty_fpga_resource_report();
int m_fpga_resource_report_integrate(m_fpga_resource_report *cxt, m_fpga_resource_report *local);

void m_fpga_comms_task(void *param);

#endif

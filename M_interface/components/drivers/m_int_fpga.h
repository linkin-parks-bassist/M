#ifndef M_INT_FPGA_H_
#define M_INT_FPGA_H_

#define M_FPGA_SAMPLE_RATE 44100

//#define PRINT_TRANSFER_BATCHES
//#define PRINT_SPI_BYTES

// Do nothing. This doesn't even use a branch;
// it isn't passed on from the instruction
// fetch/decode stage
#define BLOCK_INSTR_NOP 			0

// Regular arithmetic writing to channels.
// Uses main branch
#define BLOCK_INSTR_MADD			1
#define BLOCK_INSTR_ARSH 			2

// Single stage math operations/moves, writing
// to channels. Uses MISC branch
#define BLOCK_INSTR_LSH 			3
#define BLOCK_INSTR_RSH 			4
#define BLOCK_INSTR_ABS				5
#define BLOCK_INSTR_MIN			    6
#define BLOCK_INSTR_MAX			    7
#define BLOCK_INSTR_CLAMP		    8
#define BLOCK_INSTR_MOV_ACC			9
#define BLOCK_INSTR_MOV_LACC		10
#define BLOCK_INSTR_MOV_UACC		11

#define MISC_OPCODE_MIN 3
#define N_MISC_OPS 		9

// Accumulator MAC instructions. Uses MAC branch
// _MAC_: acc = a * b + acc
// _MACZ: acc = a * b + 0
// UMAC_: a and b are treated as unsigned
//
// MAC branch is specialised as it does not
// wait on the accumulator as a dependency
// the addition is done in the commit stage
// therefore is it much faster!
#define BLOCK_INSTR_MACZ			12
#define BLOCK_INSTR_UMACZ			13
#define BLOCK_INSTR_MAC				14
#define BLOCK_INSTR_UMAC			15

// Interfacing with #resources'. Each has its own branch
#define BLOCK_INSTR_LUT_READ		16
#define BLOCK_INSTR_DELAY_READ 		17
#define BLOCK_INSTR_DELAY_WRITE 	18
#define BLOCK_INSTR_MEM_READ 		19
#define BLOCK_INSTR_MEM_WRITE		20

#define NO_SHIFT 255

#define ZERO_REGISTER_ADDR 		2
#define POS_ONE_REGISTER_ADDR  	3
#define NEG_ONE_REGISTER_ADDR   4

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
#define COMMAND_ALLOC_DELAY 		0b00100000
#define COMMAND_SWAP_PIPELINES 		0b00000001
#define COMMAND_RESET_PIPELINE 		0b00001001
#define COMMAND_SET_INPUT_GAIN 		0b00000010
#define COMMAND_SET_OUTPUT_GAIN 	0b00000011
#define COMMAND_COMMIT_REG_UPDATES 	0b00001010

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
m_dsp_block_instr m_dsp_block_instr_mul(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest, int shift);
m_dsp_block_instr m_dsp_block_instr_mul_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_mul_unsat(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest, int shift);
m_dsp_block_instr m_dsp_block_instr_mul_unsat_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_madd(int src_a, int src_a_reg, int src_b, int src_b_reg, int src_c, int src_c_reg, int dest, int shift);
m_dsp_block_instr m_dsp_block_instr_madd_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg, int src_c, int src_c_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_madd_unsat(int src_a, int src_a_reg, int src_b, int src_b_reg, int src_c, int src_c_reg, int dest, int shift);
m_dsp_block_instr m_dsp_block_instr_madd_unsat_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg, int src_c, int src_c_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_macz(int src_a, int src_a_reg, int src_b, int src_b_reg, int shift);
m_dsp_block_instr m_dsp_block_instr_macz_unsat(int src_a, int src_a_reg, int src_b, int src_b_reg, int shift);
m_dsp_block_instr m_dsp_block_instr_macz_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg);
m_dsp_block_instr m_dsp_block_instr_macz_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg);
m_dsp_block_instr m_dsp_block_instr_mac(int src_a, int src_a_reg, int src_b, int src_b_reg, int shift);
m_dsp_block_instr m_dsp_block_instr_mac_unsat(int src_a, int src_a_reg, int src_b, int src_b_reg);
m_dsp_block_instr m_dsp_block_instr_mac_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg);
m_dsp_block_instr m_dsp_block_instr_mac_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg);
m_dsp_block_instr m_dsp_block_instr_mov_acc(int dest);
m_dsp_block_instr m_dsp_block_instr_mov_acc_sh(int sh, int dest);
m_dsp_block_instr m_dsp_block_instr_mov_uacc(int dest);
m_dsp_block_instr m_dsp_block_instr_mov_lacc(int dest);

m_dsp_block_instr m_dsp_block_instr_lsh(int src_a, int src_a_reg, int shift, int dest);
m_dsp_block_instr m_dsp_block_instr_rsh(int src_a, int src_a_reg, int shift, int dest);
m_dsp_block_instr m_dsp_block_instr_arsh(int src_a, int src_a_reg, int shift, int dest);
m_dsp_block_instr m_dsp_block_instr_abs(int src_a, int src_a_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_min(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_max(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_clamp(int src_a, int src_a_reg, int src_b, int src_b_reg, int src_c, int src_c_reg, int dest);
m_dsp_block_instr m_dsp_block_instr_lut_read(int src_a, int src_a_reg, int lut, int dest);
m_dsp_block_instr m_dsp_block_instr_delay_read(int buffer, int dest);
m_dsp_block_instr m_dsp_block_instr_delay_write(int src, int src_reg, int inc, int inc_reg, int buffer);
m_dsp_block_instr m_dsp_block_instr_mem_write(int src, int src_reg, int addr);
m_dsp_block_instr m_dsp_block_instr_mem_read(int addr, int dest);


typedef struct
{
	int len;
	uint8_t *buf;
	int buf_len;
	int buffer_owned;
} m_fpga_transfer_batch;

m_fpga_transfer_batch m_new_fpga_transfer_batch();
void m_free_fpga_transfer_batch(m_fpga_transfer_batch batch);

int m_send_bytes_to_fpga(uint8_t *buf, int n);
int m_send_byte_to_fpga(uint8_t byte);

int m_fpga_send_byte(uint8_t byte);

void m_fpga_set_input_gain(float gain_db);
void m_fpga_set_output_gain(float gain_db);
void m_fpga_commit_reg_updates();

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

int m_fpga_spi_init();

#endif

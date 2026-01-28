#include <freertos/FreeRTOS.h>
#include <driver/spi_master.h>
#include <string.h>
#include <math.h>

#include "m_alloc.h"
#include "m_error_codes.h"

#include "m_int_hfunc.h"
#include "m_int_fpga.h"

#define PIN_NUM_MISO  	14
#define PIN_NUM_MOSI  	6
#define PIN_NUM_CLK   	5
#define PIN_NUM_CS		4

spi_device_handle_t spi_handle;

QueueHandle_t m_fpga_send_queue;

// IBM = "initial bit mask"; 0b000..0111...1 with "x" 1s
#define IBM(x) ((1u << (x)) - 1)
// Extracts n bits, starting at x, and shifted to the start 
#define range_bits(x, n, start) (((x) >> (start)) & IBM(n))
// Gives a word with bits y to x being the initial bits of "val"
#define place_bits(x, y, val) ((IBM((x)-(y)+1) & ((uint32_t)val)) << y) 

int m_fpga_block_opcode_format(int opcode)
{
	return (opcode == BLOCK_INSTR_DELAY_READ
		 || opcode == BLOCK_INSTR_DELAY_WRITE
		 || opcode == BLOCK_INSTR_FRAC_DELAY
		 || opcode == BLOCK_INSTR_SAVE
		 || opcode == BLOCK_INSTR_LOAD
		 || opcode == BLOCK_INSTR_LOAD_ACC
		 || opcode == BLOCK_INSTR_SAVE_ACC
		 || opcode == BLOCK_INSTR_LUT) ? INSTR_FORMAT_B : INSTR_FORMAT_A;
}
int m_dsp_block_instr_format(m_dsp_block_instr instr)
{
	return m_fpga_block_opcode_format(instr.opcode);
}

uint32_t m_encode_dsp_block_instr(m_dsp_block_instr instr)
{
	if (m_fpga_block_opcode_format(instr.opcode) == INSTR_FORMAT_B)
	{
		return place_bits(5,  0, instr.opcode) | (1 << 5)
		 | place_bits( 9,  6, instr.src_a) | ((!!instr.src_a_reg) << 10)
		 | place_bits(14, 11, instr.src_b) | ((!!instr.src_b_reg) << 15)
		 | place_bits(19, 16, instr.dest)
		 | place_bits(27, 20, instr.res_addr);
	}
	else
	{
		return place_bits( 5,  0, instr.opcode)
		 | place_bits( 9,  6, instr.src_a) | ((!!instr.src_a_reg) << 10)
		 | place_bits(14, 11, instr.src_b) | ((!!instr.src_b_reg) << 15)
		 | place_bits(19, 16, instr.src_c) | ((!!instr.src_c_reg) << 20)
		 | place_bits(24, 21, instr.dest)
		 | place_bits(29, 25, instr.shift) | ((!!instr.sat) << 30) | ((!!instr.no_shift) << 31);
	}
}

m_dsp_block_instr m_dsp_block_instr_type_a_str(int opcode, int src_a, int src_a_reg, int src_b, int src_b_reg, int src_c, int src_c_reg, int dest, int shift, int sat)
{
	m_dsp_block_instr res;
	
	res.opcode = opcode;
	res.src_a = src_a;
	res.src_a_reg = src_a_reg;
	res.src_b = src_b;
	res.src_b_reg = src_b_reg;
	res.src_c = src_c;
	res.src_c_reg = src_c_reg;
	res.dest = dest;
	
	
	res.no_shift = (shift == NO_SHIFT);
	res.shift = (shift == NO_SHIFT) ? 0 : shift;
	res.sat = sat;
	
	res.res_addr = 0;
	
	return res;
}

m_dsp_block_instr m_dsp_block_instr_type_b_str(int opcode, int src_a, int src_a_reg, int src_b, int src_b_reg, int dest, int res_addr)
{
	m_dsp_block_instr res;
	
	res.opcode = opcode;
	res.src_a = src_a;
	res.src_a_reg = src_a_reg;
	res.src_b = src_b;
	res.src_b_reg = src_b_reg;
	res.src_c = 0;
	res.src_c_reg = 0;
	res.dest = dest;
	
	res.no_shift = 0;
	res.shift = 0;
	res.sat = 0;
	
	res.res_addr = res_addr;
	
	return res;
}

m_dsp_block_instr m_dsp_block_instr_nop()
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_NOP, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_add(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_ADD, src_a, src_a_reg, src_b, src_b_reg, 0, 0, dest, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_add_unsat(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_ADD, src_a, src_a_reg, src_b, src_b_reg, 0, 0, dest, 0, 1);
}

m_dsp_block_instr m_dsp_block_instr_sub(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_SUB, src_a, src_a_reg, src_b, src_b_reg, 0, 0, dest, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_sub_unsat(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_SUB, src_a, src_a_reg, src_b, src_b_reg, 0, 0, dest, 0, 1);
}

m_dsp_block_instr m_dsp_block_instr_lsh(int src_a, int src_a_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_LSH, src_a, src_a_reg, 0, 0, 0, 0, dest, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_rsh(int src_a, int src_a_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_RSH, src_a, src_a_reg, 0, 0, 0, 0, dest, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_arsh(int src_a, int src_a_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_ARSH, src_a, src_a_reg, 0, 0, 0, 0, dest, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_lsh4(int src_a, int src_a_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_LSH, src_a, src_a_reg, 4, 0, 0, 0, dest, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_rsh4(int src_a, int src_a_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_RSH, src_a, src_a_reg, 4, 0, 0, 0, dest, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_arsh4(int src_a, int src_a_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_ARSH, src_a, src_a_reg, 4, 0, 0, 0, dest, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_lsh8(int src_a, int src_a_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_LSH, src_a, src_a_reg, 8, 0, 0, 0, dest, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_rsh8(int src_a, int src_a_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_RSH, src_a, src_a_reg, 8, 0, 0, 0, dest, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_arsh8(int src_a, int src_a_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_ARSH, src_a, src_a_reg, 8, 0, 0, 0, dest, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_mul(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest, int shift)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_MUL, src_a, src_a_reg, src_b, src_b_reg, 0, 0, dest, shift, 0);
}

m_dsp_block_instr m_dsp_block_instr_mul_unsat(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_MUL, src_a, src_a_reg, src_b, src_b_reg, 0, 0, dest, 0, 1);
}

m_dsp_block_instr m_dsp_block_instr_mul_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_MUL, src_a, src_a_reg, src_b, src_b_reg, 0, 0, dest, NO_SHIFT, 0);
}

m_dsp_block_instr m_dsp_block_instr_mul_unsat_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_MUL, src_a, src_a_reg, src_b, src_b_reg, 0, 0, dest, NO_SHIFT, 1);
}

m_dsp_block_instr m_dsp_block_instr_madd(int src_a, int src_a_reg, int src_b, int src_b_reg, int src_c, int src_c_reg, int dest, int shift)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_MADD, src_a, src_a_reg, src_b, src_b_reg, src_c, src_c_reg, dest, shift, 0);
}

m_dsp_block_instr m_dsp_block_instr_madd_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg, int src_c, int src_c_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_MADD, src_a, src_a_reg, src_b, src_b_reg, src_c, src_c_reg, dest, NO_SHIFT, 0);
}

m_dsp_block_instr m_dsp_block_instr_madd_unsat(int src_a, int src_a_reg, int src_b, int src_b_reg, int src_c, int src_c_reg, int dest, int shift)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_MADD, src_a, src_a_reg, src_b, src_b_reg, src_c, src_c_reg, dest, shift, 1);
}

m_dsp_block_instr m_dsp_block_instr_madd_unsat_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg, int src_c, int src_c_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_MADD, src_a, src_a_reg, src_b, src_b_reg, src_c, src_c_reg, dest, NO_SHIFT, 1);
}

m_dsp_block_instr m_dsp_block_instr_abs(int src_a, int src_a_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_ABS, src_a, src_a_reg, 0, 0, 0, 0, dest, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_lut(int src_a, int src_a_reg, int lut, int dest)
{
	return m_dsp_block_instr_type_b_str(BLOCK_INSTR_LUT, src_a, src_a_reg, 0, 0, dest, lut);
}

m_dsp_block_instr m_dsp_block_instr_delay_read(int delay, int delay_reg, int buffer, int dest)
{
	return m_dsp_block_instr_type_b_str(BLOCK_INSTR_DELAY_READ, delay, delay_reg, 0, 0, dest, buffer);
}

m_dsp_block_instr m_dsp_block_instr_delay_write(int src, int src_reg, int buffer)
{
	return m_dsp_block_instr_type_b_str(BLOCK_INSTR_DELAY_WRITE, src, src_reg, 0, 0, 0, buffer);
}

m_dsp_block_instr m_dsp_block_instr_save(int addr, int src, int src_reg)
{
	return m_dsp_block_instr_type_b_str(BLOCK_INSTR_SAVE, src, src_reg, 0, 0, 0, addr);
}

m_dsp_block_instr m_dsp_block_instr_load(int addr, int dest)
{
	return m_dsp_block_instr_type_b_str(BLOCK_INSTR_LOAD, 0, 0, 0, 0, dest, addr);
}

m_dsp_block_instr m_dsp_block_instr_mov(int src, int src_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_MOV, src, src_reg, 0, 0, 0, 0, dest, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_clamp(int src_a, int src_a_reg, int src_b, int src_b_reg, int src_c, int src_c_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_CLAMP, src_a, src_a_reg, src_b, src_b_reg, src_c, src_c_reg, dest, 0, 0);
}
m_dsp_block_instr m_dsp_block_instr_macz(int src_a, int src_a_reg, int src_b, int src_b_reg)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_MACZ, src_a, src_a_reg, src_b, src_b_reg, 0, 0, 0, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_macz_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_MACZ, src_a, src_a_reg, src_b, src_b_reg, 0, 0, 0, NO_SHIFT, 0);
}

m_dsp_block_instr m_dsp_block_instr_mac(int src_a, int src_a_reg, int src_b, int src_b_reg)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_MAC, src_a, src_a_reg, src_b, src_b_reg, 0, 0, 0, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_mac_noshift(int src_a, int src_a_reg, int src_b, int src_b_reg)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_MAC, src_a, src_a_reg, src_b, src_b_reg, 0, 0, 0, NO_SHIFT, 0);
}

m_dsp_block_instr m_dsp_block_instr_mov_acc(int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_MOV_ACC, 0, 0, 0, 0, 0, 0, dest, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_linterp(int src_a, int src_a_reg, int src_b, int src_b_reg, int src_c, int src_c_reg, int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_LINTERP, src_a, src_a_reg, src_b, src_b_reg, src_c, src_c_reg, dest, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_frac_delay(int buffer, int dest)
{
	return m_dsp_block_instr_type_b_str(BLOCK_INSTR_FRAC_DELAY, 0, 0, 0, 0, dest, buffer);
}

m_dsp_block_instr m_dsp_block_instr_load_acc(int addr)
{
	return m_dsp_block_instr_type_b_str(BLOCK_INSTR_LOAD_ACC, 0, 0, 0, 0, 0, addr);
}

m_dsp_block_instr m_dsp_block_instr_save_acc(int addr)
{
	return m_dsp_block_instr_type_b_str(BLOCK_INSTR_SAVE_ACC, 0, 0, 0, 0, 0, addr);
}

m_dsp_block_instr m_dsp_block_instr_acc(int src_a, int src_a_reg)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_ACC, src_a, src_a_reg, 0, 0, 0, 0, 0, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_accu(int src_a, int src_a_reg)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_ACC, src_a, src_a_reg, 0, 0, 0, 0, 0, NO_SHIFT, 0);
}

m_dsp_block_instr m_dsp_block_instr_clear_acc()
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_CLEAR_ACC, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

m_dsp_block_instr m_dsp_block_instr_mov_uacc(int dest)
{
	return m_dsp_block_instr_type_a_str(BLOCK_INSTR_MOV_UACC, 0, 0, 0, 0, 0, 0, dest, 0, 0);
}


m_dsp_block_instr m_decode_dsp_block_instr(uint32_t code)
{
	m_dsp_block_instr result;
	result.opcode = range_bits(code, 5, 0);
	int format = !!(code & (1 << 5));
	
	result.src_a 	 = range_bits(code, 4, 6);
	result.src_a_reg = !!(code & (1 << 10));
	
	result.src_b 	 = range_bits(code, 4, 11);
	result.src_b_reg = !!(code & (1 << 15));
	
	result.no_shift = 0;
	
	if (format)
	{
		result.src_c = 0;
		result.src_c_reg = 0;
		
		result.dest = range_bits(code, 4, 16);
		result.shift = 0;
		result.sat = 0;
		
		result.res_addr = range_bits(code, 8, 20);
	}
	else
	{
		result.src_c 	 = range_bits(code, 4, 16);
		result.src_c_reg = !!(code & (1 << 20));
		
		result.dest = range_bits(code, 4, 21);
		result.shift = range_bits(code, 5, 25);
		result.sat = !!(code & (1 << 30));
		result.no_shift = !!(code & (1 << 31));
		
		result.res_addr = 0;
	}

    return result;
}

int m_fpga_comms_init(void)
{
    esp_err_t ret;

    spi_bus_config_t buscfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4096,
    };

    ret = spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
    if (ret != ESP_OK)
        return ERR_SPI_FAIL;

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 1 * 1000 * 1000,
        .mode = 0,
        .spics_io_num = PIN_NUM_CS,
        .queue_size = 4,
    };

    ret = spi_bus_add_device(SPI2_HOST, &devcfg, &spi_handle);
    if (ret != ESP_OK)
        return ERR_SPI_FAIL;
    
    return NO_ERROR;
}

int m_fpga_txrx(uint8_t *tx, uint8_t *rx, size_t len)
{
    spi_transaction_t t = {
        .length = len * 8,
        .tx_buffer = tx,
        .rx_buffer = rx,
    };

	esp_err_t err = spi_device_transmit(spi_handle, &t);
	
	return (err == ESP_OK) ? NO_ERROR : ERR_SPI_FAIL;
}

int m_fpga_send_byte(uint8_t byte)
{
	return m_fpga_txrx(&byte, NULL, 1);
}

m_fpga_transfer_batch m_new_fpga_transfer_batch()
{
	m_fpga_transfer_batch seq;
	
	seq.buf = m_alloc(sizeof(uint32_t) * N_BLOCKS);
	seq.len = 0;
	seq.buf_len = (int)(sizeof(uint32_t) * N_BLOCKS);
	
	return seq;
}

void m_free_fpga_transfer_batch(m_fpga_transfer_batch batch)
{
	if (batch.buf) m_free(batch.buf);
}

int m_fpga_batch_append(m_fpga_transfer_batch *seq, uint8_t byte)
{
	if (!seq)
		return ERR_NULL_PTR;
	
	if (seq->len >= seq->buf_len)
	{
		uint8_t *new_ptr = m_realloc(seq->buf,(seq->buf_len * 2) * sizeof(uint8_t));
		
		if (!new_ptr)
			return ERR_ALLOC_FAIL;
		
		seq->buf = new_ptr;
		seq->buf_len *= 2;
	}
	
	seq->buf[seq->len++] = byte;
	
	return NO_ERROR;
}

int m_fpga_batch_append_32(m_fpga_transfer_batch *seq, uint32_t x)
{
	uint8_t bytes[4];
	
	bytes[0] = range_bits(x, 8, 24);
	bytes[1] = range_bits(x, 8, 16);
	bytes[2] = range_bits(x, 8,  8);
	bytes[3] = range_bits(x, 8,  0);
	
	int ret_val;
	
	if ((ret_val = m_fpga_batch_append(seq, bytes[0])) != NO_ERROR)
		return ret_val;
	
	if ((ret_val = m_fpga_batch_append(seq, bytes[1])) != NO_ERROR)
		return ret_val;
	
	if ((ret_val = m_fpga_batch_append(seq, bytes[2])) != NO_ERROR)
		return ret_val;
	
	if ((ret_val = m_fpga_batch_append(seq, bytes[3])) != NO_ERROR)
		return ret_val;
	
	return ret_val;
}

int m_fpga_batch_append_16(m_fpga_transfer_batch *seq, uint16_t x)
{
	uint8_t bytes[2];
	
	bytes[0] = range_bits(x, 8,  8);
	bytes[1] = range_bits(x, 8,  0);
	
	int ret_val;
	
	if ((ret_val = m_fpga_batch_append(seq, bytes[0])) != NO_ERROR)
		return ret_val;
	
	if ((ret_val = m_fpga_batch_append(seq, bytes[1])) != NO_ERROR)
		return ret_val;
	
	return ret_val;
}

int m_fpga_batch_concat(m_fpga_transfer_batch *seq, m_fpga_transfer_batch *seq2)
{
	if (!seq || !seq2)
		return ERR_NULL_PTR;
	
	if (!seq2->buf)
		return ERR_BAD_ARGS;
	
	if (!seq->buf)
	{
		seq->buf = m_alloc(seq2->len);
		
		if (!seq->buf)
			return ERR_ALLOC_FAIL;
		
		seq->buf_len = seq2->len;
		seq->len = 0;
	}
	else if (seq->len + seq2->len > seq->buf_len)
	{
		int new_len = seq->buf_len;
		while (new_len < seq->len + seq2->len)
			new_len *= 2;
		
		uint8_t *new_ptr = m_realloc(seq->buf, new_len * sizeof(uint8_t));
		
		if (!new_ptr) return ERR_ALLOC_FAIL;
		
		seq->buf_len = new_len;
		seq->buf = new_ptr;
	}
	
	for (int i = 0; i < seq2->len; i++)
		seq->buf[seq->len + i] = seq2->buf[i];
	
	seq->len += seq2->len;
	
	return 0;
}

char *m_dsp_block_opcode_to_string(uint32_t opcode)
{
	switch (opcode)
	{
		case BLOCK_INSTR_NOP: 			return (char*)"BLOCK_INSTR_NOP";
		case BLOCK_INSTR_ADD: 			return (char*)"BLOCK_INSTR_ADD";
		case BLOCK_INSTR_SUB: 			return (char*)"BLOCK_INSTR_SUB";
		case BLOCK_INSTR_LSH: 			return (char*)"BLOCK_INSTR_LSH";
		case BLOCK_INSTR_RSH: 			return (char*)"BLOCK_INSTR_RSH";
		case BLOCK_INSTR_ARSH: 			return (char*)"BLOCK_INSTR_ARSH";
		case BLOCK_INSTR_MUL: 			return (char*)"BLOCK_INSTR_MUL";
		case BLOCK_INSTR_MADD: 			return (char*)"BLOCK_INSTR_MADD";
		case BLOCK_INSTR_ABS: 			return (char*)"BLOCK_INSTR_ABS";
		case BLOCK_INSTR_LUT: 			return (char*)"BLOCK_INSTR_LUT";
		case BLOCK_INSTR_ENVD: 			return (char*)"BLOCK_INSTR_ENVD";
		case BLOCK_INSTR_DELAY_READ: 	return (char*)"BLOCK_INSTR_DELAY_READ";
		case BLOCK_INSTR_DELAY_WRITE: 	return (char*)"BLOCK_INSTR_DELAY_WRITE";
		case BLOCK_INSTR_SAVE: 			return (char*)"BLOCK_INSTR_SAVE";
		case BLOCK_INSTR_LOAD: 			return (char*)"BLOCK_INSTR_LOAD";
		case BLOCK_INSTR_MOV: 			return (char*)"BLOCK_INSTR_MOV";
		case BLOCK_INSTR_CLAMP: 		return (char*)"BLOCK_INSTR_CLAMP";
		case BLOCK_INSTR_MACZ: 			return (char*)"BLOCK_INSTR_MACZ";
		case BLOCK_INSTR_MAC: 			return (char*)"BLOCK_INSTR_MAC";
		case BLOCK_INSTR_MOV_ACC: 		return (char*)"BLOCK_INSTR_MOV_ACC";
		case BLOCK_INSTR_LINTERP: 		return (char*)"BLOCK_INSTR_LINTERP";
		case BLOCK_INSTR_FRAC_DELAY: 	return (char*)"BLOCK_INSTR_FRAC_DELAY";
		case BLOCK_INSTR_LOAD_ACC: 		return (char*)"BLOCK_INSTR_LOAD_ACC";
		case BLOCK_INSTR_SAVE_ACC: 		return (char*)"BLOCK_INSTR_SAVE_ACC";
		case BLOCK_INSTR_ACC: 			return (char*)"BLOCK_INSTR_ACC";
		case BLOCK_INSTR_CLEAR_ACC:		return (char*)"BLOCK_INSTR_CLEAR_ACC";
		case BLOCK_INSTR_MOV_UACC:		return (char*)"BLOCK_INSTR_MOV_UACC";
	}
	
	return NULL;
}

void print_instruction(m_dsp_block_instr instr)
{
	switch (m_dsp_block_instr_format(instr))
	{
		case INSTR_FORMAT_A:
			printf("Instruction = %s(%d, %d, %d, %d, %d, %d, %d %d, %d, %d)",
						m_dsp_block_opcode_to_string(instr.opcode),
						instr.src_a,
						instr.src_a_reg,
						instr.src_b,
						instr.src_b_reg,
						instr.src_c,
						instr.src_c_reg,
						instr.dest,
						
						instr.no_shift,
						instr.shift,
						instr.sat);
			break;
		
		case INSTR_FORMAT_B:
			printf("Instruction = %s(%d, %d, %d, %d, %d, 0x%04x)",
						m_dsp_block_opcode_to_string(instr.opcode),
							instr.src_a,
							instr.src_a_reg,
							instr.src_b,
							instr.src_b_reg,
							instr.dest,
							instr.res_addr);
			break;
	}
}

int m_fpga_batch_print(m_fpga_transfer_batch seq)
{
	int n = seq.len;
	
	printf("Reading out FPGA transfer batch %p (length %d)\n", seq.buf, n);
	
	if (!seq.buf)
	{
		printf("Buffer is NULL!\n");
	}
	
	if (n < 1)
	{
		printf("Batch has no bytes!\n");
	}
	
	int i = 0;
	
	int state = 0;
	int ret_state;
	int skip = 0;
	
	uint8_t byte;
	
	int ctr = 0;
	
	uint8_t reg_no = 0;
	int16_t value = 0;
	uint32_t instruction = 0;
	
	m_dsp_block_instr instr_str;
	
	while (i < n)
	{
		byte = seq.buf[i];
		
		printf("\tByte %s%d: 0x%02X. ", (n > 9 && i < 10) ? " " : "", i, byte);
		
		switch (state)
		{
			case 0: // expecting a command
				switch (byte)
				{
					
					case COMMAND_WRITE_BLOCK_INSTR:
						printf("Command WRITE_BLOCK_INSTR");
						state = 1;
						ret_state = 2;
						ctr = 0;
						instruction = 0;
						break;

					case COMMAND_WRITE_BLOCK_REG:
						printf("Command WRITE_BLOCK_REG");
						state = 1;
						ret_state = 3;
						value = 0;
						ctr = 0;
						break;

					case COMMAND_UPDATE_BLOCK_REG:
						printf("Command UPDATE_BLOCK_REG");
						state = 1;
						ret_state = 3;
						value = 0;
						ctr = 0;
						break;

					case COMMAND_ALLOC_SRAM_DELAY:
						printf("Command ALLOC_SRAM_DELAY");
						state = 4;
						value = 0;
						ctr = 0;
						break;

					case COMMAND_SWAP_PIPELINES:
						printf("Command SWAP_PIPELINES");
						break;

					case COMMAND_RESET_PIPELINE:
						printf("Command RESET_PIPELINE");
						break;

					case COMMAND_SET_INPUT_GAIN:
						printf("Command SET_INPUT_GAIN");
						break;

					case COMMAND_SET_OUTPUT_GAIN:
						printf("Command SET_OUTPUT_GAIN");
						break;

				}
				break;
			
			case 1: // expecting block number
				printf("Block number %d", byte);
				state = ret_state;
				break;
			
			case 2: // expecting instruction
				if (ctr == 3)
				{
					state = 0;
					
					instruction = (instruction << 8) | byte;
					
					instr_str = m_decode_dsp_block_instr(instruction);
					
					printf("Word: %s; ", binary_print_32(instruction));
					print_instruction(instr_str);
				}
				else
				{
					instruction = (instruction << 8) | byte;
					ctr++;
				}
				break;
			
			case 3: // expecting register number then register value
				printf("Register %d", byte);
				state = 4;
				break;
			
			case 4:
				if (ctr == 1)
				{
					state = 0;
					
					value = (value << 8) | byte;
					printf("Value: %s = %d = %f (in q1.15)", binary_print_16(value), value, (float)value / (powf(2.0, 15)));
				}
				else
				{
					value = (value << 8) | byte;
					ctr++;
				}
				break;
			
			default:
				printf("Unknown :(\n");
				return 1;
		}
		
		printf("\n");
		
		i++;
	}
	
	return 0;
}

int m_fpga_transfer_batch_send(m_fpga_transfer_batch batch)
{
	//m_fpga_batch_print(batch);
	
	return m_fpga_txrx(batch.buf, NULL, batch.len);
}

void write_block_instr(int block, uint32_t instr)
{
	m_fpga_send_byte(COMMAND_WRITE_BLOCK_INSTR);
	
	m_fpga_send_byte(block);
	
	m_fpga_send_byte((instr >> 24) & 0xFFFF);
	
	m_fpga_send_byte((instr >> 16) & 0xFFFF);
	
	m_fpga_send_byte((instr >> 8) & 0xFFFF);
	
	m_fpga_send_byte(instr & 0xFFFF);
}

void send_data_command(int command, uint16_t data)
{
	m_fpga_send_byte(command);
	m_fpga_send_byte((data >> 8) & 0xFFFF);
	m_fpga_send_byte(data & 0xFFFF);
}

void write_block_register(int block, int reg, uint16_t val)
{
	printf("Write block register: %d.%d <= %.06f\n", block, reg, (float)(val / (float)(1 << 15)));
	
	printf("Send command COMMAND_WRITE_BLOCK_REG\n");
	m_fpga_send_byte(COMMAND_WRITE_BLOCK_REG);
	
	printf("Send block number\n");
	m_fpga_send_byte(block);
	
	printf("Send register number\n");
	
	m_fpga_send_byte(reg & 0xFFFF);
	
	printf("Send value\n");
	m_fpga_send_byte((val >> 8) & 0xFFFF);
	
	m_fpga_send_byte(val & 0xFFFF);
}

#if 0

void load_biquad(int base_block,
                 float b0, float b1, float b2,
                 float a1, float a2)
{
	// channels:
	// ch0 = x[n]
	// ch1 = x[n]
	// ch2 = x[n-1]
	// ch3 = x[n-2]
	// ch4 = y[n-1]
	// ch5 = y[n-2]
	
	// move previous sample's x[n-1] to ch3
    write_block_instr(base_block + 0,
        BLOCK_INSTR_S(BLOCK_INSTR_MOV, 2, 0, 0, 3, 0, 0, 0, 0, 0, 1));
    // move previous sample's x[n] to ch2
    write_block_instr(base_block + 1,
        BLOCK_INSTR_S(BLOCK_INSTR_MOV, 1, 0, 0, 2, 0, 0, 0, 0, 0, 1));
    // copy x[n] to ch1
    write_block_instr(base_block + 2,
        BLOCK_INSTR_S(BLOCK_INSTR_MOV, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1));

	// ch0 = b0*x[n] = b0*ch0
    write_block_register(base_block + 3, 0, float_to_q_nminus1(b0, 1));
    write_block_instr(base_block + 3,
        BLOCK_INSTR_S(BLOCK_INSTR_MUL, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1));

	// ch0 = b0*x[n] + b1*x[n-1] = b1*ch2 + ch0
    write_block_register(base_block + 4, 0, float_to_q_nminus1(b1, 1));
    write_block_instr(base_block + 4,
        BLOCK_INSTR_S(BLOCK_INSTR_MADD, 2, 0, 0, 0, 0, 1, 0, 0, 0, 1));

	// ch0 = b0*x[n] + b1*x[n-1] + b2*x[n-1] = b2*ch3 + ch0
    write_block_register(base_block + 5, 0, float_to_q_nminus1(b2, 1));
    write_block_instr(base_block + 5,
        BLOCK_INSTR_S(BLOCK_INSTR_MADD, 3, 0, 0, 0, 0, 1, 0, 0, 0, 1));

	// ch0 = b0*x[n] + b1*x[n-1] + b2*x[n-1] - a1y[n-1] = -a1*ch4 + ch0
    write_block_register(base_block + 6, 0, float_to_q_nminus1(-a1, 1));
    write_block_instr(base_block + 6,
        BLOCK_INSTR_S(BLOCK_INSTR_MADD, 4, 0, 0, 0, 0, 1, 0, 0, 0, 1));

	// ch0 = b0*x[n] + b1*x[n-1] + b2*x[n-1] - a1y[n-1] - a2y[n-2] = -a2*ch5 + ch0
    write_block_register(base_block + 7, 0, float_to_q_nminus1(-a2, 1));
    write_block_instr(base_block + 7,
        BLOCK_INSTR_S(BLOCK_INSTR_MADD, 5, 0, 0, 0, 0, 1, 0, 0, 0, 1));

	// clamp to [-1, 1)
	write_block_instr(base_block + 8,
        BLOCK_INSTR_S(BLOCK_INSTR_CLAMP, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0));
       
    // shift back to format
	write_block_instr(base_block + 9,
        BLOCK_INSTR_S(BLOCK_INSTR_LSH, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));

	// move previous sample's y[n-1] to ch5
    write_block_instr(base_block + 10,
        BLOCK_INSTR_S(BLOCK_INSTR_MOV, 4, 0, 0, 5, 0, 0, 0, 0, 0, 0));
    // move y[n] to ch4
    write_block_instr(base_block + 11,
        BLOCK_INSTR_S(BLOCK_INSTR_MOV, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0));
}

#endif

void m_fpga_comms_task(void *param)
{
	m_fpga_comms_init();
	
	vTaskDelay(pdMS_TO_TICKS(2000));
	
	printf("try...\n");
	m_fpga_send_byte(COMMAND_ALLOC_SRAM_DELAY);
	m_fpga_send_byte((4096 & 0xFF00) >> 8);
	m_fpga_send_byte( 0);
	
	m_fpga_send_byte(COMMAND_SWAP_PIPELINES);
	
	printf("try...\n");
	m_fpga_send_byte(COMMAND_ALLOC_SRAM_DELAY);
	m_fpga_send_byte((4096) >> 8);
	m_fpga_send_byte( 0);
	
	m_fpga_send_byte(COMMAND_SWAP_PIPELINES);
	
	vTaskDelete(NULL);
}

void m_fpga_set_input_gain(float gain_db)
{
	float v = powf(10, gain_db / 20.0);
	uint16_t s = float_to_q_nminus1(v, 5);
			
	printf("Telling FPGA to change input gain to %fdB = %f = 0b%d%d%d%d%d.%d%d%d%d%d%d%d%d%d%d%d\n", gain_db, v,
		!!(s & (1 << 15)),
		!!(s & (1 << 14)),
		!!(s & (1 << 13)),
		!!(s & (1 << 12)),
		!!(s & (1 << 11)),
		!!(s & (1 << 10)),
		!!(s & (1 << 9)),
		!!(s & (1 << 8)),
		!!(s & (1 << 7)),
		!!(s & (1 << 6)),
		!!(s & (1 << 5)),
		!!(s & (1 << 4)),
		!!(s & (1 << 3)),
		!!(s & (1 << 2)),
		!!(s & (1 << 1)),
		!!(s & (1 << 0)));
	
	m_fpga_send_byte(COMMAND_SET_INPUT_GAIN);
	m_fpga_send_byte((s & 0xFF00) >> 8);
	m_fpga_send_byte(s & 0x00FF);
}

void m_fpga_set_output_gain(float gain_db)
{
	float v = powf(10, gain_db / 20.0);
	uint16_t s = float_to_q_nminus1(v, 5);
			
	printf("Telling FPGA to change input gain to %fdB = %f = 0b%d%d%d%d%d.%d%d%d%d%d%d%d%d%d%d%d\n", gain_db, v,
		!!(s & (1 << 15)),
		!!(s & (1 << 14)),
		!!(s & (1 << 13)),
		!!(s & (1 << 12)),
		!!(s & (1 << 11)),
		!!(s & (1 << 10)),
		!!(s & (1 << 9)),
		!!(s & (1 << 8)),
		!!(s & (1 << 7)),
		!!(s & (1 << 6)),
		!!(s & (1 << 5)),
		!!(s & (1 << 4)),
		!!(s & (1 << 3)),
		!!(s & (1 << 2)),
		!!(s & (1 << 1)),
		!!(s & (1 << 0)));
	
	m_fpga_send_byte(COMMAND_SET_OUTPUT_GAIN);
	m_fpga_send_byte((s & 0xFF00) >> 8);
	m_fpga_send_byte(s & 0x00FF);
}

m_fpga_resource_report m_empty_fpga_resource_report()
{
	m_fpga_resource_report result;
	memset(&result, 0, sizeof(m_fpga_resource_report));
	return result;
}

int m_fpga_resource_report_integrate(m_fpga_resource_report *cxt, m_fpga_resource_report *local)
{
	if (!cxt || !local)
		return ERR_NULL_PTR;
	
	cxt->blocks += local->blocks;
	cxt->memory += local->memory;
	cxt->sdelay += local->sdelay;
	cxt->ddelay += local->ddelay;
	cxt->luts   += local->luts;
	
	return NO_ERROR;
}

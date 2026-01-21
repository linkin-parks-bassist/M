#include <freertos/FreeRTOS.h>
#include <driver/spi_master.h>
#include <math.h>

#include "m_error_codes.h"
#include "m_int_fpga.h"

#define PIN_NUM_MISO  	14
#define PIN_NUM_MOSI  	6
#define PIN_NUM_CLK   	5
#define PIN_NUM_CS		4

spi_device_handle_t spi_handle;

QueueHandle_t m_fpga_send_queue;

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
    if (ret != ESP_OK) {
        return ERR_SPI_FAIL;
    }

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 10 * 1000 * 1000,
        .mode = 0,
        .spics_io_num = PIN_NUM_CS,
        .queue_size = 4,
    };

    ret = spi_bus_add_device(SPI2_HOST, &devcfg, &spi_handle);
    if (ret != ESP_OK) {
        return ERR_SPI_FAIL;
    }
    
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

int16_t float_to_q_nminus1(float x, int shift)
{
    int n = 15 - shift;

    float scale = (float)(1 << n);

    float max =  (float)((1 << 15) - 1) / scale;
    float min = -(float)(1 << 15)       / scale;

    if (x > max) x = max;
    if (x < min) x = min;

    return (int16_t)lrintf(x * scale);
}


int16_t float_to_q15(float x)
{
	if (x >= 0.999969482421875f) return  32767;
    if (x <= -1.0f)              return -32768;
    
    return (int16_t)lrintf(x * 32768.0f);
}

void write_block_instr(int block, uint32_t instr)
{
	printf("Set block %d instruction to %d = 0b%032b\n", block, instr, instr);
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
        BLOCK_INSTR_S(BLOCK_INSTR_MAD, 2, 0, 0, 0, 0, 1, 0, 0, 0, 1));

	// ch0 = b0*x[n] + b1*x[n-1] + b2*x[n-1] = b2*ch3 + ch0
    write_block_register(base_block + 5, 0, float_to_q_nminus1(b2, 1));
    write_block_instr(base_block + 5,
        BLOCK_INSTR_S(BLOCK_INSTR_MAD, 3, 0, 0, 0, 0, 1, 0, 0, 0, 1));

	// ch0 = b0*x[n] + b1*x[n-1] + b2*x[n-1] - a1y[n-1] = -a1*ch4 + ch0
    write_block_register(base_block + 6, 0, float_to_q_nminus1(-a1, 1));
    write_block_instr(base_block + 6,
        BLOCK_INSTR_S(BLOCK_INSTR_MAD, 4, 0, 0, 0, 0, 1, 0, 0, 0, 1));

	// ch0 = b0*x[n] + b1*x[n-1] + b2*x[n-1] - a1y[n-1] - a2y[n-2] = -a2*ch5 + ch0
    write_block_register(base_block + 7, 0, float_to_q_nminus1(-a2, 1));
    write_block_instr(base_block + 7,
        BLOCK_INSTR_S(BLOCK_INSTR_MAD, 5, 0, 0, 0, 0, 1, 0, 0, 0, 1));

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

void m_fpga_comms_task(void *param)
{
	m_fpga_comms_init();
	
	vTaskDelay(pdMS_TO_TICKS(2000));
	
	//load_biquad(0,  (float)0.0039160767, (float)0.0078321534, (float)0.0039160767, (float)-1.8153179157, (float)0.8309822224);
	//load_biquad(20, (float)0.0039160767, (float)0.0078321534, (float)0.0039160767, (float)-1.8153179157, (float)0.8309822224);
	//load_biquad(40, (float)0.0039160767, (float)0.0078321534, (float)0.0039160767, (float)-1.8153179157, (float)0.8309822224);

	//write_block_instr(0, BLOCK_INSTR_S(BLOCK_INSTR_MUL, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0));
	//write_block_register(0, 0, float_to_q15(0.05));
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

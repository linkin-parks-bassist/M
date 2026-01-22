#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "esp_check.h"
#include "esp_log.h"

#include "m_error_codes.h"

#include "driver/spi_master.h"
#include "driver/i2c_master.h"
#include "driver/pulse_cnt.h"
#include "driver/gpio.h"

#include "m_int_sgtl5000.h"   // your register defines (CHIP_*, DAP_*, etc)

#define SGTL5000_SDA 15
#define SGTL5000_SCL 16

static const char *TAG = "sgtl5000";

int sgtl5000_status = 0;

static uint16_t ana_ctrl;
static uint8_t  i2c_addr = 0x0A;   // default, you override with sgtl5000_set_address()

static bool muted;
static bool semi_automated;

static i2c_master_bus_handle_t bus;
static i2c_master_dev_handle_t dev;

typedef struct {
    int i2c_port;
    int sda_gpio;
    int scl_gpio;
    uint32_t i2c_hz;
} sgtl5000_i2c_cfg_t;

int sgtl5000_i2c_init(const sgtl5000_i2c_cfg_t *cfg)
{
    if (!cfg) return ESP_ERR_INVALID_ARG;

    i2c_master_bus_config_t bus_cfg = {
        .i2c_port = -1,
        .sda_io_num = cfg->sda_gpio,
        .scl_io_num = cfg->scl_gpio,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .intr_priority = 0,
        .trans_queue_depth = 0,
        .flags.enable_internal_pullup = false,
    };

    esp_err_t err = i2c_new_master_bus(&bus_cfg, &bus);
    if (err != ESP_OK) return err;

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address  = i2c_addr,
        .scl_speed_hz    = cfg->i2c_hz,
    };

    err = i2c_master_bus_add_device(bus, &dev_cfg, &dev);
    
    return (err == ESP_OK) ? NO_ERROR : ERR_I2C_FAIL;
}

int sgtl5000_set_address_level(int cs_level_high)
{
    uint8_t new_addr = cs_level_high ? SGTL5000_I2C_ADDR_CS_HIGH : SGTL5000_I2C_ADDR_CS_LOW;
    i2c_addr = new_addr;

    if (!bus) return ERR_BAD_ARGS;

    if (dev) {
        i2c_master_bus_rm_device(dev);
        dev = NULL;
    }

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address  = i2c_addr,
        .scl_speed_hz    = 400000,
    };
    
    esp_err_t err = i2c_master_bus_add_device(bus, &dev_cfg, &dev);
    
    return (err == ESP_OK) ? NO_ERROR : ERR_I2C_FAIL;
}

int sgtl5000_read_reg(uint16_t reg, uint16_t *out_val)
{
    if (!dev || !out_val) return ESP_ERR_INVALID_STATE;

    uint8_t addr_be[2] = { (uint8_t)(reg >> 8), (uint8_t)(reg & 0xFF) };
    uint8_t data[2]    = {0, 0};

    esp_err_t err = i2c_master_transmit_receive(dev, addr_be, sizeof(addr_be), data, sizeof(data), -1);
    if (err != ESP_OK) return ERR_I2C_FAIL;
    
	vTaskDelay(pdMS_TO_TICKS(2));

    *out_val = ((uint16_t)data[0] << 8) | (uint16_t)data[1];
    return NO_ERROR;
}

int sgtl5000_write_reg(uint16_t reg, uint16_t val)
{
    if (!dev) return ESP_ERR_INVALID_STATE;

    if (reg == CHIP_ANA_CTRL) ana_ctrl = val;

    uint8_t pkt[4] = {
        (uint8_t)(reg >> 8), (uint8_t)(reg & 0xFF),
        (uint8_t)(val >> 8), (uint8_t)(val & 0xFF)
    };

	esp_err_t err = i2c_master_transmit(dev, pkt, sizeof(pkt), -1);

    if (err != ESP_OK)
		return ERR_I2C_FAIL;
	
	return NO_ERROR;
}

int sgtl5000_modify_reg(uint16_t reg, uint16_t val, uint16_t mask, uint16_t *out_newval)
{
    uint16_t cur;
    int ret_val = sgtl5000_read_reg(reg, &cur);
    if (ret_val != NO_ERROR) return ret_val;

    uint16_t newv = (cur & ~mask) | (val & mask);
    ret_val = sgtl5000_write_reg(reg, newv);
    if (ret_val != NO_ERROR) return ret_val;

    if (out_newval) *out_newval = newv;
    return NO_ERROR;
}

int sgtl5000_enable(void)
{
    if (!dev) return ESP_ERR_INVALID_STATE;

    muted = true;
	
	printf("Send power sequence...\n");

	int ret_val;

    if ((ret_val = sgtl5000_write_reg(CHIP_LINREG_CTRL, 	0x006C)) != NO_ERROR) return ret_val;
    if ((ret_val = sgtl5000_write_reg(CHIP_REF_CTRL, 		0x01F2)) != NO_ERROR) return ret_val;
    if ((ret_val = sgtl5000_write_reg(CHIP_LINE_OUT_CTRL, 	0x0F22)) != NO_ERROR) return ret_val;
    if ((ret_val = sgtl5000_write_reg(CHIP_SHORT_CTRL, 		0x4446)) != NO_ERROR) return ret_val;
    if ((ret_val = sgtl5000_write_reg(CHIP_ANA_CTRL, 		0x0137)) != NO_ERROR) return ret_val;

    if ((ret_val = sgtl5000_write_reg(CHIP_ANA_POWER, 		0x40FF)) != NO_ERROR) return ret_val;
    if ((ret_val = sgtl5000_write_reg(CHIP_DIG_POWER, 		0x0073)) != NO_ERROR) return ret_val;
    
    // delay(400);
    vTaskDelay(pdMS_TO_TICKS(400));

    if ((ret_val = sgtl5000_write_reg(CHIP_LINE_OUT_VOL, 	0x1D1D)) != NO_ERROR) return ret_val;

    if ((ret_val = sgtl5000_write_reg(CHIP_CLK_CTRL, 		0x0004)) != NO_ERROR) return ret_val;
    if ((ret_val = sgtl5000_write_reg(CHIP_I2S_CTRL, 		0x0030)) != NO_ERROR) return ret_val;
    
    if ((ret_val = sgtl5000_write_reg(CHIP_SSS_CTRL, 		0x0010)) != NO_ERROR) return ret_val;    
    if ((ret_val = sgtl5000_write_reg(CHIP_ADCDAC_CTRL, 	0x0000)) != NO_ERROR) return ret_val;    
    if ((ret_val = sgtl5000_write_reg(CHIP_DAC_VOL, 		0x3C3C)) != NO_ERROR) return ret_val;    
    if ((ret_val = sgtl5000_write_reg(CHIP_ANA_HP_CTRL, 	0x7F7F)) != NO_ERROR) return ret_val;    
    if ((ret_val = sgtl5000_write_reg(CHIP_ANA_CTRL, 		0x0036)) != NO_ERROR) return ret_val;

    semi_automated = true;

    // Set input as line in
    if ((ret_val = sgtl5000_write_reg(0x0020, 0x0055)) != NO_ERROR) return ret_val;
	if ((ret_val = sgtl5000_write_reg(0x0024, ana_ctrl | (1u<<2))) != NO_ERROR) return ret_val;
    
    if ((ret_val = sgtl5000_modify_reg(CHIP_ADCDAC_CTRL, 0, 0x0300, NULL)) != NO_ERROR)
		return ret_val;
	
	printf("Done.\n");

    return NO_ERROR;
}

int sgtl5000_line_in_level(uint8_t n)
{
	if (n > 15) n = 15;
	return sgtl5000_write_reg(CHIP_ANA_ADC_CTRL, (n << 4) | n);
}

int sgtl5000_line_out_level(uint8_t n)
{
	if (n > 31) n = 31;
	else if (n < 13) n = 13;
	return sgtl5000_modify_reg(CHIP_LINE_OUT_VOL,(n<<8)|n, (31<<8)|31, NULL);
}

void sgtl_power_gpio_init(void)
{
    gpio_config_t cfg = {
        .pin_bit_mask = 1ULL << 2,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };

    gpio_config(&cfg);
}

static void read_and_print(uint16_t reg, const char *name)
{
    uint16_t v = 0xFFFF;
    int ret_val = sgtl5000_read_reg(reg, &v);
    if (ret_val != NO_ERROR)
    {
        printf("RD  %-18s (0x%04X): ERROR\n", name, reg);
        return;
    }
    printf("RD  %-18s (0x%04X): 0x%04X\n", name, reg, v);
}

typedef struct {
    uint16_t reg;
    const char *name;
} sgtl_reg_desc_t;

void sgtl5000_readout_registers()
{
    static const sgtl_reg_desc_t reads[] = {
        { CHIP_ID,        "CHIP_ID"        },
        { CHIP_DIG_POWER,   "CHIP_DIG_POWER"   },
        { CHIP_ANA_POWER,   "CHIP_ANA_POWER"   },
        { CHIP_CLK_CTRL,    "CHIP_CLK_CTRL"    },
        { CHIP_I2S_CTRL,    "CHIP_I2S_CTRL"    },
        { CHIP_ADCDAC_CTRL, "CHIP_ADCDAC_CTRL" },
        { CHIP_DAC_VOL, 	 "CHIP_DAC_VOL"	    },
        { CHIP_PAD_STRENGTH, 	 "CHIP_PAD_STRENGTH"	    },
        { CHIP_ANA_ADC_CTRL, 	 "CHIP_ANA_ADC_CTRL"	    },
        { CHIP_ANA_HP_CTRL, 	 "CHIP_ANA_HP_CTRL"	    },
        { CHIP_ANA_CTRL, 	 "CHIP_ANA_CTRL"	    },
        { CHIP_LINREG_CTRL, 	 "CHIP_LINREG_CTRL"	    },
        { CHIP_REF_CTRL, 	 "CHIP_REF_CTRL"	    },
        { CHIP_MIC_CTRL, 	 "CHIP_MIC_CTRL"	    },
        { CHIP_LINE_OUT_CTRL, 	 "CHIP_LINE_OUT_CTRL"	    },
        { CHIP_LINE_OUT_VOL, 	 "CHIP_LINE_OUT_VOL"	    },
        { CHIP_ANA_POWER, 	 "CHIP_ANA_POWER"	    },
        { CHIP_PLL_CTRL, 	 "CHIP_PLL_CTRL"	    },
        { CHIP_CLK_TOP_CTRL, 	 "CHIP_CLK_TOP_CTRL"	    },
        { CHIP_ANA_STATUS, 	 "CHIP_ANA_STATUS"	    },
        { CHIP_ANA_TEST1, 	 "CHIP_ANA_TEST1"	    },
        { CHIP_ANA_TEST2, 	 "CHIP_ANA_TEST2"	    },
        { CHIP_SHORT_CTRL, 	 "CHIP_SHORT_CTRL"	    },
        { CHIP_SSS_CTRL, 	 "CHIP_SSS_CTRL"	    },
    };

    printf("\n=== SGTL5000 READ DUMP ===\n");
    for (size_t i = 0; i < sizeof(reads)/sizeof(reads[0]); i++) {
        (void)read_and_print(reads[i].reg, reads[i].name);
    }
}

void m_int_sgtl5000_init(void *param)
{
	sgtl_power_gpio_init();
	
	sgtl5000_i2c_cfg_t sgtl_i2c_cfg = {
        .i2c_port = -1,
        .sda_gpio = SGTL5000_SDA,
        .scl_gpio = SGTL5000_SCL,
        .i2c_hz   = 400000,
    };
    
    
    
	vTaskDelay(pdMS_TO_TICKS(3000));

    int ret_val;
    
    printf("Initialise I2C bus with SGTL5000...\n");
    if ((ret_val = sgtl5000_i2c_init(&sgtl_i2c_cfg)) != NO_ERROR)
	{
		printf("Error initialising I2C bus with SGTL5000...\n");
		return;
	}
    
    if ((ret_val = sgtl5000_set_address_level(0)) != NO_ERROR)
		return;
    
    printf("Initialising SGTL5000...\n");
    if ((ret_val = sgtl5000_enable()) != NO_ERROR)
	{
		printf("Error initialising SGTL5000...\n");
		return;
	}
	
	sgtl5000_line_in_level(3);
	sgtl5000_line_out_level(31);
	
	sgtl5000_status = 1;
	
	printf("SGTL5000 Initialised\n");
	
	//sgtl5000_readout_registers();
	
	vTaskDelete(NULL);
}

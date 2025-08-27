#include "M.h"

#include "sgtl5000_macros.h"

unsigned int sgtl5000_read(sgtl5000_str *sgtl5000, unsigned int reg)
{
	if (!sgtl5000)
		return 0;
	
	unsigned int val;
	
	Wire.beginTransmission(sgtl5000->i2c_addr);
	Wire.write(reg >> 8);
	Wire.write(reg);
	
	if (Wire.endTransmission(false) != 0)
		return 0;
	
	if (Wire.requestFrom((int)sgtl5000->i2c_addr, 2) < 2)
		return 0;
	
	val = Wire.read() << 8;
	val |= Wire.read();
	
	return val;
}

int sgtl5000_write(sgtl5000_str *sgtl5000, unsigned int reg, unsigned int val)
{
	if (!sgtl5000)
		return ERR_NULL_PTR;
	
	if (reg == CHIP_ANA_CTRL)
		sgtl5000->ana_ctrl = val;
	
	m_printf("Opening I2C... ");
	Wire.beginTransmission(sgtl5000->i2c_addr);
	
	m_printf("Writing... ");
	Wire.write(reg >> 8);
	Wire.write(reg);
	Wire.write(val >> 8);
	Wire.write(val);
	
	m_printf("Write complete. ");
	
	int ret_val = Wire.endTransmission();
	
	if (ret_val)
	{
		Serial.print("I2C write error ");
		Serial.println(ret_val);
		
		return ERR_SGTL5000_WRITE_FAIL;
	}
	
	m_printf("Write succesful.\n");
	return NO_ERROR;
}

int sgtl5000_init(sgtl5000_str *sgtl5000)
{
	if (!sgtl5000)
		return ERR_NULL_PTR;
	
	sgtl5000->i2c_addr = SGTL5000_I2C_ADDR_CS_LOW;
    sgtl5000->muted = 1;
    
    Wire.begin();
	delay(5);
    
    sgtl5000_read(sgtl5000, CHIP_I2S_CTRL);

	// VDDD is externally driven with 1.8V
	m_printf("Writing 0x4060 to SGTL5000 register CHIP_ANA_POWER...\n");
	if (sgtl5000_write(sgtl5000, CHIP_ANA_POWER, 0x4060) != NO_ERROR) return ERR_SGTL5000_WRITE_FAIL;
	
	m_printf("Writing 0x006C to SGTL5000 register CHIP_LINREG_CTRL...\n");
	sgtl5000_write(sgtl5000, CHIP_LINREG_CTRL, 		0x006C);  	// VDDA & VDDIO both over 3.1V
	m_printf("Writing 0x01F2 to SGTL5000 register CHIP_REF_CTRL...\n");
	sgtl5000_write(sgtl5000, CHIP_REF_CTRL, 		0x01F2); 	// VAG=1.575, normal ramp, +12.5% bias current
	m_printf("Writing 0x0F22 to SGTL5000 register CHIP_LINE_OUT_CTRL...\n");
	sgtl5000_write(sgtl5000, CHIP_LINE_OUT_CTRL, 	0x0F22); 	// LO_VAGCNTRL=1.65V, OUT_CURRENT=0.54mA
	m_printf("Writing 0x4446 to SGTL5000 register CHIP_SHORT_CTRL...\n");
	sgtl5000_write(sgtl5000, CHIP_SHORT_CTRL, 		0x4446);  	// allow up to 125mA
	m_printf("Writing 0x0137 to SGTL5000 register CHIP_ANA_CTRL...\n");
	sgtl5000_write(sgtl5000, CHIP_ANA_CTRL, 		0x0137);  	// enable zero cross detectors
	
	m_printf("Writing 0x40FF to SGTL5000 register CHIP_ANA_POWER...\n");
	sgtl5000_write(sgtl5000, CHIP_ANA_POWER, 0x40FF);
	
	m_printf("Writing 0x0073 to SGTL5000 register CHIP_DIG_POWER...\n");
	sgtl5000_write(sgtl5000, CHIP_DIG_POWER, 0x0073); 			// power up all digital stuff
	
	Serial.println("SGTL5000 powered on...");
	delay(400);
	m_printf("Writing 0x1D1D to SGTL5000 register CHIP_LINE_OUT_VOL...\n");
	sgtl5000_write(sgtl5000, CHIP_LINE_OUT_VOL, 0x1D1D); 		// default approx 1.3 volts peak-to-peak
	
	//SGTL is I2S Slave
	m_printf("Writing 0x0004 to SGTL5000 register CHIP_CLK_CTRL...\n");
	sgtl5000_write(sgtl5000, CHIP_CLK_CTRL, 0x0004);  			// 44.1 kHz, 256*Fs
	m_printf("Writing 0x0030 to SGTL5000 register CHIP_I2S_CTRL...\n");
	sgtl5000_write(sgtl5000, CHIP_I2S_CTRL, 0x0030); 			// SCLK=64*Fs, 16bit, I2S format

	// default signal routing is ok?
	m_printf("Writing 0x0010 to SGTL5000 register CHIP_SSS_CTRL...\n");
	sgtl5000_write(sgtl5000, CHIP_SSS_CTRL, 	0x0010); 		// ADC->I2S, I2S->DAC
	m_printf("Writing 0x0000 to SGTL5000 register CHIP_ADCDAC_CTRL...\n");
	sgtl5000_write(sgtl5000, CHIP_ADCDAC_CTRL, 	0x0000); 		// disable dac mute
	m_printf("Writing 0x3C3C to SGTL5000 register CHIP_DAC_VOL...\n");
	sgtl5000_write(sgtl5000, CHIP_DAC_VOL, 		0x3C3C); 		// digital gain, 0dB
	m_printf("Writing 0x7F7F to SGTL5000 register CHIP_ANA_HP_CTRL...\n");
	sgtl5000_write(sgtl5000, CHIP_ANA_HP_CTRL, 	0x7F7F); 		// set volume (lowest level)
	m_printf("Writing 0x0036 to SGTL5000 register CHIP_ANA_CTRL...\n");
	sgtl5000_write(sgtl5000, CHIP_ANA_CTRL, 	0x0036);  		// enable zero cross detectors

	sgtl5000->semi_automated = 1;
	
	Serial.println("SGTL5000 initialisation complete.");
	Serial.flush();
	
	return NO_ERROR;
}

int sgtl5000_mute_headphone(sgtl5000_str *sgtl5000)
{
	if (!sgtl5000)
		return ERR_NULL_PTR;
	
	return sgtl5000_write(sgtl5000, 0x0024, sgtl5000->ana_ctrl | (1<<4));
}

int sgtl5000_unmute_headphone(sgtl5000_str *sgtl5000)
{
	if (!sgtl5000)
		return ERR_NULL_PTR;
	
	return sgtl5000_write(sgtl5000, 0x0024, sgtl5000->ana_ctrl & ~(1<<4));
}

int sgtl5000_set_volume(sgtl5000_str *sgtl5000, float v)
{
	if (!sgtl5000)
		return ERR_NULL_PTR;
	
	unsigned int n = v * 129 + 0.499f;
	if (n == 0)
	{
		sgtl5000->muted = true;
		sgtl5000_write(sgtl5000, CHIP_ANA_HP_CTRL, 0x7F7F);
		return sgtl5000_mute_headphone(sgtl5000);
	}
	else if (n > 0x80)
	{
		n = 0;
	} else
	{
		n = 0x80 - n;
	}
	if (sgtl5000->muted)
	{
		sgtl5000->muted = false;
		sgtl5000_unmute_headphone(sgtl5000);
	}
	
	n = n | (n << 8);
	
	return sgtl5000_write(sgtl5000, CHIP_ANA_HP_CTRL, n);  // set volume
}

int sgtl5000_enable_line_in(sgtl5000_str *sgtl5000)
{
	if (!sgtl5000)
		return ERR_NULL_PTR;
	
	if (sgtl5000_write(sgtl5000, 0x0020, 0x055) != NO_ERROR)				// +7.5dB gain (1.3Vp-p full scale)
		return ERR_SGTL5000_WRITE_FAIL;
	if (sgtl5000_write(sgtl5000, 0x0024, sgtl5000->ana_ctrl | (1<<2)) != NO_ERROR); 	// enable linein
		return ERR_SGTL5000_WRITE_FAIL;
	
	return NO_ERROR;
}

int sgtl5000_line_in_level(sgtl5000_str *sgtl5000, uint8_t level)
{
	if (!sgtl5000)
		return ERR_NULL_PTR;
	
	if (level > 15) level = 15;
	return sgtl5000_write(sgtl5000, CHIP_ANA_ADC_CTRL, (level << 4) | level);
}

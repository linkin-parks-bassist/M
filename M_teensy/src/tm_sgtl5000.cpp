/* tm_Audio Library for Teensy 3.X
 *Copyright (c) 2014, Paul Stoffregen, paul@pjrc.com
static const char *FNAME = "tm_sgtl5000.c";
 *
 *Development of this audio library was funded by PJRC.COM, LLC by sales of
 *Teensy and tm_Audio Adaptor boards.  Please support PJRC's efforts to develop
 *open source software by purchasing Teensy or other PJRC products.
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, sgtl5000_modify, merge, publish, distribute, sublicense, and/or sell
 *copies of the Software, and to permit persons to whom the Software is
 *furnished to do so, subject to the following conditions:
 *
 *The above copyright notice, development funding notice, and this permission
 *notice shall be included in all copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *THE SOFTWARE.
 */

#include <Arduino.h>
#include <Wire.h>

#include "tm.h"
#include "tm_sgtl5000_defs.h"

static const char *FNAME = "tm_sgtl5000.cpp";

static uint16_t ana_ctrl;
static uint8_t i2c_addr = 0x0A;

static bool muted;
static bool semi_automated;

int sgtl5000_volume(float n) 		{ return sgtl5000_volume_integer(n *129 + 0.499f);		}
int sgtl5000_mute_headphone()	 	{ return sgtl5000_write_reg(0x0024, ana_ctrl | (1<<4)); }
int sgtl5000_unmute_headphone() 	{ return sgtl5000_write_reg(0x0024, ana_ctrl & ~(1<<4));}
int sgtl5000_mute_line_out() 		{ return sgtl5000_write_reg(0x0024, ana_ctrl | (1<<8)); }
int sgtl5000_unmute_line_out() 		{ return sgtl5000_write_reg(0x0024, ana_ctrl & ~(1<<8));}

void sgtl5000_set_address(uint8_t level)
{
	FUNCTION_START();

	if (level == LOW)
		i2c_addr = SGTL5000_I2C_ADDR_CS_LOW;
	else
		i2c_addr = SGTL5000_I2C_ADDR_CS_HIGH;
}


int sgtl5000_start()
{
	FUNCTION_START();

	sgtl5000_enable();
	
	sgtl5000_line_in_level(3);
	sgtl5000_line_out_level(31);
	
	return NO_ERROR;
}

int sgtl5000_enable()
{
	FUNCTION_START();

	Wire.begin();
	delay(5);
	
	//Check if we are in Master Mode and if the Teensy had a reset:
	sgtl5000_read_reg(CHIP_I2S_CTRL);

	muted = true;

	// VDDD is externally driven with 1.8V
	if (!sgtl5000_write_reg(CHIP_ANA_POWER, 0x4060)) return ERR_SGTL5000_WRITE_FAIL;
	
	sgtl5000_write_reg(CHIP_LINREG_CTRL, 	0x006C);  	// VDDA & VDDIO both over 3.1V
	sgtl5000_write_reg(CHIP_REF_CTRL, 		0x01F2); 	// VAG=1.575, normal ramp, +12.5% bias current
	sgtl5000_write_reg(CHIP_LINE_OUT_CTRL, 	0x0F22); 	// LO_VAGCNTRL=1.65V, OUT_CURRENT=0.54mA
	sgtl5000_write_reg(CHIP_SHORT_CTRL, 	0x4446);  	// allow up to 125mA
	sgtl5000_write_reg(CHIP_ANA_CTRL, 		0x0137);  	// enable zero cross detectors
	
	sgtl5000_write_reg(CHIP_ANA_POWER, 		0x40FF); 	// power up: lineout, hp, adc, dac

	sgtl5000_write_reg(CHIP_DIG_POWER, 		0x0073);	// power up all digital stuff
	delay(400);
	sgtl5000_write_reg(CHIP_LINE_OUT_VOL, 	0x1D1D); 	// default approx 1.3 volts peak-to-peak
	
	sgtl5000_write_reg(CHIP_CLK_CTRL, 		0x0004);  	// 44.1 kHz, 256*Fs
	sgtl5000_write_reg(CHIP_I2S_CTRL, 		0x0030); 	// SCLK=64*Fs, 16bit, I2S format

	// default signal routing is ok?
	sgtl5000_write_reg(CHIP_SSS_CTRL, 		0x0010); 	// ADC->I2S, I2S->DAC
	sgtl5000_write_reg(CHIP_ADCDAC_CTRL, 	0x0000); 	// disable dac mute
	sgtl5000_write_reg(CHIP_DAC_VOL, 		0x3C3C); 	// digital gain, 0dB
	sgtl5000_write_reg(CHIP_ANA_HP_CTRL, 	0x7F7F); 	// set volume (lowest level)
	sgtl5000_write_reg(CHIP_ANA_CTRL, 		0x0036);  	// enable zero cross detectors

	semi_automated = true;
	
	// Set input as line in
	sgtl5000_write_reg(0x0020, 0x055); // +7.5dB gain (1.3Vp-p full scale)
	sgtl5000_write_reg(0x0024, ana_ctrl | (1<<2));
	
	sgtl5000_modify_reg(CHIP_ADCDAC_CTRL, 0, 0x300);
	
	return NO_ERROR;
}


unsigned int sgtl5000_read_reg(unsigned int reg)
{
	FUNCTION_START();

	unsigned int val;
	Wire.beginTransmission(i2c_addr);
	Wire.write(reg >> 8);
	Wire.write(reg);
	if (Wire.endTransmission(false) != 0) RETURN_INT(0);
	if (Wire.requestFrom((int)i2c_addr, 2) < 2) RETURN_INT(0);
	val = Wire.read() << 8;
	val |= Wire.read();
	return val;
}

int sgtl5000_write_reg(unsigned int reg, unsigned int val)
{
	FUNCTION_START();

	if (reg == CHIP_ANA_CTRL) ana_ctrl = val;
	Wire.beginTransmission(i2c_addr);
	Wire.write(reg >> 8);
	Wire.write(reg);
	Wire.write(val >> 8);
	Wire.write(val);
	
	return (Wire.endTransmission() == 0);
}

unsigned int sgtl5000_modify_reg(unsigned int reg, unsigned int val, unsigned int i_mask)
{
	FUNCTION_START();

	unsigned int val1 = (sgtl5000_read_reg(reg)&(~i_mask))|val;
	
	if (!sgtl5000_write_reg(reg,val1))
		RETURN_INT(0);
	
	return val1;
}

int sgtl5000_volume_integer(unsigned int n)
{
	FUNCTION_START();

	if (n == 0)
	{
		muted = true;
		sgtl5000_write_reg(CHIP_ANA_HP_CTRL, 0x7F7F);
		return sgtl5000_mute_headphone();
	}
	else if (n > 0x80)
	{
		n = 0;
	}
	else
	{
		n = 0x80 - n;
	}
	if (muted)
	{
		muted = false;
		sgtl5000_unmute_headphone();
	}
	
	n = n | (n << 8);
	
	return sgtl5000_write_reg(CHIP_ANA_HP_CTRL, n);  // set volume
}

// CHIP_ANA_ADC_CTRL
// Actual measured full-scale peak-to-peak sine wave input for max signal
//  0: 3.12 Volts p-p
//  1: 2.63 Volts p-p
//  2: 2.22 Volts p-p
//  3: 1.87 Volts p-p
//  4: 1.58 Volts p-p
//  5: 1.33 Volts p-p
//  6: 1.11 Volts p-p
//  7: 0.94 Volts p-p
//  8: 0.79 Volts p-p
//  9: 0.67 Volts p-p
// 10: 0.56 Volts p-p
// 11: 0.48 Volts p-p
// 12: 0.40 Volts p-p
// 13: 0.34 Volts p-p
// 14: 0.29 Volts p-p
// 15: 0.24 Volts p-p

int sgtl5000_line_in_level(uint8_t n)
{
	FUNCTION_START();

	if (n > 15) n = 15;
	return sgtl5000_write_reg(CHIP_ANA_ADC_CTRL, (n << 4) | n);
}

// CHIP_LINE_OUT_VOL
//  Actual measured full-scale peak-to-peak sine wave output voltage:
//  0-12: output has clipping
//  13: 3.16 Volts p-p
//  14: 2.98 Volts p-p
//  15: 2.83 Volts p-p
//  16: 2.67 Volts p-p
//  17: 2.53 Volts p-p
//  18: 2.39 Volts p-p
//  19: 2.26 Volts p-p
//  20: 2.14 Volts p-p
//  21: 2.02 Volts p-p
//  22: 1.91 Volts p-p
//  23: 1.80 Volts p-p
//  24: 1.71 Volts p-p
//  25: 1.62 Volts p-p
//  26: 1.53 Volts p-p
//  27: 1.44 Volts p-p
//  28: 1.37 Volts p-p
//  29: 1.29 Volts p-p
//  30: 1.22 Volts p-p
//  31: 1.16 Volts p-p

unsigned short sgtl5000_line_out_level(uint8_t n)
{
	FUNCTION_START();

	if (n > 31) n = 31;
	else if (n < 13) n = 13;
	return sgtl5000_modify_reg(CHIP_LINE_OUT_VOL,(n<<8)|n,(31<<8)|31);
}

unsigned short sgtl5000_adc_high_pass_filter_enable()
{
	FUNCTION_START();

	return sgtl5000_modify_reg(CHIP_ADCDAC_CTRL, 0, 3);
}

unsigned short sgtl5000_adc_high_pass_filter_freeze()
{
	FUNCTION_START();

	return sgtl5000_modify_reg(CHIP_ADCDAC_CTRL, 2, 3);
}

unsigned short sgtl5000_adc_high_pass_filter_disable()
{
	FUNCTION_START();

	return sgtl5000_modify_reg(CHIP_ADCDAC_CTRL, 1, 3);
}


void sgtl5000_kill_automation()
{
	FUNCTION_START();

	semi_automated=false;
}

unsigned char calc_vol(float n, unsigned char range)
{
	FUNCTION_START();

	// n=(n*(((float)range)/100))+0.499;
	n = (n * (float)range) + 0.499;
	if ((unsigned char)n>range)
		n = range;
	return (unsigned char)n;
}

// DAP_AUDIO_EQ_BASS_BAND0 & DAP_AUDIO_EQ_BAND1 & DAP_AUDIO_EQ_BAND2 etc etc
unsigned short sgtl5000_dap_audio_eq_band(uint8_t band_num, float n) // by signed percentage -100/+100; dap_audio_eq(3);
{
	FUNCTION_START();
	
	n=(n*48)+0.499;
	if(n<-47) n=-47;
	if(n>48) n=48;
	n+=47;
	return sgtl5000_modify_reg(DAP_AUDIO_EQ_BASS_BAND0+(band_num*2),(unsigned int)n,127);
}

unsigned short sgtl5000_eq_select(uint8_t n) // 0=NONE, 1=PEQ (7 IIR Biquad filters), 2=TONE (tone), 3=GEQ (5 band EQ)
{
	FUNCTION_START();
	
	return sgtl5000_modify_reg(DAP_AUDIO_EQ,n&3,3);
}

void sgtl5000_automate(uint8_t dap, uint8_t eq)
{
	FUNCTION_START();

	//if((dap!=0)&&(!(read(DAP_CONTROL)&1))) audioProcessor_enable();
	if((sgtl5000_read_reg(DAP_AUDIO_EQ)&3) != eq) sgtl5000_eq_select(eq);
}

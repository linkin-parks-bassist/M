/* tm_Audio Library for Teensy 3.X
 *Copyright (c) 2014, Paul Stoffregen, paul@pjrc.com
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
	if (level == LOW)
		i2c_addr = SGTL5000_I2C_ADDR_CS_LOW;
	else
		i2c_addr = SGTL5000_I2C_ADDR_CS_HIGH;
}


int sgtl5000_start()
{
	sgtl5000_enable();
}

int sgtl5000_enable()
{
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
	
	return NO_ERROR;
}


unsigned int sgtl5000_read_reg(unsigned int reg)
{
	unsigned int val;
	Wire.beginTransmission(i2c_addr);
	Wire.write(reg >> 8);
	Wire.write(reg);
	if (Wire.endTransmission(false) != 0) return 0;
	if (Wire.requestFrom((int)i2c_addr, 2) < 2) return 0;
	val = Wire.read() << 8;
	val |= Wire.read();
	return val;
}

int sgtl5000_write_reg(unsigned int reg, unsigned int val)
{
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
	unsigned int val1 = (sgtl5000_read_reg(reg)&(~i_mask))|val;
	
	if (!sgtl5000_write_reg(reg,val1))
		return 0;
	
	return val1;
}

int sgtl5000_volume_integer(unsigned int n)
{
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

int sgtl5000_volume(float left, float right)
{
	unsigned short m=((0x7F-calc_vol(right,0x7F))<<8)|(0x7F-calc_vol(left,0x7F));
	return sgtl5000_write_reg(CHIP_ANA_HP_CTRL, m);
}

int sgtl5000_mic_gain(unsigned int dB)
{
	unsigned int preamp_gain, input_gain;

	if (dB >= 40)
	{
		preamp_gain = 3;
		dB -= 40;
	}
	else if (dB >= 30)
	{
		preamp_gain = 2;
		dB -= 30;
	}
	else if (dB >= 20)
	{
		preamp_gain = 1;
		dB -= 20;
	}
	else
	{
		preamp_gain = 0;
	}
	
	input_gain = (dB *2) / 3;
	
	if (input_gain > 15)
		input_gain = 15;

	return sgtl5000_write_reg(CHIP_MIC_CTRL, 0x0170 | preamp_gain)
		&& sgtl5000_write_reg(CHIP_ANA_ADC_CTRL, (input_gain << 4) | input_gain);
}

int sgtl5000_headphone_select(int n)
{
	if (n == AUDIO_HEADPHONE_DAC)
		return sgtl5000_write_reg(0x0024, ana_ctrl | (1<<6)); // route DAC to headphones out
	else if (n == AUDIO_HEADPHONE_LINEIN)
		return sgtl5000_write_reg(0x0024, ana_ctrl & ~(1<<6)); // route linein to headphones out
	else
		return false;
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
	return sgtl5000_line_in_level(n, n);
}

int sgtl5000_line_in_level(uint8_t left, uint8_t right)
{
	if (left > 15) left = 15;
	if (right > 15) right = 15;
	return sgtl5000_write_reg(CHIP_ANA_ADC_CTRL, (left << 4) | right);
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
	if (n > 31) n = 31;
	else if (n < 13) n = 13;
	return sgtl5000_modify_reg(CHIP_LINE_OUT_VOL,(n<<8)|n,(31<<8)|31);
}

unsigned short sgtl5000_line_out_level(uint8_t left, uint8_t right)
{
	left  = (left  > 31) ? 31 : left;
	right = (right > 31) ? 31 : right;
	
	/*if (left > 31)
		left = 31;
	else if (left < 13)
		left = 13;
	
	if (right > 31)
		right = 31;
	else if (right < 13)
		right = 13;*/
	
	return sgtl5000_modify_reg(CHIP_LINE_OUT_VOL,(right<<8)|left,(31<<8)|31);
}

unsigned short sgtl5000_dac_volume(float n) // set both directly
{
	if ((sgtl5000_read_reg(CHIP_ADCDAC_CTRL)&(3<<2)) != ((n>0 ? 0:3)<<2)) {
		sgtl5000_modify_reg(CHIP_ADCDAC_CTRL,(n>0 ? 0:3)<<2,3<<2);
	}
	unsigned char m=calc_vol(n,0xC0);
	return sgtl5000_modify_reg(CHIP_DAC_VOL,((0xFC-m)<<8)|(0xFC-m),65535);
}
unsigned short sgtl5000_dac_volume(float left, float right)
{
	unsigned short adcdac=((right>0 ? 0:2)|(left>0 ? 0:1))<<2;
	if ((sgtl5000_read_reg(CHIP_ADCDAC_CTRL)&(3<<2)) != adcdac) {
		sgtl5000_modify_reg(CHIP_ADCDAC_CTRL,adcdac,1<<2);
	}
	unsigned short m=(0xFC-calc_vol(right,0xC0))<<8|(0xFC-calc_vol(left,0xC0));
	return sgtl5000_modify_reg(CHIP_DAC_VOL,m,65535);
}

int sgtl5000_dac_volume_ramp()
{
	return sgtl5000_modify_reg(CHIP_ADCDAC_CTRL, 0x300, 0x300);
}

int sgtl5000_dac_volume_ramp_linear()
{
	return sgtl5000_modify_reg(CHIP_ADCDAC_CTRL, 0x200, 0x300);
}

int sgtl5000_dac_volume_ramp_disable()
{
	return sgtl5000_modify_reg(CHIP_ADCDAC_CTRL, 0, 0x300);
}

unsigned short sgtl5000_adc_high_pass_filter_enable()
{
	return sgtl5000_modify_reg(CHIP_ADCDAC_CTRL, 0, 3);
}

unsigned short sgtl5000_adc_high_pass_filterFreeze()
{
	return sgtl5000_modify_reg(CHIP_ADCDAC_CTRL, 2, 3);
}

unsigned short sgtl5000_adc_high_pass_filter_disable()
{
	return sgtl5000_modify_reg(CHIP_ADCDAC_CTRL, 1, 3);
}


// DAP_CONTROL

unsigned short sgtl5000_audio_pre_processor_enable()
{
	// audio processor used to pre-process analog input before Teensy
	return sgtl5000_write_reg(DAP_CONTROL, 1) && sgtl5000_write_reg(CHIP_SSS_CTRL, 0x0013);
}

unsigned short sgtl5000_audio_post_processor_enable()
{
	// audio processor used to post-process Teensy output before headphones/lineout
	return sgtl5000_write_reg(DAP_CONTROL, 1) && sgtl5000_write_reg(CHIP_SSS_CTRL, 0x0070);
}

unsigned short sgtl5000_audioProcessor_disable()
{
	return sgtl5000_write_reg(CHIP_SSS_CTRL, 0x0010) && sgtl5000_write_reg(DAP_CONTROL, 0);
}


// DAP_PEQ
unsigned short sgtl5000_eq_filter_count(uint8_t n) // valid to n&7, 0 thru 7 filters enabled.
{
	return sgtl5000_modify_reg(DAP_PEQ,(n&7),7);
}

// DAP_AUDIO_EQ
unsigned short sgtl5000_eq_select(uint8_t n) // 0=NONE, 1=PEQ (7 IIR Biquad filters), 2=TONE (tone), 3=GEQ (5 band EQ)
{
	return sgtl5000_modify_reg(DAP_AUDIO_EQ,n&3,3);
}

unsigned short sgtl5000_eqBand(uint8_t band_num, float n)
{
	if (semi_automated)
		sgtl5000_automate(1, 3);
	return sgtl5000_dap_audio_eq_band(band_num, n);
}
void sgtl5000_eqBands(float bass, float mid_bass, float midrange, float mid_treble, float treble)
{
	if(semi_automated)
		sgtl5000_automate(1,3);
	
	sgtl5000_dap_audio_eq_band(0,bass);
	sgtl5000_dap_audio_eq_band(1,mid_bass);
	sgtl5000_dap_audio_eq_band(2,midrange);
	sgtl5000_dap_audio_eq_band(3,mid_treble);
	sgtl5000_dap_audio_eq_band(4,treble);
}
void sgtl5000_eqBands(float bass, float treble) // dap_audio_eq(2);
{
	if(semi_automated) 
		sgtl5000_automate(1,2);
	
	sgtl5000_dap_audio_eq_band(0,bass);
	sgtl5000_dap_audio_eq_band(4,treble);
}

// SGTL5000 PEQ Coefficient loader
void sgtl5000_eq_filter(uint8_t filterNum, int *filter_parameters)
{
	// TODO: add the part that selects 7 PEQ filters.
	if(semi_automated)
		sgtl5000_automate(1,1,filterNum+1);
	
	sgtl5000_modify_reg(DAP_FILTER_COEF_ACCESS,(uint16_t)filterNum,15);
	sgtl5000_write_reg(DAP_COEF_WR_B0_MSB,(*filter_parameters>>4)&65535);
	sgtl5000_write_reg(DAP_COEF_WR_B0_LSB,(*filter_parameters++)&15);
	sgtl5000_write_reg(DAP_COEF_WR_B1_MSB,(*filter_parameters>>4)&65535);
	sgtl5000_write_reg(DAP_COEF_WR_B1_LSB,(*filter_parameters++)&15);
	sgtl5000_write_reg(DAP_COEF_WR_B2_MSB,(*filter_parameters>>4)&65535);
	sgtl5000_write_reg(DAP_COEF_WR_B2_LSB,(*filter_parameters++)&15);
	sgtl5000_write_reg(DAP_COEF_WR_A1_MSB,(*filter_parameters>>4)&65535);
	sgtl5000_write_reg(DAP_COEF_WR_A1_LSB,(*filter_parameters++)&15);
	sgtl5000_write_reg(DAP_COEF_WR_A2_MSB,(*filter_parameters>>4)&65535);
	sgtl5000_write_reg(DAP_COEF_WR_A2_LSB,(*filter_parameters++)&15);
	sgtl5000_write_reg(DAP_FILTER_COEF_ACCESS,(uint16_t)0x100|filterNum);
}

/* Valid values for dap_avc parameters

	max_gain; Maximum gain that can be applied
	0 - 0 dB
	1 - 6.0 dB
	2 - 12 dB

	lbi_response; Integrator Response
	0 - 0 mS
	1 - 25 mS
	2 - 50 mS
	3 - 100 mS

	hardLimit
	0 - Hard limit disabled. AVC Compressor/Expander enabled.
	1 - Hard limit enabled. The signal is limited to the programmed threshold (signal saturates at the threshold)

	threshold
	floating point in range 0 to -96 dB

	attack
	floating point figure is dB/s rate at which gain is increased

	decay
	floating point figure is dB/s rate at which gain is reduced
*/
unsigned short sgtl5000_auto_volumeControl(uint8_t max_gain, uint8_t lbi_response, uint8_t hardLimit, float threshold, float attack, float decay)
{
	if(max_gain>2) max_gain=2;
	lbi_response&=3;
	hardLimit&=1;
	
	uint8_t thresh=(pow(10,threshold/20)*0.636)*pow(2,15);
	uint8_t att=(1-pow(10,-(attack/(20*44100))))*pow(2,19);
	uint8_t dec=(1-pow(10,-(decay/(20*44100))))*pow(2,23);
	
	sgtl5000_write_reg(DAP_AVC_THRESHOLD,thresh);
	sgtl5000_write_reg(DAP_AVC_ATTACK,att);
	sgtl5000_write_reg(DAP_AVC_DECAY,dec);
	
	return sgtl5000_modify_reg(DAP_AVC_CTRL,max_gain<<12|lbi_response<<8|hardLimit<<5,3<<12|3<<8|1<<5);
}
unsigned short sgtl5000_auto_volume_enable()
{
	return sgtl5000_modify_reg(DAP_AVC_CTRL, 1, 1);
}
unsigned short sgtl5000_auto_volume_disable()
{
	return sgtl5000_modify_reg(DAP_AVC_CTRL, 0, 1);
}

unsigned short sgtl5000_enhance_bass(float lr_lev, float bass_lev)
{
	return sgtl5000_modify_reg(DAP_BASS_ENHANCE_CTRL,((0x3F-calc_vol(lr_lev,0x3F))<<8) | (0x7F-calc_vol(bass_lev,0x7F)), (0x3F<<8) | 0x7F);
}
unsigned short sgtl5000_enhance_bass(float lr_lev, float bass_lev, uint8_t hpf_bypass, uint8_t cutoff)
{
	sgtl5000_modify_reg(DAP_BASS_ENHANCE,(hpf_bypass&1)<<8|(cutoff&7)<<4,1<<8|7<<4);
	return sgtl5000_enhance_bass(lr_lev,bass_lev);
}
unsigned short sgtl5000_enhance_bass_enable()
{
	return sgtl5000_modify_reg(DAP_BASS_ENHANCE, 1, 1);
}
unsigned short sgtl5000_enhance_bass_disable()
{
	return sgtl5000_modify_reg(DAP_BASS_ENHANCE, 0, 1);
}
unsigned short sgtl5000_surround_sound(uint8_t width)
{
	return sgtl5000_modify_reg(DAP_SGTL_SURROUND,(width&7)<<4,7<<4);
}
unsigned short sgtl5000_surround_sound(uint8_t width, uint8_t select)
{
	return sgtl5000_modify_reg(DAP_SGTL_SURROUND,((width&7)<<4)|(select&3), (7<<4)|3);
}
unsigned short sgtl5000_surround_sound_enable()
{
	return sgtl5000_modify_reg(DAP_SGTL_SURROUND, 3, 3);
}
unsigned short sgtl5000_surround_sound_disable()
{
	return sgtl5000_modify_reg(DAP_SGTL_SURROUND, 0, 3);
}


void sgtl5000_kill_automation()
{
	semi_automated=false;
}

unsigned char calc_vol(float n, unsigned char range)
{
	// n=(n*(((float)range)/100))+0.499;
	n = (n * (float)range) + 0.499;
	if ((unsigned char)n>range)
		n = range;
	return (unsigned char)n;
}

// DAP_AUDIO_EQ_BASS_BAND0 & DAP_AUDIO_EQ_BAND1 & DAP_AUDIO_EQ_BAND2 etc etc
unsigned short sgtl5000_dap_audio_eq_band(uint8_t band_num, float n) // by signed percentage -100/+100; dap_audio_eq(3);
{
	n=(n*48)+0.499;
	if(n<-47) n=-47;
	if(n>48) n=48;
	n+=47;
	return sgtl5000_modify_reg(DAP_AUDIO_EQ_BASS_BAND0+(band_num*2),(unsigned int)n,127);
}

void sgtl5000_automate(uint8_t dap, uint8_t eq)
{
	//if((dap!=0)&&(!(read(DAP_CONTROL)&1))) audioProcessor_enable();
	if((sgtl5000_read_reg(DAP_AUDIO_EQ)&3) != eq) sgtl5000_eq_select(eq);
}

void sgtl5000_automate(uint8_t dap, uint8_t eq, uint8_t filter_count)
{
	sgtl5000_automate(dap,eq);
	
	if (filter_count > (sgtl5000_read_reg(DAP_PEQ)&7))
		sgtl5000_eq_filter_count(filter_count);
}


// if(SGTL5000_PEQ) quantization_unit=524288; if(tm_AudioFilterBiquad) quantization_unit=2147483648;
void sgtl5000_calc_biquad(uint8_t filtertype, float fC, float dB_Gain, float Q, uint32_t quantization_unit, uint32_t fS, int *coef)
{

// I used resources like http://www.musicdsp.org/files/tm_Audio-EQ-Cookbook.txt
// to make this routine, I tested most of the filter types and they worked. Such filters have limits and
// before calling this routine with varying values the end user should check that those values are limited
// to valid results.

	float A;
	if (filtertype < FILTER_PARAEQ)
		A = pow(10, dB_Gain/20);
	else
		A = pow(10, dB_Gain/40);
	
	float W0 = 2*3.14159265358979323846*fC/fS;
	float cosw=cosf(W0);
	float sinw=sinf(W0);
	//float alpha = sinw*sinh((log(2)/2)*BW*W0/sinw);
	//float beta = sqrt(2*A);
	float alpha = sinw / (2 *Q);
	float beta = sqrtf(A)/Q;
	float b0,b1,b2,a0,a1,a2;

	switch(filtertype)
	{
		case FILTER_LOPASS:
			b0 = (1.0F - cosw) *0.5F; // =(1-COS($H$2))/2
			b1 = 1.0F - cosw;
			b2 = (1.0F - cosw) *0.5F;
			a0 = 1.0F + alpha;
			a1 = 2.0F *cosw;
			a2 = alpha - 1.0F;
		break;
		case FILTER_HIPASS:
			b0 = (1.0F + cosw) *0.5F;
			b1 = -(cosw + 1.0F);
			b2 = (1.0F + cosw) *0.5F;
			a0 = 1.0F + alpha;
			a1 = 2.0F *cosw;
			a2 = alpha - 1.0F;
		break;
		case FILTER_BANDPASS:
			b0 = alpha;
			b1 = 0.0F;
			b2 = -alpha;
			a0 = 1.0F + alpha;
			a1 = 2.0F *cosw;
			a2 = alpha - 1.0F;
	   break;
		case FILTER_NOTCH:
			b0=1;
			b1=-2*cosw;
			b2=1;
			a0=1+alpha;
			a1=2*cosw;
			a2=-(1-alpha);
		break;
			case FILTER_PARAEQ:
			b0 = 1 + (alpha*A);
			b1 =-2 *cosw;
			b2 = 1 - (alpha*A);
			a0 = 1 + (alpha/A);
			a1 = 2 *cosw;
			a2 =-(1-(alpha/A));
		break;
		case FILTER_LOSHELF:
			b0 = A *((A+1.0F) - ((A-1.0F)*cosw) + (beta*sinw));
			b1 = 2.0F *A *((A-1.0F) - ((A+1.0F)*cosw));
			b2 = A *((A+1.0F) - ((A-1.0F)*cosw) - (beta*sinw));
			a0 = (A+1.0F) + ((A-1.0F)*cosw) + (beta*sinw);
			a1 = 2.0F *((A-1.0F) + ((A+1.0F)*cosw));
			a2 = -((A+1.0F) + ((A-1.0F)*cosw) - (beta*sinw));
		break;
		case FILTER_HISHELF:
			b0 = A *((A+1.0F) + ((A-1.0F)*cosw) + (beta*sinw));
			b1 = -2.0F *A *((A-1.0F) + ((A+1.0F)*cosw));
			b2 = A *((A+1.0F) + ((A-1.0F)*cosw) - (beta*sinw));
			a0 = (A+1.0F) - ((A-1.0F)*cosw) + (beta*sinw);
			a1 = -2.0F *((A-1.0F) - ((A+1.0F)*cosw));
			a2 = -((A+1.0F) - ((A-1.0F)*cosw) - (beta*sinw));
		break;
		default:
			b0 = 0.5;
			b1 = 0.0;
			b2 = 0.0;
			a0 = 1.0;
			a1 = 0.0;
			a2 = 0.0;
		break;
	}

	a0=(a0*2)/(float)quantization_unit; // once here instead of five times there...
	b0/=a0;
	*coef++=(int)(b0+0.499);
	b1/=a0;
	*coef++=(int)(b1+0.499);
	b2/=a0;
	*coef++=(int)(b2+0.499);
	a1/=a0;
	*coef++=(int)(a1+0.499);
	a2/=a0;
	*coef++=(int)(a2+0.499);
}



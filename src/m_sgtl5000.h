/* m_Audio Library for Teensy 3.X
 *Copyright (c) 2014, Paul Stoffregen, paul@pjrc.com
 *
 *Development of this audio library was funded by PJRC.COM, LLC by sales of
 *Teensy and m_Audio Adaptor boards.  Please support PJRC's efforts to develop
 *open source software by purchasing Teensy or other PJRC products.
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
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

#ifndef control_sgtl5000_h_
#define control_sgtl5000_h_

#include "m_audiostream.h" // github.com/PaulStoffregen/cores/blob/master/teensy4/m_audio_stream.h
#include "m_audiocontrol.h"

int sgtl5000_enable();

void sgtl5000_set_address(uint8_t level);

int sgtl5000_volume(float n);
int sgtl5000_mute_headphone();
int sgtl5000_unmute_headphone();
int sgtl5000_mute_line_out();
int sgtl5000_unmute_line_out();

int sgtl5000_volume(float left, float right);
int sgtl5000_mic_gain(unsigned int dB);
int sgtl5000_input_select(int n);
int sgtl5000_line_in_level(uint8_t n);
int sgtl5000_line_in_level(uint8_t left, uint8_t right);
unsigned short sgtl5000_line_out_level(uint8_t n);
unsigned short sgtl5000_line_out_level(uint8_t left, uint8_t right);
unsigned short sgtl5000_dac_volume(float n);
unsigned short sgtl5000_dac_volume(float left, float right);
int sgtl5000_dac_volume_ramp();
int sgtl5000_dac_volume_ramp_linear();
int sgtl5000_dac_volume_ramp_disable();
unsigned short sgtl5000_adc_high_pass_filter_enable();
unsigned short sgtl5000_adc_high_pass_filterFreeze();
unsigned short sgtl5000_adc_high_pass_filter_disable();
unsigned short sgtl5000_audio_pre_processor_enable();
unsigned short sgtl5000_audio_post_processor_enable();
unsigned short sgtl5000_audio_processor_disable();
unsigned short sgtl5000_eq_filter_count(uint8_t n);
unsigned short sgtl5000_eq_select(uint8_t n);
unsigned short sgtl5000_eq_band(uint8_t band_num, float n);
void sgtl5000_eq_bands(float bass, float mid_bass, float midrange, float mid_treble, float treble);
void sgtl5000_eq_bands(float bass, float treble);
void sgtl5000_eq_filter(uint8_t filterNum, int *filter_parameters);
unsigned short sgtl5000_auto_volumeControl(uint8_t max_gain, uint8_t lbi_response, uint8_t hardLimit, float threshold, float attack, float decay);
unsigned short sgtl5000_auto_volume_enable();
unsigned short sgtl5000_auto_volume_disable();
unsigned short sgtl5000_enhance_bass(float lr_lev, float bass_lev);
unsigned short sgtl5000_enhance_bass(float lr_lev, float bass_lev, uint8_t hpf_bypass, uint8_t cutoff);
unsigned short sgtl5000_enhance_bass_enable();
unsigned short sgtl5000_enhance_bass_disable();
unsigned short sgtl5000_surround_sound(uint8_t width);
unsigned short sgtl5000_surround_sound(uint8_t width, uint8_t select);
unsigned short sgtl5000_surround_sound_enable();
unsigned short sgtl5000_surround_sound_disable();
void sgtl5000_kill_automation();
void sgtl5000_set_master_mode(uint32_t freqMCLK_in);

int 			sgtl5000_volume_integer	  (unsigned int n); // range: 0x00 to 0x80
unsigned char 	calc_vol		  (float n, unsigned char range);
unsigned int 	sgtl5000_read_reg		  (unsigned int reg);
int 		 	sgtl5000_write_reg		  (unsigned int reg, unsigned int val);
unsigned int 	sgtl5000_modify_reg		  (unsigned int reg, unsigned int val, unsigned int i_mask);
unsigned short 	sgtl5000_dap_audio_eq_band(uint8_t band_num, float n);

void sgtl5000_automate(uint8_t dap, uint8_t eq);
void sgtl5000_automate(uint8_t dap, uint8_t eq, uint8_t filter_count);

void sgtl5000_calc_biquad(uint8_t filtertype, float fC, float dB_Gain, float Q, uint32_t quantization_unit, uint32_t fS, int *coef);

#endif

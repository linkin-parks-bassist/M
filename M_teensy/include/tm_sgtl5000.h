#ifndef control_sgtl5000_h_
#define control_sgtl5000_h_

int sgtl5000_start();
int sgtl5000_soft_reboot();

int sgtl5000_healthy();

int sgtl5000_enable();

void sgtl5000_set_address(uint8_t level);

int sgtl5000_volume(float n);
int sgtl5000_mute_headphone();
int sgtl5000_unmute_headphone();
int sgtl5000_mute_line_out();
int sgtl5000_unmute_line_out();

int sgtl5000_volume(float left, float right);
int sgtl5000_mic_gain(unsigned int dB);
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
unsigned short sgtl5000_adc_high_pass_filter_freeze();
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
unsigned int 	sgtl5000_read_reg		  (unsigned int reg);
int 		 	sgtl5000_write_reg		  (unsigned int reg, unsigned int val);
unsigned int 	sgtl5000_modify_reg		  (unsigned int reg, unsigned int val, unsigned int i_mask);
unsigned short 	sgtl5000_dap_audio_eq_band(uint8_t band_num, float n);

void sgtl5000_automate(uint8_t dap, uint8_t eq);
void sgtl5000_automate(uint8_t dap, uint8_t eq, uint8_t filter_count);

void sgtl5000_calc_biquad(uint8_t filtertype, float fC, float dB_Gain, float Q, uint32_t quantization_unit, uint32_t fS, int *coef);

unsigned char 	calc_vol(float n, unsigned char range);

#endif

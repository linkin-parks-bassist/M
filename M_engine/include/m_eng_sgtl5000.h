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

int sgtl5000_mic_gain(unsigned int dB);
int sgtl5000_line_in_level(uint8_t n);
unsigned short sgtl5000_line_out_level(uint8_t n);
unsigned short sgtl5000_adc_high_pass_filter_enable();
unsigned short sgtl5000_adc_high_pass_filter_freeze();
unsigned short sgtl5000_adc_high_pass_filter_disable();
void sgtl5000_kill_automation();
void sgtl5000_set_master_mode(uint32_t freqMCLK_in);

int 			sgtl5000_volum_eng_integer	  (unsigned int n); // range: 0x00 to 0x80
unsigned int 	sgtl5000_read_reg		  (unsigned int reg);
int 		 	sgtl5000_write_reg		  (unsigned int reg, unsigned int val);
unsigned int 	sgtl5000_modify_reg		  (unsigned int reg, unsigned int val, unsigned int i_mask);
unsigned short 	sgtl5000_dap_audio_eq_band(uint8_t band_num, float n);

void sgtl5000_automate(uint8_t dap, uint8_t eq);

unsigned char 	calc_vol(float n, unsigned char range);

#endif

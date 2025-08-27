#ifndef SGTL5000_H_
#define SGTL5000_H_

typedef struct
{
	int muted;
	int semi_automated;
	
	uint16_t ana_ctrl;
	uint8_t i2c_addr;
} sgtl5000_str;

int sgtl5000_init(sgtl5000_str *cxt);

int sgtl5000_mute_headphone		(sgtl5000_str *sgtl5000);
int sgtl5000_unmute_headphone	(sgtl5000_str *sgtl5000);
int sgtl5000_enable_line_in		(sgtl5000_str *sgtl5000);
int sgtl5000_set_volume			(sgtl5000_str *sgtl5000, float v);
int sgtl5000_line_in_level		(sgtl5000_str *sgtl5000, uint8_t level);

#endif

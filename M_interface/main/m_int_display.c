#include "m_int.h"

int init_display(lv_disp_t **disp)
{
	#ifndef M_SIMULATED
	waveshare_esp32_s3_rgb_lcd_init(disp);
	#endif
	return NO_ERROR;
}

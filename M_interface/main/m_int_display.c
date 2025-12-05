#include "m_int.h"

int init_display(lv_disp_t **disp)
{
	#ifndef M_SIMULATED
	#ifdef USE_5A
	waveshare_dsi_touch_5_a_init(disp);
	#else
	waveshare_esp32_s3_rgb_lcd_init(disp);
	#endif
	#endif
	return NO_ERROR;
}

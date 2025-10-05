#include "waveshare_rgb_lcd_port.h"
#include "em.h"

int init_display(lv_disp_t **disp)
{
	waveshare_esp32_s3_rgb_lcd_init(disp);
	return NO_ERROR;
}

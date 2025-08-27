#include <Arduino.h>
#include "M.h"

int init_audio_context(audio_context *cxt)
{
	if (!cxt) return ERR_NULL_PTR;
	
	int ret_val;
	
	m_printf("Enabling interrupt requests... ");
	//__enable_irq();
	m_printf("✅\n");
	
	m_printf("Configuring I2S... ");
	configure_i2s();
	m_printf("✅\n");
	
	m_printf("Enabling I2S input... ");
	if ((ret_val = init_i2s_input(&cxt->i2s_input)) != NO_ERROR) return ret_val;
	m_printf("✅\n");
	
	m_printf("Enabling I2S output... ");
	if ((ret_val = init_i2s_output(&cxt->i2s_output)) != NO_ERROR) return ret_val;
	m_printf("✅\n");
	
	//delay(10);
	
	m_printf("Initialising SGTL5000...\n");
	if ((ret_val = sgtl5000_init(&cxt->sgtl5000)) != NO_ERROR) return ret_val;
	m_printf("✅\n");
	
	m_printf("Enabling line in... ");
	if ((ret_val = sgtl5000_enable_line_in	(&cxt->sgtl5000)) 		!= NO_ERROR) return ret_val;
	m_printf("✅\n");
	m_printf("Setting default volume... ");
	if ((ret_val = sgtl5000_set_volume		(&cxt->sgtl5000, 0.75)) != NO_ERROR) return ret_val;
	m_printf("✅\n");
	m_printf("Adjusting line in level... ");
	if ((ret_val = sgtl5000_line_in_level	(&cxt->sgtl5000,    5)) != NO_ERROR) return ret_val;
	m_printf("✅\n");
	
	return NO_ERROR;
}

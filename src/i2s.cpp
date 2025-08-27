#include <Arduino.h>
#include "M.h"

DMAMEM __attribute__((aligned(32))) static uint32_t i2s_rx_buffer[AUDIO_BLOCK_N_SAMPLES];
DMAMEM __attribute__((aligned(32))) static uint32_t i2s_tx_buffer[AUDIO_BLOCK_N_SAMPLES];

FLASHMEM
void set_audio_clock(int nfact, int32_t nmult, uint32_t ndiv) // sets PLL4
{
	if (CCM_ANALOG_PLL_AUDIO & CCM_ANALOG_PLL_AUDIO_ENABLE) return;

	CCM_ANALOG_PLL_AUDIO = CCM_ANALOG_PLL_AUDIO_BYPASS | CCM_ANALOG_PLL_AUDIO_ENABLE
			     | CCM_ANALOG_PLL_AUDIO_POST_DIV_SELECT(2) // page 1105
			     | CCM_ANALOG_PLL_AUDIO_DIV_SELECT(nfact);

	CCM_ANALOG_PLL_AUDIO_NUM   = nmult & CCM_ANALOG_PLL_AUDIO_NUM_MASK;
	CCM_ANALOG_PLL_AUDIO_DENOM = ndiv & CCM_ANALOG_PLL_AUDIO_DENOM_MASK;
	
	CCM_ANALOG_PLL_AUDIO &= ~CCM_ANALOG_PLL_AUDIO_POWERDOWN;//Switch on PLL
	while (!(CCM_ANALOG_PLL_AUDIO & CCM_ANALOG_PLL_AUDIO_LOCK)) {}; //Wait for pll-lock
	
	const int div_post_pll = 1; // other values: 2,4
	CCM_ANALOG_MISC2 &= ~(CCM_ANALOG_MISC2_DIV_MSB | CCM_ANALOG_MISC2_DIV_LSB);
	
	if (div_post_pll>1)
		CCM_ANALOG_MISC2 |= CCM_ANALOG_MISC2_DIV_LSB;
	if (div_post_pll>3)
		CCM_ANALOG_MISC2 |= CCM_ANALOG_MISC2_DIV_MSB;
	
	CCM_ANALOG_PLL_AUDIO &= ~CCM_ANALOG_PLL_AUDIO_BYPASS;//Disable Bypass
}

void configure_i2s()
{
	CCM_CCGR5 |= CCM_CCGR5_SAI1(CCM_CCGR_ON);

	// if either transmitter or receiver is enabled, do nothing
	if ((I2S1_TCSR & I2S_TCSR_TE) != 0 || (I2S1_RCSR & I2S_RCSR_RE) != 0)
	{
		CORE_PIN23_CONFIG = 3;  //1:MCLK
		CORE_PIN20_CONFIG = 3;  //1:RX_SYNC (LRCLK)
		return ;
	}

	//PLL:
	int fs = AUDIO_SAMPLE_RATE_EXACT;
	// PLL between 27*24 = 648MHz und 54*24=1296MHz
	int n1 = 4; //SAI prescaler 4 => (n1*n2) = multiple of 4
	int n2 = 1 + (24000000 * 27) / (fs * 256 * n1);

	double C = ((double)fs * 256 * n1 * n2) / 24000000;
	int c0 = C;
	int c2 = 10000;
	int c1 = C * c2 - (c0 * c2);
	set_audio_clock(c0, c1, c2);

	// clear SAI1_CLK register locations
	CCM_CSCMR1 = (CCM_CSCMR1 & ~(CCM_CSCMR1_SAI1_CLK_SEL_MASK))
				| CCM_CSCMR1_SAI1_CLK_SEL(2); // &0x03 // (0,1,2): PLL3PFD0, PLL5, PLL4
	CCM_CS1CDR = (CCM_CS1CDR & ~(CCM_CS1CDR_SAI1_CLK_PRED_MASK | CCM_CS1CDR_SAI1_CLK_PODF_MASK))
				| CCM_CS1CDR_SAI1_CLK_PRED(n1-1) // &0x07
				| CCM_CS1CDR_SAI1_CLK_PODF(n2-1); // &0x3f

	// Select MCLK
	IOMUXC_GPR_GPR1 = (IOMUXC_GPR_GPR1
		& ~(IOMUXC_GPR_GPR1_SAI1_MCLK1_SEL_MASK))
		| (IOMUXC_GPR_GPR1_SAI1_MCLK_DIR | IOMUXC_GPR_GPR1_SAI1_MCLK1_SEL(0));

	CORE_PIN23_CONFIG = 3;  //1:MCLK
	CORE_PIN20_CONFIG = 3;  //1:RX_SYNC  (LRCLK)
	
	CORE_PIN21_CONFIG = 3;  //1:RX_BCLK

	int rsync = 0;
	int tsync = 1;

	I2S1_TMR = 0;
	//I2S1_TCSR = (1<<25); //Reset
	I2S1_TCR1 = I2S_TCR1_RFW(1);
	I2S1_TCR2 = I2S_TCR2_SYNC(tsync) | I2S_TCR2_BCP // sync=0; tx is async;
			| (I2S_TCR2_BCD | I2S_TCR2_DIV((1)) | I2S_TCR2_MSEL(1));
	I2S1_TCR3 = I2S_TCR3_TCE;
	I2S1_TCR4 = I2S_TCR4_FRSZ((2-1)) | I2S_TCR4_SYWD((32-1)) | I2S_TCR4_MF
			| I2S_TCR4_FSD | I2S_TCR4_FSE | I2S_TCR4_FSP;
	I2S1_TCR5 = I2S_TCR5_WNW((32-1)) | I2S_TCR5_W0W((32-1)) | I2S_TCR5_FBT((32-1));

	I2S1_RMR = 0;
	//I2S1_RCSR = (1<<25); //Reset
	I2S1_RCR1 = I2S_RCR1_RFW(1);
	I2S1_RCR2 = I2S_RCR2_SYNC(rsync) | I2S_RCR2_BCP  // sync=0; rx is async;
			| (I2S_RCR2_BCD | I2S_RCR2_DIV((1)) | I2S_RCR2_MSEL(1));
	I2S1_RCR3 = I2S_RCR3_RCE;
	I2S1_RCR4 = I2S_RCR4_FRSZ((2-1)) | I2S_RCR4_SYWD((32-1)) | I2S_RCR4_MF
			| I2S_RCR4_FSE | I2S_RCR4_FSP | I2S_RCR4_FSD;
	I2S1_RCR5 = I2S_RCR5_WNW((32-1)) | I2S_RCR5_W0W((32-1)) | I2S_RCR5_FBT((32-1));
}

int init_i2s_input(i2s_input_struct *str)
{
	if (!str) return ERR_NULL_PTR;
	
	str->dma.begin(true);
	
	CORE_PIN8_CONFIG = 3;
	
	IOMUXC_SAI1_RX_DATA0_SELECT_INPUT = 2;

	str->dma.TCD->SADDR = (void *)((uint32_t)&I2S1_RDR0 + 2);
	str->dma.TCD->SOFF 	= 0;
	str->dma.TCD->ATTR 	= DMA_TCD_ATTR_SSIZE(1) | DMA_TCD_ATTR_DSIZE(1);
	
	str->dma.TCD->NBYTES_MLNO = 2;
	
	str->dma.TCD->SLAST = 0;
	str->dma.TCD->DADDR = i2s_rx_buffer;
	str->dma.TCD->DOFF 	= 2;
	
	str->dma.TCD->CITER_ELINKNO =  sizeof(i2s_rx_buffer) / 2;
	str->dma.TCD->DLASTSGA 		= -sizeof(i2s_rx_buffer);
	str->dma.TCD->BITER_ELINKNO =  sizeof(i2s_rx_buffer) / 2;
	str->dma.TCD->CSR 			=  DMA_TCD_CSR_INTHALF | DMA_TCD_CSR_INTMAJOR;
	str->dma.triggerAtHardwareEvent(DMAMUX_SOURCE_SAI1_RX);

	I2S1_RCSR = I2S_RCSR_RE | I2S_RCSR_BCE | I2S_RCSR_FRDE | I2S_RCSR_FR;
	
	str->dma.enable();
	str->dma.attachInterrupt(i2s_input_isr);
	
	return NO_ERROR;
}

DMAChannel *dma_output_channel = NULL;

int init_i2s_output(i2s_output_struct *str)
{
	if (!str)
		return ERR_NULL_PTR;

	str->dma.begin(true); // Allocate the DMA channel first

	CORE_PIN7_CONFIG  = 3;  //1:TX_DATA0
	str->dma.TCD->SADDR = i2s_tx_buffer;
	str->dma.TCD->SOFF = 2;
	str->dma.TCD->ATTR = DMA_TCD_ATTR_SSIZE(1) | DMA_TCD_ATTR_DSIZE(1);
	str->dma.TCD->NBYTES_MLNO = 2;
	str->dma.TCD->SLAST = -sizeof(i2s_tx_buffer);
	str->dma.TCD->DOFF = 0;
	str->dma.TCD->CITER_ELINKNO = sizeof(i2s_tx_buffer) / 2;
	str->dma.TCD->DLASTSGA = 0;
	str->dma.TCD->BITER_ELINKNO = sizeof(i2s_tx_buffer) / 2;
	str->dma.TCD->CSR = DMA_TCD_CSR_INTHALF | DMA_TCD_CSR_INTMAJOR;
	str->dma.TCD->DADDR = (void *)((uint32_t)&I2S1_TDR0 + 2);
	str->dma.triggerAtHardwareEvent(DMAMUX_SOURCE_SAI1_TX);
	str->dma.enable();

	I2S1_RCSR |= I2S_RCSR_RE | I2S_RCSR_BCE;
	I2S1_TCSR = I2S_TCSR_TE | I2S_TCSR_BCE | I2S_TCSR_FRDE;

	str->dma.attachInterrupt(i2s_output_isr);
	dma_output_channel = &str->dma;

	return NO_ERROR;
}

void i2s_input_isr()
{
	float mean = 0.0;
	
	for (int i = 0; i < AUDIO_BLOCK_N_SAMPLES; i++)
		mean += (float)i2s_rx_buffer[i] / (float)AUDIO_BLOCK_N_SAMPLES;
	
	//Serial.print("Obtained a buffer with mean ");
	//Serial.println(mean, 4);
}

void i2s_output_isr()
{
	Serial.println("Output isr triggered\n");
	int16_t *dest;
	uint32_t saddr;

	saddr = (uint32_t)(dma_output_channel->TCD->SADDR);
	dma_output_channel->clearInterrupt();
	if (saddr < (uint32_t)i2s_tx_buffer + sizeof(i2s_tx_buffer) / 2) {
		// DMA is transmitting the first half of the buffer
		// so we must fill the second half
		dest = (int16_t *)&i2s_tx_buffer[AUDIO_BLOCK_N_SAMPLES/2];
	}
	else
	{
		// DMA is transmitting the second half of the buffer
		// so we must fill the first half
		dest = (int16_t *)i2s_tx_buffer;
	}
	
	
	
	for (int i = 0; i < AUDIO_BLOCK_N_SAMPLES; i++)
	{
		dest[2 * i] = (int16_t)(pow(2, 14) * sin(3.14159 * ((float)i / AUDIO_BLOCK_N_SAMPLES)));
		dest[2 * i+1] = dest[i];
	}
	//memset(dest, 0, AUDIO_BLOCK_N_SAMPLES * 2);
	
	arm_dcache_flush_delete(dest, sizeof(i2s_tx_buffer) / 2 );
}

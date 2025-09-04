#include <DMAChannel.h>
#include "M.h"

DMAMEM __attribute__((aligned(32))) static uint32_t i2s_rx_buffer[AUDIO_BLOCK_SAMPLES];
DMAMEM __attribute__((aligned(32))) static uint32_t i2s_tx_buffer[AUDIO_BLOCK_SAMPLES];

m_audio_block_int *i2s_in_block_left  = NULL;
m_audio_block_int *i2s_in_block_right = NULL;

uint16_t	i2s_in_block_offset = 0;
bool 	 	i2s_in_update_responsibility = false;
DMAChannel 	i2s_in_dma(false);

m_audio_block_int *i2s_out_block_left_1st  = NULL;
m_audio_block_int *i2s_out_block_right_1st = NULL;
m_audio_block_int *i2s_out_block_left_2nd  = NULL;
m_audio_block_int *i2s_out_block_right_2nd = NULL;

uint16_t   i2s_out_block_left_offset = 0;
uint16_t   i2s_out_block_right_offset = 0;
bool 	   i2s_out_update_responsibility = false;
DMAChannel i2s_out_dma(false);

m_audio_block_int	i2s_input_blocks [2];
m_audio_block_int	i2s_output_blocks[2];

void configure_i2s()
{
	CCM_CCGR5 |= CCM_CCGR5_SAI1(CCM_CCGR_ON);

	// if either transmitter or receiver is enabled, do nothing
	if ((I2S1_TCSR & I2S_TCSR_TE) != 0 || (I2S1_RCSR & I2S_RCSR_RE) != 0)
	{
		CORE_PIN23_CONFIG = 3;  //1:MCLK
		CORE_PIN20_CONFIG = 3;  //1:RX_SYNC (LRCLK)
		return;
	}

	//PLL:
	int fs = AUDIO_SAMPLE_RATE_EXACT;
	// PLL between 27*24 = 648MHz und 54*24=1296MHz
	int n1 = 4; //SAI prescaler 4 => (n1*n2) = multiple of 4
	int n2 = 1 + (24000000 *27) / (fs *256 *n1);

	double C = ((double)fs *256 *n1 *n2) / 24000000;
	int c0 = C;
	int c2 = 10000;
	int c1 = C *c2 - (c0 *c2);
	m_set_audioClock(c0, c1, c2);

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

void init_i2s()
{
	/* First, init i2s input */
	i2s_in_dma.begin(true); // Allocate the DMA channel first

	configure_i2s();

	CORE_PIN8_CONFIG  = 3;  //1:RX_DATA0
	IOMUXC_SAI1_RX_DATA0_SELECT_INPUT = 2;

	i2s_in_dma.TCD->SADDR = (void *)((uint32_t)&I2S1_RDR0 + 2);
	i2s_in_dma.TCD->SOFF = 0;
	i2s_in_dma.TCD->ATTR = DMA_TCD_ATTR_SSIZE(1) | DMA_TCD_ATTR_DSIZE(1);
	i2s_in_dma.TCD->NBYTES_MLNO = 2;
	i2s_in_dma.TCD->SLAST = 0;
	i2s_in_dma.TCD->DADDR = i2s_rx_buffer;
	i2s_in_dma.TCD->DOFF = 2;
	i2s_in_dma.TCD->CITER_ELINKNO = sizeof(i2s_rx_buffer) / 2;
	i2s_in_dma.TCD->DLASTSGA = -sizeof(i2s_rx_buffer);
	i2s_in_dma.TCD->BITER_ELINKNO = sizeof(i2s_rx_buffer) / 2;
	i2s_in_dma.TCD->CSR = DMA_TCD_CSR_INTHALF | DMA_TCD_CSR_INTMAJOR;
	i2s_in_dma.triggerAtHardwareEvent(DMAMUX_SOURCE_SAI1_RX);

	I2S1_RCSR = I2S_RCSR_RE | I2S_RCSR_BCE | I2S_RCSR_FRDE | I2S_RCSR_FR;

	i2s_in_update_responsibility = update_setup();
	i2s_in_dma.enable();
	i2s_in_dma.attachInterrupt(m_i2s_input_isr);
	
	/* Next, init i2s output */
	
	i2s_out_dma.begin(true); // Allocate the DMA channel first

	i2s_out_block_left_1st  = NULL;
	i2s_out_block_right_1st = NULL;
	
	configure_i2s();

	CORE_PIN7_CONFIG  = 3;  //1:TX_DATA0
	i2s_out_dma.TCD->SADDR = i2s_tx_buffer;
	i2s_out_dma.TCD->SOFF = 2;
	i2s_out_dma.TCD->ATTR = DMA_TCD_ATTR_SSIZE(1) | DMA_TCD_ATTR_DSIZE(1);
	i2s_out_dma.TCD->NBYTES_MLNO = 2;
	i2s_out_dma.TCD->SLAST = -sizeof(i2s_tx_buffer);
	i2s_out_dma.TCD->DOFF = 0;
	i2s_out_dma.TCD->CITER_ELINKNO = sizeof(i2s_tx_buffer) / 2;
	i2s_out_dma.TCD->DLASTSGA = 0;
	i2s_out_dma.TCD->BITER_ELINKNO = sizeof(i2s_tx_buffer) / 2;
	i2s_out_dma.TCD->CSR = DMA_TCD_CSR_INTHALF | DMA_TCD_CSR_INTMAJOR;
	i2s_out_dma.TCD->DADDR = (void *)((uint32_t)&I2S1_TDR0 + 2);
	i2s_out_dma.triggerAtHardwareEvent(DMAMUX_SOURCE_SAI1_TX);
	i2s_out_dma.enable();

	I2S1_RCSR |= I2S_RCSR_RE | I2S_RCSR_BCE;
	I2S1_TCSR = I2S_TCSR_TE | I2S_TCSR_BCE | I2S_TCSR_FRDE;

	i2s_out_update_responsibility = update_setup();
	i2s_out_dma.attachInterrupt(m_i2s_output_isr);
}

void m_i2s_input_isr()
{
	uint32_t daddr, offset;
	const int16_t *src, *end;
	int16_t *dest_left, *dest_right;
	m_audio_block_int *left, *right;

	daddr = (uint32_t)(i2s_in_dma.TCD->DADDR);
	i2s_in_dma.clearInterrupt();

	if (daddr < (uint32_t)i2s_rx_buffer + sizeof(i2s_rx_buffer) / 2)
	{
		// DMA is receiving to the first half of the buffer
		// need to remove data from the second half
		src = (int16_t *)&i2s_rx_buffer[AUDIO_BLOCK_SAMPLES/2];
		end = (int16_t *)&i2s_rx_buffer[AUDIO_BLOCK_SAMPLES];
		
		if (i2s_in_update_responsibility) update_all();
	}
	else
	{
		// DMA is receiving to the second half of the buffer
		// need to remove data from the first half
		src = (int16_t*)&i2s_rx_buffer[0];
		end = (int16_t*)&i2s_rx_buffer[AUDIO_BLOCK_SAMPLES/2];
	}
	
	left  = i2s_in_block_left;
	right = i2s_in_block_right;
	
	if (left != NULL && right != NULL)
	{
		offset = i2s_in_block_offset;
		if (offset <= AUDIO_BLOCK_SAMPLES/2)
		{
			dest_left  = &(left->data[offset]);
			dest_right = &(right->data[offset]);
			
			i2s_in_block_offset = offset + AUDIO_BLOCK_SAMPLES/2;
			arm_dcache_delete((void*)src, sizeof(i2s_rx_buffer) / 2);
			
			do {
				*dest_left++  = *src++;
				*dest_right++ = *src++;
			} while (src < end);
		}
	}
}

void m_i2s_output_isr()
{
	int16_t *dest;
	m_audio_block_int *blockL, *blockR;
	uint32_t saddr, offsetL, offsetR;

	saddr = (uint32_t)(i2s_out_dma.TCD->SADDR);
	i2s_out_dma.clearInterrupt();
	
	if (saddr < (uint32_t)i2s_tx_buffer + sizeof(i2s_tx_buffer) / 2)
	{
		// DMA is transmitting the first half of the buffer
		// so we must fill the second half
		dest = (int16_t*)&i2s_tx_buffer[AUDIO_BLOCK_SAMPLES/2];
		if (i2s_out_update_responsibility) update_all();
	}
	else
	{
		// DMA is transmitting the second half of the buffer
		// so we must fill the first half
		dest = (int16_t*)i2s_tx_buffer;
	}

	blockL  = i2s_out_block_left_1st;
	blockR  = i2s_out_block_right_1st;
	offsetL = i2s_out_block_left_offset;
	offsetR = i2s_out_block_right_offset;

	if (blockL && blockR)
	{
		memcpy_tointerleaveLR(dest, blockL->data + offsetL, blockR->data + offsetR);
		offsetL += AUDIO_BLOCK_SAMPLES / 2;
		offsetR += AUDIO_BLOCK_SAMPLES / 2;
	}
	else if (blockL)
	{
		memcpy_tointerleaveL(dest, blockL->data + offsetL);
		offsetL += AUDIO_BLOCK_SAMPLES / 2;
	}
	else if (blockR)
	{
		memcpy_tointerleaveR(dest, blockR->data + offsetR);
		offsetR += AUDIO_BLOCK_SAMPLES / 2;
	}
	else
	{
		memset(dest, 0, AUDIO_BLOCK_SAMPLES * 2);
	}

	arm_dcache_flush_delete(dest, sizeof(i2s_tx_buffer) / 2);

	if (offsetL < AUDIO_BLOCK_SAMPLES)
	{
		i2s_out_block_left_offset = offsetL;
	}
	else
	{
		i2s_out_block_left_offset = 0;
		release_block_int(blockL);
		i2s_out_block_left_1st = i2s_out_block_left_2nd;
		i2s_out_block_left_2nd = NULL;
	}
	
	if (offsetR < AUDIO_BLOCK_SAMPLES)
	{
		i2s_out_block_right_offset = offsetR;
	}
	else
	{
		i2s_out_block_right_offset = 0;
		release_block_int(blockR);
		i2s_out_block_right_1st = i2s_out_block_right_2nd;
		i2s_out_block_right_2nd = NULL;
	}
}

void i2s_in_transmit(m_audio_block_int *block, unsigned char index)
{
	#ifdef SKIP_EVERYTHING
	#ifdef TRY_CONVERT
	float f[AUDIO_BLOCK_SAMPLES];
	convert_block_int_to_float(f, block->data);
	convert_block_float_to_int(i2s_output_blocks[1 - index].data, f);
	#else
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		i2s_output_blocks[1 - index].data[i] = block->data[i];
	}
	#endif
	#else
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		i2s_input_blocks[index].data[i] = block->data[i];
	}
	#endif
	
	/*for (m_audio_connection *c = i2s_destination_list; c != NULL; c = c->next_dest)
	{
		if (c->src_index == index)
		{
			if (c->dst->inputQueue[c->dest_index] == NULL)
			{
				c->dst->inputQueue[c->dest_index] = block;
				block->ref_count++;
			}
		}
	}*/
}

void i2s_input_update()
{
	m_audio_block_int *new_left=NULL, *new_right=NULL, *out_left=NULL, *out_right=NULL;

	// allocate 2 new blocks, but if one fails, allocate neither
	new_left = allocate_block_int();
	if (new_left != NULL)
	{
		new_right = allocate_block_int();
		if (new_right == NULL)
		{
			release_block_int(new_left);
			new_left = NULL;
		}
	}
	
	__disable_irq();
	
	if (i2s_in_block_offset >= AUDIO_BLOCK_SAMPLES)
	{
		// the DMA filled 2 blocks, so grab them and get the
		// 2 new blocks to the DMA, as quickly as possible
		out_left 			= i2s_in_block_left;
		i2s_in_block_left 	= new_left;
		out_right 			= i2s_in_block_right;
		i2s_in_block_right 	= new_right;
		i2s_in_block_offset = 0;
		
		__enable_irq();
		
		// then transmit the DMA's former blocks
		i2s_in_transmit(out_left, 0);
		release_block_int(out_left);
		
		i2s_in_transmit(out_right, 1);
		release_block_int(out_right);
	}
	else if (new_left != NULL)
	{
		// the DMA didn't fill blocks, but we allocated blocks
		if (i2s_in_block_left == NULL)
		{
			// the DMA doesn't have any blocks to fill, so
			// give it the ones we just allocated
			i2s_in_block_left = new_left;
			i2s_in_block_right = new_right;
			i2s_in_block_offset = 0;
			__enable_irq();
		}
		else
		{
			// the DMA already has blocks, doesn't need these
			__enable_irq();
			release_block_int(new_left);
			release_block_int(new_right);
		}
	}
	else
	{
		// The DMA didn't fill blocks, and we could not allocate
		// memory... the system is likely starving for memory!
		// Sadly, there's nothing we can do.
		__enable_irq();
	}
}

// Receive block from an input.  The block's data
// may be shared with other streams, so it must not be written
m_audio_block_int *i2s_out_receive_read_only(unsigned int index)
{
	m_audio_block_int *in;

	if (index >= 2)
		return NULL;
	
	in = &i2s_output_blocks[index];
	
	return in;
}

void i2s_output_update()
{
	m_audio_block_int *block;
	block = i2s_out_receive_read_only(0); // input 0 = left channel
	if (block)
	{
		__disable_irq();
		if (i2s_out_block_left_1st == NULL)
		{
			i2s_out_block_left_1st = block;
			i2s_out_block_left_offset = 0;
			__enable_irq();
		} else if (i2s_out_block_left_2nd == NULL)
		{
			i2s_out_block_left_2nd = block;
			__enable_irq();
		}
		else
		{
			i2s_out_block_left_1st = i2s_out_block_left_2nd;
			i2s_out_block_left_2nd = block;
			i2s_out_block_left_offset = 0;
			__enable_irq();
		}
	}
	block = i2s_out_receive_read_only(1); // input 1 = right channel
	if (block) 
	{
		__disable_irq();
		if (i2s_out_block_right_1st == NULL)
		{
			i2s_out_block_right_1st = block;
			i2s_out_block_right_offset = 0;
			__enable_irq();
		}
		else if (i2s_out_block_right_2nd == NULL)
		{
			i2s_out_block_right_2nd = block;
			__enable_irq();
		}
		else
		{
			i2s_out_block_right_1st = i2s_out_block_right_2nd;
			i2s_out_block_right_2nd = block;
			i2s_out_block_right_offset = 0;
			__enable_irq();
		}
	}
	
	
}


void i2s_output_transmit_mono(m_audio_block_float *block)
{
	if (!block)
		return;
	
	convert_block_float_to_int(i2s_output_blocks[0].data, block->data);
	convert_block_float_to_int(i2s_output_blocks[1].data, block->data);
}

#ifndef M_I2S_DMA_H_
#define M_I2S_DMA_H_

typedef int16_t raw_sample_t;

void init_i2s_dma();

void m_eng_i2s_input_isr();
void m_eng_i2s_output_isr();

void i2s_input_update();
void i2s_output_update();

void i2s_output_transmit_mono_int  (raw_sample_t *block);
void i2s_output_transmit_mono_float(float *block);

extern raw_sample_t	i2s_input_blocks[2][AUDIO_BLOCK_SAMPLES];

#endif

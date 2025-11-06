#ifndef M_I2S_DMA_H_
#define M_I2S_DMA_H_

void init_i2s();

void m_eng_i2s_input_isr();
void m_eng_i2s_output_isr();

void i2s_input_update();
void i2s_output_update();

void i2s_output_transmit_mono_int  (int16_t *block);
void i2s_output_transmit_mono_float(float   *block);

extern m_eng_audio_block_int	i2s_input_blocks[2];

#endif

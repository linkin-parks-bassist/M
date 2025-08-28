#ifndef M_I2S_DMA_H_
#define M_I2S_DMA_H_

void init_i2s();

void m_i2s_input_isr();
void m_i2s_output_isr();

void i2s_input_update();
void i2s_output_update();

extern m_audio_connection*	i2s_destination_list;
extern m_audio_block_t*		i2s_output_queue[2];
extern uint8_t				n_i2s_out_connections;

#endif

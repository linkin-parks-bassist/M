#ifndef M_I2S_H_
#define M_I2S_H_

#include <DMAChannel.h>

typedef struct
{
	DMAChannel dma;
} i2s_input_struct;


typedef struct
{
	DMAChannel dma;
} i2s_output_struct;

void i2s_input_isr();
void i2s_output_isr();

int init_i2s_input(i2s_input_struct *str);
int init_i2s_output(i2s_output_struct *str);

void configure_i2s();

#endif

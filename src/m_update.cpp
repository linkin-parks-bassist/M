#include "M.h"

m_pipeline *active_pipeline = NULL;

void set_active_pipeline(m_pipeline *pipeline)
{
	active_pipeline = pipeline;
	//m_printf("Obtained new active pipeline, 0x%x.\n", active_pipeline);
}

void update_all()
{
	NVIC_SET_PENDING(IRQ_SOFTWARE);
}

bool update_setup()
{
	if (update_scheduled)
		return false;
	
	attachInterruptVector(IRQ_SOFTWARE, m_software_isr);
	NVIC_SET_PRIORITY(IRQ_SOFTWARE, 208); // 255 = lowest priority
	NVIC_ENABLE_IRQ(IRQ_SOFTWARE);
	
	update_scheduled = true;
	return true;
}

void update_stop()
{
	NVIC_DISABLE_IRQ(IRQ_SOFTWARE);
	update_scheduled = false;
}

float output_avg = 0.0f;

void m_software_isr()
{
	i2s_input_update();
	
	m_audio_block_int *block_in = &i2s_input_blocks[1];
	int16_t *data_in = i2s_input_blocks[1].data;
	
	float avg = 0.0f;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		avg += (float)data_in[i];
	}
	avg /= AUDIO_BLOCK_SAMPLES;
	
	m_printf("Average input data: %f\n", avg);
	//Serial.println(abs, 4);
	
	if (!active_pipeline)
	{
		m_audio_block_float f_block;
		convert_block_int_to_float(f_block.data, data_in);
		i2s_output_transmit_mono(&f_block);
	}
	else
	{
		compute_pipeline(active_pipeline, data_in);
		#ifndef SKIP_EVERYTHING
		i2s_output_transmit_mono(active_pipeline->output_node.block);
		
		avg = 0.0f;
		for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		{
			avg += 32767.0f * active_pipeline->output_node.block->data[i];
		}
		avg /= AUDIO_BLOCK_SAMPLES;
		
		m_printf("Average output data: %f\n", avg);
		
		output_avg = 0.9 * output_avg + 0.1 * avg;
		
		m_printf("Aggregate avg output: %6f\n", output_avg);
		#endif
		
		
		
		for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		{
			//Serial.print(data_in[i], 7);
			//Serial.print(" ");
			//Serial.print(active_pipeline->output_node.block->data[i], 7);
			//Serial.print("\n");
			Serial.flush();
		}
	}
	
	i2s_output_update();

	asm("DSB");
}

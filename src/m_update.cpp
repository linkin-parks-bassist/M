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

void m_software_isr()
{
	i2s_input_update();
	
	m_audio_block_float *block_in = &i2s_input_blocks[1];
	float *data_in = i2s_input_blocks[1].data;
	
	/*float abs_max = 0;
	float abs;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		abs = fabs(data_in[i]);
		if (abs > abs_max)
			abs_max = abs;
	}
	
	//Serial.println(abs, 4);*/
	
	if (!active_pipeline)
	{
		i2s_output_transmit_mono(block_in);
	}
	else
	{
		compute_pipeline(active_pipeline, data_in);
		#ifndef SKIP_EVERYTHING
		i2s_output_transmit_mono(active_pipeline->output_node.block);
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

#include "M.h"

m_pipeline *active_pipeline = NULL;

void set_active_pipeline(m_pipeline *pipeline)
{
	active_pipeline = pipeline;
	m_printf("Obtained new active pipeline, 0x%x.\n", active_pipeline);
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
	m_printf("Software isr called.\n");
	if (!active_pipeline)
	{
		m_printf("No active pipeline; transmit all zeroes\n");
		
		m_audio_block_float zero;
		for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
			zero.data[i] = 0;
		i2s_output_transmit_mono(&zero);
		
		return;
	}
	m_audio_stream *p;

	uint32_t totalcycles = ARM_DWT_CYCCNT;
	
	i2s_input_update();
	
	m_printf("Obtained input data....\n");
	
	float max_abs = 0;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		if (fabs(i2s_input_blocks[0].data[i]) > max_abs)
			max_abs = fabs(i2s_input_blocks[0].data[i]);
	}
	
	m_printf("Input block peak amplitude: %4f\n", max_abs);
	
	compute_pipeline(active_pipeline, i2s_input_blocks[0].data);
	
	m_audio_block_float *output = active_pipeline->output_node.block;
	
	if (!output)
	{
		m_printf("Outblock is null!!\n");
	}
	
	max_abs = 0.0;
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		if (fabs(output->data[i]) > max_abs)
			max_abs = fabs(output->data[i]);
	}
	
	m_printf("Output block peak amplitude: %4f\n", max_abs);
	
	i2s_output_transmit_mono(active_pipeline->output_node.block);
	
	
	
	/*
	for (p = first_update; p; p = p->next_update)
	{
		if (p->active)
		{
			uint32_t cycles = ARM_DWT_CYCCNT;
			p->update();
			// TODO: traverse inputQueueArray and release
			// any input blocks that weren't consumed?
			cycles = (ARM_DWT_CYCCNT - cycles) >> 6;
			p->cpu_cycles = cycles;
			
			if (cycles > p->cpu_cycles_max)
				p->cpu_cycles_max = cycles;
		}
	}
	*/
	
	totalcycles = (ARM_DWT_CYCCNT - totalcycles) >> 6;
	cpu_cycles_total = totalcycles;
	
	if (totalcycles > cpu_cycles_total_max)
	{
		cpu_cycles_total_max = totalcycles;
	}
	
	i2s_output_update();

	asm("DSB");
}

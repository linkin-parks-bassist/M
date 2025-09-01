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
	
	if (!active_pipeline)
	{
		i2s_output_transmit_mono(&i2s_input_blocks[0]);
	}
	else
	{
		compute_pipeline(active_pipeline, i2s_input_blocks[0].data);
		i2s_output_transmit_mono(active_pipeline->output_node.block);
	}
	
	i2s_output_update();

	asm("DSB");
}

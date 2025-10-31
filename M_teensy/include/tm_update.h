#ifndef M_UPDATE_H_
#define M_UPDATE_H_

#ifndef TM_SIMULATED
#define tm_disable_software_interrupts() 			(NVIC_DISABLE_IRQ(IRQ_SOFTWARE))
#define tm_enable_software_interrupts()   			(NVIC_ENABLE_IRQ(IRQ_SOFTWARE))
#else
#define tm_disable_software_interrupts()
#define tm_enable_software_interrupts()
#endif

void update_all();

int update_setup();
void update_stop();

void set_active_pipeline(tm_pipeline *pipeline);
int switch_active_pipeline(tm_pipeline *pipeline);

void tm_software_isr();

extern tm_pipeline *active_pipeline;

#endif

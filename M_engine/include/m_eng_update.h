#ifndef M_UPDATE_H_
#define M_UPDATE_H_

#ifndef M_ENG_SIMULATED
#define m_eng_disable_software_interrupts() 			(NVIC_DISABLE_IRQ(IRQ_SOFTWARE))
#define m_eng_enable_software_interrupts()   			(NVIC_ENABLE_IRQ(IRQ_SOFTWARE))
#else
#define m_eng_disable_software_interrupts()
#define m_eng_enable_software_interrupts()
#endif

void update_all();

int update_setup();
void update_stop();

void set_active_pipeline(m_eng_pipeline *pipeline);
int switch_active_pipeline(m_eng_pipeline *pipeline);

void m_eng_software_isr();

extern m_eng_pipeline *active_pipeline;

#endif

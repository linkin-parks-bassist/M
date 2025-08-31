#ifndef M_UPDATE_H_
#define M_UPDATE_H_

void update_all();

bool update_setup();
void update_stop();

void set_active_pipeline(m_pipeline *pipeline);
void m_software_isr();

extern m_pipeline *active_pipeline;

#endif

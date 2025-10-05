#ifndef M_UPDATE_H_
#define M_UPDATE_H_

void update_all();

bool update_setup();
void update_stop();

void set_active_pipeline(tm_pipeline *pipeline);
int switch_active_pipeline(tm_pipeline *pipeline);

void tm_software_isr();

extern tm_pipeline *active_pipeline;

#endif

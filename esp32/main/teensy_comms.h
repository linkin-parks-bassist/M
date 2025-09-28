#ifndef M_TEENSY_COMMS_H_
#define M_TEENSY_COMMS_H_

#include "m_comms.h"

#define ET_PING_INTERVAL_MS_ONLINE  1000
#define ET_PING_INTERVAL_MS_OFFLINE  100

extern QueueHandle_t et_msg_queue;

int init_teensy_comms();

int queue_msg_to_teensy(et_msg msg);

#endif

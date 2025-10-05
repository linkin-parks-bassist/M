#ifndef M_TEENSY_COMMS_H_
#define M_TEENSY_COMMS_H_

#define ET_PING_INTERVAL_MS_ONLINE  1000
#define ET_PING_INTERVAL_MS_OFFLINE  100

#define PRINT_RESPONSE_BYTES
//#define PING_TEENSY

extern QueueHandle_t et_msg_queue;

int init_teensy_msg_queue();
int begin_teensy_comms();

int queue_msg_to_teensy(et_msg msg);

int send_parameter_change  (m_parameter_id id, float new_value);
int request_parameter_value(m_parameter_id id, void *widget);

int comms_idle();

void init_teensy_sync_all();
void init_teensy_sync_profile	 (uint16_t pid);
void init_teensy_sync_transformer(uint16_t pid, uint16_t tid);
void init_teensy_sync_parameter	 (uint16_t pid, uint16_t tid, uint16_t id);


#endif

#ifndef M_TEENSY_COMMS_H_
#define M_TEENSY_COMMS_H_

#define ET_PING_INTERVAL_MS_ONLINE  1000
#define ET_PING_INTERVAL_MS_OFFLINE  100

//#define PING_TEENSY

DECLARE_LINKED_PTR_LIST(m_message);

extern QueueHandle_t m_message_queue;

int init_m_int_msg_queue();
int begin_m_int_comms();

int queue_msg_to_teensy(m_message msg);

int send_parameter_change  (m_parameter_id id, float new_value);
int request_parameter_value(m_parameter_id id, void *widget);

#endif

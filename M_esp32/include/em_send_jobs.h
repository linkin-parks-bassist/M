#ifndef EM_SEND_JOBS_H_
#define EM_SEND_JOBS_H_


typedef struct
{
	int done;
	void *data;
	void (*callback)(void *arg);
} em_send_job;

int init_send_jobs_handler();
void send_jobs_handler_task(void *arg);

extern QueueHandle_t send_jobs_queue;

#endif

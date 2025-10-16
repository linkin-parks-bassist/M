#include "em.h"

QueueHandle_t send_jobs_queue;
static TaskHandle_t send_jobs_handle;

void submit_send_job(em_send_job job)
{
	xQueueSend(send_jobs_queue, &job, portMAX_DELAY);
}

void send_jobs_handler_task(void *arg)
{
	TickType_t last_wake = xTaskGetTickCount();
	
	em_send_job job;
	
	while (true)
	{
		if (xQueueReceive(send_jobs_queue, &job, 0) == pdTRUE)
		{
			if (job.callback)
			{
				job.callback(&job);
				
				while (!job.done)
					vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(10));
			}
		}
		
		vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(3));
	}
}

int init_send_jobs_handler()
{
	send_jobs_queue = xQueueCreate(256, sizeof(em_send_job));
	
	xTaskCreatePinnedToCore(
		send_jobs_handler_task,
		"Sendjobs handler task",
		1024,
		NULL,
		8,
		&send_jobs_handle,
		1
	);
}

#include "m_int.h"

IMPLEMENT_LINKED_PTR_LIST(m_representation);

QueueHandle_t m_rep_update_queue;

void m_representation_pll_update_all(m_representation_pll *reps)
{
	m_representation_pll *current = reps;
	
	while (current)
	{
		if (current->data && current->data->update)
		{
			current->data->update(current->data->representer, current->data->representee);
		}
		
		current = current->next;
	}
}

void update_queued_representations_cb(lv_timer_t * timer)
{
	m_representation_pll *list;
	
	while (xQueueReceive(m_rep_update_queue, &list, 0) == pdTRUE)
	{
		if (list)
			m_representation_pll_update_all(list);
	}
}

int init_representation_updater()
{
	m_rep_update_queue = xQueueCreate(16, sizeof(m_representation_pll*));
	lv_timer_t * timer = lv_timer_create(update_queued_representations_cb, 1,  NULL);
	return NO_ERROR;
}

int queue_representation_list_update(m_representation_pll *reps)
{
	if (xQueueSend(m_rep_update_queue, (void*)&reps, (TickType_t)10) != pdPASS)
	{
		printf("Representation list queueing failed!\n");
		return ERR_QUEUE_SEND_FAILED;
	}
	
	return NO_ERROR;
}


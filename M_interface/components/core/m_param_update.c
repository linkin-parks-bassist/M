#include <freertos/FreeRTOS.h>
#include "m_linked_list.h"
#include "m_int_parameter.h"
#include "m_int_transformer.h"
#include "m_int_context.h"
#include "m_param_update.h"
#include "m_int_fpga.h"

#include "m_error_codes.h"

#define UPDATE_QUEUE_LENGTH 64

static m_parameter_update update_queue[UPDATE_QUEUE_LENGTH];
static int n_waiting = 0;
static int update_queue_head = 0;
static int update_queue_tail = 0;

static m_parameter_update update_array[MAX_CONCURRENT_PARAM_UPDATES];
static int n_updates = 0;

QueueHandle_t update_rtos_queue;

void remove_param_update(int index)
{
	for (int i = index; i + 1 < n_updates; i++)
		update_array[i] = update_array[i+1];
	
	n_updates--;
}

int add_param_update(m_parameter_update up)
{
	for (int i = 0; i < n_updates; i++)
	{
		if (update_queue[i].id.profile_id 		== up.id.profile_id
		 && update_queue[i].id.transformer_id 	== up.id.transformer_id
		 && update_queue[i].id.parameter_id 	== up.id.parameter_id)
		{
			update_array[i].target = up.target;
		}
	}
	
	if (n_updates + 1 >= MAX_CONCURRENT_PARAM_UPDATES)
		return ERR_CURRENTLY_EXHAUSTED;
	
	update_array[n_updates++] = up;
	
	return NO_ERROR;
}

void print_parameter_update(m_parameter_update up)
{
	printf("%d.%d.%d -> %s%.03f", up.id.profile_id, up.id.transformer_id, up.id.parameter_id, (up.target >= 0) ? " " : "", up.target);
}

void m_param_update_task(void *arg)
{
	update_rtos_queue = xQueueCreate(16, sizeof(m_parameter_update));
	
	TickType_t last_wake = xTaskGetTickCount();
	
	m_parameter_update current;
	m_transformer *trans;
	m_parameter *param;
	
	float diff;
	int enqueue;
	int send;
	
	while (1)
	{
		while ((update_queue_tail + 1) % UPDATE_QUEUE_LENGTH != update_queue_head && xQueueReceive(update_rtos_queue, &current, 0) == pdPASS)
		{
			printf("Considering new update ");
			print_parameter_update(current);
			
			enqueue = 1;
			printf(". Check array (%d entries)\n", n_updates);
			for (int i = 0; i < n_updates; i++)
			{
				printf("array_update[%d] = ", i);
				print_parameter_update(current);
				printf("\n");
				if (update_array[i].id.profile_id 		== current.id.profile_id
				 && update_array[i].id.transformer_id 	== current.id.transformer_id
				 && update_array[i].id.parameter_id 	== current.id.parameter_id)
				{
					printf("This is the same parameter. Update its target\n");
					update_array[i].target = current.target;
					enqueue = 0;
					break;
				}
			}
			
			if (!enqueue)
				continue;
			
			printf("Check waiting queue (%d entries)\n",
				((update_queue_tail < update_queue_head) ? update_queue_tail + UPDATE_QUEUE_LENGTH : update_queue_tail) - update_queue_head);
			for (int j = update_queue_tail; j != update_queue_head; j = (j - 1) % UPDATE_QUEUE_LENGTH)
			{
				printf("array_queue[%d] = ", j);
				print_parameter_update(current);
				printf("\n");
				if (update_queue[j].id.profile_id 		== current.id.profile_id
				 && update_queue[j].id.transformer_id 	== current.id.transformer_id
				 && update_queue[j].id.parameter_id 	== current.id.parameter_id)
				{
					printf("This is the same parameter. Update its target\n");
					update_queue[j].target = current.target;
					enqueue = 0;
					break;
				}
			}
			
			if (enqueue)
			{
				update_queue[(update_queue_tail + 1) % UPDATE_QUEUE_LENGTH] = current;
				update_queue_tail = (update_queue_tail + 1) % UPDATE_QUEUE_LENGTH;
			}
		}
		
		while (update_queue_tail != update_queue_head && n_updates < MAX_CONCURRENT_PARAM_UPDATES)
		{
			update_array[n_updates++] = update_queue[update_queue_head];
			update_queue_head = (update_queue_head + 1) % UPDATE_QUEUE_LENGTH;
		}
		
		for (int i = 0; i < n_updates; i++)
		{
			if (cxt_get_parameter_and_transformer_by_id(&global_cxt, update_array[i].id, &update_array[i].p, &update_array[i].t) != NO_ERROR)
			{
				remove_param_update(i);
				i--;
				continue;
			}
			
			param = update_array[i].p;
			
			if (!param)
			{
				remove_param_update(i);
				i--;
				continue;
			}
			
			update_array[i].send = 1;
			
			for (int j = 0; j < i; j++)
			{
				if (update_array[j].t == update_array[i].t)
					update_array[i].send = 0;
			}
			
			if (!(update_array[i].send && update_array[i].t && xSemaphoreTake(update_array[i].t->mutex, 0) == pdTRUE))
				update_array[i].send = 0;
			
			diff = update_array[i].target - param->value;
			
			if (diff > param->max_velocity)
				diff = param->max_velocity;
			
			if (diff < -param->max_velocity)
				diff = -param->max_velocity;
			
			//printf("Move parameter %s (%d.%d.%d) by %f from %f to %f, with target %f\n", param->name, param->id.profile_id, param->id.transformer_id, param->id.parameter_id,
		//		diff, param->value, param->value + diff, update_array[i].target);
			
			param->value = param->value + diff;
		}
		
		for (int i = 0; i < n_updates; i++)
		{			
			if (update_array[i].t && update_array[i].send)
			{
				m_transformer_update_fpga_registers(update_array[i].t);
				xSemaphoreGive(update_array[i].t->mutex);
			}
		}
		
		for (int i = 0; i < n_updates; i++)
		{
			if (!update_array[i].p)
			{
				remove_param_update(i);
				i--;
				continue;
			}
			
			if (update_array[i].p->value == update_array[i].target)
			{
				remove_param_update(i);
				i--;
				continue;
			}
		}
		
		xTaskDelayUntil(&last_wake, pdMS_TO_TICKS(10));
	}
}

int m_parameter_trigger_update(m_parameter *param, float target)
{
	printf("m_parameter_trigger_update, param = %p, target = %f\n", param, target);
	if (!param)
		return ERR_NULL_PTR;
	
	printf("Parameter %s, ID %d.%d.%d. Current value: %f. Update target: %f. Max velocity: %f\n",
		param->name, param->id.profile_id, param->id.transformer_id, param->id.parameter_id,
		param->value, target, param->max_velocity);
	
	m_parameter_update up;
	up.id = param->id;
	up.target = target;
	
	if (xQueueSend(update_rtos_queue, &up, pdMS_TO_TICKS(1)) != pdPASS)
		return ERR_CURRENTLY_EXHAUSTED;
	
	return NO_ERROR;
}

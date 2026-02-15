#include <freertos/FreeRTOS.h>
#include "m_int.h"

#include "m_error_codes.h"

#define UPDATE_QUEUE_LENGTH 64

static m_parameter_update update_queue[UPDATE_QUEUE_LENGTH];
static int n_waiting = 0;
static int update_queue_head = 0;
static int update_queue_tail = 0;

static m_parameter_update update_array[MAX_CONCURRENT_PARAM_UPDATES];
static int n_updates = 0;

#define UPDATE_RATE_HZ 300
#define UPDATE_PERIOD_MS (1000.0f / (float)UPDATE_RATE_HZ)

static const int update_period_ticks = (pdMS_TO_TICKS((int)UPDATE_PERIOD_MS) == 0) ? 1 : pdMS_TO_TICKS((int)UPDATE_PERIOD_MS);

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
	////printf("%d.%d.%d -> %s%.03f\n", up.id.profile_id, up.id.transformer_id, up.id.parameter_id, (up.target >= 0) ? " " : "", up.target);
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
	int commit;
	
	while (1)
	{
		while ((update_queue_tail + 1) % UPDATE_QUEUE_LENGTH != update_queue_head && xQueueReceive(update_rtos_queue, &current, 0) == pdPASS)
		{
			////printf("Considering new update ");
			print_parameter_update(current);
			
			enqueue = 1;
			////printf("Check array (%d entries)\n", n_updates);
			for (int i = 0; i < n_updates; i++)
			{
				////printf("update_array[%d] = ", i);
				print_parameter_update(current);
				if (update_array[i].id.profile_id 		== current.id.profile_id
				 && update_array[i].id.transformer_id 	== current.id.transformer_id
				 && update_array[i].id.parameter_id 	== current.id.parameter_id)
				{
					////printf("This is the same parameter. Update its target\n");
					update_array[i].target = current.target;
					enqueue = 0;
					break;
				}
			}
			
			if (!enqueue)
				continue;
			
			////printf("Check waiting queue (%d entries)\n", ((update_queue_tail < update_queue_head) ? update_queue_tail + UPDATE_QUEUE_LENGTH : update_queue_tail) - update_queue_head);
			for (int j = update_queue_head; j != update_queue_tail; j = (j + 1) % UPDATE_QUEUE_LENGTH)
			{
				////printf("update_queue[%d] = ", j);
				print_parameter_update(update_queue[j]);
				
				if (update_queue[j].id.profile_id 		== current.id.profile_id
				 && update_queue[j].id.transformer_id 	== current.id.transformer_id
				 && update_queue[j].id.parameter_id 	== current.id.parameter_id)
				{
					////printf("This is the same parameter. Update its target\n");
					update_queue[j].target = current.target;
					enqueue = 0;
					break;
				}
			}
			
			if (enqueue)
			{
				////printf("Adding this update to the queue.\n");
				update_queue[update_queue_tail] = current;
				update_queue_tail = (update_queue_tail + 1) % UPDATE_QUEUE_LENGTH;
			}
		}
		
		while (update_queue_tail != update_queue_head && n_updates < MAX_CONCURRENT_PARAM_UPDATES)
		{
			////printf("Moving updates from queue to array. update_queue_tail = %d, update_queue_head = %d. n_updates = %d.\n", update_queue_tail, update_queue_head, n_updates);
			update_array[n_updates++] = update_queue[update_queue_head];
			update_queue_head = (update_queue_head + 1) % UPDATE_QUEUE_LENGTH;
			////printf("Added: ");
			//print_parameter_update(update_array[n_updates - 1]);
		}
		
		////printf("Update_queue_tail = %d, update_queue_head = %d. n_updates = %d.\n", update_queue_tail, update_queue_head, n_updates);
		
		commit = 0;
		
		for (int i = 0; i < n_updates; i++)
		{
			current = update_array[i];
			////printf("Processing update %d of %d: ", i, n_updates);
			print_parameter_update(current);
			////printf("First, fetch the pointers.\n");
			
			if (cxt_get_parameter_and_transformer_by_id(&global_cxt, update_array[i].id, &update_array[i].p, &update_array[i].t) != NO_ERROR)
			{
				//printf("Removing update %d from array for reason: parameter fetch function returned error\n", i);
				remove_param_update(i);
				i--;
				continue;
			}
			
			param = update_array[i].p;
			
			if (!param)
			{
				//printf("Removing update %d from queue for reason: no such parameter found (NULL pointer)\n", i);
				
				remove_param_update(i);
				i--;
				continue;
			}
			
			if (update_array[i].id.profile_id != CONTEXT_PROFILE_ID)
			{
				update_array[i].send = (update_array[i].t != NULL);
			
				if (update_array[i].send)
				{
					for (int j = 0; j < i && update_array[i].send; j++)
					{
						if (update_array[j].t == update_array[i].t)
							update_array[i].send = 0;
					}
					
					if (!(update_array[i].send && update_array[i].t && xSemaphoreTake(update_array[i].t->mutex, 0) == pdTRUE))
						update_array[i].send = 0;
				}
			}
			
			diff = update_array[i].target - param->value;
			
			if (param->scale == PARAMETER_SCALE_LINEAR)
			{
				if (diff > UPDATE_PERIOD_MS * param->max_velocity)
					diff = UPDATE_PERIOD_MS * param->max_velocity;
				
				if (diff < -UPDATE_PERIOD_MS * param->max_velocity)
					diff = -UPDATE_PERIOD_MS * param->max_velocity;
			}
			else if (param->scale == PARAMETER_SCALE_LOGARITHMIC)
			{
				if (diff > UPDATE_PERIOD_MS * param->max_velocity * param->value)
					diff = UPDATE_PERIOD_MS * param->max_velocity * param->value;
				
				if (diff < -UPDATE_PERIOD_MS * param->max_velocity * param->value)
					diff = -UPDATE_PERIOD_MS * param->max_velocity * param->value;
			}
			//////printf("Move parameter %s (%d.%d.%d) by %f from %f to %f, with target %f\n", param->name, param->id.profile_id, param->id.transformer_id, param->id.parameter_id,
			//	diff, param->value, param->value + diff, update_array[i].target);
			
			param->value = param->value + diff;
			
			if (update_array[i].id.profile_id == CONTEXT_PROFILE_ID)
			{
				update_array[i].send = 0;
				if (param == &global_cxt.settings.input_gain)
				{
					m_fpga_queue_input_gain_set(param->value);
				}
				else if (param == &global_cxt.settings.output_gain)
				{
					m_fpga_queue_output_gain_set(param->value);
				}
			}
			else
			{
				commit = 1;
			}
			
		}
		
		for (int i = 0; i < n_updates; i++)
		{			
			if (update_array[i].t && update_array[i].send)
			{
				if (global_cxt.active_profile && global_cxt.active_profile->id == update_array[i].id.profile_id)
					m_transformer_update_fpga_registers(update_array[i].t);
				xSemaphoreGive(update_array[i].t->mutex);
			}
		}
		
		for (int i = 0; i < n_updates; i++)
		{
			if (!update_array[i].p)
			{
				//printf("Removing update %d from queue for reason: no such parameter found (NULL pointer)\n", i);
				remove_param_update(i);
				i--;
				continue;
			}
			
			if (update_array[i].p->value == update_array[i].target)
			{
				////printf("Removing update %d from queue for reason: value %.03f equals target %.03f\n", i, update_array[i].p->value, update_array[i].target);
				remove_param_update(i);
				i--;
				continue;
			}
		}
		
		if (commit)
		{
			m_fpga_queue_register_commit();
		}
		
		////printf("UPDATE_PERIOD_MS = %f, (int)UPDATE_PERIOD_MS = %d, pdMS_TO_CITKS((int)UPDATE_PERIOD_MS) = %d, update_period_ticks = %d\n",
		//	UPDATE_PERIOD_MS, (int)UPDATE_PERIOD_MS, pdMS_TO_TICKS((int)UPDATE_PERIOD_MS), update_period_ticks);
		xTaskDelayUntil(&last_wake, update_period_ticks);
	}
}

int m_parameter_trigger_update(m_parameter *param, float target)
{
	//printf("m_parameter_trigger_update, param = %p, target = %f\n", param, target);
	if (!param)
		return ERR_NULL_PTR;
	
	//printf("Parameter %s, ID %d.%d.%d. Current value: %f. Update target: %f. Max velocity: %f\n",
	//	param->name, param->id.profile_id, param->id.transformer_id, param->id.parameter_id,
	//	param->value, target, param->max_velocity);
	
	m_parameter_update up;
	up.id = param->id;
	up.target = target;
	
	if (xQueueSend(update_rtos_queue, &up, pdMS_TO_TICKS(1)) != pdPASS)
		return ERR_CURRENTLY_EXHAUSTED;
	
	return NO_ERROR;
}

#include "m_int.h"

uint8_t left_switch_state = 0;
uint8_t right_switch_state = 0;

void read_footswitch_states(uint8_t *left, uint8_t *right)
{
	if (!left || !right)
		return;
	
	uint8_t ch422g_state = m_ch422g_read();
	
	*left  = ((ch422g_state & (1 << 7)) != 0);
	*right = ((ch422g_state & (1 << 2)) != 0);
}

void footswitch_poll_task()
{
	TickType_t last_wake = xTaskGetTickCount();
	uint8_t ch422g_state;
	
	uint8_t new_left, new_right;

	while (true)
	{
		ch422g_state = m_ch422g_read();
	
		new_left  = ((ch422g_state & (1 << 0)) != 0);
		new_right = ((ch422g_state & (1 << 5)) != 0);
		
		if (new_left != left_switch_state)
			cxt_handle_hw_switch(&global_cxt, 0);
		
		if (new_right != right_switch_state)
			cxt_handle_hw_switch(&global_cxt, 1);
		
		left_switch_state = new_left;
		right_switch_state = new_right;
		
		/*printf("ch422g_state = 0b");
		
		for (int i = 0; i < 8; i++)
			printf("%d", (ch422g_state & (1 << (7 - i))) != 0);
		
		printf("\n");
		
		printf("Footswitch states: (%d, %d)\n", left_switch_state, right_switch_state);*/
		vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(5));
	}

	vTaskDelete(NULL);
}

int init_footswitch_poll_task()
{
	return NO_ERROR;
	
	m_ch422g_init_pull(0xFF);
	
	read_footswitch_states(&left_switch_state, &right_switch_state);
	
	
	
	xTaskCreate(
		footswitch_poll_task,
		"footswitch_task",
		8192,
		NULL,
		5,                  
		NULL
	);
	
	return NO_ERROR;
}

#include "m_int.h"

#define HW_SWITCH_GPIO_0   22   // n = 0
#define HW_SWITCH_GPIO_1   23   // n = 1

#define HW_SWITCH_DEBOUNCE_MS  20
#define HW_SWITCH_TASK_STACK  2048
#define HW_SWITCH_TASK_PRIO   6

uint8_t left_switch_state = 0;
uint8_t right_switch_state = 0;

void read_footswitch_states(uint8_t *left, uint8_t *right)
{
	if (!left || !right)
		return;
	
	#ifndef USE_5A
	uint8_t ch422g_state = m_ch422g_read();
	
	*left  = ((ch422g_state & (1 << 7)) != 0);
	*right = ((ch422g_state & (1 << 2)) != 0);
	#endif
}

/* ----------------------------------- */

static QueueHandle_t hw_switch_queue = NULL;

/* ----------- ISR ----------- */
static void IRAM_ATTR hw_switch_isr(void *arg)
{
    int n = (int)arg;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xQueueSendFromISR(hw_switch_queue, &n, &xHigherPriorityTaskWoken);

    if (xHigherPriorityTaskWoken) {
        portYIELD_FROM_ISR();
    }
}

void footswitch_task(void *arg)
{
	#ifndef USE_5A
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
	#else
	
	printf("FOOTSWITCHIES\n");
	int n;
    TickType_t last_event_tick[2] = {0, 0};
    const TickType_t debounce_ticks = pdMS_TO_TICKS(HW_SWITCH_DEBOUNCE_MS);

    while (true)
    {
        if (xQueueReceive(hw_switch_queue, &n, portMAX_DELAY) == pdTRUE)
        {
            TickType_t now = xTaskGetTickCount();

            if ((now - last_event_tick[n]) >= debounce_ticks)
            {
                last_event_tick[n] = now;

                cxt_handle_hw_switch(&global_cxt, n);
            }
        }
    }
	#endif
}

int init_footswitch_task()
{
	#ifndef USE_5A
	m_ch422g_init_pull(0xFF);
	
	read_footswitch_states(&left_switch_state, &right_switch_state);
	
	xTaskCreate(
		footswitch_task,
		"footswitch_task",
		8192,
		NULL,
		5,                  
		NULL
	);
	#else
	/* 1. Create event queue */
    hw_switch_queue = xQueueCreate(8, sizeof(int));

    /* 2. GPIO configuration */
    gpio_config_t cfg = {
        .pin_bit_mask =
            (1ULL << HW_SWITCH_GPIO_0) |
            (1ULL << HW_SWITCH_GPIO_1),
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_ANYEDGE
    };

    gpio_config(&cfg);

    /* 3. Install ISR service */
    gpio_install_isr_service(0);

    gpio_isr_handler_add(HW_SWITCH_GPIO_0, hw_switch_isr, (void *)0);
    gpio_isr_handler_add(HW_SWITCH_GPIO_1, hw_switch_isr, (void *)1);

    /* 4. Start task */
    xTaskCreate(
        footswitch_task,
        "hw_switch_task",
        HW_SWITCH_TASK_STACK,
        NULL,
        HW_SWITCH_TASK_PRIO,
        NULL
    );
	#endif
	
	return NO_ERROR;
}

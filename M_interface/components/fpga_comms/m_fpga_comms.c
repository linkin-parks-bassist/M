#include "m_int.h"

#define M_FPGA_MSG_TYPE_BATCH 			0
#define M_FPGA_MSG_TYPE_SET_INPUT_GAIN 	1
#define M_FPGA_MSG_TYPE_SET_OUTPUT_GAIN 2
#define M_FPGA_MSG_TYPE_COMMAND			3

#define FPGA_BOOT_MS 2000

typedef struct {
	int type;
	
	union {
		float level;
		uint8_t command;
		m_fpga_transfer_batch batch;
	} data;
} m_fpga_msg;

static QueueHandle_t fpga_msg_queue;
static int initialised = 0;

void m_fpga_comms_task(void *param)
{
	m_fpga_spi_init();
	
	fpga_msg_queue = xQueueCreate(32, sizeof(m_fpga_msg));
	initialised = 1;
	
	vTaskDelay(pdMS_TO_TICKS(FPGA_BOOT_MS));
	
	m_fpga_set_input_gain(global_cxt.settings.input_gain.value);
	m_fpga_set_output_gain(global_cxt.settings.output_gain.value);
	
	m_fpga_msg msg;
	
	while (1)
	{
		xQueueReceive(fpga_msg_queue, &msg, portMAX_DELAY);
		
		switch (msg.type)
		{
			case M_FPGA_MSG_TYPE_BATCH:
				m_fpga_transfer_batch_send(msg.data.batch);
				m_free_fpga_transfer_batch(msg.data.batch);
				break;
			
			case M_FPGA_MSG_TYPE_SET_INPUT_GAIN:
				m_fpga_set_input_gain(msg.data.level);
				break;
			
			case M_FPGA_MSG_TYPE_SET_OUTPUT_GAIN:
				m_fpga_set_output_gain(msg.data.level);
				break;
				
			case M_FPGA_MSG_TYPE_COMMAND:
				m_fpga_send_byte(msg.data.command);
				break;
		}
	}
	
	vTaskDelete(NULL);
}

static inline int m_fpga_queue_msg(m_fpga_msg msg)
{
	while (!initialised);
	
	if (xQueueSend(fpga_msg_queue, (void*)&msg, (TickType_t)1) != pdPASS)
		return ERR_QUEUE_SEND_FAILED;
	
	return NO_ERROR;
}

int m_fpga_queue_transfer_batch(m_fpga_transfer_batch batch)
{	
	m_fpga_msg msg;
	
	msg.type = M_FPGA_MSG_TYPE_BATCH;
	msg.data.batch = batch;
	
	return m_fpga_queue_msg(msg);
}

int m_fpga_queue_input_gain_set(float gain_db)
{
	m_fpga_msg msg;
	
	msg.type = M_FPGA_MSG_TYPE_SET_INPUT_GAIN;
	msg.data.level = gain_db;
	
	return m_fpga_queue_msg(msg);
}

int m_fpga_queue_output_gain_set(float gain_db)
{
	m_fpga_msg msg;
	
	msg.type = M_FPGA_MSG_TYPE_SET_OUTPUT_GAIN;
	msg.data.level = gain_db;
	
	return m_fpga_queue_msg(msg);
}

int m_fpga_queue_register_commit()
{
	m_fpga_msg msg;
	
	msg.type = M_FPGA_MSG_TYPE_COMMAND;
	msg.data.command = COMMAND_COMMIT_REG_UPDATES;
	
	return m_fpga_queue_msg(msg);
}

int m_fpga_queue_pipeline_swap()
{
	m_fpga_msg msg;
	
	msg.type = M_FPGA_MSG_TYPE_COMMAND;
	msg.data.command = COMMAND_SWAP_PIPELINES;
	
	return m_fpga_queue_msg(msg);
}

int m_fpga_queue_pipeline_reset()
{
	m_fpga_msg msg;
	
	msg.type = M_FPGA_MSG_TYPE_COMMAND;
	msg.data.command = COMMAND_RESET_PIPELINE;
	
	return m_fpga_queue_msg(msg);
}

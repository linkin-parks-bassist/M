#include "m_eng.h"

static const char *FNAME = "m_eng_mempool.c";

int head = 0;
int tail = MEM_SIZE - 1;

int mem_pools_initialised = 0;

#define BUFFER_QUEUE_STATIC
//#define BUFFER_QUEUE_DMAMEM

#ifdef BUFFER_QUEUE_STATIC
#ifdef BUFFER_QUEUE_DMAMEM
DMAMEM
#endif
float   buffer_pool[M_BUFFER_POOL_SIZE][AUDIO_BLOCK_SAMPLES];
#endif
float  *buffer_buffer[M_BUFFER_POOL_SIZE];

int buffer_head = 0;
int buffer_tail = M_BUFFER_POOL_SIZE - 1;

float zero_buffer[AUDIO_BLOCK_SAMPLES];
float sink_buffer[AUDIO_BLOCK_SAMPLES];

#define MEMPOOL_MALLOC_TRIES 6

// Set up the pool of audio data blocks
// placing them all onto the free list
#ifndef M_SIMULATED
FLASHMEM
#endif
void init_mem_pools()
{
	unsigned int i;
	
	__disable_irq();
	
	for (int i = 0; i < M_BUFFER_POOL_SIZE; i++)
	{
		#ifdef BUFFER_QUEUE_STATIC
		buffer_buffer[i] = buffer_pool[i];
		#else
		buffer_buffer[i] = NULL;
		for (int j = 0; j < MEMPOOL_MALLOC_TRIES && !buffer_buffer[i]; j++)
			buffer_buffer[i] = (float*)m_alloc(sizeof(float) * AUDIO_BLOCK_SAMPLES);
		#endif
	}
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		zero_buffer[i] = 0.0;
	
	mem_pools_initialised = 1;
	
	__enable_irq();
}

float *allocate_buffer()
{
	FUNCTION_START();
	
	//m_printf("allocate_buffer. MPI: %d. buffer_head: %d. buffer_tail: %d\n", mem_pools_initialised, buffer_head, buffer_tail);
	if (!mem_pools_initialised)
	{
		RETURN_PTR(NULL);
	}
	
	float *ret_buffer = NULL;
	
	if (buffer_head != buffer_tail)
	{
		ret_buffer = buffer_buffer[buffer_head];
		buffer_head = (buffer_head + 1) % M_BUFFER_POOL_SIZE;
	}
	else
	{
		M_LOG("Out of buffers!\n");
	}
	
	RETURN_PTR(ret_buffer);
}

void release_buffer(float *buffer)
{
	FUNCTION_START();

	if (!buffer || !mem_pools_initialised)
	{
		RETURN_VOID();
	}
	
	buffer_tail = (buffer_tail + 1) % M_BUFFER_POOL_SIZE;
	buffer_buffer[buffer_tail] = buffer;
	
	RETURN_VOID();
}

void print_mempool_info()
{
	FUNCTION_START();

	m_printf("MEMPOOL\n");
	
	int available_buffers = buffer_tail - buffer_head + ((buffer_tail < buffer_head) ? M_BUFFER_POOL_SIZE : 0);
	int used_buffers = M_BUFFER_POOL_SIZE - available_buffers;
	m_printf("Used buffers: %d. Available buffers: %d\n", used_buffers, available_buffers);
	
	RETURN_VOID();
}

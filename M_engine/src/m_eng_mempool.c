#include "m_eng.h"

static const char *FNAME = "m_eng_mempool.c";

DMAMEM m_eng_audio_block_int int_block_pool[MEM_SIZE];
uint16_t		 		int_block_pool_first_mask;
uint32_t 				int_block_pool_available_mask[NUM_MASKS];

m_eng_audio_block_float	 float_block_pool[MEM_SIZE] __attribute__((aligned(16)));
m_eng_audio_block_float	*float_block_queue[MEM_SIZE];

int head = 0;
int tail = MEM_SIZE - 1;

uint16_t		 	float_block_pool_first_mask;
uint32_t 			float_block_pool_available_mask[NUM_MASKS];

int mem_pools_initialised = 0;

#define BUFFER_QUEUE_STATIC

#ifdef BUFFER_QUEUE_STATIC
float   buffer_pool[M_ENG_BUFFER_POOL_SIZE][AUDIO_BLOCK_SAMPLES];
#endif
float  *buffer_buffer[M_ENG_BUFFER_POOL_SIZE];

int buffer_head = 0;
int buffer_tail = M_ENG_BUFFER_POOL_SIZE - 1;

float zero_buffer[AUDIO_BLOCK_SAMPLES];
float sink_buffer[AUDIO_BLOCK_SAMPLES];

#define MEMPOOL_MALLOC_TRIES 6

// Set up the pool of audio data blocks
// placing them all onto the free list
FLASHMEM void init_mem_pools()
{
	unsigned int i;
	
	__disable_irq();
	
	for (int i = 0; i < M_ENG_BUFFER_POOL_SIZE; i++)
	{
		#ifdef BUFFER_QUEUE_STATIC
		buffer_buffer[i] = buffer_pool[i];
		#else
		buffer_buffer[i] = NULL;
		for (int j = 0; j < MEMPOOL_MALLOC_TRIES && !buffer_buffer[i]; j++)
			buffer_buffer[i] = (float*)malloc(sizeof(float) * AUDIO_BLOCK_SAMPLES);
		#endif
	}
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		zero_buffer[i] = 0.0;
	
	int_block_pool_first_mask = 0;
	
	for (i=0; i < NUM_MASKS; i++)
		int_block_pool_available_mask[i] = 0;
	
	for (i=0; i < MEM_SIZE; i++)
		int_block_pool_available_mask[i >> 5] |= (1 << (i & 0x1F));
	
	for (i=0; i < MEM_SIZE; i++)
		int_block_pool[i].block_pool_index = i;
	
	for (int i = 0; i < MEM_SIZE; i++)
		float_block_queue[i] = &float_block_pool[i];
	
	/*
	float_block_pool_first_mask = 0;
	
	for (i=0; i < NUM_MASKS; i++)
		float_block_pool_available_mask[i] = 0;
	
	
	for (i=0; i < MEM_SIZE; i++)
		float_block_pool_available_mask[i >> 5] |= (1 << (i & 0x1F));
	
	for (i=0; i < MEM_SIZE; i++)
		float_block_pool[i].block_pool_index = i;
	
	if (update_scheduled == false)
	{
		// if no hardware I/O has taken responsibility for update,
		// start a timer which will call update_all() at the correct rate
		IntervalTimer *timer = new IntervalTimer();
		if (timer) {
			float usec = 1e6 * AUDIO_BLOCK_SAMPLES / AUDIO_SAMPLE_RATE_EXACT;
			timer->begin(update_all, usec);
			update_setup();
		}
	}*/
	
	mem_pools_initialised = 1;
	
	__enable_irq();
}

// Allocate 1 audio data block.  If successful
// the caller is the only owner of this new block
m_eng_audio_block_int *allocate_block_int()
{
	if (!mem_pools_initialised)
	{
		RETURN_PTR(NULL);
	}
	
	uint32_t n, index, avail;
	uint32_t *p, *end;
	m_eng_audio_block_int *block;
	uint32_t used;

	p = int_block_pool_available_mask;
	end = p + NUM_MASKS;
	
	__disable_irq();
	
	index = int_block_pool_first_mask;
	p += index;
	
	while (1)
	{
		if (p >= end)
		{
			__enable_irq();
			////Serial.println("alloc:null");
			RETURN_PTR(NULL);
		}
		avail = *p;
		if (avail) break;
		index++;
		p++;
	}
	
	n = __builtin_clz(avail);
	avail &= ~(0x80000000 >> n);
	*p = avail;
	
	if (!avail) index++;
	
	int_block_pool_first_mask = index;
	used = memory_used + 1;
	memory_used = used;
	
	__enable_irq();
	
	index = p - int_block_pool_available_mask;
	block = int_block_pool + ((index << 5) + (31 - n));
	block->ref_count = 1;
	
	if (used > memory_used_max)
		memory_used_max = used;
	
	return block;
}

// Release ownership of a data block.  If no
// other streams have ownership, the block is
// returned to the free pool
void release_block_int(m_eng_audio_block_int *block)
{
	FUNCTION_START();

	if (!block || !mem_pools_initialised)
	{
		RETURN_VOID();
	}
	
	uint32_t mask = (0x80000000 >> (31 - (block->block_pool_index & 0x1F)));
	uint32_t index = block->block_pool_index >> 5;

	__disable_irq();
	if (block->ref_count > 1)
	{
		block->ref_count--;
	}
	else 
	{
		int_block_pool_available_mask[index] |= mask;
		if (index < int_block_pool_first_mask) int_block_pool_first_mask = index;
		memory_used--;
	}
	
	__enable_irq();
	
	RETURN_VOID();
}

m_eng_audio_block_float *allocate_block()
{
	FUNCTION_START();
	
	if (!mem_pools_initialised)
	{
		RETURN_PTR(NULL);
	}
	
	m_eng_audio_block_float *ret_block = NULL;
	
	if (head != tail)
	{
		ret_block = float_block_queue[head];
		head = (head + 1) % MEM_SIZE;
	}
	
	RETURN_PTR(ret_block);
}

void release_block(m_eng_audio_block_float *block)
{
	FUNCTION_START();

	if (!block || !mem_pools_initialised)
	{
		RETURN_VOID();
	}
	
	tail = (tail + 1) % MEM_SIZE;
	float_block_queue[tail] = block;
	
	RETURN_VOID();
}

float *allocate_buffer()
{
	FUNCTION_START();
	
	//m_eng_printf("allocate_buffer. MPI: %d. buffer_head: %d. buffer_tail: %d\n", mem_pools_initialised, buffer_head, buffer_tail);
	if (!mem_pools_initialised)
	{
		RETURN_PTR(NULL);
	}
	
	float *ret_buffer = NULL;
	
	if (buffer_head != buffer_tail)
	{
		ret_buffer = buffer_buffer[buffer_head];
		buffer_head = (buffer_head + 1) % M_ENG_BUFFER_POOL_SIZE;
	}
	else
	{
		m_eng_printf("BUFFER ALLOCATION FAIL\n");
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
	
	buffer_tail = (buffer_tail + 1) % M_ENG_BUFFER_POOL_SIZE;
	buffer_buffer[buffer_tail] = buffer;
	
	RETURN_VOID();
}

void print_mempool_info()
{
	FUNCTION_START();

	m_eng_printf("MEMPOOL\n");
	
	int available_buffers = buffer_tail - buffer_head + ((buffer_tail < buffer_head) ? M_ENG_BUFFER_POOL_SIZE : 0);
	int used_buffers = M_ENG_BUFFER_POOL_SIZE - available_buffers;
	m_eng_printf("Used buffers: %d. Available buffers: %d\n", used_buffers, available_buffers);
	
	RETURN_VOID();
}

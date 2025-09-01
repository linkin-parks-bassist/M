#include "M.h"


DMAMEM m_audio_block_int int_block_pool[MEM_SIZE];
uint16_t		 		int_block_pool_first_mask;
uint32_t 				int_block_pool_available_mask[NUM_MASKS];

m_audio_block_float	 float_block_pool[MEM_SIZE];
m_audio_block_float	*float_block_queue[MEM_SIZE];

int head = 0;
int tail = MEM_SIZE - 1;

uint16_t		 	float_block_pool_first_mask;
uint32_t 			float_block_pool_available_mask[NUM_MASKS];


// Set up the pool of audio data blocks
// placing them all onto the free list
FLASHMEM void init_mem_pools()
{
	unsigned int i;
	
	__disable_irq();
	
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
	
	__enable_irq();
}

// Allocate 1 audio data block.  If successful
// the caller is the only owner of this new block
m_audio_block_int *allocate_block_int()
{
	uint32_t n, index, avail;
	uint32_t *p, *end;
	m_audio_block_int *block;
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
			//Serial.println("alloc:null");
			return NULL;
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
void release_block_int(m_audio_block_int *block)
{
	if (!block) return;
	
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
}

// Allocate 1 audio data block.  If successful
// the caller is the only owner of this new block
m_audio_block_float *allocate_block()
{
	//m_printf("Allocating block...\n");
	
	m_audio_block_float *ret_block = NULL;
	
	if (head != tail)
	{
		ret_block = float_block_queue[head];
		head = (head + 1) % MEM_SIZE;
	}
	
	//m_printf("Returning 0x%8x...\n", ret_block);
	return ret_block;
	
	/*
	uint32_t n, index, avail;
	uint32_t *p, *end;
	m_audio_block_float *block;
	uint32_t used;

	p = float_block_pool_available_mask;
	end = p + NUM_MASKS;
	
	__disable_irq();
	
	index = float_block_pool_first_mask;
	p += index;
	
	while (1)
	{
		//m_printf("Walking array... p = 0x%08x\n", p);
		if (p >= end)
		{
			__enable_irq();
			//m_printf("alloc:null");
			return NULL;
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
	
	float_block_pool_first_mask = index;
	used = memory_used + 1;
	memory_used = used;
	
	__enable_irq();
	
	index = p - float_block_pool_available_mask;
	block = float_block_pool + ((index << 5) + (31 - n));
	block->ref_count = 1;
	
	if (used > memory_used_max)
		memory_used_max = used;
	
	return block;*/
}

// Release ownership of a data block.  If no
// other streams have ownership, the block is
// returned to the free pool
void release_block(m_audio_block_float *block)
{
	if (!block) return;
	
	tail = (tail + 1) % MEM_SIZE;
	float_block_queue[tail] = block;
	
	return;
	
	uint32_t mask = (0x80000000 >> (31 - (block->block_pool_index & 0x1F)));
	uint32_t index = block->block_pool_index >> 5;

	__disable_irq();
	if (block->ref_count > 1)
	{
		block->ref_count--;
	}
	else 
	{
		float_block_pool_available_mask[index] |= mask;
		if (index < float_block_pool_first_mask) float_block_pool_first_mask = index;
		memory_used--;
	}
	
	__enable_irq();
}


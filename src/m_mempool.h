#ifndef M_MEMPOOL_H_
#define M_MEMPOOL_H_

#define MAX_AUDIO_MEMORY 229376

#define MEM_SIZE 20

extern m_audio_block_int	int_block_pool[MEM_SIZE];
extern uint16_t		 		int_block_pool_first_mask;
extern uint32_t 			int_block_pool_available_mask[];

extern m_audio_block_float	float_block_pool[MEM_SIZE];
extern uint16_t		 		float_block_pool_first_mask;
extern uint32_t 			float_block_pool_available_mask[];

m_audio_block_int *allocate_block_int();
void release_block_int(m_audio_block_int *block);

m_audio_block_float *allocate_block();
void release_block(m_audio_block_float *block);

void init_mem_pools();

#endif

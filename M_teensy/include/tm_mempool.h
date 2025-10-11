#ifndef M_MEMPOOL_H_
#define M_MEMPOOL_H_

#define MAX_AUDIO_MEMORY 229376

#define MEM_SIZE 48

extern tm_audio_block_int	int_block_pool[MEM_SIZE];
extern uint16_t		 		int_block_pool_first_mask;
extern uint32_t 			int_block_pool_available_mask[];

extern tm_audio_block_float	float_block_pool[MEM_SIZE];
extern uint16_t		 		float_block_pool_first_mask;
extern uint32_t 			float_block_pool_available_mask[];

tm_audio_block_int *allocate_block_int();
void release_block_int(tm_audio_block_int *block);

tm_audio_block_float *allocate_block();
void release_block(tm_audio_block_float *block);

float *allocate_buffer();
void release_buffer(float *buffer);

void init_mem_pools();

extern float zero_buffer[AUDIO_BLOCK_SAMPLES];
extern float sink_buffer[AUDIO_BLOCK_SAMPLES];

#endif

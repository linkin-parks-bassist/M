#ifndef M_MEMPOOL_H_
#define M_MEMPOOL_H_

#define MAX_AUDIO_MEMORY 229376

#define MEM_SIZE 48
#define M_ENG_BUFFER_POOL_SIZE 96

float *allocate_buffer();
void release_buffer(float *buffer);

void init_mem_pools();

extern float zero_buffer[AUDIO_BLOCK_SAMPLES];
extern float sink_buffer[AUDIO_BLOCK_SAMPLES];

void print_mempool_info();

#endif

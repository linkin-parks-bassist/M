#ifndef M_AUDIO_BLOCK_H_
#define M_AUDIO_BLOCK_H_

#ifndef AUDIO_BLOCK_SAMPLES
#define AUDIO_BLOCK_SAMPLES  128
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	uint8_t  ref_count;
	uint8_t  pad;
	uint16_t block_pool_index;
	int16_t  data[AUDIO_BLOCK_SAMPLES];
} tm_audio_block_int;

typedef struct
{
	uint8_t  ref_count;
	uint8_t  pad;
	uint16_t block_pool_index;
	float	data[AUDIO_BLOCK_SAMPLES];
} tm_audio_block_float;

int zero_out_block_float(tm_audio_block_float *block);

int convert_block_int_to_float(float *dest, int16_t *src);
int convert_block_float_to_int(int16_t *src, float *dest);

tm_audio_block_float *convert_and_allocate_int_block(tm_audio_block_int block);

#ifdef __cplusplus
}
#endif

#endif

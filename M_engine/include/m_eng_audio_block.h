#ifndef M_AUDIO_BLOCK_H_
#define M_AUDIO_BLOCK_H_

#ifndef AUDIO_BLOCK_SAMPLES
#define AUDIO_BLOCK_SAMPLES  128
#endif

#ifdef __cplusplus
extern "C" {
#endif

int convert_block_int_to_float(float *dest, int16_t *src);
int convert_block_float_to_int(int16_t *src, float *dest);

#ifdef __cplusplus
}
#endif

#endif

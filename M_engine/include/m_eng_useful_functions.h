#ifndef M_ENG_USEFUL_FUNCTIONS_H_
#define M_ENG_USEFUL_FUNCTIONS_H_

float identity_function(float x);

float normalised_arctan(float x);

float hard_clip(float x);

float soft_fold(float x);

int convert_block_int_to_float(float *dest, int16_t *src);
int convert_block_float_to_int(int16_t *src, float *dest);

#endif

#ifndef M_INT_HELPER_FUNCTIONS_H_
#define M_INT_HELPER_FUNCTIONS_H_

int16_t float_to_q_nminus1(float x, int shift);
int16_t float_to_q15(float x);

#define binary_max(x, y) ((x > y) ? x : y)
#define binary_min(x, y) ((x > y) ? y : x)

#define sqr(x) (x * x)

char *binary_print_8 (uint8_t x);
char *binary_print_16(uint16_t x);
char *binary_print_32(uint32_t x);

#endif

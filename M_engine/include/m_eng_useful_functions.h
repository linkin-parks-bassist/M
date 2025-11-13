#ifndef M_ENG_USEFUL_FUNCTIONS_H_
#define M_ENG_USEFUL_FUNCTIONS_H_

float identity_function(float x);

float normalised_arctan(float x);

float hard_clip(float x);

float soft_fold(float x);

int convert_block_int_to_float(float *dest, int16_t *src);
int convert_block_float_to_int(int16_t *src, float *dest);

static inline int positive_mod(int x, int m)
{
    int r = x % m;
    return r < 0 ? r + m : r;
}

static inline int floor_divide(int x, int d)
{
    // d > 0
    if (x >= 0) return x / d;
    return -(( -x + d - 1) / d);
}

static inline int ring_index(int i, int n)
{
    int r = i % n;
    return r < 0 ? r + n : r;
}

#endif

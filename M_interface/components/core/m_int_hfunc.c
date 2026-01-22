#include <stdint.h>
#include <math.h>

#include "m_int_hfunc.h"

char binary_print_buffer[35];

int16_t float_to_q_nminus1(float x, int shift)
{
    int n = 15 - shift;

    float scale = (float)(1 << n);

    float max =  (float)((1 << 15) - 1) / scale;
    float min = -(float)(1 << 15)       / scale;

    if (x > max) x = max;
    if (x < min) x = min;

    return (int16_t)lrintf(x * scale);
}


int16_t float_to_q15(float x)
{
	if (x >= 0.999969482421875f) return  32767;
    if (x <= -1.0f)              return -32768;
    
    return (int16_t)lrintf(x * 32768.0f);
}

char *binary_print_8 (uint8_t x)
{
	binary_print_buffer[0] = '0';
	binary_print_buffer[1] = 'b';
	
	for (int i = 0; i < 8; i++)
	{
		binary_print_buffer[i+2] = '0' + (!!(x & (1 << (7 - i))));
	}
	
	binary_print_buffer[11] = 0;
	
	return binary_print_buffer;
}

char *binary_print_16(uint16_t x)
{
	binary_print_buffer[0] = '0';
	binary_print_buffer[1] = 'b';
	
	for (int i = 0; i < 16; i++)
	{
		binary_print_buffer[i+2] = '0' + (!!(x & (1 << (15 - i))));
	}
	
	binary_print_buffer[19] = 0;
	
	return binary_print_buffer;
}

char *binary_print_32(uint32_t x)
{
	binary_print_buffer[0] = '0';
	binary_print_buffer[1] = 'b';
	
	for (int i = 0; i < 32; i++)
	{
		binary_print_buffer[i+2] = '0' + (!!(x & (1 << (31 - i))));
	}
	
	binary_print_buffer[35] = 0;
	
	return binary_print_buffer;
}

#ifndef MY_PRINTF_H_
#define MY_PRINTF_H_

void m_eng_printf(const char *fmt, ...);
void pretty_print_block(int16_t *data, const char *start);
void pretty_print_block_float(float *data, const char *start);

void serial_print_blocks(int n, ...);

#endif

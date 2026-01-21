#ifndef MY_PRINTF_H_
#define MY_PRINTF_H_

void m_voice_printf(int who, const char *fmt, ...);

void m_mute_voice(int who);
void m_unmute_voice(int who);

void m_printf(const char *fmt, ...);
void pretty_print_block(int16_t *data, const char *start);
void pretty_print_block_float(float *data, const char *start);
void pretty_print_buffer(float *data, int n, const char *start);

void serial_print_blocks(int n, ...);

#endif

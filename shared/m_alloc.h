#ifndef M_MALLOC_WRAPPER_H_
#define M_MALLOC_WRAPPER_H_

void *m_alloc(size_t size);
void *m_realloc(void *ptr, size_t size);
char *m_strndup(const char *str, size_t n);
void m_free(void *ptr);

void *m_int_lv_malloc(size_t size);
void m_int_lv_free(void *ptr);

void print_memory_report();

#endif

#ifndef M_INT_MALLOC_WRAPPER_H_
#define M_INT_MALLOC_WRAPPER_H_

void *m_int_malloc(size_t sz);
char *m_int_strndup(const char *s, size_t n);
void m_int_free(void *q);

void *m_int_lv_malloc(size_t sz);
void m_int_lv_free(void *p);

void print_memory_report();

#endif

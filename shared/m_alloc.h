#ifndef M_MALLOC_WRAPPER_H_
#define M_MALLOC_WRAPPER_H_

void *m_alloc(size_t sz);
char *m_int_strndup(const char *s, size_t n);
void m_free(void *q);

void *m_int_lv_malloc(size_t sz);
void m_int_lv_free(void *p);

void print_memory_report();

#endif

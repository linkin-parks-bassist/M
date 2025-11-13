#ifdef M_INTERFACE
#include "m_int.h"
#endif

#ifdef M_SIMULATED
#include "M_teensy_simulator.h"
#elif defined(M_ENGINE)
#include "m_eng.h"
#endif

static size_t total_current, total_peak;

void *m_alloc(size_t sz)
{
    uint8_t *p = malloc(sz + sizeof(size_t));
    
    if (!p)
		return NULL;
    
    *(size_t*)p = sz;
    
    total_current += sz;
    
    if (total_current > total_peak)
        total_peak = total_current;
    
    return p + sizeof(size_t);
}

char *m_int_strndup(const char *s, size_t n)
{
    size_t len = strnlen(s, n);
    char *d = m_alloc(len + 1);
    if (!d) return NULL;
    memcpy(d, s, len);
    d[len] = '\0';
    return d;
}

void m_free(void *q)
{
    if (!q)
		return;
    
    uint8_t *p = (uint8_t*)q - sizeof(size_t);
    
    size_t sz = *(size_t*)p;
    
    total_current -= sz;
    
    free(p);
}

#ifdef M_INTERFACE
void *m_int_lv_malloc(size_t sz)
{
    return heap_caps_malloc(sz, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
}

void m_int_lv_free(void *p)
{
    heap_caps_free(p);
}
#endif

void print_memory_report()
{      
    printf("Memory usage: %d alloc'd, %d at peak\n", total_current, total_peak);
}

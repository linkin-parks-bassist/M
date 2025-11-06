#include "m_int.h"

static size_t total_current, total_peak;

void *m_int_malloc(size_t sz)
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
    char *d = m_int_malloc(len + 1);
    if (!d) return NULL;
    memcpy(d, s, len);
    d[len] = '\0';
    return d;
}

void m_int_free(void *q)
{
    if (!q)
		return;
    
    uint8_t *p = (uint8_t*)q - sizeof(size_t);
    
    size_t sz = *(size_t*)p;
    
    total_current -= sz;
    
    free(p);
}

void *m_int_lv_malloc(size_t sz)
{
    return heap_caps_malloc(sz, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
}
void m_int_lv_free(void *p)
{
    heap_caps_free(p);
}

void print_memory_report()
{
	lv_mem_monitor_t m; lv_mem_monitor(&m);
    heap_caps_print_heap_info(MALLOC_CAP_INTERNAL);
    printf("[LVGL] total=%u free=%u max_used=%u frag=%u%% free_biggest=%u free_cnt=%u\n",
           (unsigned)m.total_size, (unsigned)m.free_size, (unsigned)m.max_used,
           (unsigned)m.frag_pct, (unsigned)m.free_biggest_size, (unsigned)m.free_cnt);
           
    printf("M memory usage: %d alloc'd, %d at peak\n", total_current, total_peak);
}

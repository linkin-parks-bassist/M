#ifdef M_INTERFACE
#include "m_int.h"
#elif defined(M_ENGINE)
#include "m_eng.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <freertos/FreeRTOS.h>

#include "m_int.h"

static size_t total_current, total_peak;

void *m_alloc(size_t size)
{
	if (size == 0)
		return NULL;
	
    uint8_t *ptr = malloc(size + sizeof(size_t));
    
    if (!ptr)
		return NULL;
    
    *(size_t*)ptr = size;
    
    total_current += size;
    
    if (total_current > total_peak)
        total_peak = total_current;
    
    return ptr + sizeof(size_t);
}

void m_free(void *ptr)
{
    if (!ptr)
		return;
    
    uint8_t *base_ptr = (uint8_t*)ptr - sizeof(size_t);
    
    size_t size = *(size_t*)base_ptr;
    
    total_current -= size;
    
    free(base_ptr);
}

void *m_realloc(void *ptr, size_t size)
{
	if (!ptr)
		return m_alloc(size);
	
	if (size == 0)
		m_free(ptr);
	
    uint8_t *base_ptr = (uint8_t*)ptr - sizeof(size_t);
    size_t base_size = *(size_t*)base_ptr;
    
    uint8_t *new_ptr = realloc(base_ptr, size + sizeof(size_t));
    
    if (!new_ptr)
		return NULL;
    
    *(size_t*)new_ptr = size;
    
    total_current += (size - base_size);
    
    if (total_current > total_peak)
        total_peak = total_current;
    
    return new_ptr + sizeof(size_t);
}

char *m_strndup(const char *str, size_t n)
{
    size_t len = strnlen(str, n);
    
    char *new_str = m_alloc(len + 1);
    
    if (!new_str) return NULL;
    memcpy(new_str, str, len);
    new_str[len] = '\0';
    
    return new_str;
}

void m_mem_monitor_task(void *param)
{
	while (1)
	{
		print_memory_report();
		vTaskDelay(pdMS_TO_TICKS(2000));
	}
}


void m_mem_init()
{
	printf("m_mem_init()");
	#ifdef PRINT_MEMORY_USAGE
	printf("Spinning off memory printer task...\n");
	xTaskCreate(
		m_mem_monitor_task,
		"memory_log",
		2048,
		NULL,
		5,                  
		NULL
	);
	#endif
}

void lv_mem_init(void)
{
	return;
}

void lv_mem_deinit(void)
{
	return;
}

void * lv_malloc_core(size_t size)
{
	return m_alloc(size);
}
void * lv_realloc_core(void * p, size_t new_size)
{
	return m_realloc(p, new_size);
}

void lv_free_core(void * p)
{
	return m_free(p);
}

#ifdef M_INTERFACE
void *m_int_lv_malloc(size_t size)
{
    return heap_caps_malloc(size, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
}

void m_int_lv_free(void *ptr)
{
    heap_caps_free(ptr);
}
#endif

void print_memory_report()
{
    printf("Memory usage: %d alloc'd, %d at peak\n", total_current, total_peak);
}

#ifndef M_SIMULATED
#include <Arduino.h>
#endif
#include "m_eng.h"


static const char *FNAME = "m_eng_logging.cpp";

#define M_ENG_LOG_ENTRIES_N 64

static m_eng_log_entry log_entries[M_ENG_LOG_ENTRIES_N];

static int log_entries_index = 0;
static int log_entries_wrapped = 0;

#if M_ENG_LOG_LEVEL == M_ENG_LOG_TRACE
#define MESSAGE_BEGIN_COL 43
#else
#define MESSAGE_BEGIN_COL 80
#endif

int format_log_entry(int index, char *buf, int max_len, int max_indent)
{
	double seconds = cycles_to_seconds(log_entries[index].cycle);
	const char *error_message = NULL;
	
	int i = 0;
	
	i += snprintf(&buf[i], max_len - i, "(%.06fs) ", seconds);
	//i += snprintf(&buf[i], max_len - i, "%ds", 		(int)floor(seconds));
	//i += snprintf(&buf[i], max_len - i, "%03dms", 	((int)floor(1000 * seconds)) % 1000);
	//i += snprintf(&buf[i], max_len - i, "%03dus: ", ((int)floor(1000000 * seconds)) % 1000);
	
	if (i >= max_len - 1) return i;
	
	int j = 0;
	
	for (j = 0; log_entries[index].file_name[j] != 0 && i < max_len - 1; j++)
	{
		buf[i] = log_entries[index].file_name[j];
		i++;
	}
	
	if (i >= max_len - 1) return i;
	
	buf[i++] = ':';
	
	for (j = 0; log_entries[index].line[j] != 0 && i < max_len - 1; j++)
	{
		buf[i] = log_entries[index].line[j];
		i++;
	}
	
	if (i >= max_len - 1) return i;
	
	buf[i++] = ' ';
	
	#if M_ENG_LOG_LEVEL == M_ENG_LOG_TRACE
	if (log_entries[index].type == M_ENG_TRACE_FUNCTION_ENTER || log_entries[index].type == M_ENG_TRACE_FUNCTION_RETURN)
	{
		for (j = 0; i < MESSAGE_BEGIN_COL && i < max_len - 1; j++)
			buf[i++] = ' ';
		
		if (i >= max_len - 1) return i;
		
		#ifdef M_ENG_LOG_INDENT_TRACE
		for (j = 0; j < binary_max(0, max_indent - (int)log_entries[index].trace_depth) && i < max_len - 1; j++)
				buf[i++] = ' ';
			
		if (i >= max_len - 1) return i;
		
		if (log_entries[index].type == M_ENG_TRACE_FUNCTION_RETURN)
		{
			buf[i++] = ' ';
			if (i >= max_len - 1) return i;
		}
		#endif
		
		for (j = 0; log_entries[index].function[j] != 0 && i < max_len - 1; j++)
			buf[i++] = log_entries[index].function[j];
		
		if (i >= max_len - 1) return i;
		
		buf[i++] = ' ';
	
		if (i >= max_len - 1) return i;
		
		for (j = 0; log_entries[index].message[j] != 0 && i < max_len - 1; j++)
			buf[i++] = log_entries[index].message[j];
		
		if (i >= max_len - 1) return i;
	}
	else
	{
		for (j = 0; log_entries[index].function[j] != 0 && i < max_len - 1; j++)
			buf[i++] = log_entries[index].function[j];
		
		if (i >= max_len - 1) return i;
		
		buf[i++] = ' ';
		
		if (i >= max_len - 1) return i;
		
		for (j = 0; i < MESSAGE_BEGIN_COL && i < max_len - 1; j++)
			buf[i++] = ' ';
		
		if (i >= max_len - 1) return i;
		
		for (j = 0; log_entries[index].message[j] != 0 && i < max_len - 1; j++)
			buf[i++] = log_entries[index].message[j];
		
		if (i >= max_len - 1) return i;
	}
	#else
	for (j = 0; log_entries[index].function[j] != 0 && i < max_len - 1; j++)
		buf[i++] = log_entries[index].function[j];
	
	if (i >= max_len - 1) return i;
	
	buf[i++] = ' ';
	
	if (i >= max_len - 1) return i;
	
	for (j = 0; i < MESSAGE_BEGIN_COL && i < max_len - 1; j++)
		buf[i++] = ' ';
	
	if (i >= max_len - 1) return i;
	
	for (j = 0; log_entries[index].message[j] != 0 && i < max_len - 1; j++)
		buf[i++] = log_entries[index].message[j];
	
	if (i >= max_len - 1) return i;
	#endif
	
	if (i >= max_len - 1) return i;
	
	switch (log_entries[index].type)
	{		
		case M_ENG_LOG_ENTRY_ERROR:
		case M_ENG_LOG_ENTRY_RETURN_ERR:
			error_message = m_error_code_to_string(log_entries[index].data);
			
			if (error_message)
			{
				for (j = 0; error_message[j] != 0 && i < max_len - 1; j++)
					buf[i++] = error_message[j];
			}
			break;
		
		case M_ENG_LOG_ENTRY_RETURN_PTR:
			i += snprintf(&buf[i], max_len - i, "%p", (void*)log_entries[index].data);
			break;
		
		case M_ENG_LOG_ENTRY_RETURN_INT:
			i += snprintf(&buf[i], max_len - i, "%d", (int)log_entries[index].data);
			break;
		
		default:
			break;
	}
	
	if (i < max_len)
		buf[i++] = '\n';
	else if (i > 0)
		buf[i - 1] = '\n';
	
	return i;
}

static inline void increment_log_entry()
{
	int new_index = (log_entries_index + 1) % M_ENG_LOG_ENTRIES_N;
	if (new_index == 0)
		log_entries_wrapped = 1;
	log_entries_index = new_index;
}

static inline void write_log_entry
	(
		int type,
		const char *file_name,
		const char *line,
		const char *function,
		const char *message,
		uint32_t data,
		uint32_t trace_depth,
		uint64_t cycle
	)
{
	log_entries[log_entries_index].type = type;
	log_entries[log_entries_index].file_name = file_name;
	log_entries[log_entries_index].line = line;
	log_entries[log_entries_index].function = function;
	log_entries[log_entries_index].message = message;
	log_entries[log_entries_index].cycle = cycle;
	log_entries[log_entries_index].data = data;
	log_entries[log_entries_index].trace_depth = trace_depth;
	
	increment_log_entry();
}

void m_eng_trace_log_begin(const char *fname, const char *line, const char *function, int local_trace_depth, uint64_t cycle)
{
	write_log_entry(M_ENG_TRACE_FUNCTION_ENTER, fname, line, function, "entered", 0, trace_depth, cycle);
	trace_depth++;
}

void m_eng_trace_log_return(const char *fname, const char *line, const char *function, int local_trace_depth, uint64_t cycle)
{
	write_log_entry(M_ENG_TRACE_FUNCTION_RETURN, fname, line, function, "returned", 0, trace_depth, cycle);
	trace_depth--;
}

void m_eng_log_error_code(const char *fname, const char *line, const char *function, int error_code, uint64_t cycle)
{
	write_log_entry(M_ENG_LOG_ENTRY_ERROR, fname, line, function, "error: ", error_code, 0, cycle);
}

void m_eng_log_return_err(const char *fname, const char *line, const char *function, int error_code, uint64_t cycle)
{
	write_log_entry(M_ENG_LOG_ENTRY_RETURN_ERR, fname, line, function, "returned with error code ", error_code, 0, cycle);
}

void m_eng_log_return_ptr(const char *fname, const char *line, const char *function, void *ptr, uint64_t cycle)
{
	write_log_entry(M_ENG_LOG_ENTRY_RETURN_PTR, fname, line, function, "returned with pointer ", (uint32_t)ptr, 0, cycle);
}

void m_eng_log_return_int(const char *fname, const char *line, const char *function, int val, uint64_t cycle)
{
	write_log_entry(M_ENG_LOG_ENTRY_RETURN_PTR, fname, line, function, "returned with integer ", val, 0, cycle);
}

void m_eng_log_return_(const char *fname, const char *line, const char *function, uint64_t cycle)
{
	write_log_entry(M_ENG_LOG_ENTRY_RETURN, fname, line, function, "returned something", 0, 0, cycle);
}

void m_eng_log_message(const char *fname, const char *line, const char *function, uint64_t cycle, const char *fmt, ...)
{
	char buf[1024];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);
	write_log_entry(M_ENG_LOG_ENTRY_MESSAGE, fname, line, function, m_strndup(buf, 1024), 0, 0, cycle);
}

#define LOG_ENTRIES_PRINT_BUF_LEN 4096

void m_eng_print_flush_log()
{
	if (!log_entries_index && !log_entries_wrapped)
	{
		return;
	}
	
	char buf[LOG_ENTRIES_PRINT_BUF_LEN];
	
	int wrap = log_entries_wrapped;
	int i = 0;
	int break_index = wrap ? M_ENG_LOG_ENTRIES_N : log_entries_index;
	int index = wrap ? log_entries_index : 0;
	
	int max_depth = 0;
	
find_max_indent:
	
	while (index < break_index)
	{
		if (log_entries[index].trace_depth > max_depth)
			max_depth = log_entries[index].trace_depth;
		index++;
	}
	
	if (wrap)
	{
		index = 0;
		break_index = log_entries_index;
		wrap = 0;
		goto find_max_indent;
	}
	
	break_index = wrap ? M_ENG_LOG_ENTRIES_N : log_entries_index;
	index = wrap ? log_entries_index : 0;

log_bufferize:
	
	while (i < LOG_ENTRIES_PRINT_BUF_LEN && index < break_index)
	{
		i += format_log_entry(index++, &buf[i], LOG_ENTRIES_PRINT_BUF_LEN - i, max_depth);
	}
	
	if (wrap)
	{
		index = 0;
		break_index = log_entries_index;
		wrap = 0;
		goto log_bufferize;
	}
	if (i < LOG_ENTRIES_PRINT_BUF_LEN)
	{
		buf[i++] = 0;
	}
	else
	{
		buf[LOG_ENTRIES_PRINT_BUF_LEN - 1] = 0;
	}
	
	m_voice_printf(M_VOICE_LOG, buf);
	
	if (buf[(i < LOG_ENTRIES_PRINT_BUF_LEN) ? i - 1 : LOG_ENTRIES_PRINT_BUF_LEN - 2] != '\n')
	{
		#ifndef M_SIMULATED
		Serial.print("\n");
		#else
		printf("\n");
		#endif
	}
	
	log_entries_index = 0;
	log_entries_wrapped = 0;
}

#define M_ENG_PROFILER_ARRAY_N 256
static m_eng_profiler_entry profiler_entries[M_ENG_PROFILER_ARRAY_N];
static int profiler_entries_used = 0;

void m_eng_init_profiler()
{
	for (int i = 0; i < M_ENG_PROFILER_ARRAY_N; i++)
	{
		profiler_entries[i].function_name = NULL;
		profiler_entries[i].open_cycle = 0;
		profiler_entries[i].total_cycles = 0;
		profiler_entries[i].calls = 0;
		profiler_entries[i].peak_cycles = 0;
		profiler_entries[i].ra_cycles = 0.0;
	}
}

void m_eng_profiler_log_entry(const char *function_name)
{
	int index = -1;
	
	for (int i = 0; i < binary_min(M_ENG_PROFILER_ARRAY_N, profiler_entries_used); i++)
	{
		if (profiler_entries[i].function_name == function_name)
		{
			index = i;
			break;
		}
	}
	
	if (index == -1)
	{
		index = profiler_entries_used;
		
		if (index >= M_ENG_PROFILER_ARRAY_N)
			return;
		
		profiler_entries[index].function_name = function_name;
		profiler_entries_used++;
	}
	
	profiler_entries[index].calls++;
	profiler_entries[index].open_cycle = current_cycle();
}

#define M_ENG_PROFILER_RA_CYCLES_ALPHA 0.9

void m_eng_profiler_log_return(const char *function_name, uint64_t cycle)
{
	int index = -1;
	
	for (int i = 0; i < binary_min(M_ENG_PROFILER_ARRAY_N, profiler_entries_used); i++)
	{
		if (profiler_entries[i].function_name == function_name)
		{
			index = i;
			break;
		}
	}
	
	if (index == -1)
	{
		return;
	}
	
	uint64_t call_cycles = cycle - profiler_entries[index].open_cycle;
	
	profiler_entries[index].total_cycles += call_cycles;
	
	if (call_cycles > profiler_entries[index].peak_cycles)
	{
		profiler_entries[index].peak_cycles = call_cycles;
	}
	
	#if M_ENG_LOG_LEVEL & M_ENG_LOG_SPIKES
	if (profiler_entries[index].calls > 50 && call_cycles >= 3 * profiler_entries[index].ra_cycles)
	{
		M_LOG("Warning: duration spike in function %s; call took %d cycles vs average of %.01f",
			profiler_entries[index].function_name, call_cycles, profiler_entries[index].ra_cycles);
	}
	#endif
	
	profiler_entries[index].ra_cycles = M_ENG_PROFILER_RA_CYCLES_ALPHA * profiler_entries[index].ra_cycles + (1.0 - M_ENG_PROFILER_RA_CYCLES_ALPHA) * (double)call_cycles;
	
}

// Sort so that the function using the most CPU time appears last when printed
void m_eng_profiler_sort()
{
	int n = profiler_entries_used;
	
	if (!n) return;
	
	m_eng_profiler_entry tmp;
	
	int sorted;
	
	do
	{
		sorted = 1;
		for (int i = 0; i < n - 1; i++)
		{
			if (profiler_entries[i].total_cycles > profiler_entries[i + 1].total_cycles)
			{
				sorted = 0;
				
				memcpy(&tmp, 				 	 &profiler_entries[i],		sizeof(m_eng_profiler_entry));
				memcpy(&profiler_entries[i], 	 &profiler_entries[i + 1], 	sizeof(m_eng_profiler_entry));
				memcpy(&profiler_entries[i + 1], &tmp, 						sizeof(m_eng_profiler_entry));
			}
		}
	} while (!sorted);
}

void m_eng_profiler_print()
{
	m_voice_printf(M_VOICE_PRF, "Profiler data\n\n");
	
	m_eng_profiler_sort();
	
	for (int i = 0; i < profiler_entries_used; i++)
	{
		m_voice_printf(M_VOICE_PRF, "Function: %s\n\tTotal     calls: %d\n\n\tTotal    cycles: %llu\n\tTotal      time: %.3fms",
			profiler_entries[i].function_name, profiler_entries[i].calls, profiler_entries[i].total_cycles,
			CYCLES_TO_SECONDS(profiler_entries[i].total_cycles) * 1000.0);
		m_voice_printf(M_VOICE_PRF, "\n\tAverage  cycles: %.3f\n\tAverage    time: %.3fus",
			(double)profiler_entries[i].total_cycles / (double)profiler_entries[i].calls,
			CYCLES_TO_SECONDS((double)profiler_entries[i].total_cycles / (double)profiler_entries[i].calls) * 1000000.0);
		m_voice_printf(M_VOICE_PRF, "\n\tPeak     cycles: %llu\n\tPeak       time: %.3fus\n",
			profiler_entries[i].peak_cycles, CYCLES_TO_SECONDS(profiler_entries[i].peak_cycles) * 1000000.0);
		m_voice_printf(M_VOICE_PRF, "\n\tRunning average cycles: %.3f\n\tRunning average   time: %.3fus\n\n",
			profiler_entries[i].ra_cycles, CYCLES_TO_SECONDS(profiler_entries[i].ra_cycles) * 1000000.0);
	}
}

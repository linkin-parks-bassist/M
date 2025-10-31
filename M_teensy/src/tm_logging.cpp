#include <Arduino.h>
#include "tm.h"

static const char *FNAME = "tm_logging.cpp";

#define TM_LOG_ENTRIES_N 64

static tm_log_entry log_entries[TM_LOG_ENTRIES_N];

static int log_entries_index = 0;
static int log_entries_wrapped = 0;

static const char *return_string = " returned";

#if TM_LOG_LEVEL == TM_LOG_TRACE
#define MESSAGE_BEGIN_COL 43
#else
#define MESSAGE_BEGIN_COL 80
#endif

int format_log_entry(int index, char *buf, int max_len)
{
	double seconds = cycles_to_seconds(log_entries[index].cycle);
	char *error_message = NULL;
	
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
	
	#if TM_LOG_LEVEL == TM_LOG_TRACE
	if (log_entries[index].type == TM_TRACE_FUNCTION_ENTER || log_entries[index].type == TM_TRACE_FUNCTION_RETURN)
	{
		for (j = 0; i < MESSAGE_BEGIN_COL && i < max_len - 1; j++)
			buf[i++] = ' ';
		
		if (i >= max_len - 1) return i;
		
		#ifdef TM_LOG_INDENT_TRACE
		for (j = 0; (uint32_t)j < log_entries[index].trace_depth && i < max_len - 1; j++)
				buf[i++] = ' ';
			
		if (i >= max_len - 1) return i;
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
		case TM_LOG_ENTRY_ERROR:
		case TM_LOG_ENTRY_RETURN_ERR:
			error_message = m_error_code_to_string(log_entries[index].data);
			
			if (error_message)
			{
				for (j = 0; error_message[j] != 0 && i < max_len - 1; j++)
					buf[i++] = error_message[j];
			}
			break;
		
		case TM_LOG_ENTRY_RETURN_PTR:
			i += snprintf(&buf[i], max_len - i, "%p", (void*)log_entries[index].data);
			break;
		
		case TM_LOG_ENTRY_RETURN_INT:
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
	int new_index = (log_entries_index + 1) % TM_LOG_ENTRIES_N;
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

void tm_trace_log_begin(const char *fname, const char *line, const char *function, int local_trace_depth, uint32_t cycle)
{
	write_log_entry(TM_TRACE_FUNCTION_ENTER, fname, line, function, "entered", 0, trace_depth, cycle);
	trace_depth++;
}

void tm_trace_log_return(const char *fname, const char *line, const char *function, int local_trace_depth, uint32_t cycle)
{
	write_log_entry(TM_TRACE_FUNCTION_RETURN, fname, line, function, "returned", 0, trace_depth, cycle);
	trace_depth--;
}

void tm_log_error_code(const char *fname, const char *line, const char *function, int error_code, uint32_t cycle)
{
	write_log_entry(TM_LOG_ENTRY_ERROR, fname, line, function, "error: ", error_code, 0, cycle);
}

void tm_log_return_err(const char *fname, const char *line, const char *function, int error_code, uint32_t cycle)
{
	write_log_entry(TM_LOG_ENTRY_RETURN_ERR, fname, line, function, "returned with error code ", error_code, 0, cycle);
}

void tm_log_return_ptr(const char *fname, const char *line, const char *function, void *ptr, uint32_t cycle)
{
	write_log_entry(TM_LOG_ENTRY_RETURN_PTR, fname, line, function, "returned with pointer ", (uint32_t)ptr, 0, cycle);
}

void tm_log_return_int(const char *fname, const char *line, const char *function, int val, uint32_t cycle)
{
	write_log_entry(TM_LOG_ENTRY_RETURN_PTR, fname, line, function, "returned with integer ", val, 0, cycle);
}

void tm_log_return_(const char *fname, const char *line, const char *function, uint32_t cycle)
{
	write_log_entry(TM_LOG_ENTRY_RETURN, fname, line, function, "returned something", 0, 0, cycle);
}

#define LOG_ENTRIES_PRINT_BUF_LEN 4096

void tm_print_flush_log()
{
	if (!log_entries_index && !log_entries_wrapped)
		return;
	
	char buf[LOG_ENTRIES_PRINT_BUF_LEN];
	
	int wrap = log_entries_wrapped;
	int i = 0;
	int break_index = wrap ? TM_LOG_ENTRIES_N : log_entries_index;
	int index = wrap ? log_entries_index : 0;
	
log_bufferize:
	
	while (i < LOG_ENTRIES_PRINT_BUF_LEN && index < break_index)
	{
		i += format_log_entry(index++, &buf[i], LOG_ENTRIES_PRINT_BUF_LEN - i);
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
	
	Serial.print(buf);
	if (buf[(i < LOG_ENTRIES_PRINT_BUF_LEN) ? i - 1 : LOG_ENTRIES_PRINT_BUF_LEN - 2] != '\n')
		Serial.print("\n");
	
	log_entries_index = 0;
	log_entries_wrapped = 0;
}

#ifndef M_ENG_LOGGING_H_
#define M_ENG_LOGGING_H_

#define M_ENG_TRACE_FUNCTION_ENTER  	0
#define M_ENG_TRACE_FUNCTION_RETURN 	1
#define M_ENG_LOG_ENTRY_ERROR		 	2
#define M_ENG_LOG_ENTRY_RETURN_ERR 	3
#define M_ENG_LOG_ENTRY_RETURN_PTR 	4
#define M_ENG_LOG_ENTRY_RETURN_INT 	5
#define M_ENG_LOG_ENTRY_RETURN  		6

typedef struct
{
	int type;
	const char *file_name;
	const char *line;
	const char *data_type;
	const char *function;
	const char *message;
	uint64_t cycle;
	uint32_t data;
	uint32_t trace_depth;
} m_eng_log_entry;

typedef struct
{
	const char *function_name;
	uint64_t open_cycle;
	uint64_t calls;
	uint64_t total_cycles;
	double ra_cycles;
} m_eng_profiler_entry;

#define M_ENG_LOG_ERRORS 	0b0001
#define M_ENG_LOG_TRACE  	0b0010
#define M_ENG_LOG_RETURNS 	0b0100

#define M_ENG_LOG_EVERYTHING (M_ENG_LOG_ERRORS | M_ENG_LOG_TRACE | M_ENG_LOG_RETURNS)

#define STR(x) #x
#define XSTR(x) (STR(x))

#define M_ENG_LOG_LEVEL M_ENG_LOG_ERRORS
//#define M_ENG_PROFILER


#define M_ENG_LOG_INDENT_TRACE

#ifdef  M_ENG_LOG_LEVEL
	#if M_ENG_LOG_LEVEL & M_ENG_LOG_TRACE
		#define M_ENG_TRACE_LOG_ENTRY()  m_eng_trace_log_begin (FNAME, XSTR(__LINE__), __func__, trace_depth, current_cycle());
		#define M_ENG_TRACE_LOG_RETURN() m_eng_trace_log_return(FNAME, XSTR(__LINE__), __func__, trace_depth, current_cycle());
	#endif
	
	#if M_ENG_LOG_LEVEL & M_ENG_LOG_RETURNS
		#define M_ENG_LOG_RETURN_ERR_CODE(x)	m_eng_log_return_err(FNAME, XSTR(__LINE__), __func__, x, current_cycle());
		#define M_ENG_LOG_RETURN_PTR(x) 		m_eng_log_return_ptr(FNAME, XSTR(__LINE__), __func__, x, current_cycle());
		#define M_ENG_LOG_RETURN_INT(x) 		m_eng_log_return_int(FNAME, XSTR(__LINE__), __func__, x, current_cycle());
		#define M_ENG_LOG_RETURN(x) 	 		m_eng_log_return_	(FNAME, XSTR(__LINE__), __func__,    current_cycle());
	#endif
	
	#if M_ENG_LOG_LEVEL & M_ENG_LOG_ERRORS
		#define M_ENG_LOG_ERROR(x) \
			if (x != NO_ERROR) \
				m_eng_log_error_code(FNAME, XSTR(__LINE__), __func__, x, current_cycle());
	#endif
#endif

#ifdef M_ENG_PROFILER
	#define M_ENG_PROFILER_LOG_ENTRY()  m_eng_profiler_log_entry ( __func__);
	#define M_ENG_PROFILER_LOG_RETURN() m_eng_profiler_log_return( __func__, current_cycle());
#else
	#define M_ENG_PROFILER_LOG_ENTRY()
	#define M_ENG_PROFILER_LOG_RETURN()
#endif

#ifndef M_ENG_TRACE_LOG_ENTRY
#define M_ENG_TRACE_LOG_ENTRY()
#endif

#ifndef M_ENG_TRACE_LOG_RETURN
#define M_ENG_TRACE_LOG_RETURN()
#endif

#ifndef M_ENG_LOG_RETURN_ERR_CODE
#define M_ENG_LOG_RETURN_ERR_CODE(x)
#endif

#ifndef M_ENG_LOG_RETURN_PTR
#define M_ENG_LOG_RETURN_PTR(x)
#endif

#ifndef M_ENG_LOG_RETURN_INT
#define M_ENG_LOG_RETURN_INT(x)
#endif

#ifndef M_ENG_LOG_RETURN
#define M_ENG_LOG_RETURN(x)
#endif

#ifndef M_ENG_LOG_ERROR
#define M_ENG_LOG_ERROR(x)
#endif

#define FUNCTION_START() 		M_ENG_PROFILER_LOG_ENTRY();  M_ENG_TRACE_LOG_ENTRY();
#define RETURN_VOID() 			M_ENG_PROFILER_LOG_RETURN(); M_ENG_TRACE_LOG_RETURN(); return;
#define RETURN_ERR_CODE(x) 		M_ENG_PROFILER_LOG_RETURN(); M_ENG_LOG_ERROR(x); M_ENG_TRACE_LOG_RETURN(); M_ENG_LOG_RETURN_ERR_CODE(x); return x;
#define RETURN_NEG_ERR_CODE(x) 	M_ENG_PROFILER_LOG_RETURN(); M_ENG_LOG_ERROR(x); M_ENG_TRACE_LOG_RETURN(); M_ENG_LOG_RETURN_ERR_CODE(x); return -x;
#define RETURN_PTR(x)			M_ENG_PROFILER_LOG_RETURN(); M_ENG_TRACE_LOG_RETURN(); M_ENG_LOG_RETURN_PTR(x); return x;
#define RETURN_INT(x)			M_ENG_PROFILER_LOG_RETURN(); M_ENG_TRACE_LOG_RETURN(); M_ENG_LOG_RETURN_INT(x); return x;
#define RETURN(x)				M_ENG_PROFILER_LOG_RETURN(); M_ENG_TRACE_LOG_RETURN(); M_ENG_LOG_RETURN(); return x;

void m_eng_log(const char *fmt, ...);
void m_eng_print_log();
void m_eng_print_flush_log();

void m_eng_trace_log_begin	(const char *fname, const char *line, const char *function, int local_trace_depth, uint32_t cycle);
void m_eng_trace_log_return (const char *fname, const char *line, const char *function, int local_trace_depth, uint32_t cycle);
void m_eng_log_error_code	(const char *fname, const char *line, const char *function, int error_code, uint32_t cycle);
void m_eng_log_return_err	(const char *fname, const char *line, const char *function, int error_code, uint32_t cycle);
void m_eng_log_return_ptr	(const char *fname, const char *line, const char *function, void *ptr, uint32_t cycle);
void m_eng_log_return_int	(const char *fname, const char *line, const char *function, int val, uint32_t cycle);
void m_eng_log_return_		(const char *fname, const char *line, const char *function, uint32_t cycle);

#define M_LOG_ERROR(x) m_eng_log_error_code(FNAME, XSTR(__LINE__), __func__, x, current_cycle());

#ifdef M_ENG_PROFILER
void m_eng_init_profiler();
void m_eng_profiler_log_entry (const char *function_name);
void m_eng_profiler_log_return(const char *function_name, uint64_t cycle);

void m_eng_profiler_print();
#endif

#define CYCLES_TO_SECONDS(x) ((double)(x) * 1.66666667e-9)

#endif

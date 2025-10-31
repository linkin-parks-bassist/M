#ifndef TM_LOGGING_H_
#define TM_LOGGING_H_

#define TM_TRACE_FUNCTION_ENTER  	0
#define TM_TRACE_FUNCTION_RETURN 	1
#define TM_LOG_ENTRY_ERROR		 	2
#define TM_LOG_ENTRY_RETURN_ERR 	3
#define TM_LOG_ENTRY_RETURN_PTR 	4
#define TM_LOG_ENTRY_RETURN_INT 	5
#define TM_LOG_ENTRY_RETURN  		6

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
} tm_log_entry;

#define TM_LOG_ERRORS 	0b01
#define TM_LOG_TRACE  	0b10
#define TM_LOG_RETURNS 	0b100

#define TM_LOG_EVERYTHING (TM_LOG_ERRORS | TM_LOG_TRACE | TM_LOG_RETURNS)

#define STR(x) #x
#define XSTR(x) (STR(x))

#define TM_LOG_LEVEL TM_LOG_EVERYTHING

//#define TM_LOG_INDENT_TRACE

#ifdef  TM_LOG_LEVEL
	#if TM_LOG_LEVEL & TM_LOG_TRACE
		#define TM_TRACE_LOG_ENTRY()  tm_trace_log_begin (FNAME, XSTR(__LINE__), __func__, trace_depth, ARM_DWT_CYCCNT + cycles_upper);
		#define TM_TRACE_LOG_RETURN() tm_trace_log_return(FNAME, XSTR(__LINE__), __func__, trace_depth, ARM_DWT_CYCCNT + cycles_upper);
	#endif
	
	#if TM_LOG_LEVEL & TM_LOG_RETURNS
		#define TM_LOG_RETURN_ERR_CODE(x)	tm_log_return_err(FNAME, XSTR(__LINE__), __func__, x, ARM_DWT_CYCCNT + cycles_upper);
		#define TM_LOG_RETURN_PTR(x) 		tm_log_return_ptr(FNAME, XSTR(__LINE__), __func__, x, ARM_DWT_CYCCNT + cycles_upper);
		#define TM_LOG_RETURN_INT(x) 		tm_log_return_int(FNAME, XSTR(__LINE__), __func__, x, ARM_DWT_CYCCNT + cycles_upper);
		#define TM_LOG_RETURN(x) 	 		tm_log_return_	 (FNAME, XSTR(__LINE__), __func__, ARM_DWT_CYCCNT + cycles_upper);
	#endif
	
	#if TM_LOG_LEVEL & TM_LOG_ERRORS
		#define TM_LOG_ERROR(x) \
			if (x != NO_ERROR) \
				tm_log_error_code(FNAME, XSTR(__LINE__), __func__, x, ARM_DWT_CYCCNT + cycles_upper);
	#endif
#endif

#ifndef TM_TRACE_LOG_ENTRY
#define TM_TRACE_LOG_ENTRY()
#endif

#ifndef TM_TRACE_LOG_RETURN
#define TM_TRACE_LOG_RETURN()
#endif

#ifndef TM_LOG_RETURN_ERR_CODE
#define TM_LOG_RETURN_ERR_CODE(x)
#endif

#ifndef TM_LOG_RETURN_PTR
#define TM_LOG_RETURN_PTR(x)
#endif

#ifndef TM_LOG_RETURN_INT
#define TM_LOG_RETURN_INT(x)
#endif

#ifndef TM_LOG_RETURN
#define TM_LOG_RETURN(x)
#endif

#ifndef TM_LOG_ERROR
#define TM_LOG_ERROR(x)
#endif

#define FUNCTION_START() 		TM_TRACE_LOG_ENTRY();
#define RETURN_VOID() 			TM_TRACE_LOG_RETURN(); return;
#define RETURN_ERR_CODE(x) 		TM_LOG_ERROR(x); TM_TRACE_LOG_RETURN(); TM_LOG_RETURN_ERR_CODE(x); return x;
#define RETURN_NEG_ERR_CODE(x) 	TM_LOG_ERROR(x); TM_TRACE_LOG_RETURN(); TM_LOG_RETURN_ERR_CODE(x); return -x;
#define RETURN_PTR(x)			TM_TRACE_LOG_RETURN(); TM_LOG_RETURN_PTR(x); return x;
#define RETURN_INT(x)			TM_TRACE_LOG_RETURN(); TM_LOG_RETURN_INT(x); return x;
#define RETURN(x)				TM_TRACE_LOG_RETURN(); TM_LOG_RETURN(); return x;

void tm_log(const char *fmt, ...);
void tm_print_log();
void tm_print_flush_log();

void tm_trace_log_begin	(const char *fname, const char *line, const char *function, int local_trace_depth, uint32_t cycle);
void tm_trace_log_return(const char *fname, const char *line, const char *function, int local_trace_depth, uint32_t cycle);
void tm_log_error_code	(const char *fname, const char *line, const char *function, int error_code, uint32_t cycle);
void tm_log_return_err	(const char *fname, const char *line, const char *function, int error_code, uint32_t cycle);
void tm_log_return_ptr	(const char *fname, const char *line, const char *function, void *ptr, uint32_t cycle);
void tm_log_return_int	(const char *fname, const char *line, const char *function, int val, uint32_t cycle);
void tm_log_return_		(const char *fname, const char *line, const char *function, uint32_t cycle);

#endif

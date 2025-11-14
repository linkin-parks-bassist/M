#include "m_error_codes.h"

static const char *FNAME = "m_error_codes.c";

// Copy in #define's and regex replace
//
// #define ([^\s]*)\s*[0-9]*\n
//
// with
//
// \t\tcase \1:\n\t\t\treturn "\1";\n

const char *m_error_code_to_string(int error_code)
{
	switch (error_code)
	{
		case NO_ERROR:
			return "NO_ERROR";
		case ERR_NULL_PTR:
			return "ERR_NULL_PTR";
		case ERR_BAD_ARGS:
			return "ERR_BAD_ARGS";
		case ERR_SGTL5000_WRITE_FAIL:
			return "ERR_SGTL5000_WRITE_FAIL";

		case ERR_ALLOC_FAIL:
			return "ERR_ALLOC_FAIL";

		case ERR_PIPELINE_NULL:
			return "ERR_PIPELINE_NULL";
		case ERR_PIPELINE_FULL:
			return "ERR_PIPELINE_FULL";
		case ERR_POSITION_ILLEGAL:
			return "ERR_POSITION_ILLEGAL";
		case ERR_POSITION_OCCUPIED:
			return "ERR_POSITION_OCCUPIED";

		case ERR_TRANSFORMER_MALFORMED:
			return "ERR_TRANSFORMER_MALFORMED";
		case ERR_ARRAY_MALFORMED:
			return "ERR_ARRAY_MALFORMED";

		case ERR_POT_LINK_MALFORMED:
			return "ERR_POT_LINK_MALFORMED";
		case ERR_SWITCH_LINK_MALFORMED:
			return "ERR_SWITCH_LINK_MALFORMED";

		case ERR_MUTEX_UNAVAILABLE:
			return "ERR_MUTEX_UNAVAILABLE";

		case ERR_FIXED_ARRAY_FULL:
			return "ERR_FIXED_ARRAY_FULL";

		case ERR_BUSTED_MSG:
			return "ERR_BUSTED_MSG";
		case ERR_BAD_REQUEST:
			return "ERR_BAD_REQUEST";

		case ERR_QUEUE_SEND_FAILED:
			return "ERR_QUEUE_SEND_FAILED";
		case ERR_QUEUE_FULL:
			return "ERR_QUEUE_FULL";
		case ERR_LOOP_DETECTED:
			return "ERR_LOOP_DETECTED";

		case ERR_NODE_PRIVATE:
			return "ERR_NODE_PRIVATE";
		case ERR_PIPELINE_BUSTED:
			return "ERR_PIPELINE_BUSTED";

		case ERR_INVALID_MESSAGE:
			return "ERR_INVALID_MESSAGE";

		case ERR_VALUE_OUT_OF_BOUNDS:
			return "ERR_VALUE_OUT_OF_BOUNDS";

		case ERR_INVALID_PARAMETER_ID:
			return "ERR_INVALID_PARAMETER_ID";
		case ERR_INVALID_OPTION_ID:
			return "ERR_INVALID_OPTION_ID";
		case ERR_INVALID_TRANSFORMER_ID:
			return "ERR_INVALID_TRANSFORMER_ID";
		case ERR_INVALID_PROFILE_ID:
			return "ERR_INVALID_PROFILE_ID";

		case ERR_INCONSISTENT_BACK_PIPELINE:
			return "ERR_INCONSISTENT_BACK_PIPELINE";

		case ERR_UNKNOWN_ERR:
			return "ERR_UNKNOWN_ERR";
		case ERR_UNIMPLEMENTED:
			return "ERR_UNIMPLEMENTED";
		
		default:
			return "UNKNOWN ERROR CODE";
	}
}

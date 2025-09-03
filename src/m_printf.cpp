#include <Arduino.h>
#include <cstdarg>  // or <stdarg.h> in C
#include <cstdio>   // for vsnprintf()
#include "m_printf.h"

//#define ALLOW_PRINTLINES

void m_printf(const char *fmt, ...)
{
	#ifdef ALLOW_PRINTLINES
	char buf[256];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);
	//Serial.print(buf);
	Serial.flush();
	#endif
}

#include "shell.h"

void ts_print(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	vprintf(format, args);

	va_end(args);
}


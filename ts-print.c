#include "shell.h"

void ts-print(const char *message)
{
	write(STDOUT_FILENO, message, strlen(message));
}

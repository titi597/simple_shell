#include "shell.h"
#include "env_command.h"

int execute_setenv(char **tokens)
{
	if (tokens[1] && tokens[2])
	{
		if (setenv(tokens[1], tokens[2], 1) != 0)
		{
			fprintf(stderr, "Error setting environment variable\n");
			return (1);
		}
	} else
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (1);
	}
	return (0);
}

int execute_unsetenv(char **tokens)
{
	if (tokens[1])
	{
		if (unsetenv(tokens[1]) != 0)
		{
			fprintf(stderr, "Error unsetting environment variable\n");
			return (1);
		}
	}
	else
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (1);
	}
	return (0);
}


#include "shell.h"

void execmd(char **argv)
{
	char *command = NULL, *actual_command = NULL;

	if (argv && argv[0])
	{
		/* get the command */
		command = argv[0];

		/* generate the path to this command before passing it to execve */
		actual_command = get_location(command);

		if (actual_command == NULL)
		{
			perror("./hsh");
			return;
		}
		/* This code will be executed in the child process. */
		if (execve(actual_command, argv, NULL) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
}


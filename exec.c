#include "shell.h"

void execmd(char **argv)
{
	pid_t child;
	int status;
	char *command = NULL, *actual_command = NULL;

	if (argv && argv[0])
	{
		/* get the command */
		command = argv[0];

		if (strcmp(command, "exit") == 0)
		{
			exit(0);
		}

		/* generate the path to this command before passing it to execve */
		actual_command = get_location(command);

		if (actual_command == NULL)
		{
			perror("./hsh");
			return;
		}
		child = fork();

		if (child == 0)
		{
			/* This code will be executed in the child process. */
			if (execve(actual_command, argv, NULL) == -1)
			{
				perror("Error");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);

			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
				return;
		}
	}
}


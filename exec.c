#include "shell.h"

void execmd(char **argv)
{
	pid_t pid;

	if (!argv || !argv[0])
	{
		return; /* Do nothing if there's no command. */
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork error");
	}
	else if (pid == 0)
	{
		/* This code will be executed in the child process. */
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("./hsh");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* This code will be executed in the parent process. */
		int status;

		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Waitpid error");
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		{

		}
	}
}



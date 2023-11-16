#include "shell.h"

/**
 * execute_exit - function that execute exiting status
 * done by Schiphtan and Thierry
 * @argv: pointer to an array
 */
void execute_exit(char **argv)
{
	int exit_status = 0;

	if (argv[1])
	{
		exit_status = atoi(argv[1]);
	}
	exit(exit_status);
}
/**
 * execute_env - function that execute envrnm
 * done by Schiphtan and Thierry
 * Descrption: executing the environment
 */
void execute_env(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
/**
 * execute_command - function that execute process id and wait status
 * done by Schiphtan and Thierry
 * @argv: pointer to an array
 * @actual_command: variable which is pointer
 */
void execute_command(char *actual_command, char **argv)
{
	pid_t child;
	int status;

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
/**
 * execmd - function that execute
 * done by Schiphtan and Thierry
 * @argv: pointer to an array
 */
void execmd(char **argv)
{
	char *command = NULL, *actual_command = NULL;


	if (argv && argv[0])
	{
		/* get the command */
		command = argv[0];

		if (strcmp(command, "exit") == 0)
		{
			execute_exit(argv);
		}
		else if (strcmp(command, "env") == 0)
		{
			execute_env();
		}
		else
		{
			/* generate the path to this command before passing it to execve */
			actual_command = get_location(command);

			if (actual_command == NULL)
			{
				perror("./hsh");
				return;
			}
			execute_command(actual_command, argv);
		}
	}
}

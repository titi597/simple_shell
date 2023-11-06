#include "shell.h"

static int running = 1;

void sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		/* Handle Ctrl+C here (e.g., print a message) */
		running = 0; /* Set the flag to exit the shell */
	}
}

void cleanup(char *lineptr, char *lineptr_copy, char **argv)
{
	int i;

	if (lineptr)
	{
		free(lineptr);
	}
	if (lineptr_copy)
	{
		free(lineptr_copy);
	}
	if (argv)
	{
		for (i = 0; argv[i]; i++)
		{
			free(argv[i]);
		}
		free(argv);
	}
}
void process_input(char *lineptr)
{
	char *delim = "\n";
	char *token = strtok(lineptr, delim);

	while (token != NULL)
	{
		char *command = strtok(token, "\t\n");

		if (command != NULL)
		{
			char *argv[2];

			argv[0] = command;
			argv[1] = NULL;
			execmd(argv);
		}
		token = strtok(NULL, delim);
	}
}
static int is_running(void)
{
	return (running);
}
int main(int ac, char **argv)
{
	(void)ac, (void)argv;

	signal(SIGINT, sigint_handler);

	while (is_running())
	{
		size_t n = 0;
		ssize_t nchars_read;
		char *lineptr = NULL, *lineptr_copy = NULL;

		printf("(ts_shell) $ ");

		nchars_read = getline(&lineptr, &n, stdin);

		if (nchars_read == -1)
		{
			printf("\n");
			return (-1);
		}
		lineptr_copy = malloc(sizeof(char) * nchars_read);
		if (lineptr_copy == NULL)
		{
			perror("tsh: memory allocation error");
			return (-1);
		}
		strcpy(lineptr_copy, lineptr);
		process_input(lineptr_copy);

		cleanup(lineptr, lineptr_copy, NULL);
	}
	return (0);
}


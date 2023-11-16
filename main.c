#include "shell.h"
#include "env_command.h"
#include "commands_handler.h"
#include <string.h>

/**
 * print_prompt - function for printing prompt
 * @cwd: pointer to an array
 */
void print_prompt(const char *cwd)
{
	char prompt[MAX_PATH_LENGTH + 30];

	snprintf(prompt, sizeof(prompt), "(ts_shell) $ %s# ", cwd);
	printf("%s", prompt);
}
/**
 * handle_input - function that handlers input commands
 * @lineptr_copy: pointer to an arry
 */
void handle_input(char *lineptr_copy)
{
	char cwd[MAX_PATH_LENGTH];

	if (strncmp(lineptr_copy, "cd", 2) == 0)
	{
		char *directory = strtok(lineptr_copy + 2, " \t\r\n");

		if (changeDirectory(directory) != 0)
		{
			/* Handle the error as needed */
		}
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			/* Print current directory or handle as needed */
		}
		else
		{
			perror("getcwd");
		}
	}
	else
	{
		handle_commands(lineptr_copy);
	}
}
/**
 * main - main function of the shell
 * @ac: an array
 * @argv: pointer to an array
 * Return: 0 (success)
 */
int main(int ac, char **argv)
{
	char *lineptr = NULL, *lineptr_copy = NULL;
	size_t n = 0;
	ssize_t nchars_read;

	(void)ac, (void)argv;
	/* Create a loop for the shell's prompt */
	while (1)
	{
		char cwd[MAX_PATH_LENGTH];

		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("getcwd");
			strcpy(cwd, "?");
		}
		print_prompt(cwd);
		nchars_read = getline(&lineptr, &n, stdin);
		/* check if the getline function failed or reached EOF */
		if (nchars_read == -1)
		{
			printf("\n");
			free(lineptr);
			exit(-1);
		}
		/* allocate space for a copy of the lineptr */
		lineptr_copy = malloc(sizeof(char) * nchars_read);
		if (lineptr_copy == NULL)
		{
			perror("tsh: memory allocation error");
			free(lineptr);
			exit(-1);
		}
		/* copy lineptr to lineptr_copy */
		strcpy(lineptr_copy, lineptr);
		handle_input(lineptr_copy);
		free(lineptr_copy);
	}
	/* free up allocated memory */
	free(lineptr);
	return (0);
}


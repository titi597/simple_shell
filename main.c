#include "shell.h"
#include "env_command.h"
#include <string.h>

/**
 * main - main function that is helping the shell to work interactively
 * done by Schiphtan and Thierry
 * @ac: an array
 * @argv: pointer to an array
 * Return: 0 success
 */
int main(int ac, char **argv)
{
	char prompt[MAX_PATH_LENGTH + 30];
	char *lineptr = NULL, *lineptr_copy = NULL;
	size_t n = 0;
	ssize_t nchars_read;
	const char *delim = " \n";
	int num_tokens = 0;
	char *token;
	char **tokens;
	int i, j;

	/* declaring void variables */
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
		snprintf(prompt, sizeof(prompt), "(ts_shell) $ %s# ", cwd);
		printf("%s", prompt);
		nchars_read = getline(&lineptr, &n, stdin);

		/* check if the getline function failed or reached EOF or use CTRL + D */
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
		/********** split the string (lineptr) into an array of words ********/
		/* calculate the total number of tokens */
		token = strtok(lineptr, delim);

		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, delim);
		}
		num_tokens++;

		/* Allocate space to hold the array of strings */
		tokens = (char **)malloc(sizeof(char *) * num_tokens);
		/* Store each token in the argv array */
		token = strtok(lineptr_copy, delim);

		for (i = 0; token != NULL; i++)
		{
			tokens[i] = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(tokens[i], token);
			token = strtok(NULL, delim);
		}
		tokens[i] = NULL;

		if (tokens != NULL && tokens[0] != NULL)
		{
			if (strcmp(tokens[0], "setenv") == 0)
			{
				int result = execute_setenv(tokens);

				if (result != 0)
				{
					/* Handle failure */
				}
			}
			else if (strcmp(tokens[0], "unsetenv") == 0)
			{
				int result = execute_unsetenv(tokens);

				if (result != 0)
				{
					/* Handle failure */
				}
			}
			else if (strcmp(tokens[0], "cd") == 0)
			{
				const char *newDir = (num_tokens > 1) ? tokens[1] : getenv("HOME");
				char cwd[MAX_PATH_LENGTH];

				if (strcmp(newDir, "-") == 0)
				{
					const char *oldDir = getenv("OLDPWD");

					if (oldDir == NULL)
					{
						fprintf(stderr, "OLDPWD not set\n");
						/* handle the error as needed */
					}
					newDir = oldDir;
					printf("%s\n", newDir);
				}
				/* Integrate changeDirectory and updatePWD here */
				if (changeDirectory(newDir) != 0)
				{

				}
				if (getcwd(cwd, sizeof(cwd)) != NULL)
				{
					printf("Current directory: %s\n", cwd);
				}
				else
				{
					perror("getcwd");
				}
				continue;
			}
			else
			{
				/* execute the command */
				execmd(tokens);
			}
			for (j = 0; j < i; j++)
			{
				free(tokens[j]);
			}
			free(tokens);
		}
		free(lineptr_copy);
	}
	/* free up allocated memory */
	free(lineptr);
	return (0);
}

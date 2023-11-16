#include <stdarg.h>
#include "shell.h"

/**
 * get_location - Find the full path of a command by
 * searching the PATH variable.
 * @command: The command to search for.
 *
 * Return: The full path of the command if found, otherwise NULL.
 */
char *get_location(char *command)
{
	struct stat buffer;

	if (command[0] == '/')
	{
		if (stat(command, &buffer) == 0)
		{
			return (strdup(command));
		}
	}
	else
	{
		char *path = getenv("PATH");

		if (path)
		{
			char *path_copy = strdup(path);
			char *path_token = strtok(path_copy, ":");

			while (path_token != NULL)
			{
				char *file_path = malloc(strlen(path_token) + 1 + strlen(command) + 1);

				sprintf(file_path, "%s/%s", path_token, command);

				if (stat(file_path, &buffer) == 0)
				{
					free(path_copy);
					return (file_path);
				}
				else
				{
					free(file_path);
					path_token = strtok(NULL, ":");
				}
			}
			free(path_copy);
		}
	}
	return (NULL);
}
/**
 * search_in_path - Search for a command in each directory
 * specified in the PATH variable.
 * @command: The command to search for.
 * @path_copy: Copy of the PATH variable.
 *
 * Return: The full path of the command if found, otherwise NULL.
 */
char *search_in_path(char *command, char *path_copy)
{
	char *path_token = strtok(path_copy, ":");

	while (path_token)
	{
		char *file_path = build_file_path(path_token, command);

		if (file_exists(file_path))
		{
			return (file_path);
		}
		fprintf(stderr, "File not found: %s\n", file_path);
		free(file_path);
		path_token = strtok(NULL, ":");
	}
	fprintf(stderr, "Command not found in PATH\n");
	return (NULL);
}

/**
 * search_in_current_directory - Search for a command in the current directory.
 * @command: The command to search for.
 *
 * Return: The full path of the command if found, otherwise NULL.
 */
char *search_in_current_directory(char *command)
{
	char *file_path = build_file_path(".", command);

	if (file_exists(file_path))
	{
		return (file_path);
	}
	free(file_path);
	return (NULL);
}

/**
 * build_file_path - Build the full path for a command in a given directory.
 * @directory: The directory to search in.
 * @command: The command to search for.
 *
 * Return: The full path of the command.
 */
char *build_file_path(char *directory, char *command)
{
	char *file_path;
	int directory_length = strlen(directory);
	int command_length = strlen(command);

	file_path = malloc(directory_length + command_length + 2);
	strcpy(file_path, directory);
	strcat(file_path, "/");
	strcat(file_path, command);
	strcat(file_path, "\0");

	return (file_path);
}
/**
 * file_exists - Check if a file exists.
 * @file_path: The path of the file to check.
 *
 * Return: 1 if the file exists, 0 otherwise.
 */
int file_exists(char *file_path)
{
	struct stat buffer;

	return (stat(file_path, &buffer) == 0);
}

#include "shell.h"

/**
 * changeDirectory - finction that will change directory
 * done by Schiphtan and Thierry
 * @path: pointer to an array
 * Return: 0 (sucess)
 */
int changeDirectory(const char *path)
{
	char cwd[MAX_PATH_LENGTH];

	if (chdir(path) != 0)
	{
		perror("cd");
		return (-1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		setenv("PWD", cwd, 1);
	}
	else
	{
		perror("getcwd");
		return (-1);
	}
	return (0);
}

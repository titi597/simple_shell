#include "shell.h"

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


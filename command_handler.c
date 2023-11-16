#include "shell.h"

/**
 * handle_commands - function that handles commands separated by ';'
 * @line: input line containing commands
 */
void handle_commands(char *line)
{
    char *token, *saveptr;
    char *commands[256];  // Adjust the size as needed

    // Tokenize the input line based on ';'
    int i = 0;
    token = strtok_r(line, ";", &saveptr);
    while (token != NULL)
    {
        commands[i++] = token;
        token = strtok_r(NULL, ";", &saveptr);
    }
    commands[i] = NULL;

    // Execute each command
    i = 0;
    while (commands[i] != NULL)
    {
        char *command_line = commands[i];
        char **argv = split_line(command_line);

        if (argv != NULL && argv[0] != NULL)
        {
            execmd(argv);
            free(argv);
        }

        i++;
    }
}


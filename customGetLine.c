#include "shell.h"
#include <errno.h>

#define MAX_LINE_LENGTH 1024

static char input_buffer[MAX_LINE_LENGTH];
static int buffer_pos;
static int buffer_size;

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);

/**
 * read_into_buffer - Helper function to read more characters into the buffer
 * @stream: variable which is pointer to an array
 * Return: the size of buffer
 */
static int read_into_buffer(FILE *stream)
{
	buffer_size = read(fileno(stream), input_buffer, MAX_LINE_LENGTH);
	buffer_pos = 0;
	return (buffer_size);
}

/**
 * find_end_of_line - Helper function to find the end of a line within
 * the buffer done by Schiphtan and Thierry
 * Dsecription: finding the end of line within buffer
 * Return: -1 success
 */
static int find_end_of_line(void)
{
	int i;

	for (i = buffer_pos; i < buffer_size; i++)
	{
		if (input_buffer[i] == '\n')
		{
			return (i + 1);  /* Include the newline character */
		}
	}
	return (-1);  /* End of line not found in the current buffer */
}

/**
 * resize_line_buffer - Helper function to resize the line buffer
 * @lineptr: pointer to an array
 * @n: variable which is a pointer to an array
 * @chars_read: an array  which reads
 */
static void resize_line_buffer(char **lineptr, size_t *n, ssize_t chars_read)
{
	if ((size_t)chars_read + buffer_pos >= *n)
	{
		*n *= 2;  /* Double the buffer size */
		*lineptr = (char *)realloc(*lineptr, *n);
	}
}
/**
 * split_line - function for tokenizing without use of strtok
 * @line: pointer to an array
 * Return: number of tokens
 */
char **split_line(char *line)
{
	char **tokens = (char **)malloc(sizeof(char *));
	const char *delim = " \t\n"; /* Define delimiters */
	int token_count = 0;
	char *token = strtok(line, delim);

	if (line == NULL)
	{
		return (NULL);
	}
	if (tokens == NULL)
	{
		return (NULL);
	}
	while (token != NULL)
	{
		int i;

		tokens[token_count] = (char *)malloc(strlen(token) + 1);
		if (tokens[token_count] == NULL)
		{
			for (i = 0; i < token_count; i++)
			{
				free(tokens[i]);
			}
			free(tokens);
			return (NULL);
		}
		strcpy(tokens[token_count], token);
		token_count++;
		/* Resize the tokens array */
		tokens = (char **)realloc(tokens, (token_count + 1) * sizeof(char *));
		if (tokens == NULL)
		{
			for (i = 0; i < token_count; i++)
			{
				free(tokens[i]);
			}
			return (NULL);
		}
		token = strtok(NULL, delim);
	}
	tokens[token_count] = NULL;
	return (tokens);
}
/**
 * custom_getline - function aiming creation of our own getline function
 * done by Schiphtan and Thierry
 * @lineptr: variable which is pointer
 * @n: variable which is pointer also to an array
 * @stream: pointer to an array
 * Return: chars calculated
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t chars_read = 0;

	if (lineptr == NULL || n == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	if (*lineptr == NULL || *n < MAX_LINE_LENGTH)
	{
		if (*lineptr != NULL)
		{
			free(*lineptr);
		}
		*n = MAX_LINE_LENGTH;
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
		{
			return (-1);
		}
	}
	while (1)
	{
		int j;
		int end_of_line = find_end_of_line();

		if (buffer_pos >= buffer_size)
		{
			if (read_into_buffer(stream) <= 0)
			{
				if (chars_read == 0)
				{
					return (-1);
				}
				else
				{
					break;
				}
			}
		}
		if (end_of_line != -1)
		{
			int copy_len = end_of_line - buffer_pos;

			resize_line_buffer(lineptr, n, chars_read);
			for (j = 0; j < copy_len; j++)
			{
				(*lineptr)[chars_read++] = input_buffer[buffer_pos++];
			}
			(*lineptr)[chars_read] = '\0';
			return (chars_read);
		}
		else
		{
			int remaining = buffer_size - buffer_pos;

			resize_line_buffer(lineptr, n, chars_read);
			for (j = 0; j < remaining; j++)
			{
				(*lineptr)[chars_read++] = input_buffer[buffer_pos++];
			}
		}
	}
	return (chars_read);
}

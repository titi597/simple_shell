#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

int main(int ac, char **argv);
void execmd(char **argv);
void process_input(char *lineptr);
void cleanup(char *lineptr, char *lineptr_copy, char **argv);
void sigint_handler(int signum);
char *get_location(char *command);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);

#endif

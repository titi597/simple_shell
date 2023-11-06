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

int main(int ac, char **argv);
void execmd(char **argv);
void process_input(char *lineptr);
void cleanup(char *lineptr, char *lineptr_copy, char **argv);
void sigint_handler(int signum);

#endif

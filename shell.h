#ifndef SHELL_H
#define SHELL_H

#define MAX_PATH_LENGTH 1024

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

void handle_input(char *lineptr_copy);
void print_prompt(const char *cwd);
int main(int ac, char **argv);
void execmd(char **argv);
void process_input(char *lineptr);
void cleanup(char *lineptr, char *lineptr_copy, char **argv);
void sigint_handler(int signum);
char *get_location(char *command);
char *search_in_path(char *command, char *path_copy);
char *search_in_current_directory(char *command);
char *build_file_path(char *directory, char *command);
int file_exists(char *file_path);
char *strdup_printf(const char *format, ...);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
int changeDirectory(const char *path);
void handle_cd(char *directory);
#endif

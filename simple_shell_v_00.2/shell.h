#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

extern char **environ;
void display_prompt(void);
ssize_t read_command(char **lineptr, size_t *len);
void delete_newline(char *lineptr, ssize_t read);
int is_empty_line(const char *lineptr);
int execute_command(char *cmd);

#endif

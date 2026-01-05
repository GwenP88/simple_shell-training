#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 1024
#define MAX_PATH 4096
#define PROMPT "-_- \\_(ツ)_/ "

/* Structure pour les built-ins */
typedef struct
{
	char *name;
	int (*func)(void);
} builtin_t;

/* Fonctions built-in */
int builtin_exit(void);
int builtin_env(void);
int builtin_cd(void);

/* Fonctions utilitaires */
char *find_command(char *command);
char *get_path(void);
int execute_builtin(char *command);
int is_builtin(char *command);
char *_getenv(const char *name);

#endif
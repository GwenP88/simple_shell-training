#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Nombre maximum d'arguments supportés (argv) */
#define MAX_ARGS 64
/* Taille maximum pour construire un chemin complet de commande */
#define MAX_PATH 1024
/* Texte affiché comme prompt en mode interactif */
#define PROMPT "test "

char *get_path(void);
char *find_command(char *command);
char *_getenv(const char *name);

#endif

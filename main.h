#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

extern char **environ;
char **empty_array(void);
char **split_string(char *string);
char **empty_array(void);

#endif

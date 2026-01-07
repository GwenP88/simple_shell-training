#include "shell.h"

/**
 * parse_line - Split an input line into tokens and build an argv array.
 * @line: Input string to tokenize.
 * @argv: Output array to fill with pointers to tokens.
 * @max_args: Maximum size of @argv.
 *
 * Return: Number of tokens stored in @argv,
 * or 0 if no token is found.
 */


int parse_line(char *line, char **argv, int max_args)
{
	char *token;
	int i = 0;

	token = strtok(line, " \t");
	while (token != NULL && i < max_args - 1)
	{
		argv[i] = token;
		i++;
		token = strtok(NULL, " \t");
	}
	argv[i] = NULL;
	return (i);
}

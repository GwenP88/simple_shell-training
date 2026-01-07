#include "shell.h"

/**
 * builtin_env - Prints the current environment
 *
 * Return: Always 0
 */
int builtin_env(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}

/**
 * builtin_exit - Exits the shell
 *
 * Return: EXIT_SHELL to request shell termination
 */
int builtin_exit(void)
{
	return (EXIT_SHELL);
}

/**
 * builtin_cd - Changes directory
 *
 * Return: 0 on success, 1 on failure
 */
int builtin_cd(void)
{
	/* À implémenter plus tard */
	return (0);
}

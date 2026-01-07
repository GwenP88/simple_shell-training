#include "shell.h"

/**
 * is_builtin - Checks if a command is a built-in
 * @command: Command to check
 *
 * Return: 1 if built-in, 0 otherwise
 */
int is_builtin(char *command)
{
	builtin_t builtins[] = {
		{"env", builtin_env},
		{"exit", builtin_exit},
		{"cd", builtin_cd},
		{NULL, NULL}
	};

	int i = 0;

	while (builtins[i].name)
	{
		if (strcmp(builtins[i].name, command) == 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * execute_builtin - Executes a built-in command
 * @command: Command to execute
 *
 * Return: 0 on success, -1 on failure
 */
int execute_builtin(char *command)
{
	builtin_t builtins[] = {
		{"env", builtin_env},
		{"exit", builtin_exit},
		{"cd", builtin_cd},
		{NULL, NULL}
	};

	int i = 0;

	while (builtins[i].name)
	{
		if (strcmp(builtins[i].name, command) == 0)
			return (builtins[i].func());
		i++;
	}
	return (-1);
}

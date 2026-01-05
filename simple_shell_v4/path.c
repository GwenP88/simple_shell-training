#include "shell.h"

/**
 * get_path - Get PATH from environment
 *
 * Return: PATH string or NULL
 */
char *get_path(void)
{
	return (getenv("PATH"));
}


char *find_command(char *command)
{
	char *path, *path_copy, *dir;
	static char full_path[MAX_PATH];

	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, X_OK) == 0)
			return (command);
		return (NULL);
	}

	path = get_path();
	if (path == NULL)
		return (NULL);

	path_copy = strdup(path);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		snprintf(full_path, MAX_PATH, "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
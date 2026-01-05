#include "shell.h"

/**
 * get_path - Get PATH from environment
 *
 * Return: PATH string or NULL
 */

char *get_path(void)
{
	return (_getenv("PATH"));
}

char *find_command(char *command)
{
	char *path, *path_copy, *dir;
	static char full_path[MAX_PATH];
	size_t len_dir = 0;
	size_t len_command = 0;

	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, X_OK) == 0)
			return (command);
		return (NULL);
	}

	path = get_path();
	if (path == NULL)
		return (NULL);

	path_copy = malloc(strlen(path) + 1);
	if (path_copy == NULL)
		return (NULL);
	strcpy(path_copy, path);
	
	len_command = strlen(command);
	dir = strtok(path_copy, ":");
	
	while (dir != NULL)
	{
		len_dir = strlen(dir);
		if (len_dir == 0)
		{
			full_path[0] = '.';
			full_path[1] = '/';

			strcpy(full_path + 2, command);

			if (access(full_path, X_OK) == 0)
			{
				free(path_copy);
				return (full_path);
			}
			dir = strtok(NULL, ":");
			continue;
		}

		
		if ((len_dir + len_command + 2) >= MAX_PATH)
		{
			dir = strtok(NULL, ":");
			continue;
		}

		strcpy(full_path, dir);
		if (dir[len_dir - 1] != '/')
			strcat(full_path, "/");

		strcat(full_path, command);

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

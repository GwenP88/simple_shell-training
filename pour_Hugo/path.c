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

/**
 * build_and_check_path - Build a candidate path from a PATH directory
 * and check it.
 * @dir: Current PATH directory segment.
 * @command: Command name to append to @dir.
 * @full_path: Buffer where the candidate full path is written.
 * @len_command: Length of @command (precomputed to avoid recalculating).
 *
 * Return: 1 if an executable command is found, otherwise 0.
 */

static int build_and_check_path
(char *dir, char *command, char *full_path, size_t len_command)
{
	size_t len_dir;

	len_dir = strlen(dir);

	if (len_dir == 0)
	{
		full_path[0] = '.';
		full_path[1] = '/';

		strcpy(full_path + 2, command);

		if (access(full_path, X_OK) == 0)
			return (1);
		return (0);
	}

	if ((len_dir + len_command + 2) >= MAX_PATH)
		return (0);

	strcpy(full_path, dir);
	if (dir[len_dir - 1] != '/')
		strcat(full_path, "/");

	strcat(full_path, command);

	if (access(full_path, X_OK) == 0)
		return (1);
	return (0);
}

/**
 * find_command - Find the full path of a command using the PATH variable.
 * @command: Command name to search for or a path starting with '/' or '.'.
 *
 * Return:
 * On success, a pointer to the full path string (static buffer) is returned.
 * If @command is an executable absolute/relative path, it returns @command.
 * On failure, returns NULL.
 */

char *find_command(char *command)
{
	char *path, *path_copy, *dir;
	static char full_path[MAX_PATH];
	size_t len_command;

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
		if (build_and_check_path(dir, command, full_path, len_command))
		{
			free(path_copy);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

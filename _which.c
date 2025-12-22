#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char *find_in_path(const char *cmd, char *path_env);

/**
 * main - entry point for a simple _which clone
 * @ac: number of arguments passed to the program
 * @av: array of strings containing the arguments
 *
 * Return: 0 if all commands are found, 1 if at least one command is not found,
 *	or 1 if the usage is incorrect (no command provided).
 */

int main(int ac, char **av)
{
	int i, status;
	char *path_env, *found_path;

	if (ac < 2)
	{
		printf("Usage: ./_which filename ...\n");
		return (1);
	}

	path_env = getenv("PATH");
	i = 1;
	status = 0;
	while (av[i])
	{
		if (strchr(av[i], '/') == NULL)
		{
			found_path = find_in_path(av[i], path_env);
			if (found_path != NULL)
			{
				printf("%s\n", found_path);
				free(found_path);
			}
			else
			{
				printf("%s: command not found\n", av[i]);
				status = 1;
			}
		}
		else
		{
			if (access(av[i], X_OK) == 0)
				printf("%s\n", av[i]);
			else
			{
				printf("%s: command not found\n", av[i]);
				status = 1;
			}
		}
		i++;
	}
	return (status);
}

/**
 * find_in_path - searches for a command in PATH directories
 * @cmd: command name to search for (without path)
 * @path_env: PATH environment variable content (colon-separated directories)
 *
 * Return: a newly allocated string containing
 *	the full executable path if found,
 *	or NULL if not found or on allocation error.
 */

char *find_in_path(const char *cmd, char *path_env)
{
	const char *seg_start, *seg_current;
	char *candidate_path;
	size_t seg_len, cmd_len, i, j;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);
	if (path_env == NULL || path_env[0] == '\0')
		return (NULL);

	seg_start = path_env;
	seg_current = path_env;
	cmd_len = strlen(cmd);

	while (1)
	{
		while (*seg_current != ':' && *seg_current != '\0')
		{
			seg_current++;
		}
		seg_len = seg_current - seg_start;
		if (seg_len == 0)
		{
			candidate_path = malloc(cmd_len + 3);
			if (candidate_path == NULL)
				return (NULL);
			candidate_path[0] = '.';
			candidate_path[1] = '/';
			strcpy(candidate_path + 2, cmd);
			if (access(candidate_path, X_OK) == 0)
				return (candidate_path);
			free(candidate_path);
		}
		else if (seg_len > 0)
		{
			candidate_path = malloc(cmd_len + seg_len + 2);
			if (candidate_path == NULL)
				return (NULL);
			for (i = 0; i < seg_len; i++)
			{
				candidate_path[i] = seg_start[i];
			}
			candidate_path[seg_len] = '/';
			for (j = 0; j < cmd_len; j++)
			{
				candidate_path[seg_len + 1 + j] = cmd[j];
			}
			candidate_path[seg_len + cmd_len + 1] = '\0';

			if (access(candidate_path, X_OK) == 0)
				return (candidate_path);
			free(candidate_path);
		}
		if (*seg_current == ':')
		{
			seg_current++;
			seg_start = seg_current;
		} else if (*seg_current == '\0')
			break;
	}
	return (NULL);
}

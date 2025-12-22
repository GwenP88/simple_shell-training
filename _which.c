#include "shell.h"



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
			candidate_path = malloc((cmd_len + 3);
			if (candidate_path == NULL)
				return (NULL);
			candidate_path[0] = '.';
			candidate_path[1] = '/';
			strcpy(candidate_path + 2, cmd);
			if (access(candidate_path, X_OK) == 0)
				return (candidate_path);
			else
				free (candidate_path);
		}
		else if (seg_len > 0)
		{
			candidate_path = malloc((cmd_len + seg_len + 2);
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
			else
				free (candidate_path);
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
	

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

extern char **environ;

int _setenv(const char *name, const char *value, int overwrite)
{
	size_t len_name, len_value, i, j, k, m;
	int size, count;
	char **buff, **new_environ, **old_env;
	char *buffer;
	static int env_copied = 0;

	if (name == NULL || name[0] == '\0' || value == NULL || strchr(name, '=') != NULL)
	{
		errno = EINVAL;	
		return (- 1);
	}

	if (env_copied == 0)
	{
		count = 0;
		while(environ[count] != NULL)
			count++;
		new_environ = malloc((count + 1) * sizeof(char*));
		if (new_environ == NULL)
		{
			errno = ENOMEM;
			return (-1);
		}
		for (k = 0; environ[k] != NULL; k++)
		{
			new_environ[k] = malloc(strlen(environ[k]) + 1);
			if (new_environ[k] == NULL) 
			{
				for (m = 0; m < k; m++) 
				{
					free(new_environ[m]);
				}
				free(new_environ);
				errno = ENOMEM;
				return (-1);
			}
			strcpy(new_environ[k], environ[k]);
		}
		new_environ[count] = NULL;
		environ = new_environ;
		env_copied = 1;
	}

	len_name = strlen(name);
	len_value = strlen(value);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(name, environ[i], len_name) == 0 && environ[i][len_name] == '=')
		{
			if (overwrite == 0)
				return (0);
			buffer = malloc(len_name + len_value + 2);
			if (buffer == NULL)
			{
				errno = ENOMEM;
				return (-1);
			}
			size = sprintf(buffer, "%s=%s", name, value);
			if (size < 0)
			{
				free(buffer);
				errno = ENOMEM;
				return (-1);
			}
			free(environ[i]);
			environ[i] = buffer;
			return (0);
		}
	}
	buffer = malloc(len_name + len_value + 2);
	if (buffer == NULL)
	{
		errno = ENOMEM;
		return (-1);
	}
	size = sprintf(buffer, "%s=%s", name, value);
	if (size < 0)
	{
		free(buffer);
		errno = ENOMEM;
		return (-1);
	}
	buff = malloc((i + 2) * sizeof(char *));
	if (buff == NULL)
	{
		free(buffer);
		errno = ENOMEM;
		return (-1);
	}
	j = 0;
	while (environ[j] != NULL)
	{
		buff[j] = environ[j];
		j++;
	}
	buff[i] = buffer;
	buff[i + 1] = NULL;
	old_env = environ;
	environ = buff;
	free(old_env);
	return (0);
}
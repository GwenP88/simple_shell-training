#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;
int _unsetenv(const char *name);

int main(void)
{
	if (setenv("TEST_VAR", "hello", 1) != 0)
	{
		perror("setenv");
		return (1);
	}

	printf("Before _unsetenv:\n");
	printf("TEST_VAR = %s\n", getenv("TEST_VAR"));

	if (_unsetenv("TEST_VAR") == -1)
	{
		perror("_unsetenv");
		return (1);
	}

	printf("\nAfter _unsetenv:\n");
	printf("TEST_VAR = %s\n", getenv("TEST_VAR"));

	printf("\nError tests:\n");

	if (_unsetenv(NULL) == -1)
		perror("NULL name");

	if (_unsetenv("") == -1)
		perror("Empty name");

	if (_unsetenv("A=B") == -1)
		perror("Invalid name (contains '=')");

	return (0);
}

/**
 * _unsetenv - delete an environment variable.
 * @name: Name of the environment variable to delete.
 *
 * Return: 0 on success, -1 on failure.
 */

int _unsetenv(const char *name)
{
	size_t len_name, i, j;

	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	if (environ == NULL)
		return (0);

	len_name = strlen(name);

	i = 0;

	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, len_name) == 0 && environ[i][len_name] == '=')
		{
			j = i;
			while (environ[j + 1] != NULL)
			{
				environ[j] = environ[j + 1];
				j++;
			}
			environ[j] = NULL;
		} else
		{
			i++;
		}
	}
	return (0);
}

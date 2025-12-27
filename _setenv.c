#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

extern char **environ;
int _setenv(const char *name, const char *value, int overwrite);

int main(void)
{
	const char *var = "HOLB_TEST_ENV";
	const char *v;
	int ret, e;

	/* État initial */
	v = getenv(var);
	printf("Initial getenv(%s) = %s\n", var, v ? v : "NULL");

	/* Ajout */
	errno = 0;
	ret = _setenv(var, "first", 0);
	e = errno;
	printf("\nAdd: _setenv(%s, first, 0) -> %d errno=%d (%s)\n",
	       var, ret, e, strerror(e));
	v = getenv(var);
	printf("After add getenv(%s) = %s\n", var, v ? v : "NULL");

	/* overwrite = 0 (ne change pas) */
	errno = 0;
	ret = _setenv(var, "second", 0);
	e = errno;
	printf("\nNo overwrite: _setenv(%s, second, 0) -> %d errno=%d (%s)\n",
	       var, ret, e, strerror(e));
	v = getenv(var);
	printf("After overwrite=0 getenv(%s) = %s\n", var, v ? v : "NULL");

	/* overwrite = 1 (remplace) */
	errno = 0;
	ret = _setenv(var, "second", 1);
	e = errno;
	printf("\nOverwrite: _setenv(%s, second, 1) -> %d errno=%d (%s)\n",
	       var, ret, e, strerror(e));
	v = getenv(var);
	printf("After overwrite=1 getenv(%s) = %s\n", var, v ? v : "NULL");

	/* Erreurs */
	errno = 0;
	ret = _setenv(NULL, "x", 1);
	e = errno;
	printf("\nError name=NULL -> %d errno=%d (%s)\n", ret, e, strerror(e));

	errno = 0;
	ret = _setenv("", "x", 1);
	e = errno;
	printf("Error name=\"\" -> %d errno=%d (%s)\n", ret, e, strerror(e));

	errno = 0;
	ret = _setenv("A=B", "x", 1);
	e = errno;
	printf("Error name contains '=' -> %d errno=%d (%s)\n", ret, e, strerror(e));

	errno = 0;
	ret = _setenv(var, NULL, 1);
	e = errno;
	printf("Error value=NULL -> %d errno=%d (%s)\n", ret, e, strerror(e));

	return 0;
}

int _setenv(const char *name, const char *value, int overwrite)
{
	size_t len_name, len_value, i, j;
	int size;
	char **new_env;
	char *buffer;

	if (name == NULL || name[0] == '\0' || value == NULL || strchr(name, '=') != NULL)
	{
		errno = EINVAL;	
		return (- 1);
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
	new_env = malloc((i + 2) * sizeof(char *));
	if (new_env == NULL)
	{
		free(buffer);
		errno = ENOMEM;
		return (-1);
	}
	j = 0;
	while (environ[j] != NULL)
	{
		new_env[j] = environ[j];
		j++;
	}
	new_env[i] = buffer;
	new_env[i + 1] = NULL;
	environ = new_env;
	return (0);
}
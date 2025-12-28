#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern char **environ;
int _setenv(const char *name, const char *value, int overwrite);

/**
 * cleanup_env - Frees the current environment array and its strings.
 *
 * Description: Iterates over `environ`,
 * frees each "NAME=VALUE" string,
 * then frees the `environ` array itself
 * and sets `environ` to NULL.
 *
 * Return: Void.
 */

static void cleanup_env(void)
{
	size_t i;

	if (!environ)
		return;

	for (i = 0; environ[i]; i++)
		free(environ[i]);

	free(environ);
	environ = NULL;
}

/**
 * main - Tests the custom _setenv implementation
 * with different overwrite modes.
 *
 * Return: 0 on success.
 */

int main(void)
{
	const char *var = "HOLB_TEST_ENV";
	const char *v;

	/* Force your _setenv to duplicate/own environ */
	_setenv("HOLB_INIT_ENV", "1", 0);

	/* Add */
	_setenv(var, "first", 0);
	v = getenv(var);
	printf("After add: %s=%s\n", var, v ? v : "NULL");

	/* No overwrite */
	_setenv(var, "second", 0);
	v = getenv(var);
	printf("After overwrite=0: %s=%s\n", var, v ? v : "NULL");

	/* Overwrite */
	_setenv(var, "second", 1);
	v = getenv(var);
	printf("After overwrite=1: %s=%s\n", var, v ? v : "NULL");

	/* Valgrind cleanup */
	cleanup_env();

	return (0);
}

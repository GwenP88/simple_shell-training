#include <stdio.h>

extern char **environ;

/**
 * main - prints the current process environment
 * @argc: argument count (unused)
 * @argv: rgument (unused)
 * @env: environment array passed to main
 *
 * Return: 0 on success
 */

int main(int argc __attribute__((unused)),
	char *argv[] __attribute__((unused)), char **env)
{
	/* Cast to void * because printf with %p expects a void pointer */
	printf("%p\n", (void *)environ);
	/* Cast to void * because printf with %p expects a void pointer */
	printf("%p\n", (void *)env);
	return (0);
}

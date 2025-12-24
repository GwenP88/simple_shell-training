#include <stdio.h>

extern char **environ;

/**
 * main - prints the current process environment
 *
 * Return: 0 on success
 */

int main(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
	return (0);
}

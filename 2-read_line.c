#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

/**
 * main - reads a line from standard input and prints it back (prompt loop)
 *
 * Return: 0 on success.
 */

int main(void)
{
	size_t len = 0;
	ssize_t read;
	char *lineptr = NULL;

	while (1)
	{
		printf("$ ");
		read = getline(&lineptr, &len, stdin);
		if (read == -1)
		{
			break;
		}
		printf("%s", lineptr);
	}
	printf("\n");
	free(lineptr);
	return (0);
}

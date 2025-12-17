#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

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
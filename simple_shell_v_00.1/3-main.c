#include <stdio.h>
#include <stdlib.h>

char **split_string(char *string);

int main(int argc, char **argv)
{
	char **tokens;
	int i;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s \"string\"\n", argv[0]);
		return (1);
	}

	tokens = split_string(argv[1]);
	if (tokens == NULL)
	{
		fprintf(stderr, "Error: split_string failed\n");
		return (1);
	}

	for (i = 0; tokens[i] != NULL; i++)
		printf("token[%d]: \"%s\"\n", i, tokens[i]);

	for (i = 0; tokens[i] != NULL; i++)
		free(tokens[i]);
	free(tokens);

	return (0);
}




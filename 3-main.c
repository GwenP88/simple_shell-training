#include "main.h"

/**
 * main - tests split_string by printing each token from a given input string
 * @argc: number of arguments passed to the program
 * @argv: array of strings containing the program arguments
 *
 * Return: 0 on success, 1 on error.
 */

int main(int argc, char **argv)
{
	/* Tableau de tokens retournés par split_string */
	char **tokens;
	int i;

	/* Vérifie qu'on a exactement 1 argument (la string à découper) */
	if (argc != 2)
	{
		/* Affiche l'usage sur stderr */
		fprintf(stderr, "Usage: %s \"string\"\n", argv[0]);
		return (1);
	}

	/* Découpe la string en tokens */
	tokens = split_string(argv[1]);

	/* Si split_string échoue */
	if (tokens == NULL)
	{
		/* Affiche l'erreur sur stderr */
		fprintf(stderr, "Error: split_string failed\n");
		return (1);
	}

	/* Affiche chaque token */
	for (i = 0; tokens[i] != NULL; i++)
		printf("token[%d]: \"%s\"\n", i, tokens[i]);

	/* Libère chaque token */
	for (i = 0; tokens[i] != NULL; i++)
		free(tokens[i]);

	/* Libère le tableau de pointeurs */
	free(tokens);

	return (0);
}

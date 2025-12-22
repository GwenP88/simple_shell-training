#include <stdio.h>

/**
 * main - prints all arguments passed to the program, one per line
 * @ac: number of arguments (unused)
 * @av: array of strings containing the arguments
 *
 * Return: 0 on success
 */

int main(int ac __attribute__((unused)), char **av)
{
	/* Parcourt av jusqu'au NULL final */
	while (*av != NULL)
	{
		/* Affiche l'argument courant */
		printf("%s\n", *av);
		/* Passe à l'argument suivant */
		av++;
	}
	return (0);
}

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

/**
 * main - reads a line from standard input 
 * and prints it back (prompt loop)
 *
 * Return: 0 on success.
 */

int main(void)
{
	/* Taille du buffer géré par getline */
	size_t len = 0;
	/* Nombre de caractères lus par getline (ou -1 si EOF/erreur) */
	ssize_t read;
	/* Pointeur vers la ligne lue (allouée/agrandie par getline) */
	char *lineptr = NULL;

	while (1)
	{
		/* Affiche le prompt */
		printf("$ ");
		/* Lit une ligne de stdin */
		read = getline(&lineptr, &len, stdin);

		/* Si EOF/erreur => stop */
		if (read == -1)
		{
			break;
		}
		/* Ré-affiche la ligne telle quelle */
		printf("%s", lineptr);
	}
	/* Ajoute un \n à la sortie proprement */
	printf("\n");
	/* Libère le buffer alloué par getline */
	free(lineptr);
	return (0);
}

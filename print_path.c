#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;
char *_getenv(const char *name);
void print_path_dirs(void);

/**
 * main - prints each directory from
 * the PATH environment variable
 *
 * Return: 0 on success
 */

int main(void)
{
	print_path_dirs();
	return (0);
}

/**
 * _getenv - that gets an environment variable.
 * @name: name of the environment variable to get
 *
 * Return: a pointer to the environment variable
 * or NULL if it doesn't exist
 */

char *_getenv(const char *name)
{
	size_t len, i;

	/* Vérifie que le nom est valide (non NULL, non vide et sans '=') */
	if (name == NULL || name[0] == '\0' || (strchr(name, '=')) != NULL)
		return (NULL);

	/* Stocke la longueur du nom pour la comparaison */
	len = strlen(name);

	/* Parcourt la liste des variables d'environnement */
	for (i = 0; environ[i] != NULL; i++)
	{
		/* Compare le nom et vérifie la présence du '=' juste après */
		if (strncmp(name, environ[i], len) == 0 && environ[i][len] == '=')
			/* Retourne un pointeur vers la valeur (après le '=') */
			return (&environ[i][len + 1]);
	}
	/* Variable d'environnement non trouvée */
	return (NULL);
}

/**
 * print_path_dirs - prints each directory
 * contained in PATH, one per line
 *
 * Return: Nothing
 */

void print_path_dirs(void)
{
	char *path_dir;
	const char *seg_start, *seg_current, *p;

	/* Récupère la variable d’environnement PATH */
	path_dir = _getenv("PATH");

	/* Si PATH n’existe pas ou est vide, il n’y a rien à afficher */
	if (path_dir == NULL || path_dir[0] == '\0')
		return;

	/* Initialise les pointeurs au début de la chaîne PATH */
	seg_start = path_dir;
	seg_current = path_dir;

	/* Parcourt la chaîne PATH jusqu’à la fin */
	while (1)
	{
		/* Si on rencontre ':' ou la fin '\0', on a trouvé un segment complet */
		if (*seg_current == ':' || *seg_current == '\0')
		{
			/* Si le segment est vide cela représente le répertoire courant */
			if (seg_current == seg_start)
			{
				/* Affiche '.' pour représenter le répertoire courant */
				write(1, ".", 1);

			} else
			{
				/* Affiche le segment caractère par caractère */
				for (p = seg_start; p < seg_current; p++)
					/* Écrit un caractère du répertoire */
					write(1, p, 1);
			}
			/* Retour à la ligne après chaque répertoire */
			write(1, "\n", 1);
			/* Place le début du prochain segment juste après ':' */
			seg_start = seg_current + 1;

			/* Si on est à la fin de la chaîne, on sort de la boucle */
			if (*seg_current == '\0')
				break;
		}
		/* Avance d’un caractère dans la chaîne PATH */
		seg_current++;
	}
}

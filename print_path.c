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

	path_dir = _getenv("PATH");

	if (path_dir == NULL || path_dir[0] == '\0')
		return;

	seg_start = path_dir;
	seg_current = path_dir;

	while (1)
	{
		if (*seg_current == ':' || *seg_current == '\0')
		{
			if (seg_current == seg_start)
			{
				write(1, ".", 1);

			} else
			{
				for (p = seg_start; p < seg_current; p++)
					write(1, p, 1);
			}
			write(1, "\n", 1);
			seg_start = seg_current + 1;
			if (*seg_current == '\0')
				break;
		}
		seg_current++;
	}
}

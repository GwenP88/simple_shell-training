#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;
int _unsetenv(const char *name);

/**
 * main - Test the custom _unsetenv function.
 *
 * Return: 0 on success, 1 on failure.
 */

int main(void)
{
	if (setenv("TEST_VAR", "hello", 1) != 0)
	{
		perror("setenv");
		return (1);
	}

	printf("Before _unsetenv:\n");
	printf("TEST_VAR = %s\n", getenv("TEST_VAR"));

	if (_unsetenv("TEST_VAR") == -1)
	{
		perror("_unsetenv");
		return (1);
	}

	printf("\nAfter _unsetenv:\n");
	printf("TEST_VAR = %s\n", getenv("TEST_VAR"));

	printf("\nError tests:\n");

	if (_unsetenv(NULL) == -1)
		perror("NULL name");

	if (_unsetenv("") == -1)
		perror("Empty name");

	if (_unsetenv("A=B") == -1)
		perror("Invalid name (contains '=')");

	return (0);
}

/**
 * _unsetenv - delete an environment variable.
 * @name: Name of the environment variable to delete.
 *
 * Return: 0 on success, -1 on failure.
 */

int _unsetenv(const char *name)
{
	size_t len_name, i, j;

	/* Vérifie que le nom est valide (non NULL, non vide, sans '=') */
	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
	{
		/* Définit errno pour signaler un argument invalide */
		errno = EINVAL;
		return (-1);
	}

	/* Si l'environnement est vide, rien à supprimer */
	if (environ == NULL)
		return (0);

	/* Calcule la longueur du nom de la variable */
	len_name = strlen(name);

	/* Initialisation de l'index de parcours */
	i = 0;

	/* Parcourt toutes les variables d'environnement */
	while (environ[i] != NULL)
	{
		/* Vérifie si la variable correspond exactement au nom recherché */
		if (strncmp(environ[i], name, len_name) == 0 && environ[i][len_name] == '=')
		{
			/* Initialise l'index pour le décalage */
			j = i;
			while (environ[j + 1] != NULL)
			{
				/* Décale toutes les variables suivantes vers la gauche */
				environ[j] = environ[j + 1];
				j++;
			}
			/* Place NULL à la fin pour conserver un tableau valide */
			environ[j] = NULL;
		} else
		{
			/* Passe à la variable suivante si pas de correspondance */
			i++;
		}
	}
	/* Retourne succès même si la variable n'existait pas */
	return (0);
}

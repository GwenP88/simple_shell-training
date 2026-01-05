#include "shell.h"

extern char **environ;
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

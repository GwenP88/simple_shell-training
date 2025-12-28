#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

extern char **environ;
char *build_env_string(const char *name, const char *value);
char **copy_environ(void);

/**
 * _setenv - Adds or updates an environment variable.
 * @name: Name of the environment variable to set
 * @value: Value to assign to the variable.
 * @overwrite: If 0, do not overwrite an existing variable
 *  otherwise overwrite it.
 *
 * Return: 0 on success, -1 on failure (errno is set accordingly).
 */

int _setenv(const char *name, const char *value, int overwrite)
{
	size_t len_name, i, j;
	char **buff, **old_env;
	char *buffer, **tmp;
	static int env_copied;

	/* Vérifie les paramètres et refuse un nom invalide */
	if (name == NULL || name[0] == '\0' || value == NULL
					 || strchr(name, '=') != NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	/* Copie environ une seule fois pour pouvoir le modifier en sécurité */
	if (env_copied == 0)
	{
		/* Duplique le tableau d’environnement actuel */
		tmp = copy_environ();
		if (tmp == NULL)
		{
			return (-1);
		}
		/* Bascule environ vers la copie modifiable */
		environ = tmp;
		/* Marque la copie comme déjà effectuée */
		env_copied = 1;
	}

	/* Calcule la taille de name pour comparaison*/
	len_name = strlen(name);

	/* Parcourt l’environnement + si variable existe */
	for (i = 0; environ[i] != NULL; i++)
	{
		/* Vérifie si l’entrée correspond exactement à "name=" */
		if (strncmp(name, environ[i], len_name) == 0 && environ[i][len_name] == '=')
		{
			/* si overwrite vaut 0 alors ne rien faire */
			if (overwrite == 0)
				return (0);

			/* si overwrite = 1; remplacer */
			/* Construit la nouvelle chaîne "name=value" */
			buffer = build_env_string(name, value);
			if (!buffer)
				return (-1);
			/* Libère l’ancienne entrée */
			free(environ[i]);
			/* Remplace l'ancienne par la nouvelle */
			environ[i] = buffer;
			return (0);
		}
	}

	/* si variable n'existe pas */
	/* Construit la chaîne à ajouter si la variable n’existe pas */
	buffer = build_env_string(name, value);
	if (!buffer)
		return (-1);

	/* Alloue un nouveau tableau */
	buff = malloc((i + 2) * sizeof(char *));
	if (buff == NULL)
	{
		/* Libère la chaîne construite pour éviter une fuite */
		free(buffer);
		errno = ENOMEM;
		return (-1);
	}

	/* Copie les pointeurs existants dans le nouveau tableau */
	j = 0;
	while (environ[j] != NULL)
	{
		buff[j] = environ[j];
		j++;
	}

	/* Ajoute la nouvelle variable à la fin */
	buff[i] = buffer;
	/* Termine le tableau par NULL */
	buff[i + 1] = NULL;

	/* Garde l’ancien tableau pour le libérer ensuite */
	old_env = environ;
	/* Met environ à jour avec le nouveau tableau */
	environ = buff;
	/* Libère uniquement le tableau de pointeurs (pas les strings) */
	free(old_env);
	return (0);
}

/**
 * build_env_string - Builds a string for the environment.
 * @name: Name of the environment variable.
 * @value: Value of the environment variable.
 *
 * Return: Pointer to a newly allocated string on success,
 * or NULL on failure.
 */

char *build_env_string(const char *name, const char *value)
{
	size_t len_name, len_value;
	char *buffer;
	int size;

	/* Calcule les tailles des deux chaînes */
	len_name = strlen(name);
	len_value = strlen(value);

	/* Alloue "name" + "=" + "value" + '\0' */
	buffer = malloc(len_name + len_value + 2);
	if (buffer == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}

	/* Construit la chaîne finale "name=value" */
	size = sprintf(buffer, "%s=%s", name, value);
	if (size < 0)
	{
		/* Libère le buffer si sprintf échoue */
		free(buffer);
		errno = ENOMEM;
		return (NULL);
	}
	return (buffer);
}

/**
 * copy_environ - Creates a deep copy of
 * the current environment array.
 *
 * Return: Pointer to a newly allocated array on success,
 * or NULL on failure.
 */

char **copy_environ(void)
{
	size_t i, j, k;
	char **new_environ;

	/* Compte le nombre d’entrées dans environ */
	i = 0;
	while (environ[i] != NULL)
		i++;

	/* Alloue le tableau de pointeurs (+1 pour le NULL final) */
	new_environ = malloc((i + 1) * sizeof(char *));
	if (new_environ == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}

	/* Duplique chaque chaîne "NAME=VALUE" */
	for (j = 0; environ[j] != NULL; j++)
	{
		/* Alloue la place pour copier la chaîne */
		new_environ[j] = malloc(strlen(environ[j]) + 1);
		if (new_environ[j] == NULL)
		{
			/* Libère ce qui a déjà été alloué en cas d’échec */
			for (k = 0; k < j; k++)
			{
				free(new_environ[k]);
			}
			/* Libère le tableau de pointeurs */
			free(new_environ);
			errno = ENOMEM;
			return (NULL);
		}
		/* Copie le contenu de la variable d’environnement */
		strcpy(new_environ[j], environ[j]);
	}
	/* Termine le nouveau tableau par NULL */
	new_environ[i] = NULL;
	return (new_environ);
}

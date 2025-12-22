#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char *find_in_path(const char *cmd, char *path_env);

/**
 * main - entry point for a simple _which clone
 * @ac: number of arguments passed to the program
 * @av: array of strings containing the arguments
 *
 * Return: 0 if all commands are found, 1 if at least one command is not found,
 *	or 1 if the usage is incorrect (no command provided).
 */

int main(int ac, char **av)
{
	int i, status;
	char *path_env, *found_path;

	/* Si aucun nom de commande fourni => affiche l'usage */
	if (ac < 2)
	{
		printf("Usage: ./_which filename ...\n");
		return (1);
	}

	/* Récupère la variable d'environnement PATH */
	path_env = getenv("PATH");
	/* Démarre au premier argument utilisateur */
	i = 1;
	/* Status à 0 (succès), passera à 1 si au moins une commande échoue */
	status = 0;
	while (av[i])
	{
		/* Si l'argument ne contient pas '/', on cherche dans PATH */
		if (strchr(av[i], '/') == NULL)
		{
			/* Recherche dans PATH et récupère un chemin alloué (ou NULL) */
			found_path = find_in_path(av[i], path_env);
			if (found_path != NULL)
			{
				/* Si trouvé => affiche le chemin */
				printf("%s\n", found_path);
				/* Libère la chaîne allouée */
				free(found_path);
			}
			else
			{
				/* Affiche un message d'erreur friendly */
				printf("%s: command not found\n", av[i]);
				/* Marque l'échec mais continue pour les autres arguments */
				status = 1;
			}
		}
		/* Si l'argument contient '/', on teste directement ce chemin */
		else
		{
			/* Si le fichier est exécutable => on affiche l'argument tel quel */
			if (access(av[i], X_OK) == 0)
				printf("%s\n", av[i]);
			/* Sinon => pas exécutable ou inexistant */
			else
			{
				/* Affiche un message d'erreur */
				printf("%s: command not found\n", av[i]);
				/* Marque l'échec mais continue */
				status = 1;
			}
		}
		/* Passe à l'argument suivant */
		i++;
	}
	/* Retourne 0 si tout trouvé, sinon 1 */
	return (status);
}

/**
 * find_in_path - searches for a command in PATH directories
 * @cmd: command name to search for (without path)
 * @path_env: PATH environment variable content (colon-separated directories)
 *
 * Return: a newly allocated string containing
 *	the full executable path if found,
 *	or NULL if not found or on allocation error.
 */

char *find_in_path(const char *cmd, char *path_env)
{
	const char *seg_start, *seg_current;
	char *candidate_path;
	size_t seg_len, cmd_len, i, j;

	/* Vérifie que cmd est valide */
	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);
	
	/* Vérifie que PATH est valide */
	if (path_env == NULL || path_env[0] == '\0')
		return (NULL);

	/* Début du premier segment de PATH */
	seg_start = path_env;
	/* Curseur de scan */
	seg_current = path_env;
	/* Longueur de la commande */
	cmd_len = strlen(cmd);

	/* Boucle sur tous les segments */
	while (1)
	{
		/* Avance jusqu'au ':' ou fin de chaîne */
		while (*seg_current != ':' && *seg_current != '\0')
		{
			seg_current++;
		}
		/* Calcule la longueur du segment courant */
		seg_len = seg_current - seg_start;
		/* Segment vide => signifie répertoire courant (.) dans PATH */
		if (seg_len == 0)
		{
			/* Alloue "./" + cmd + '\0' */
			candidate_path = malloc(cmd_len + 3);
			/* Si malloc échoue => NULL */
			if (candidate_path == NULL)
				return (NULL);
			
			/* Construit "./" */
			candidate_path[0] = '.';
			candidate_path[1] = '/';
			
			/* Copie cmd après "./" */
			strcpy(candidate_path + 2, cmd);

			/* Vérifie si exécutable */
			if (access(candidate_path, X_OK) == 0)
				return (candidate_path);
			
			/* Sinon libère et continue */
			free(candidate_path);
		}
		/* Segment non vide => construit "segment/cmd" */
		else if (seg_len > 0)
		{
			/* Alloue "segment" + "/" + "cmd" + '\0' */
			candidate_path = malloc(cmd_len + seg_len + 2);
			/* Si malloc échoue => NULL */
			if (candidate_path == NULL)
				return (NULL);

			/* Copie le segment (répertoire) dans candidate_path */
			for (i = 0; i < seg_len; i++)
			{
				candidate_path[i] = seg_start[i];
			}
			/* Ajoute le '/' */
			candidate_path[seg_len] = '/';

			/* Copie cmd après le '/' */
			for (j = 0; j < cmd_len; j++)
			{
				candidate_path[seg_len + 1 + j] = cmd[j];
			}
			/* Termine la chaîne */
			candidate_path[seg_len + cmd_len + 1] = '\0';

			/* Vérifie si exécutable */
			if (access(candidate_path, X_OK) == 0)
				return (candidate_path);
			/* Sinon libère et continue */
			free(candidate_path);
		}
		/* Si on est sur ':' => passe au segment suivant */
		if (*seg_current == ':')
		{
			/* Saute le ':' */
			seg_current++;
			/* Nouveau départ de segment */
			seg_start = seg_current;
		
		/* Si fin de chaîne => on arrête la recherche */
		} else if (*seg_current == '\0')
			break;
	}
	/* Aucun exécutable trouvé */
	return (NULL);
}

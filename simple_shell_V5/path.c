#include "shell.h"

/**
 * get_path - Get PATH from environment
 *
 * Return: PATH string or NULL
 */
char *get_path(void)
{
	/* Récupère la variable d'environnement PATH */
	return (_getenv("PATH"));
}


/**
 * find_command - Recherche une commande dans le PATH
 * @command: nom de la commande à chercher (ex: "ls")
 *
 * Return: chemin complet si trouvé, sinon NULL
 */
char *find_command(char *command)
{
	/* Pointeurs pour manipuler PATH et parcourir ses dossiers */
	char *path, *path_copy, *dir;

	/* Buffer statique pour construire le chemin complet de la commande */
	static char full_path[MAX_PATH];

	size_t len_dir = 0;
	size_t len_command = 0;

	/* Si la commande ressemble déjà à un chemin (absolu ou relatif), on la teste directement */
	if (command[0] == '/' || command[0] == '.')
	{
		/* Vérifie que le fichier est exécutable */
		if (access(command, X_OK) == 0)
			/* Retourne le chemin tel quel s'il est valide */
			return (command);
		/* Retourne NULL si la commande n'est pas exécutable/introuvable */
		return (NULL);
	}

	/* Récupère la variable PATH depuis l'environnement */
	path = get_path();
	/* Si PATH n'existe pas, on ne peut pas rechercher la commande */
	if (path == NULL)
		return (NULL);

	/* Duplique PATH pour pouvoir le découper sans modifier l'original */
	path_copy = strdup(path);
	/* Arrête si l'allocation échoue */
	if (path_copy == NULL)
		return (NULL);

	/* Découpe PATH en dossiers, séparés par ':' */
	dir = strtok(path_copy, ":");
	/* Parcourt chaque dossier pour construire un chemin possible */
	while (dir != NULL)
	{
		/* Construit "dossier/commande" dans full_path */
		len_dir = strlen(dir);
		len_command = strlen(command);
		if ((len_dir + len_command + 2) >= MAX_PATH)
			continue;

		strcpy(full_path, dir);
		
		if (dir[len_dir - 1] != '/')
			strcat(full_path, "/");

		strcat(full_path, command);

		/* Vérifie si ce chemin pointe vers un exécutable */
		if (access(full_path, X_OK) == 0)
		{
			/* Libère la copie de PATH avant de retourner */
			free(path_copy);
			/* Retourne le chemin complet trouvé */
			return (full_path);
		}

		/* Passe au dossier suivant dans PATH */
		dir = strtok(NULL, ":");
	}

	/* Libère la copie de PATH si rien n'a été trouvé */
	free(path_copy);
	/* Retourne NULL si aucun exécutable n'a été trouvé */
	return (NULL);
}

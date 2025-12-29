#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * struct path_node - singly linked list node for PATH directories
 * @dir: directory path stored in the node (dynamically allocated string)
 * @next: pointer to the next node in the list
 */

typedef struct path_node
{
	char *dir;
	struct path_node *next;
} path_node_t;

extern char **environ;
char *_getenv(const char *name);
path_node_t *build_path_list(void);
void free_path_list(path_node_t *head);

/**
 * main - prints each directory from
 * the PATH environment variable
 *
 * Return: 0 on success
 */

int main(void)
{
	path_node_t *head, *tmp;

	head = build_path_list();
	tmp = head;
	if (head == NULL)
		return (0);
	while (tmp != NULL)
	{
		write(1, tmp->dir, strlen(tmp->dir));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	free_path_list(head);
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
 * build_path_list - builds a linked list of directories from the PATH variable
 *
 * Return: pointer to the head of the list, or NULL on failure
 */

path_node_t *build_path_list(void)
{
	path_node_t *head, *tail, *new_node;
	char *path, *dir;
	const char *seg_start, *seg_current;
	size_t len;

	/* Récupère la variable d’environnement PATH */
	path = _getenv("PATH");

	/* Si PATH est inexistante ou vide, retourne NULL */
	if (path == NULL || path[0] == '\0')
		return (NULL);

	/* Initialise les pointeurs de parcours */
	seg_start = path;
	seg_current = path;
	head = NULL;
	tail = NULL;

	/* Parcourt toute la chaîne PATH */
	while (1)
	{
		/* Détecte la fin d’un segment (':' ou fin de chaîne) */
		if (*seg_current == ':' || *seg_current == '\0')
		{
			/* Cas d’un segment vide : correspond au répertoire courant */
			if (seg_current == seg_start)
			{
				/* Alloue la mémoire pour "." */
				dir = malloc(sizeof(char) * 2);
				if (dir == NULL)
				{
					/* Libère la liste déjà créée en cas d’erreur */
					free_path_list(head);
					return (NULL);
				}
				dir[0] = '.';
				dir[1] = '\0';

				/* Crée un nouveau noeud */
				new_node = malloc(sizeof(path_node_t));
				if (new_node == NULL)
				{
					free(dir);
					free_path_list(head);
					return (NULL);
				}
				/* Initialise le noeud */
				new_node->dir = dir;
				new_node->next = NULL;
			
				/* Ajoute le noeud à la liste */
				if (head == NULL)
					head = tail = new_node;
				else
				{
					tail->next = new_node;
					tail = new_node;
				}
			} else
			{
				/* Calcule la longueur du segment */
				len = seg_current - seg_start;

				/* Alloue la mémoire pour le répertoire */
				dir = malloc(len + 1);
				if (dir == NULL)
				{
					free_path_list(head);
					return (NULL);
				}

				/* Copie le segment dans la nouvelle chaîne */
				memcpy(dir, seg_start, len);
				dir[len] = '\0';

				/* Crée un nouveau noeud */
				new_node = malloc(sizeof(path_node_t));
				if (new_node == NULL)
				{
					free(dir);
					free_path_list(head);
					return (NULL);
				}
				
				/* Initialise le noeud */
				new_node->dir = dir;
				new_node->next = NULL;

				/* Ajoute le noeud à la liste */
				if (head == NULL)
					head = tail = new_node;
				else
				{
					tail->next = new_node;
					tail = new_node;
				}
			}
			/* Avance au début du segment suivant */
			seg_start = seg_current + 1;
			/* Si fin de chaîne atteinte, on sort de la boucle */
			if (*seg_current == '\0')
				break;
		}
		/* Avance caractère par caractère dans PATH */
		seg_current++;
	}
	/* Retourne la tête de la liste chaînée */
	return (head);
}

/**
 * free_path_list - frees a linked list of PATH directories
 * @head: pointer to the head of the list
 *
 * Return: Nothing
 */

void free_path_list(path_node_t *head)
{
	path_node_t *next;

	/* Si la liste est vide, il n’y a rien à libérer */
	if (head == NULL)
		return;

	/* Parcourt toute la liste chaînée */
	while (head)
	{
		/* Sauvegarde l’adresse du noeud suivant */
		next = head->next;
		/* Libère la chaîne contenant le répertoire */
		free(head->dir);
		/* Libère le noeud courant */
		free(head);
		/* Passe au noeud suivant */
		head = next;
	}
}

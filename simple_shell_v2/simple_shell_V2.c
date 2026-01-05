#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64

/**
 * main - Simple shell with arguments support
 *
 * Return: Always 0
 */
int main(void)
{
	/* Pointeur vers la ligne lue par getline (allouée automatiquement) */
	char *line = NULL;
	/* Taille du buffer géré par getline */
	size_t len = 0;
	/* Nombre de caractères lus (ou -1 si EOF/erreur) */
	ssize_t nread;
	/* PID retourné par fork pour distinguer parent/enfant */
	pid_t pid;
	/* Statut de fin du processus enfant */
	int status;
	/* Tableau d'arguments pour execve (commande + args + NULL) */
	char *argv[MAX_ARGS];
	/* Pointeur sur chaque morceau (token) extrait de la ligne */
	char *token;
	/* Index pour remplir argv */
	int i;
	/* Environnement à transmettre à execve */
	extern char **environ;

	/* Boucle infinie : le shell attend des commandes en continu */
	while (1)
	{
		/* Affiche le prompt seulement en mode interactif (terminal) */
		if (isatty(STDIN_FILENO))
			/* Écrit le prompt sur la sortie standard */
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		/* Lit une ligne complète depuis l'entrée standard */
		nread = getline(&line, &len, stdin);

		/* Si EOF ou erreur de lecture, on sort proprement */
		if (nread == -1)
		{
			/* En interactif, affiche un saut de ligne après Ctrl+D */
			if (isatty(STDIN_FILENO))
				/* Écrit un retour à la ligne */
				write(STDOUT_FILENO, "\n", 1);
			/* Quitte la boucle principale */
			break;
		}

		/* Remplace le '\n' final par '\0' pour nettoyer la commande */
		if (line[nread - 1] == '\n')
			/* Termine la chaîne à la place du saut de ligne */
			line[nread - 1] = '\0';

		/* Ignore les lignes vides (juste Entrée) */
		if (strlen(line) == 0)
			/* Recommence la boucle sans traitement */
			continue;

		/* Initialise l'index du tableau d'arguments */
		i = 0;
		/* Découpe la ligne en mots séparés par espace ou tabulation */
		token = strtok(line, " \t");
		/* Remplit argv tant qu'il reste des tokens et de la place */
		while (token != NULL && i < MAX_ARGS - 1)
		{
			/* Stocke l'argument courant dans argv */
			argv[i] = token;
			/* Passe à l'index suivant */
			i++;
			/* Récupère le token suivant */
			token = strtok(NULL, " \t");
		}
		/* Termine le tableau argv par NULL (format attendu par execve) */
		argv[i] = NULL;

		/* Crée un processus enfant pour exécuter la commande */
		pid = fork();

		/* Si fork échoue, affiche l'erreur et continue */
		if (pid == -1)
		{
			/* Affiche l'erreur associée au dernier errno */
			perror("./shell");
			/* Retourne au début de la boucle */
			continue;
		}

		/* Si pid == 0, on est dans le processus enfant */
		if (pid == 0)
		{
			/* Lance la commande avec ses arguments en remplaçant le processus */
			if (execve(argv[0], argv, environ) == -1)
			{
				/* Affiche un message si la commande n'existe pas */
				fprintf(stderr, "./shell: No such file or directory\n");
				/* Quitte avec le code standard "commande introuvable" */
				exit(127);
			}
		}
		else
		{
			/* Dans le parent : attend la fin du processus enfant */
			wait(&status);
		}
	}

	/* Libère la mémoire allouée par getline */
	free(line);
	/* Fin normale du programme */
	return (0);
}

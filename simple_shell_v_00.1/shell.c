#include "shell.h"

/**
 * main - simple shell loop that executes commands given by path (no arguments)
 *
 * Return: 0 on success.
 */

int main(void)
{
	/* Taille du buffer utilisée par getline */
	size_t len = 0;
	/* Nombre de caractères lus par getline */
	ssize_t read;
	/* Pointeur vers la ligne lue depuis l'entrée standard */
	char *lineptr = NULL;
	/* Tableau d'arguments pour execve (commande + NULL) */
	char *argv_exec[2];
	/* Statut de terminaison du processus fils */
	int status;
	/* PID du processus créé par fork */
	pid_t pid;

	/* Termine toujours argv_exec par NULL */
	argv_exec[1] = NULL;

	while (1)
	{
		/* Affiche le prompt du shell avant la suite du programme */
		printf("#cisfun$ ");
		fflush(stdout);
		/* Lit la ligne saisie par l'utilisateur */
		read = getline(&lineptr, &len, stdin);
		/* Gère la fin de fichier (Ctrl+D) */
		if (read == -1)
		{
			printf("\n");
			break;
		}
		/* Supprime le saut de ligne final */
		if (read > 0 && lineptr[read - 1] == '\n')
			lineptr[read - 1] = '\0';

		/* Ignore les lignes vides */
		if (lineptr[0] == '\0')
			continue;

		/* Prépare argv pour execve */
		argv_exec[0] = lineptr;

		/* Crée un nouveau processus */
		pid = fork();

		/* Vérifie l'erreur de fork */
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		/* Code exécuté dans le processus fils */
		if (pid == 0)
		{
			/* Remplace le processus par la commande demandée */
			execve(lineptr, argv_exec, environ);
			/* Affiche une erreur si execve échoue */
			perror(lineptr);
			exit(127);
		}
		/* Code exécuté dans le processus père */
		if (pid > 0)
		{
			/* Attend la fin du processus fils */
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
			/* Quitte si le fils ne s'est pas terminé normalement */
			if (!WIFEXITED(status))
				exit(EXIT_FAILURE);
			/* Continue le shell même si la commande a échoué */
			if (WEXITSTATUS(status) != 0)
				continue;
		}
	}
	/* Libère la mémoire allouée par getline */
	free(lineptr);
	/* Fin normale du programme */
	return (0);
}

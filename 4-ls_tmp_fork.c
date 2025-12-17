#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

extern char **environ;

/**
 * main - creates 5 child processes to execute "ls -l /tmp"
 * Return: 0 on success, exits with a non-zero value on error
 */

/* environnement du process courant */

int main(void)
{
	/* chemin absolu du binaire à exécuter */
	const char *path = "/usr/bin/ls";
	char *argv_exec [4] = {"ls", "-l", "/tmp", NULL};
	int i, status;
	pid_t pid;

	/* boucler 5 fois*/
	for (i = 0; i < 5; i++)
	{
		/* duplication du process courant */
		pid = fork();

		/* fork échoue : erreur système, on stoppe tout */
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		/* fork ok et dans processus fils*/
		if (pid == 0)
		{
			/* remplacement du code du fils par ls -l /tmp */
			execve(path, argv_exec, environ);
			/* si on arrive ici c'est forcément qu'il y a erreur*/
			perror(path);
			exit(127);
		}
		/* fork ok et dans processus père*/
		if (pid > 0)
		{
			/* attente du fils courant avant d’en créer un autre */
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
			/* si le fils ne s’est pas terminé normalement */
			if (!WIFEXITED(status))
				exit(EXIT_FAILURE);
			/* si le fils a quitté avec un code d’erreur */
			if (WEXITSTATUS(status) != 0)
				exit(EXIT_FAILURE);
		}
	}
	return (0);
}

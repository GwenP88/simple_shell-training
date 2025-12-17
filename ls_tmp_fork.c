#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

extern char **environ;

int main(void)
{
	const char *path = "/usr/bin/ls";
	char *argv_exec [4] = {"ls", "-l", "/tmp", NULL};
	int i, status;
	pid_t pid;

	/* boucler 5 fois*/
	for (i = 0; i < 5; i++)
	{
		/* fork*/
		pid = fork();
		/* test fork : -1 = echec du fork */
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		 /* fork ok et dans processus fils*/
		if (pid == 0)
		{
			execve(path, argv_exec, environ);
			/* si on arrive ici c'est forcément qu'il y a erreur*/
			perror(path);
    		exit(127);
		}
		/* fork ok et dans processus père*/
		if (pid > 0)
		{
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("waitpid");
            	exit(EXIT_FAILURE);	
			}
			if (!WIFEXITED(status))
				exit(EXIT_FAILURE);
			
			if (WEXITSTATUS(status) != 0)
				exit(EXIT_FAILURE);
		}
	}
	return (0);
}
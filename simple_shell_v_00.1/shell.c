#include "shell.h"

int main (void)
{
	size_t len = 0;
	ssize_t read;
	char *lineptr = NULL;
	char *argv_exec [2];
	int status;
	pid_t pid;

	argv_exec [1] = NULL;

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);
		read = getline(&lineptr, &len, stdin);
		if (read == -1)
		{
			printf("\n");
			break;
		}
		if (read > 0 && lineptr[read -1] == '\n')
			lineptr[read -1] ='\0';
		
		if (lineptr[0] == '\0')
			continue;

		argv_exec [0] = lineptr;
		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		
		if (pid == 0)
		{
			execve(lineptr, argv_exec, environ);
			perror(lineptr);
			exit(127);
		}
		
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
				continue;
		}	
	}
	free(lineptr);
	return (0);
}
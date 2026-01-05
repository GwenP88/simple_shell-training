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
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;
	char *argv[MAX_ARGS];
	char *token;
	int i;
	extern char **environ;

	while (1)
	{
		/* Display prompt */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		/* Read command */
		nread = getline(&line, &len, stdin);

		/* Handle EOF */
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Remove newline */
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* Skip empty lines */
		if (strlen(line) == 0)
			continue;

		/* Tokenize the line (split by spaces) */
		i = 0;
		token = strtok(line, " \t");  /* Split by space and tab */
		while (token != NULL && i < MAX_ARGS - 1)
		{
			argv[i] = token;
			i++;
			token = strtok(NULL, " \t");
		}
		argv[i] = NULL;  /* NULL-terminate the array */

		/* Fork and execute */
		pid = fork();

		if (pid == -1)
		{
			perror("./shell");
			continue;
		}

		if (pid == 0)
		{
			/* Child process */
			if (execve(argv[0], argv, environ) == -1)
			{
				fprintf(stderr, "./shell: No such file or directory\n");
				exit(127);
			}
		}
		else
		{
			/* Parent process */
			wait(&status);
		}
	}

	free(line);
	return (0);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * main - Entry point for simple shell
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
	char *argv[2];
	extern char **environ;

	while (1)
	{
		/* Display prompt */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		/* Read command from user */
		nread = getline(&line, &len, stdin);

		/* Handle EOF (Ctrl+D) */
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Remove newline character */
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* Skip empty lines */
		if (strlen(line) == 0)
			continue;

		/* Fork process to execute command */
		pid = fork();

		if (pid == -1)
		{
			perror("./shell");
			continue;
		}

		if (pid == 0)
		{
			/* Child process */
			argv[0] = line;
			argv[1] = NULL;

			/* Execute command */
			if (execve(line, argv, environ) == -1)
			{
				fprintf(stderr, "./shell: No such file or directory\n");
				exit(127);
			}
		}
		else
		{
			/* Parent process - wait for child */
			wait(&status);
		}
	}

	/* Free allocated memory */
	free(line);

	return (0);
}
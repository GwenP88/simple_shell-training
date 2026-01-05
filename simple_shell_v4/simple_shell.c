#include "shell.h"

/**
 * main - Simple shell with PATH support
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
	char *command_path;
	int i;
	extern char **environ;

	while (1)
	{
		/* Display prompt */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

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

		/* Parse command line */
		i = 0;
		token = strtok(line, " \t");
		while (token != NULL && i < MAX_ARGS - 1)
		{
			argv[i] = token;
			i++;
			token = strtok(NULL, " \t");
		}
		argv[i] = NULL;

		
		if (strcmp(argv[0], "exit") == 0)
		{
			break;
		}
		/* Find command in PATH */
		command_path = find_command(argv[0]);

		if (command_path == NULL)
		{
			/* Command not found - don't fork */
			fprintf(stderr, "./shell: No such file or directory\n");
			continue;
		}

		/* Fork only if command exists */
		pid = fork();

		if (pid == -1)
		{
			perror("./shell");
			continue;
		}

		if (pid == 0)
		{
			/* Child process */
			if (execve(command_path, argv, environ) == -1)
			{
				perror("./shell");
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

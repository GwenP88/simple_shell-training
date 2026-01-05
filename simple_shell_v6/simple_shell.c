#include "shell.h"

extern char **environ;

/**
 * main - Simple shell with PATH support and built-ins
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

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (strlen(line) == 0)
			continue;

		i = 0;
		token = strtok(line, " \t");
		while (token != NULL && i < MAX_ARGS - 1)
		{
			argv[i] = token;
			i++;
			token = strtok(NULL, " \t");
		}
		argv[i] = NULL;

		/* Vérifier si c'est un built-in */
		if (is_builtin(argv[0]))
		{
			execute_builtin(argv[0]);
			continue;
		}

		command_path = find_command(argv[0]);
		if (command_path == NULL)
		{
			fprintf(stderr, "./shell: No such file or directory\n");
			continue;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("./shell");
			continue;
		}
		if (pid == 0)
		{
			if (execve(command_path, argv, environ) == -1)
			{
				perror("./shell");
				exit(127);
			}
		}
		else
		{
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("./shell");
				continue;
			}
		
		}
	}
	free(line);
	return (0);
}
#include "shell.h"

/**
 * spawn_and_wait - Fork a child process, execute command, and wait for it.
 * @command_path: Full path of the executable to run.
 * @argv: NULL-terminated array of arguments passed to execve.
 * @prog_name: Program name used for error messages.
 *
 * Return: Child exit status on success, or 1 on system error.
 */


static int spawn_and_wait(char *command_path, char *argv[], char *prog_name)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror(prog_name);
		return (1);
	}
	if (pid == 0)
	{
		if (execve(command_path, argv, environ) == -1)
		{
			perror(prog_name);
			exit(126);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror(prog_name);
			return (1);
		}
		if (!WIFEXITED(status))
			return (1);
		return (WEXITSTATUS(status));
	}
	return (0);
}

/**
 * run_command - Execute a command with built-in and PATH handling.
 * @argv: NULL-terminated array of arguments.
 * @prog_name: Program name used for error messages.
 * @line_count: Current input line number.
 *
 * Return: 0 on success, 1 on system error, 127 if command is not found,
 * or EXIT_SHELL if the exit built-in is invoked.
 */


static int run_command
(char *argv[], char *prog_name, unsigned long int line_count)
{
	char *command_path;
	int ret;

	if (argv[0] == NULL)
		return (0);
	if (is_builtin(argv[0]))
	{
		ret = execute_builtin(argv[0]);
		return (ret);
	}
	command_path = find_command(argv[0]);
	if (command_path == NULL)
	{
		fprintf(stderr, "%s: %lu: %s: not found\n", prog_name, line_count, argv[0]);
		return (127);
	}
	return (spawn_and_wait(command_path, argv, prog_name));
}

/**
 * main - Simple shell with PATH support and built-ins.
 * @ac: Number of arguments (unused).
 * @av: Array of arguments.
 *
 * Return: The exit status of the last executed command.
 */


int main(int ac __attribute__((unused)), char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *argv[MAX_ARGS];
	int argc, status;
	int last_status = 0;
	unsigned long int line_count = 0;

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
		line_count++;

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (strlen(line) == 0)
			continue;

		argc = parse_line(line, argv, MAX_ARGS);
		if (argc == 0)
			continue;

		status = run_command(argv, av[0], line_count);
		if (status == EXIT_SHELL)
			break;
		last_status = status;
	}
	free(line);
	return (last_status);
}

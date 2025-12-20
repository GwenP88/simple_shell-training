#include "shell.h"

/**
 * main - simple shell loop that executes commands given by path (no arguments)
 *
 * Return: 0 on success.
 */

int main(void)
{

	while (1)
	{
		display_prompt();
		read = read_command(&lineptr, &len);
		if(read == -1 )
		{
			write(1, "\n", 1);
			break;
		}
		delete_newline(lineptr, read);
		if(is_empty_line(lineptr) == 1)
			continue;
		execute_command(lineptr);
	}
	free(lineptr);
	return (0);
}

void display_prompt(void)
{
	write(1, "#cisfun$ ", 9);
}

ssize_t read_command(char **lineptr, size_t *len)
{
	ssize_t read;

	read = getline(lineptr, len, stdin);
	return (read);
}

void delete_newline(char *lineptr, ssize_t read)
{
	if(lineptr == NULL)
		return;
	if(read > 0 && lineptr[read - 1] == '\n')
		lineptr[read - 1] = '\0';
}

int is_empty_line(const char *lineptr)
{
	if(lineptr == NULL)
		return (1);
	else if(lineptr[0] == '\0')
		return (1);
	else
		return (0);
}

int execute_command(char *cmd)
{
	char *argv_exec[2];
	int status;
	pid_t pid;

	argv_exec[1] = NULL;
	argv_exec[0] = cmd;
	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		execve(cmd, argv_exec, environ);
		perror(cmd);
		exit(127);
	}
	if (pid > 0)
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			return (1);
		}
		if (!WIFEXITED(status))
			return (1);
		if (WEXITSTATUS(status) != 0)
			return (1);
	}
	return (0);
}
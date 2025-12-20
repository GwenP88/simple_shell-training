#include "shell.h"

/**
 * main - runs a simple interactive loop
 * that reads a command line and executes
 * it as a path-only command (no arguments)
 *
 * Return: 0 on success.
 */

int main(void)
{
	size_t len = 0;
	ssize_t read;
	char *lineptr = NULL;

	while (1)
	{
		write(1, "#cisfun$ ", 9);
		read = read_command(&lineptr, &len);
		if (read == -1)
		{
			write(1, "\n", 1);
			break;
		}
		delete_newline(lineptr, read);
		if (is_empty_line(lineptr))
			continue;
		execute_command(lineptr);
	}
	free(lineptr);
	return (0);
}

/**
 * read_command - reads a command line
 * from standard input using getline
 * @lineptr: address of the buffer pointer
 * where the line will be stored/updated
 * @len: address of the buffer size used by getline
 *
 * Return: number of characters read, or -1 on EOF/error.
 */


ssize_t read_command(char **lineptr, size_t *len)
{
	ssize_t read;

	read = getline(lineptr, len, stdin);
	return (read);
}

/**
 * delete_newline - removes the trailing newline character
 * from an input line
 * @lineptr: input string to sanitize
 * @read: number of characters read (returned by getline)
 *
 * Return: nothing.
 */

void delete_newline(char *lineptr, ssize_t read)
{
	if (lineptr == NULL)
		return;
	if (read > 0 && lineptr[read - 1] == '\n')
		lineptr[read - 1] = '\0';
}

/**
 * is_empty_line - checks whether a given line is empty
 * @lineptr: string to check
 *
 * Return: 1 if the line is NULL or empty, otherwise 0.
 */

int is_empty_line(const char *lineptr)
{
	if (lineptr == NULL)
		return (1);
	else if (lineptr[0] == '\0')
		return (1);
	else
		return (0);
}

/**
 * execute_command - creates a child process
 * and executes a command using execve
 * @cmd: command path to execute (no arguments)
 *
 * Return: 0 if the command exits successfully, otherwise 1.
 */


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

#include <stdio.h>

/**
 * main - prints all arguments passed to the program, one per line
 * @ac: number of arguments (unused)
 * @av: array of strings containing the arguments
 *
 * Return: 0 on success
 */

int main(int ac __attribute__((unused)), char **av)
{
	while (*av != NULL)
	{
		printf("%s\n", *av);
		av++;
	}
	return (0);
}

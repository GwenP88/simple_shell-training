#include <stdio.h>

int main(int ac __attribute__((unused)), char **av)
{
	while (*av != NULL)
	{
		printf("%s\n", *av);
		av++;
	}
	return (0);
}

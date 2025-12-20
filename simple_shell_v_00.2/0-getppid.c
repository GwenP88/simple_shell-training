#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * main - prints the parent PID of the current process
 *
 * Return: 0 on success.
 */

int main(void)
{
	/* Variable pour stocker le PID du processus parent */
	pid_t parent_pid;

	/* Récupère le PID du processus parent */
	parent_pid = getppid();
	/* Affiche le PID du processus parent */
	printf("%d\n", parent_pid);
	/* Fin normale du programme */
	return (0);
}

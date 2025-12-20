#include <stdio.h>
#include <unistd.h>

/**
 * main - prints the PID of the current process
 *
 * Return: Always 0.
 */

int main(void)
{
	/* Variable pour stocker le PID du processus courant */
    pid_t my_pid;

	/* Récupère le PID du processus courant */
    my_pid = getpid();
	/* Affiche le PID */
    printf("%u\n", my_pid);
	/* Fin normale du programme */
    return (0);
}

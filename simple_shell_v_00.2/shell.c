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
	/* Taille du buffer géré par getline */
	size_t len = 0;
	/* Nombre de caractères lus par getline (ou -1 si EOF/erreur) */
	ssize_t read;
	/* Pointeur vers la ligne lue (allouée/agrandie par getline) */
	char *lineptr = NULL;

	while (1)
	{
		/* Affiche le prompt */
		write(1, "#cisfun$ ", 9);
		/* Lit une ligne depuis stdin (getline via read_command) */
		read = read_command(&lineptr, &len);
		/* Si EOF/erreur: on sort proprement */
		if (read == -1)
		{
			/* Saut de ligne pour revenir au prompt du terminal */
			write(1, "\n", 1);
			break;
		}
		/* Supprime le '\n' final pour avoir une chaîne "propre" */
		delete_newline(lineptr, read);
		/* Ignore les lignes vides (juste "Entrée") */
		if (is_empty_line(lineptr))
			continue;
		/* Lance l'exécution de la commande (sans arguments) */
		execute_command(lineptr);
	}
	/* Libère le buffer de getline */
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
	/* Stocke le résultat de getline */
	ssize_t read;

	/* Lit une ligne complète */
	read = getline(lineptr, len, stdin);
	/* Retourne le nombre de caractères lus ou -1 */
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
	/* Sécurité: si pointeur NULL, rien à faire */
	if (lineptr == NULL)
		return;
	/* Si la ligne se termine par '\n', on le remplace par '\0' */
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
	/* Ligne inexistante => considérée vide */
	if (lineptr == NULL)
		return (1);
	/* Ligne vide => considérée vide */
	else if (lineptr[0] == '\0')
		return (1);
	/* Sinon, il y a du contenu */
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
	/* Tableau argv minimal: argv[0]=commande, argv[1]=NULL */
	char *argv_exec[2];
	/* Statut de fin du process enfant */
	int status;
	pid_t pid;

	/* Termine le tableau argv par NULL */
	argv_exec[1] = NULL;
	/* Donne la commande à execve comme argv[0] */
	argv_exec[0] = cmd;
	/* Crée un process enfant */
	pid = fork();

	/* Gestion d'erreur fork */
	if (pid == -1)
	{
		/* Affiche l'erreur système */
		perror("fork");
		return (1);
	}
	/* Code exécuté dans l'enfant */
	if (pid == 0)
	{
		/* Remplace le process enfant par la commande */
		execve(cmd, argv_exec, environ);
		/* Si on arrive la c'est execve à échoué, on affiche l'erreur */
		perror(cmd);
		/* Code standard "command not found / cannot execute" */
		exit(127);
	}
	/* Code exécuté dans le parent */
	if (pid > 0)
	{
		/* Attend la fin de l'enfant */
		if (waitpid(pid, &status, 0) == -1)
		{
			/* Affiche l'erreur système */
			perror("waitpid");
			return (1);
		}
		/* Si l'enfant ne s'est pas terminé normalement => erreur */
		if (!WIFEXITED(status))
			return (1);
		/* Si l'enfant termine avec un code non nul => erreur */
		if (WEXITSTATUS(status) != 0)
			return (1);
	}
	return (0);
}

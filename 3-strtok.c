#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

char **empty_array(void);

/**
 * split_string - split a string into words and return a NULL-terminated array
 * @string: input string to split (words are separated by spaces/tabs/newlines)
 * Return: pointer to a NULL-terminated array of words, or NULL on failure
 */

char **split_string (char *string)
{
	char *str1, *str2, *token;
	const char *separator; 
	char **tokens;
	size_t count, i, j;

	/* Délimiteurs: espace, tab, retour ligne */
	separator = " \t\n"; 

	/* Erreur: entrée NULL */
	if (string == NULL)
		return (NULL);
	
	/* Passage 1 (comptage): On duplique la chaîne car strtok() modifie le buffer */
	str1= strdup (string);
	if (str1 == NULL)
		return (NULL);
	
	/* Cas chaîne vide => tableau vide (pas une erreur) */
	if (*str1 == '\0')
	{
		free(str1);
		return empty_array();
	}

	/* Comptage des mots: token pointe dans str1 (buffer modifié). On incrémente count par token */
	count = 0;
	token = strtok (str1, separator);
	while (token != NULL)
	{
		count ++;
		token = strtok(NULL, separator);
	}

	/* Cas: uniquement des séparateurs => 0 token - On retourne un tableau vide (pas NULL) */
	if (count == 0)
	{
		free(str1);
		return empty_array();
	}
	free (str1);

	/* Passage 2 (remplissage): Nouvelle copie car strtok() a consommé modifié la première */
	str2= strdup (string);
	if (str2 == NULL)
		return (NULL);

	/* Allocation du tableau final: count mots + 1 case pour le NULL terminal */	
	tokens = malloc ((count + 1) * sizeof(char *));
	if (tokens == NULL)
	{
		free (str2);
		return (NULL);
	}

	/* Remplissage: Chaque token est dupliqué avec strdup() */
	i = 0;
	token = strtok(str2, separator);
	while (token != NULL)
	{
		tokens[i] = strdup(token);
		if (tokens[i] == NULL)
		{
			for (j = 0; j < i; j++)
				free(tokens[j]);
			free (tokens);
			free (str2);
			return (NULL);
		}
		i++;
		token = strtok(NULL, separator);
	}
	/* ajout du marqueur de fin du tableau */
	tokens[i] = NULL;
	free (str2);
	return (tokens);
}


/**
 * empty_array - allocate and return an empty NULL-terminated array of strings
 * Return: pointer to a NULL-terminated array on success, or NULL on failure
 */

char **empty_array(void)
{
	char **array;
	array = malloc(sizeof(char *));
	if (array == NULL)
		return (NULL);
	array[0] = NULL;
	return (array);
}
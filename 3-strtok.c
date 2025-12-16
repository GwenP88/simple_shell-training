#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

char **empty_array(void);

char **split_string (char *string)
{
	char *str1, *str2, *token;
	const char *separator; 
	char **tokens;
	size_t count, i, j;

	separator = " \t\n";

	if (string == NULL)
		return (NULL);
	
	str1= strdup (string);
	if (str1 == NULL)
		return (NULL);
	
	if (*str1 == '\0')
	{
		free(str1);
		return empty_array();
	}

	count = 0;
	token = strtok (str1, separator);
	while (token != NULL)
	{
		count ++;
		token = strtok(NULL, separator);
	}

	if (count == 0)
	{
		free(str1);
		return empty_array();
	}
	free (str1);

	str2= strdup (string);
	if (str2 == NULL)
		return (NULL);

	tokens = malloc ((count + 1) * sizeof(char *));
	if (tokens == NULL)
	{
		free (str2);
		return (NULL);
	}

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
	tokens[i] = NULL;
	free (str2);
	return (tokens);
}

char **empty_array(void)
{
	char **array;
	array = malloc(sizeof(char *));
	if (array == NULL)
		return (NULL);
	array[0] = NULL;
	return (array);
}
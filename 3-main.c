#include <stdio.h>
#include <stdlib.h>

/* Prototype de ta fonction */
char **split_string(char *string);

static void free_words(char **words)
{
	size_t i;

	if (words == NULL)
		return;

	for (i = 0; words[i] != NULL; i++)
		free(words[i]);
	free(words);
}

static void run_test(char *label, char *input)
{
	char **words;
	size_t i;

	printf("\n=== %s ===\n", label);
	printf("Input: \"%s\"\n", input);

	words = split_string(input);
	if (words == NULL)
	{
		printf("Result: NULL\n");
		return;
	}

	for (i = 0; words[i] != NULL; i++)
		printf("word[%lu] = \"%s\"\n", (unsigned long)i, words[i]);

	printf("Total words: %lu\n", (unsigned long)i);
	free_words(words);
}

int main(void)
{
	run_test("Test 1 - normal mixed whitespace", "  Bonjour   le\tmonde\nC  ");
	run_test("Test 2 - empty string", "");
	run_test("Test 3 - only separators", "   \t\n  \t");
	run_test("Test 4 - single word", "Hello");
	run_test("Test 5 - leading separators", "   Hello");
	run_test("Test 6 - trailing separators", "Hello   \t\n");
	run_test("Test 7 - multiple words", "un deux   trois\tquatre\ncinq");
	run_test("Test 8 - no split (no separators)", "ABCDEF");
	run_test("Test 9 - punctuation kept", "salut, ça va?\toui!");

	/* Pour vérifier le contrat NULL */
	run_test("Test 10 - NULL input (should return NULL)", NULL);

	return (0);
}



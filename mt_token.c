#include "mutashell.h"
/**
 * _strsplit - a function for seperating strings
 * @phrase: points to whatever is received in getline
 * @divider: divides the array of string into smaller units
 * Return: whatever is created is the return
*/
char *_strsplit(char *phrase, char *divider)
{
	int n;
	static char *word;
	char *newWord;

	if (phrase != NULL)
		word = phrase;
	for (; *word != '\0'; word++)
	{
		for (n = 0; divider[n] != '\0'; n++)
		{
			if (*word == divider[n])
			break;
		}
		if (divider[n] == '\0')
			break;
	}
	newWord = word;
	if (*newWord == '\0')
		return (NULL);
	for (; *word != '\0'; word++)
	{
		for (n = 0; divider[n] != '\0'; n++)
		{
			if (*word == divider[n])
			{
				*word = '\0';
				word++;
				return (newWord);
			}
		}
	}
	return (newWord);
}		

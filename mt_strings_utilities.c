#include "mutashell.h"

char *_strlink(char *str1, char *str2);
/**
 * _strlen - length of the string
 * @str: string to be counted
 *
 * Return: str_count upon success
 */

int _strlen(char *str)
{
	int str_count;

	if (str == NULL)
	{
		return (0);
	}

	str_count = 0;
	for (; str[str_count] != '\0'; str_count++)
	{

	}
	return (str_count);
}


/**
 * _strclone - creates a duplicate of a string
 * @str: String to be duplicated
 *
 * Return: array of duplicated string
 */
char *_strclone(char *str)
{
	char *clonedStr;
	int len, index;

	if (str == NULL)
	{
		return (NULL);
	}

	len = _strlen(str) + 1;

	clonedStr = malloc(sizeof(char) * len);

	if (clonedStr == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (index = 0; index < len ; index++)
	{
		clonedStr[index] = str[index];
	}

	return (clonedStr);
}

/**
 * _strcomp - Function that compares two strings
 * @str1: string to be compared with.
 * @str2: String to be compared to.
 * @x: number of characters to be compared, 0 if infinite
 *
 * Return: 1 if the strings are equals, 0 if the strings are different
 */
int _strcomp(char *str1, char *str2, int x)
{
	int loops, s1, s2;

	s1 = _strlen(str1),  s2 = _strlen(str2);

	if (str1 == NULL && str2 == NULL)
	{
		return (1);
	}

	if (str1 == NULL || str2 == NULL)
	{
		return (0);
	}
	if (x == 0) /* infinite longitud */
	{
		if (s1 != s2)
			return (0);
		for (loops = 0; str1[loops]; loops++)
		{
			if (str1[loops] != str2[loops])
				return (0);
		}
		return (1);
	}
	else /* if there is a number of chars to be compared */
	{
		for (loops = 0; loops < x; loops++)
		{
			if (str1[loops] != str2[loops])
				return (0);
		}
		return (1);
	}
}

/**
 * _strlink - joins two strings together.
 * @str1: String to be joined with.
 * @str2: String to be joined to.
 *
 * Return: an array of the joined string.
 */
char *_strlink(char *str1, char *str2)
{
	char *linkedS;
	int len1, len2;

	len1 = 0, len2 = 0;

	if (str1 == NULL)
	{
		str1 = "";
	}
	len1 = _strlen(str1);

	if (str2 == NULL)
	{
		str2 = "";
	}
	len2 = _strlen(str2);

	linkedS = malloc(sizeof(char) * (len1 + len2 + 1));
	if (linkedS == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* copy of string1 */
	for (len1 = 0; str1[len1] != '\0'; len1++)
	{
		linkedS[len1] = str1[len1];
	}
	free(str1);

	/* copy of string2 */
	for (len2 = 0; str2[len2] != '\0'; len2++)
	{
		linkedS[len1] = str2[len2];
		len1++;
	}

	linkedS[len1] = '\0';
	return (linkedS);
}


/**
 * _revstr - reverses a string.
 *
 * @str: string to be reversed.
 * Return: Nothing.
 */
void _revstr(char *str)
{

	int ind, len = _strlen(str) - 1;
	char temp;
ind = 0;

	if (str == NULL)
	{
		return;
	}
	while (ind < len)
	{
		temp = str[ind];
		str[ind++] = str[len];
		str[len--] = temp;
	}
}

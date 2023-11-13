#include "mutashell.h"

/**
 * integerToString - converts a number to a string.
 * @numeral: number to be converten in an string.
 * @content: buffer to save the number as string.
 * @bottom: base to convert number
 *
 * Return: is returns a void
 */
void integerToString(long numeral, char *content, int bottom)
{
	int listing = 0, ngtive = 0;
	long quota = numeral;
	char symbols[] = {"0123456789abcdef"};

	if (quota == 0)
		content[listing++] = '0';

	if (content[0] == '-')
		ngtive = 1;

	while (quota)
	{
		if (quota < 0)
			content[listing++] = symbols[-(quota % bottom)];
		else
			content[listing++] = symbols[quota % bottom];
		quota /= bottom;
	}
	if (ngtive)
		content[listing++] = '-';

	content[listing] = '\0';
	_revstr(content);
}


/**
 * _atoi - convert a string to an integer.
 *
 * @z: pointer to str origen.
 * Return: an integer or (0)
 */
int _atoi(char *z)
{
	int mark = 1;
	unsigned int numeral = 0;
	/*1- analisys sign*/
	while (!('0' <= *z && *z <= '9') && *z != '\0')
	{
		if (*z == '-')
			mark *= -1;
		if (*z == '+')
			mark *= +1;
		z++;
	}

	/*2 - extract the number */
	while ('0' <= *z && *z <= '9' && *z != '\0')
	{

		numeral = (numeral * 10) + (*z - '0');
		z++;
	}
	return (numeral * mark);
}

/**
 * eval_chars - count the coincidences of character in string.
 *
 * @content: pointer to str origen.
 * @code: string with  chars to be counted
 * Return: int of string or 0.
 */
int eval_chars(char *content, char *code)
{
	int m = 0, calcu = 0;

	for (; content[m]; m++)
	{
		if (content[m] == code[0])
			calcu++;
	}
	return (calcu);
}

#include "mutaShell.h"

/**
 * _mt_tok - this function splits into tokens
 * @rd: it points to whatever is received
 * @crt: the criteria for spliting
 * Return: returns a pointer
 * */

char *_mt_tok(char *rd, char *crt)
{
	int z;
	static char *box;
	char *repbox;

	if (rd != NULL)
		box = rd;
	for (; *box != '\0'; box++)
	{
		for (z = 0; crt[z] != '\0'; z++)
		{
			if (*box == crt[z]
			break;
		}
		if (crt[z] == '\0')
			break;
	}
	repbox = box;
	if (*repbox == '\0')
		return (NULL);
	for (; *box != '\0'; box++)
	{
		for (z =0; crt[z] != '\0'; z++)
		{
			if (*box == crt[z])
			{
				*box = '\0';
				box++;
				return (repbox);
			}
		}
	}
	return (repbox);
}

			

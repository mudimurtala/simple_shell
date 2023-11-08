#include "mutaShell.h"
/**
 * division - a function that tokenizes
 * @mt: this represents the pointer
 * Return: returns void
 */
void divition(d_of *mt)
{
	char *seperator = " \t";
	int q, r, calc = 2, spread;

	spread = str_lenght(mt->input_line);
	if (spread)
	{
		if (mt->input_line[spread - 1] == '\n')
			mt->input_line[spread - 1] = '\0';
	}

	for (q = 0; mt->input_line[q]; q++)
	{
		for (r = 0; seperator[r]; r++)
		{
			if (mt->input_line[q] == seperator[r])
				calc++;
		}
	}

	mt->tokens = malloc(calc * sizeof(char *));
	if (mt->tokens == NULL)
	{
		perror(mt->program_name);
		exit(errno);
	}
	q = 0;
	mt->tokens[q] = str_duplicate(_mt_tok(mt->input_line, seperator));
	mt->command_name = str_duplicate(mt->tokens[0]);
	while (mt->tokens[q++])
	{
		mt->tokens[q] = str_duplicate(_mt_tok(NULL, seperator));
	}
}

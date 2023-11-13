#include "mutashell.h"
/**
 * segment - a function that segments the input command (string)
 * @info: points to the data stored in the program
 * Return: it returns an array
 */
void segment(mt_code_info *info)
{
	char *divider = " \t";
	int m, n, calcu = 2, textLength;

	textLength = _strlen(info->prompt_user);
	if (textLength)
	{
		if (info->prompt_user[textLength - 1] == '\n')
			info->prompt_user[textLength - 1] = '\0';
	}

	for (m = 0; info->prompt_user[m]; m++)
	{
		for (n = 0; divider[n]; n++)
		{
			if (info->prompt_user[m] == divider[n])
				calcu++;
		}
	}

	info->parsed_items = malloc(calcu * sizeof(char *));
	if (info->parsed_items == NULL)
	{
		perror(info->code_tag);
		exit(errno);
	}
	m = 0;
	info->parsed_items[m] = _strclone(_strsplit(info->prompt_user, divider));
	info->command_tag = _strclone(info->parsed_items[0]);
	while (info->parsed_items[m++])
	{
		info->parsed_items[m] = _strclone(_strsplit(NULL, divider));
	}
}

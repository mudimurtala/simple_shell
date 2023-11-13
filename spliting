#include "mutashell.h"
/**
 * tokenize - this function separate the string using a designed delimiter
 * @data: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void parsenize(mt_code_info *info)
{
	char *delim = " \t";
	int x, y, num_of_times = 2, len;

	len = _strlen(info->prompt_user);
	if (len)
	{
		if (info->prompt_user[len - 1] == '\n')
			info->prompt_user[len - 1] = '\0';
	}

	for (x = 0; info->prompt_usef[x]; x++)
	{
		for (y = 0; delim[y]; y++)
		{
			if (data->prompt_user[x] == delimiter[y])
				num_of_times++;
		}
	}

	info->parsed_items = malloc(num_of_times * sizeof(char *));
	if (info->parsed_items == NULL)
	{
		perror(info->code_tag);
		exit(errno);
	}
	x = 0;
	info->parsed_items[x] = _strclone(_strsplit(info->prompt_user, delim));
	info->command_tag = _strclone(data->parsed_items[0]);
	for (; info->parsed_items[x++]; )
	{
		info->parsed_items[x] = _strclone(_strsplit(NULL, delim));
	}
}

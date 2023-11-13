#include "mutashell.h"

/**
 * deallocate_data_space - free all field of the data
 * @info: struct of the program's data
 * Return: Nothing
 */
void deallocate_data_space(mt_code_info *info)
{
	if (info->fd != 0)
	{
		if (close(info->fd))
		{
			perror(info->code_tag);
		}	}
	deallocate_repeated_data(info);
	deallocate_pointer_elements(info->environ);
	deallocate_pointer_elements(info->mt_listAlias);
}


/**
 * deallocate_pointer_elements - frees each pointer of an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: it returns void
 */
void deallocate_pointer_elements(char **array)
{
	int ind;

	if (array != NULL)
	{
		ind = 0;
			while (array[ind])
			{ 
				free(array[ind]);
				ind++;
			}
		free(array);
		array = NULL;
	}
}




/**
 * deallocate)repeated_data - free the fields needed each loop
 * @info: struct of the program's data
 * Return: Nothing
 */
void deallocate_repeated_data(mt_code_info *info)
{
	if (info->parsed_items)
	{
		deallocate_pointer_elements(info->parsed_items);
	}
	if (info->prompt_user)
	{
		free(info->prompt_user);
	}
	if (info->command_tag)
	{
		free(info->command_tag);
	}
	info->prompt_user = NULL;
	info->command_tag = NULL;
	info->parsed_items = NULL;
}

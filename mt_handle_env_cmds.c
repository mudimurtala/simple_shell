#include "mutashell.h"

/**
 * handle_shell_env - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int handle_shell_env(mt_code_info *info)
{
	int ind;
	char env_var_name_buffer[50] = {'\0'};
	char *str_dup = NULL;

	/* if not arguments */
	if (info->parsed_items[1] == NULL)
		print_environ(info);
	else
	{
		for (ind = 0; info->parsed_items[1][ind]; ind++)
		{/* checks if exists a char = */
			if (info->parsed_items[1][ind] == '=')
			{/* checks if exists a var with the same name and change its value*/
			/* temporally */
				str_dup = _strclone(env_get_key(env_var_name_buffer, info));
				if (str_dup != NULL)
					env_set_key(env_var_name_buffer, info->parsed_items[1] + ind + 1, info);

				/* print the environ */
				print_environ(info);
				if (env_get_key(env_var_name_buffer, info) == NULL)
				{/* print the variable if it does not exist in the environ */
					_print(info->parsed_items[1]);
					_print("\n");
				}
				else
				{/* returns the old value of the var*/
					env_set_key(env_var_name_buffer, str_dup, info);
					free(str_dup);
				}
				return (0);
			}
			env_var_name_buffer[ind] = info->parsed_items[1][ind];
		}
		errno = 2;
		perror(info->command_tag);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - ..
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_env_var(mt_code_info *info)
{
	/* validate args */
	if (info->parsed_items[1] == NULL || info->parsed_items[2] == NULL)
{
		return (0);
}
	if (info->parsed_items[3] != NULL)
	{
		errno = E2BIG;
		perror(info->command_tag);
		return (5);
	}

	env_set_key(info->parsed_items[1], info->parsed_items[2], info);

	return (0);
}

/**
 * builtin_unset_env - ..
 * @data: struct for the program's data'
 * Return: ..
 */
int unset_env_var(mt_code_info *info)
{
	/* validate args */
	if (info->parsed_items[1] == NULL)
{
		return (0);
}
	if (info->parsed_items[2] != NULL)
	{
		errno = E2BIG;
		perror(info->command_tag);
		return (5);
	}
	env_remove_key(info->parsed_items[1], info);

	return (0);
}

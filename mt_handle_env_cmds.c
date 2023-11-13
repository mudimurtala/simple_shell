#include "mutashell.h"

/**
 * handle_shell_env - shows the environment where the shell runs
 * @info: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int handle_shell_env(mt_code_info *info)
{
	int ind;
	char env_var_name_buffer[50] = {'\0'};
	char *str_dup = NULL;

	/* if not arguments */
	if (info->parsed_items[1] == NULL)
		display_environment(info);
	else
	{
		for (ind = 0; info->parsed_items[1][ind]; ind++)
		{/* checks if exists a char = */
			if (info->parsed_items[1][ind] == '=')
			{/* checks if exists a var with the same name and change its value*/
			/* temporally */
				str_dup = _strclone(obtain_environment_secret(env_var_name_buffer, info));
				if (str_dup != NULL)
					obtain_environment_secret(env_var_name_buffer, info->parsed_items[1] + ind + 1, info);

				/* print the environ */
				display_environment(info);
				if (obtain_environment_secret(env_var_name_buffer, info) == NULL)
				{/* print the variable if it does not exist in the environ */
					_display(info->parsed_items[1]);
					_display("\n");
				}
				else
				{/* returns the old value of the var*/
					obtain_environment_secret(env_var_name_buffer, str_dup, info);
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
 * set_env_var - ..
 * @info: struct for the program's data
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

	obtain_environment_secret(info->parsed_items[1], info->parsed_items[2], info);

	return (0);
}

/**
 * unset_env_var - ..
 * @info: struct for the program's data'
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
	clear_environment_secret(info->parsed_items[1], info);

	return (0);
}

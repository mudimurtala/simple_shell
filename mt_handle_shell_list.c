#include "mutashell.h"

/**
 * handle_shell_list - executing a built-in command after searching for it
 * @info: represents the data the program stores
 * Return: if there is a match it returns what is executed, else
 * returns -1.
 **/
int handle_shell_list(mt_code_info *info)
{
	int navigator;
	mt_internalCommands commands[] = {
		{"exit", handle_shell_exit},
		{"help", handle_shell_help},
		{"cd", handle_shell_cd},
		{"alias", handle_shell_alias},
		{"env", handle_shell_env},
		{"setenv", set_env_var},
		{"unsetenv", unset_env_var},
		{NULL, NULL}
	};

	/* navigating the structure to access it's contents*/
	for (navigator = 0; commands[navigator].mt_internalCommand
			!= NULL; navigator++)
		/* comparing what is typed with the built_in */
		if (_strcomp(commands[navigator].mt_internalCommand, info->command_tag, 0))
		{
			/* here, the function is executed, and it's return value is returned*/
			return (commands[navigator].fn(info));
		}

	/* Return (-1) if the typed command did not match any builtin */

return (-1);
}

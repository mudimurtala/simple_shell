#include "mutashell.h"


/**
 * main - this is the entry point for any C program
 * @argc: represents the numbers of items received from the command prompt
 * @argv: represents what is being received
 * @env: this represents the environment variable
 * Return: on success (0) is returned
 */
int main(int argc, char *argv[], char *env[])
{
	mt_code_info data_struct = {NULL}, *info = &data_struct;
	char *userQuery = "";

	load_data(info, argc, argv, env);

	signal(SIGINT, terminate_gracefully);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
	/* We are in the terminal, interactive mode */
		errno = 2;/*???????*/
		userQuery = USER_MESSAGE;
	}
	errno = 0;
	persevere(userQuery, info);
	return (0);
}

/**
 * terminate_gracefully - a function that displays the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @IGNORED_PARAM: an option of the prototype
 */
void terminate_gracefully(int opr IGNORED_PARAM)
{
	_display("\n");
	_display(USER_MESSAGE);
}

/**
 * load_data - load and initialize the data of the program
 * @info: this points to the structure
 * @argv: represents the parameter passed
 * @env: this is the environment of the running program
 * @argc: represents what is received from the user
 */
void load_data(mt_code_info *info, int argc, char *argv[], char **environ)
{
	int m = 0;

	info->code_tag = argv[0];
	info->prompt_user = NULL;
	info->command_tag = NULL;
	info->command_count = 0;
	/* the (fd) file descriptor is defined here */
	if (argc == 1)
		info->fd = STDIN_FILENO;
	else
	{
		info->fd = open(argv[1], O_RDONLY);
		if (info->fd == -1)
		{
			_displayerror(info->code_tag);
			_displayerror(": 0: Can't open ");
			_displayerror(argv[1]);
			_displayerror("\n");
			exit(127);
		}
	}
	info->parsed_items = NULL;
	info->environ = malloc(sizeof(char *) * 50);
	if (environ)
	{
		for (; environ[m]; m++)
		{
			info->environ[m] = _strclone(environ[m]);
		}
	}
	info->environ[m] = NULL;
	environ = info->environ;

	info->mt_listAlias = malloc(sizeof(char *) * 20);
	for (m = 0; m < 20; m++)
	{
		info->mt_listAlias[m] = NULL;
	}
}
/**
 * persevere - a function, a loop that continue to show the prompt
 * @userQuery: this represent the prompt itself
 * @info: points to the strings
 */
void persevere(char *userQuery, mt_code_info *info)
{
	int error_code = 0, len_str = 0;

	while (++(info->command_count))
	{
		_display(userQuery);
		error_code = len_str = _accessline(info);

		if (error_code == EOF)
		{
			deallocate_data_space(info);
			exit(errno); /* if EOF is the fisrt Char of string, exit*/
		}
		if (len_str >= 1)
		{
			mt_resolveAlias(info);
			resolve_vars(info);
			segment(info);
			if (info->parsed_items[0])
			{
			/* if a text is given to prompt, execute */
				error_code = mt_execute_action(info);
				if (error_code != 0)
					showError(error_code, info);
			}
			deallocate_repeated_data(info);
		}
	}
}

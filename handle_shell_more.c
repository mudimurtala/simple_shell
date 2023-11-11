#include "mutashell.h"

/**
 * handle_shell_exit - a function that exit the program or session
 * @info: represents the data for the program
 * Return: it returns (0) on success
 */
int handle_shell_exit(mt_code_info *info)
{
	int m;

	if (info->passed_items[1] != NULL)
	{
	/*if exists arg for exit, check if is a number*/
		for (m = 0; info->passed_items[1][m]; m++)
			if ((info->passed_items[1][m] < '0' || info->passed_items[1][m] > '9')
				&& info->passed_items[1][m] != '+')
			{
			/* but if it is not a number, this happens */
				errno = 2;
				return (2);
			}
		errno = _atoi(info->passed_items[1]);
	}
	deallocate_data_space(info);
	exit(errno);
}

/**
 * handle_shell_cd - a function that is tasked with changing a current dir
 * @info: represents the data stored inside the program
 * Return: if success it returns (0)
 */
int handle_shell_cd(mt_code_info *info)
{
	char *personalDir = obtain_environment_secret("HOME", info), *dirFormer = NULL;
	char formerDir[128] = {0};
	int error_code = 0;

	if (info->passed_items[1])
	{
		if (_strcomp(info->passed_items[1], "-", 0))
		{
			dirFormer = obtain_environment_secret("OLDPWD", info);
			if (dirFormer)
				error_code = define_curr_dir(info, dirFormer);
			_display(obtain_environment_secret("PWD", info));
			_display("\n");

			return (error_code);
		}
		else
		{
			return (define_curr_dir(info, info->passed_items[1]));
		}
	}
	else
	{
		if (!personalDir)
			personalDir = getcwd(formerDir, 128);

		return (define_curr_dir(info, personalDir));
	}
	return (0);
}

/**
 * define_curr_dir - a function that sets the working directory
 * @info: struct for the program's data
 * @createdDir: this represents the working directory
 * Return: if success it returns (0), or other number if declared in the arguments
 */
int define_curr_dir(mt_code_info *info, char *createdDir)
{
	char formerDir[128] = {0};
	int err_code = 0;

	getcwd(formerDir, 128);

	if (!_strcomp(formerDir, createdDir, 0))
	{
		err_code = chdir(createdDir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		config_environment_secret("PWD", createdDir, info);
	}
	config_environment_secret("OLDPWD", formerDir, info);
	return (0);
}

/**
 * handle_shell_help - displays the space where the shell is executed
 * @info: represents the data stored in the program
 * Return: it returns (0) on success, or other numbers if declared in the arguments
 */
int handle_shell_help(mt_code_info *info)
{
	int m, textLength = 0;
	char *msgList[6] = {NULL};

	msgList[0] = HELP_MSG;

	/* checking and proofing the arguments */
	if (info->passed_items[1] == NULL)
	{
		_display(msgList[0] + 6);
		return (1);
	}
	if (info->passed_items[2] != NULL)
	{
		errno = E2BIG;
		perror(info->command_tag);
		return (5);
	}
	msgList[1] = HELP_EXIT_MSG;
	msgList[2] = HELP_ENV_MSG;
	msgList[3] = HELP_SETENV_MSG;
	msgList[4] = HELP_UNSETENV_MSG;
	msgList[5] = HELP_CD_MSG;

	for (m = 0; msgList[m]; m++)
	{
		textLength = _strlen(info->passed_items[1]);
		if (_strcomp(info->passed_items[1], msgList[m], textLength))
		{
			_display(msgList[m] + textLength + 1);
			return (1);
		}
	}
	/* error is printed or (-1) is returned if there is no match */
	errno = EINVAL;
	perror(info->command_tag);
	return (0);
}

/**
 * handle_shell_alias - a function that manages aliases
 * @info: this represents the struct for the program's data
 * Return: (0) is returned if success
 */
int handle_shell_alias(mt_code_info *info)
{
	int m = 0;

	/* the environments are printed if arguments are not found */
	if (info->passed_items[1] == NULL)
		return (mt_manageAlias(info, NULL));

	while (info->passed_items[++m])
	{
	/* printing environment variables if arguments are found */
		if (eval_chars(info->passed_items[m], "="))
			mt_positionAlias(info->passed_items[m], info);
		else
			mt_manageAlias(info, info->passed_items[m]);
	}

	return (0);
}

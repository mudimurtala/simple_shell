#include "mutashell.h"
/**
 * mt_execute_action - a function for executing commands.
 * @info: this points to the data the program contains.
 * Return: (0) on success and -1 on error.
 */
int mt_execute_action(mt_code_info *info)
{
	int response = 0, fetch_status;
	pid_t processID;

	/* to check if the program is present in built-ins */
	response = handle_shell_list(info);
	if (response != -1) /* if built-ins stores the program being searched for */
		return (response);

	/* checking the system for the program */
	response = lookup_program(info);
	if (response)
	{
	/* if the program is absent in the file system */
		return (response);
	}
	else
	{
	/* but if the program is present in the file system */
		processID = fork(); /* a child process will be created here */
		if (processID == -1)
		{
	/* let say failure occur when the fork() is called */
			perror(info->command_tag);
			exit(EXIT_FAILURE);
		}
		if (processID == 0)
		{
	/* Here I am the child process, the program is executed by me */
			response = execve(info->parsed_items[0], info->parsed_items, info->environ);
			if (response == -1) /* let say execve resulted to an error */
				perror(info->command_tag), exit(EXIT_FAILURE);
		}
		else
		{
	/* Here I am the Parent, checking my child's exit status */
			wait(&fetch_status);
			if (WIFEXITED(fetch_status))
				errno = WEXITSTATUS(fetch_status);
			else if (WIFSIGNALED(fetch_status))
				errno = 128 + WTERMSIG(fetch_status);
		}
	}
	return (0);
}

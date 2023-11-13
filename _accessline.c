#include "mutashell.h"

/**
 * _accessline - a function that reads users input
 * @info: the stuct that stores the data
 * Return: number of bytes
 */
int _accessline(mt_code_info *info)
{
	char storage[BUFFER_SIZE] = {'\0'};
	static char *handle_array_inputs[10] = {NULL};
	static char handle_array_operators[10] = {'\0'};
	ssize_t data_received, m = 0;

	/* check if doesnot exist more commands in the array */
	/* and checks the logical operators */
	if (!handle_array_inputs[0] || (handle_array_operators[0] == '&' &&
errno != 0) || (handle_array_operators[0] == '|' && errno == 0))
	{
		/*free the memory allocated in the array if it exists */
		for (m = 0; handle_array_inputs[m]; m++)
		{
			free(handle_array_inputs[m]);
			handle_array_inputs[m] = NULL;
		}

		/* read from the file descriptor int to buff */
		data_received = read(info->fd, &storage, BUFFER_SIZE - 1);
		if (data_received == 0)
			return (-1);

		/* split lines for \n or ; */
		m = 0;
		do {
			handle_array_inputs[m] = _strclone(_strsplit(m ? NULL : storage, "\n;"));
			/*checks and split for && and || operators*/
			m = inspect_logical_con(handle_array_inputs, m, handle_array_operators);
		} while (handle_array_inputs[m++]);
	}

	/*obtains the next command (command 0) and remove it for the array*/
	info->prompt_user = handle_array_inputs[0];
	for (m = 0; handle_array_inputs[m]; m++)
	{
		handle_array_inputs[m] = handle_array_inputs[m + 1];
		handle_array_operators[m] = handle_array_operators[m + 1];
	}

	return (_strlen(info->prompt_user));
}


/**
* inspect_logical_con - will handle logical operators && and ||
* @handle_array_inputs: array of the commands.
* @m: index in the array_commands to be checked
* @handle_array_operators: handle the array of the
* logical operators for each previous command
*
* Return: index of the last command in the handle_array_inputs.
*/
int inspect_logical_con(char *handle_array_inputs[],
int m, char handle_array_operators[])
{
	char *transient = NULL;
	int n;

	/* checks for the & char in the command line*/
	for (n = 0; handle_array_inputs[m] != NULL  && handle_array_inputs[m][n]; n++)
	{
		if (handle_array_inputs[m][n] == '&' && handle_array_inputs[m][n + 1] == '&')
		{
			/* split the line when chars && was found */
			transient = handle_array_inputs[m];
			handle_array_inputs[m][n] = '\0';
			handle_array_inputs[m] = _strclone(handle_array_inputs[m]);
			handle_array_inputs[m + 1] = _strclone(transient + n + 2);
			m++;
			handle_array_operators[m] = '&';
			free(transient);
			n = 0;
		}
		if (handle_array_inputs[m][n] == '|' && handle_array_inputs[m][n + 1] == '|')
		{
			/* split the line when chars || was found */
			transient = handle_array_inputs[m];
			handle_array_inputs[m][n] = '\0';
			handle_array_inputs[m] = _strclone(handle_array_inputs[m]);
			handle_array_inputs[m + 1] = _strclone(transient + n + 2);
			m++;
			handle_array_operators[m] = '|';
			free(transient);
			n = 0;
		}
	}
	return (m);
}

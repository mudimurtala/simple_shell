#include "mutashell.h"

/**
 * _display - display an array of chars to the stdio
 * @content: this points to the string
 * Return: it returns the number of the bytes typed
 * (-1) is returned on error and
 * errno is set appropriately.
 */
int _display(char *content)
{
	return (write(STDOUT_FILENO, content, _strlen(content)));
}
/**
 * _displayerror - a function that prints to the stamdaed error
 * @content: this points to the string typed
 * Return: it returns the number of bytes
 * but if error (-1) is returned
 * and errno is set appropriately.
 */
int _displayerror(char *content)
{
	return (write(STDERR_FILENO, content, _strlen(content)));
}

/**
 * showError - a function that display it's contents to the stdio
 * @info: a pointer to the program's data'
 * @errorcode: error code to print
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int showError(int errorcode, mt_code_info *info)
{
	char strNum[10] = {'\0'};

	integerToString((long) info->command_count, strNum, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_displayerror(info->code_tag);
		_displayerror(": ");
		_displayerror(strNum);
		_displayerror(": ");
		_displayerror(info->parsed_items[0]);
		if (errorcode == 2)
			_displayerror(": Illegal number: ");
		else
			_displayerror(": can't cd to ");
		_displayerror(info->parsed_items[1]);
		_displayerror("\n");
	}
	else if (errorcode == 127)
	{
		_displayerror(info->code_tag);
		_displayerror(": ");
		_displayerror(strNum);
		_displayerror(": ");
		_displayerror(info->command_tag);
		_displayerror(": not found\n");
	}
	else if (errorcode == 126)
	{
		_displayerror(info->code_tag);
		_displayerror(": ");
		_displayerror(strNum);
		_displayerror(": ");
		_displayerror(info->command_tag);
		_displayerror(": Permission denied\n");
	}
	return (0);
}
